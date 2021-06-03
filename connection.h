
#ifndef _CONNECTION_H_
#define _CONNECTION_H_
#include <Arduino.h>
#include "manager.h"
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
class Manager;
class Connection{
public:
  inline bool is_connected(void){ return SerialBT.connected();};
  inline void add_components(Manager *manager_import){manager = manager_import;}
  void send(char* data, size_t length);
  void send(String* data);
  void send(String data);
  void new_data(String);
  void init_connection(String);
  void loop(void);

private:
  BluetoothSerial SerialBT;  
  bool connected{false};
  String line {""};
  void EventHandler(void);
  Manager *manager{nullptr};
 
};
#endif
