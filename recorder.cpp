#include "Arduino.h"
#include "recorder.h"



//Contructors
Recorder::Recorder(int length_val):
  length {length_val}
{
  data = new float[length_val];
  for(int i{0}; i < length_val; i++){
    at(i, 0);    
  }
}

// float methods
float Recorder::at(int index){
  return data[get_index(index)];
}

float Recorder::at(int index, float value){
  data[get_index(index)] = value;
  return value;
}

float Recorder::record_value(float x){
  x /= 15; 
  double cosArr {(cos(x)+1)};

  return (cosArr)*50 +(random(0.0, 10)*cos(x));
  

}




// int methods
int Recorder::get_index(int index){
  return (index+ length) % length;
}


// void methods
void Recorder::mean_data(int n){
  sum -= at(last_index-n);
}

void Recorder::update(){
  //record
  at(last_index, record_value((double)last_index));

  //mean
  sum += at(last_index);
  mean_data(4);
  at(last_index, sum/4);
  //Index
  last_index++;
  update_index();

}
