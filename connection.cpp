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
  String response{"/none\n"};

  if (String("battery") == args[0]){
    response = "/reply/battery/80/end\n";

  }else if(String("start") == args[0]){
    response = "/reply/start/1/end\n";
    manager->start_record();

  }else if(String("stop") == args[0]){
    String token = manager->stop_recording();
    response = "/reply/stopped/" + token +"/end\n";

  }else if(String("send") == args[0]){
    if(args[1].length() >4){
      manager->send(&args[1]);

    }else{
      response = "/reply/error/invalid token/end\n";
    }
   

  }
  send(response);


}

void Connection::loop(void){
  if (SerialBT.available()) {
    int b = SerialBT.read();

    line += (char)b;
    for(int i {0}; i < line.length(); i++){
      if(line[i] == '\n' ){
        EventHandler();
        manager->updated();
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
