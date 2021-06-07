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

short Recorder::record_value(){
  x += (3.14 / 100.0); 
  double cosArr {(cos(x)+1)};
  return coder.position();
  return (cosArr)*40; //+(random(0.0, 4.0)*(cos(x)+1));
  

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
  coder.loop();
  actual = coder.position();
  at(last_index, actual);
  //mean
  //Serial.print("0,0,0,0"+ String(actual) + ",");


  sum += at(last_index);
  mean_data(MEAN_COUNT);
  actual = sum/MEAN_COUNT;
  //Serial.println(actual);

  at(last_index, actual);
 
  variation_calcul();
  min_and_max_calcul();
  //Index
  last_index++;
  update_index();

}
void Recorder::change(){
  actual_data->decline_rate = sum_variation/float(variation_count);
  Serial.println("min: " + String(actual_data->min) + " max: "+ String(actual_data->max));
  all_data->add_data(*actual_data);
  actual_data->clear(at(last_index)); 
  count = 0;
  variation_count = 0;
  sum_variation = 0.0; 
}
void Recorder::variation_calcul(void){
  int var {0};
  if((at(last_index-1) > actual)){
    var = -1;    

  }else if(at(last_index-1) < actual){
    var = 1;
  }else{
    var = 0;
  }

  if(var == -1){
    if(decline){
      count = 0;
      variation_count = 0;
      sum_variation = 0.0; 
      
    }else{
      count++;
      if (count > RANGE){
        count = 0;
        actual_data->grow_rate = sum_variation/float(variation_count);
        decline = true;
      }
    }
  }else if(var == 1){
    if(!decline){
        count = 0;

    }else{
      count++;
      if (count > RANGE){
        count = 0;
        decline = false;
          change();

      }
    }
  }


  sum_variation += at(last_index) - at(last_index-1);
  variation_count++;

    
  
}
void Recorder::min_and_max_calcul(void){

  if(actual_data->min > actual){
    actual_data->min = actual; 
  }

  if(actual_data->max < actual){
    actual_data->max = actual;
 
  }
}


