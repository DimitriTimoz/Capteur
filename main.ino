#include "recorder.h"
#include "data.h"
#include "BluetoothSerial.h"
#include "connection.h"
#include "configuration.h"
#include "SDManager.h"
#include "coder.h";

// recorder object
Recorder* recorder {nullptr};
// datas loaded
Datas* datas {nullptr};

SDManager* sd_manager {nullptr};

Connection* connection {nullptr};

Coder* coder {nullptr};

void setup() {
  #if DEVELOPPEMENT
  Serial.begin(SERIAL_BAUD);
  #endif
  connection = new Connection();
  connection->init_connection("BikeSensor");
  sd_manager = new SDManager();
  sd_manager->init_SD_load();
  datas = new Datas();
  recorder = new Recorder(MAX_RECORD_RANGE, datas); 
  coder = new Coder();
}

void loop() {
  coder->loop();
  recorder->update();
  connection->loop();
  
}
