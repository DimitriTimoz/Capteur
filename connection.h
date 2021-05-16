
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
  inline bool is_connected(void){ return false;};
  void send(char* data, size_t length);
  void send(String* data);
  void send(String data);
  void new_data(String);
  void init_connection(String);
  void loop(void);

private:
  bool connected{false};
  //create the bluetooth serial object
 
};
#endif