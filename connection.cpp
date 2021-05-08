#include "connection.h"
#include <Arduino.h>

void Connection::init_connection(String name){
  SerialBT.begin(name); 

}