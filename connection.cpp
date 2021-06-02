#include "connection.h"
#include <Arduino.h>
#include "manager.h"


void Connection::init_connection(String name){
  SerialBT.begin(name); 

}

void Connection::EventHandler(){
  String args[5];
  int count{0};
  int last{0};
  for(int i {0}; i < line.length(); i++){
    if(line[i] == '/' ){
      args[count] = line.substring(last, i);
      last = i + 1;
      count++;
    }
  }
  Serial.println(args[0]);
  String response{"/none\n"};
  for(auto c : args[0]){
    Serial.println(int(c));
  }
  if (String("battery") == args[0]){
    response = "/battery/80/end\n";

  }else if(String("start") == args[0]){
    response = "/start/1/end\n";
    manager->start_record();

  }else if(String("stop") == args[0]){
    response = "/stop/1/end\n";
    manager->stop_recording();

  }
  send(response);


}

void Connection::loop(void){
  if (SerialBT.available()) {
    int b = SerialBT.read();
    if(b == 10 || b == 13){
      return;
    }
    line += (char)b;

    for(int i {0}; i < line.length()-1; i++){
      if(line[i] == '\\' &&  line[i+1] == 'n'){
        Serial.println(line);
        EventHandler();
        line = "";
        return;
      }
    }
  }
}

void Connection::send(char* data, size_t length){
  for(int i{0}; i < length; i++){
    SerialBT.write(*(data + i));
  }
}

void Connection::send(String* data){
  for(int i{0}; i < data->length(); i++){
    uint8_t c = (*data)[i];
    SerialBT.write(c);
  }
}

void Connection::send(String data){
  for(int i{0}; i < data.length(); i++){
    SerialBT.write(data[i]);
  }
}