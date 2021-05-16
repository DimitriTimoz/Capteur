#include "connection.h"
#include <Arduino.h>

void Connection::init_connection(String name){
  SerialBT.begin(name); 

}

void Connection::loop(void){
  if (SerialBT.available()) {
    Serial.write(SerialBT.read());
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