#ifndef _MANAGER_H_
#define _MANAGER_H_
#include <Arduino.h>
#include "SDManager.h"
#include "connection.h"

#include "data.h"

class Datas;
class Manager{
public:
  int length_to_send{0};
  String* to_send {nullptr};
  SDManager* sd_manager {nullptr};
  Datas* datas {nullptr};


  Manager(SDManager *manager ){
    sd_manager = manager;
  }
  inline void add_components(Datas* datas_imp){datas = datas_imp;}
  void add_to_save(const String);
  void remove_to_save(const String);
  void start_record(void);
  void stop_recording(void);
  bool is_recording(void);
  void save(void);
  void load(void);
private:
  bool recording {false};

};


#endif