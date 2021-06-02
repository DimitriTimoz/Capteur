
#ifndef _CODER_H_
#define _CODER_H_

#include <Arduino.h>
#include "configuration.h"

class Coder{
public:
  int count {0};
  bool up {false};
  bool last {false};
  Coder(){
    pinMode(PIN_CODDER, OUTPUT);
    pinMode(PIN_LEFT, OUTPUT);
    pinMode(PIN_RIGHT, OUTPUT);

  }

  void loop(void);
};
#endif
