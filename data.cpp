#include "data.h"
#include <Arduino.h>
#include "configuration.h"
#include <ArduinoJson.h>

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
void Datas::add_data(Data data){
  datas[index] = data;
  Serial.println(index);
  index++;
  if(index > MAX_COUNT_FILE){
    index = 0;
    new_partition();
  }
}

void Datas::new_partition(){
  save();
  record_partition_index++;
}

void Datas::save(){
  // max ; min ; grow_rate ; decline_rate
  String name_file {"/" + String(record_token) + "-" + String(record_partition_index) + ".csv"};
  sd_manager->create_file(&name_file);
  sd_manager->load_file(&name_file, 'w');
  for(int i{0}; i < MAX_COUNT_FILE; i++ ){
    String to_save {""};
    to_save += String(datas[i].max) + ";";
    to_save += String(datas[i].min) + ";";
    to_save += String(datas[i].grow_rate) + ";";
    to_save += String(datas[i].decline_rate) + "\n";
    sd_manager->write_file(&name_file, &to_save, false);
  }
  sd_manager->close_file();

}

void Datas::new_token(){
  for(size_t i{0}; i < token_length; i++){
    record_token[i] = (char)random(65,122);
  }
  if(sd_manager->exist(String(record_token) + "-0.csv")){
    new_token();
  }else{
    return;
  }
}

void Datas::save_config(){
  
  String name_file {"/" + String(record_token) + ".conf"};
  sd_manager->create_file(&name_file);
  
}

