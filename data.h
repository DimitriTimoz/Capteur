#ifndef _DATA_H_
#define _DATA_H_
#include "connection.h"
#include "configuration.h"
#include <Arduino.h>
#include "SDManager.h"
#include "manager.h"

class Data{
public:
  short int max{0};
  short int min{0};

  float grow_rate{0};
  float decline_rate{0};

  Data(short int min_val = 0, short int max_val = 0 , float grow_val = 0.0, float decline_val = 0.0){
    max = max_val;
    min = min_val;
    grow_rate = grow_val;
    decline_rate = decline_val;
  }
  
  void clear();
}; 

class Connection;
class Manager;
class Datas{
public:
  Data* datas {nullptr};
  SDManager* sd_manager {nullptr};
  Manager *manager {nullptr};
  Datas(SDManager* sd, Manager* manager_imported, Connection* con);
  ~Datas(){
    delete [] datas;
    delete sd_manager;
  }
  void add_data(Data data); 
  void save(bool all = true); 
  void load(char token[5], int partition);
  void send(int row = -1);
  void clear(void);

private:
  size_t token_length{5};
  char record_token[5];
  int record_partition_index{0};
  int index {0};
  String* list;

  Connection* connection {nullptr};

  void new_token(void);
  void new_partition(void);
  void load_config(char token[5]);
  void save_config(void);
};


#endif
