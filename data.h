#ifndef _DATA_H_
#define _DATA_H_
#include "connection.h"
#include "configuration.h"
#include <Arduino.h>
#include "SDManager.h"
#include "manager.h"

class Data{
public:
  int max{0};
  int min{0};

  float grow_rate{0};
  float decline_rate{0};

  Data(short int min_val = 0, short int max_val = 0 , float grow_val = 0.0, float decline_val = 0.0){
    max = max_val;
    min = min_val;
    grow_rate = grow_val;
    decline_rate = decline_val;
  }
  ~Data(){
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
  void send_all(String token);
  void send(int row = -1);
  void clear(void);

  inline String get_token(){return record_token;}

private:
  String record_token;
  int record_partition_index{0};
  int record_partition_number{1};
  int index {0};
  String* list;

  Connection* connection {nullptr};
  void load();
  void new_token(void);
  void new_partition(void);
  void load_config(String token);
  void save_config(void);
};


#endif
