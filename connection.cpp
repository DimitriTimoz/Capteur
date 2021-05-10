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