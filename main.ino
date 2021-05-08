#include "recorder.h"
#include "data.h"
#include "BluetoothSerial.h"
#include "connection.h"
#include "configuration.h"
#include "SDManager.h"


// recorder object
Recorder* recorder {nullptr};
// datas loaded
Datas* datas {nullptr};

SDManager* sd_manager {nullptr};

Connection* connection {nullptr};


void setup() {
  #if DEVELOPPEMENT
  Serial.begin(115200);
  #endif
  connection = new Connection();
  connection->init_connection("BikeSensor");
  sd_manager = new SDManager();
  sd_manager->init_SD_load();
  datas = new Datas();
  recorder = new Recorder(100, datas); 
}

void loop() {
  recorder->update();
  delay(20);
}
