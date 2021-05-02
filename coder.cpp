#include "arduino.h"
void setup() {
  Serial.begin(9600);
  pinMode(3, INPUT);
  pinMode(2, INPUT);
}
long pulse = 0;
bool pA = false;
bool pB = true;

bool changed = false;

bool table[2] = {false, false};
bool same = false;
void loop() {
  table[0] = pA;
  table[1] = pB;
  if (digitalRead(2) == LOW) {
    pA = true;
  } else {
    pA = false;
  }
  if (digitalRead(3) == HIGH) {
    pB = true;
  } else {
    pB = false;
  }
  Serial.print(pA);
  Serial.print(',');
  Serial.println(pB);
  if(pA != table[0] || pB != table[1]){
    if(pA && pB){
      if (pA && table[1] ){
        pulse--;
      }else if (pB && table[0] ){
        pulse++;
      }
      changed = false;
  
      //Serial.println(pulse);
    }
  }

  delay(10);
}
