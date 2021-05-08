#include "data.h"
#include <Arduino.h>
#include "configuration.h"

void Datas::add_data(Data data){
  datas[index] = data;
  Serial.println(String(index));
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
  String to_save {""};
  // max ; min ; grow_rate ; decline_rate
  for(int i{0}; i < MAX_COUNT_FILE; i++ ){
    to_save += String(datas[i].max) + ";";
    to_save += String(datas[i].min) + ";";
    to_save += String(datas[i].grow_rate) + ";";
    to_save += String(datas[i].decline_rate) + "/n";
  }
  String name_file {record_token + "-" + String(record_partition_index)};
  sd_manager->save_file(&to_save, &name_file);
}

void Data::clear(){
  max = 0;
  min = 0;
  grow_rate = 0;
  decline_rate = 0;
}

