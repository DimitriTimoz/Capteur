
#ifndef _CONNECTION_H_
#define _CONNECTION_H_
#include <Arduino.h>
#include "BluetoothSerial.h"
class Connection{
public:
  inline bool is_connected(){ return connected;};
  bool send(String);
  void new_data(String);
  Connection(String name){
      SerialBT.begin("BikeSensor"); 
  }
private:
  bool connected{false};
  //create the bluetooth serial object
  BluetoothSerial SerialBT;  
};
#endif