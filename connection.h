
#ifndef _CONNECTION_H_
#define _CONNECTION_H_
#include <Arduino.h>
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif


class Connection{
public:
  BluetoothSerial SerialBT;  
  inline bool is_connected(){ return connected;};
  bool send(String);
  void new_data(String);
  void init_connection(String);
private:
  bool connected{false};
  //create the bluetooth serial object
 
};
#endif