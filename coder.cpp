#include "coder.h"
#include "configuration.h"
#include <Arduino.h>

void Coder::loop(){
   digitalRead(PIN_CODDER);
    
    if(digitalRead(PIN_CODDER) != last){
      if(digitalRead(PIN_LEFT)){
        up = true;
      }else if(digitalRead(PIN_RIGHT)){
        up = false;
      }
      
      count += int(up) * 1 + int(up - 1) * 1;
      last = digitalRead(PIN_CODDER);
    }
}

int Coder::position(void){
  return (int)(((float)count / (20.0f * 3.0f)) * 40);
}
