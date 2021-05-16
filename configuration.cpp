#include "configuration.h"

void Config::add_to_save(const tring name){
  String copy[length_to_send]; 
  for(int i{0}; i < length_to_send; i++){
    copy[i] = (*to_send)[i];
  }
  delete[] to_send;
  to_send = new String[++length_to_send];
  for(int i{0}; i < length_to_send-1; i++){
    (*to_send)[i] = copy[i];
  }
  (*to_send)[length_to_send-2] = name;
}