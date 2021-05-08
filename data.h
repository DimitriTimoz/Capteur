#ifndef _DATA_H_
#define _DATA_H_
#include "configuration.h"
#include <Arduino.h>
#include "SDManager.h"

class Data{
public:
  float max{0};
  float min{0};

  float grow_rate{0};
  float decline_rate{0};

  Data(float min_val, float max_val, float grow_val, float decline_val){
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
  Data* datas;
  SDManager* sd_manager;

  Datas(){
    datas = new Data[MAX_COUNT_FILE];
    sd_manager = new SDManager;
  }

  ~Datas(){
    delete [] datas;
    delete sd_manager;
  }
  void add_data(Data data); 
  void save(); 
  bool load();

private:
  String record_token {"df45gdfds"};
  int record_partition_index{0};
  int index {0};
  
  void clear();
  void new_partition();

};


#endif
