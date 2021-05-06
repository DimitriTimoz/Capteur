#include "recorder.h"
#include "data.h"

#include "connection.h"
#include "configuration.h"
#include "SDManager.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif


// recorder object
Recorder* recorder {nullptr};
// datas loaded
Datas* datas {nullptr};

Connection connection("BikeSensor");

bool is_updated(){
  return false;
}

void setup() {
  // put your setup code here, to run once:
  #if DEVELOPPEMENT
  Serial.begin(9600);
  #endif

  SDManager::init_SD_load();


  recorder = new Recorder(100);
}

void loop() {
  // put your main code here, to run repeatedly:
  recorder->update();

  delay(20);
}
