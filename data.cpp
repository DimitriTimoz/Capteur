#include "data.h"
#include <Arduino.h>
#include "configuration.h"
#include "SDManager.h"

/*
  DATA
*/


void Data::clear(){
  max = 0;
  min = 120;
  grow_rate = 0;
  decline_rate = 0;
}

/*
  DATAS
*/
void Datas::clear(void){
  for(int i{0}; i < MAX_COUNT_FILE; i++){
    datas[i].clear();
  }

  new_token();
  record_partition_index = 0;
  record_partition_number = 1;

}

Datas::Datas(SDManager* sd, Manager* manager_imported, Connection* con){
    datas = new Data[MAX_COUNT_FILE];
    sd_manager = sd;
    manager = manager_imported;
    connection = con;
    new_token();
    manager->add_to_save(record_token);
    manager->save();
  }
  
void Datas::add_data(Data data){
  datas[index] = data;
  index++;
  if(index > MAX_COUNT_FILE){
    new_partition();
    index = 0;
  }
}

void Datas::new_partition(){
  save();
  

  record_partition_index++;
  record_partition_number++;
}

void Datas::save(bool all){
  // max ; min ; grow_rate ; decline_rate
  String name_file {"/" + record_token + "-" + String(record_partition_index) + ".csv"};
  sd_manager->create_file(&name_file);
  sd_manager->load_file(&name_file, 'w');
  int max = (all) ? MAX_COUNT_FILE-1 : index-1;

  for(int i{0}; i <= max; i++ ){
    String to_save {""};
    to_save += String(i+1) + ";";
    to_save += String(datas[i].max) + ";";
    to_save += String(datas[i].min) + ";";
    to_save += String(datas[i].grow_rate) + ";";
    to_save += String(datas[i].decline_rate) + "\n";
    sd_manager->write_file(&name_file, &to_save, false);
  }

  sd_manager->close_file();
  save_config();
  Serial.println("writed in file");
}
void Datas::load(){
  String name_file {"/" + record_token + "-" + String(record_partition_index) + ".csv"};
  sd_manager->load_file(&name_file, 'r');
  int j{0}; 
  while (sd_manager->current_file.available()) {
    String buffer = sd_manager->current_file.readStringUntil('\n');
    String vals[5];
    int count {0};
    for(int i{0}; i < buffer.length(); i++){
      if(buffer[i] == ';'){
        count++;
        i++;
      }
      vals[count] += buffer[i];
    }
    Data data(vals[1].toInt(), vals[2].toInt(), vals[3].toInt(), vals[4].toInt());
    datas[j] = data;
    j++;
  }

  sd_manager->close_file();
 
}
void Datas::send_all(String token){
  manager->load();
  if(sd_manager->exist("/" + token + ".conf")){

    load_config(token);
    record_token = token;
    connection->send("/reply/send/"+ token + "/end\n");
    for(int i {0}; i < record_partition_number; i++){
      load();
      send();
      record_partition_index++;
    }
    connection->send("/reply/sended/"+ token + "/end\n");

  }else{
    connection->send("/reply/error/1/end\n");
  }
  
}

void Datas::new_token(){
  record_token = "";
  for(size_t i{0}; i < 10; i++){
    record_token += (char)random(65,90);
  }
  if(sd_manager->exist(record_token + "-0.csv")){
    new_token();
  }else{
    return;
  }
}
void Datas::send(int row){
  if(!connection->is_connected())
    return;
  if(row == -1){
    int max = (record_partition_index == record_partition_number-1)? index + 1 : MAX_COUNT_FILE;
    for(int i{0}; i < max; i++ ){
      String to_send {""};
      to_send += String(i + record_partition_index * MAX_COUNT_FILE) + ";";
      to_send += String(datas[i].max) + ";";
      to_send += String(datas[i].min) + ";";
      to_send += String(datas[i].grow_rate) + ";";
      to_send += String(datas[i].decline_rate) + "\n";
      connection->send(&to_send);
    }
  }else{
    String to_send {""};
    to_send += String(row) + ";";
    to_send += String(datas[row].max) + ";";
    to_send += String(datas[row].min) + ";";
    to_send += String(datas[row].grow_rate) + ";";
    to_send += String(datas[row].decline_rate) + "\n";
    connection->send(&to_send);
  }
}
void Datas::save_config(){
  String name = "/" + record_token + ".conf";
  sd_manager->create_file(&name);
  sd_manager->load_file(&name, 'w');
  String content {String(record_partition_number)+ "\n" + String(index)}; 
  sd_manager->write_file(&name, &content);
  sd_manager->close_file();
}

void Datas::load_config(String token){
  String name = "/" + token + ".conf";
  sd_manager->load_file(&name, 'r');
  String content = sd_manager->get_file_content_str();
  int pos = content.indexOf('\n');
  record_partition_number = content.substring(0, pos).toInt();
  index = content.substring(pos).toInt();
  sd_manager->close_file();
}

