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

  delete [] datas;

  datas = new Data[MAX_COUNT_FILE];
  
  new_token();
  record_partition_index = 0;
  manager->add_to_save(record_token);

  manager->save();

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
  save_config();

  record_partition_index++;
}

void Datas::save(bool all){
  // max ; min ; grow_rate ; decline_rate
  String name_file {"/" + String(record_token) + "-" + String(record_partition_index) + ".csv"};
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
  Serial.println("writed in file");
  //send();
}

void Datas::new_token(){
  for(size_t i{0}; i < token_length; i++){
    record_token[i] = (char)random(65,90);
  }
  if(sd_manager->exist(String(record_token) + "-0.csv")){
    new_token();
  }else{
    return;
  }
}
void Datas::send(int row){
  if(!connection->is_connected())
    return;
  connection->send("/data/" + String(record_token) + "/" + String(record_partition_index) + "/\n");
  if(row == -1){
    for(int i{0}; i < MAX_COUNT_FILE; i++ ){
      String to_send {""};
      to_send += String(i) + ";";
      to_send += String(datas[i].max) + ";";
      to_send += String(datas[i].min) + ";";
      to_send += String(datas[i].grow_rate) + ";";
      to_send += String(datas[i].decline_rate) + "\n";
      connection->send(&to_send);
      delay(1);
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
  connection->send("/end\n");    
}
void Datas::save_config(){
  String name = "/" + String(record_token) + ".conf";
  sd_manager->create_file(&name);
  sd_manager->load_file(&name);
  String content {String(record_partition_index+1)}; 
  sd_manager->write_file(&name, &content);
  sd_manager->close_file();
}
