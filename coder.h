
#ifndef _CODER_H_
#define _CODER_H_

#include <Arduino.h>
#include "configuration.h"

class Coder{
public:
  int count {0};

  Coder(){
    pinMode(PIN_CODDER, INPUT);
    pinMode(PIN_LEFT, INPUT);
    pinMode(PIN_RIGHT, INPUT);

  }
  int position(void);
  void loop(void);
private:
  bool up {false};
  bool last {false};
};
#endif
