#include "manager.h"

#include <Arduino.h>
#include "SDManager.h"
#include "data.h"

#include "configuration.h"
#include "SDManager.h"

void Manager::add_to_save(const String name){
  String copy[length_to_send]; 
  for(int i{0}; i < length_to_send; i++){
    copy[i] = (*to_send)[i];
  }
  delete[] to_send;
  to_send = new String[++length_to_send];
  for(int i{0}; i < length_to_send-1; i++){
    (*to_send+i) = copy[i];
  }
  (*to_send + (length_to_send - 2)) = name;
}

void Manager::remove_to_save(const String name){
  String copy[length_to_send]; 
  for(int i{0}; i < length_to_send; i++){
    copy[i] = (*to_send)[i];
  }
  delete[] to_send;
  to_send = new String[--length_to_send];
  bool rmv {false};
  for(int i{0}; i < length_to_send; i++){
    if(copy[i] != name){
      int incrementation = (rmv) ? (1) : 0;
      (*to_send+(i - incrementation)) = copy[i];
    }else{
      rmv = true;
    }
  }
  (*to_send + (length_to_send - 2)) = name;
}

void Manager::save(){
  String name_file {"/config.conf"};
  sd_manager->create_file(&name_file);

  String content{length_to_send};
  content += "\n";
  for(int i{0}; i < length_to_send; i++){
    content += (*to_send)[i] + "\n";
  }
  sd_manager->write_file(&name_file, &content);

}

void Manager::load(){
  String name_file {"/config.conf"};
  String content{""};
  content = sd_manager->read_file(&name_file);
  String row{""};
  int c_row{0};
  for(int i{1}; i < content.length(); i++){
    if(content[i-1] == '\\' && content[i] == 'n'){
      if(c_row == 0){
        length_to_send = row.toInt();
        to_send = new String[length_to_send];
      }else{
        to_send[c_row-1] = row;
      }
      
      row = "";
      c_row++;
    }else{
      row += content[i-1];
    }
  }
}

void Manager::start_record(){
  recording = true;
  datas->clear();
}

bool Manager::is_recording(){
  return recording;  
}

void Manager::stop_recording(){
  recording = false;
  datas->save(false);
      Serial.println("saved (manager)");

  datas->clear();
    Serial.println("saved cleared");

}
