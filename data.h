#ifndef _DATA_H_
#define _DATA_H_
#include "configuration.h"
#include "connection.h"
#include <Arduino.h>
#include "SDManager.h"

class Data{
public:
  short int max{0};
  short int min{0};

  float grow_rate{0};
  float decline_rate{0};

  Data(short int min_val, short int max_val, float grow_val, float decline_val){
    max = max_val;
    min = min_val;
    grow_rate = grow_val;
    decline_rate = decline_val;
  }

  Data(){
    
  }

  void clear();
}; 

class Datas{
public:
  Data* datas {nullptr};
  SDManager* sd_manager {nullptr};
  Config *configuration {nullptr};
  Datas(SDManager* sd_manager, Config* conf, Connection* con){
    datas = new Data[MAX_COUNT_FILE];
    sd_manager = sd_manager;
    configuration = conf;
    connection = con;
    configuration->load();
    new_token();
    configuration->add_to_save(record_token);
  }

  ~Datas(){
    delete [] datas;
    delete sd_manager;
  }
  void add_data(Data data); 
  void save(void); 
  void load(char token[5], int partition);
  void send(int row = -1);

private:
  size_t token_length{5};
  char record_token[5];
  int record_partition_index{0};
  int index {0};
  String* list;

  Connection* connection {nullptr};

  void new_token(void);
  void clear(void);
  void new_partition(void);
  void load_config(char token[5]);
  void save_config(void);
};


#endif
