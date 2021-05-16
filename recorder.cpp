#include <Arduino.h>
#include "recorder.h"
#include "data.h"


//Contructors
Recorder::Recorder(int length_val, Datas* data_var):
  length {length_val}, all_data{data_var}
{
  data = new short[length_val];
  actual_data = new Data(0,0,0,0);
  for(int i{0}; i < length_val; i++){
    at(i, 0);    
  }
}

// float methods
short Recorder::at(int index){
  return data[get_index(index)];
}

short Recorder::at(int index, short value){
  data[get_index(index)] = value;
  return value;
}

short Recorder::record_value(float x){
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

void Recorder::update(void){
  //record
  actual = record_value((double)last_index);
  at(last_index, actual);
  //mean
  sum += at(last_index);
  mean_data(MEAN_COUNT);
  actual = sum/MEAN_COUNT;
  at(last_index, actual);
 
  variation_calcul();
  min_and_max_calcul();
  //Index
  last_index++;
  update_index();

}

void Recorder::variation_calcul(void){
 if((actual >= at(last_index-1)) != decline ){
  count++;
  variation_count++;
  if(count >= RANGE){
    if(decline){
      actual_data->decline_rate = sum_variation/float(variation_count);
    }else{
      actual_data->grow_rate;
      all_data->add_data(*actual_data);
    }
    decline = !decline;
    count = 0;
    variation_count = 0;
    sum_variation = 0.0;
    
  }
 }
  sum_variation += at(last_index);

}

void Recorder::min_and_max_calcul(void){
  
  if(actual_data->min > actual){
    actual_data->min = actual; 
  }

  if(actual_data->max < actual){
    actual_data->max = actual; 
  }
}


