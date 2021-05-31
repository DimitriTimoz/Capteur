#include "recorder.h"
#include "data.h"
#include "BluetoothSerial.h"
#include "connection.h"
#include "configuration.h"
#include "SDManager.h"
#include "coder.h"

// recorder object
Recorder* recorder {nullptr};
// datas loaded
Datas* datas {nullptr};

SDManager* sd_manager{nullptr};

Connection* connection {nullptr};

Coder* coder {nullptr};

Config* config {nullptr};



void setup() {
  #if DEVELOPPEMENT
  Serial.begin(SERIAL_BAUD);
  #endif
  
  
  while (!SD.begin(SD_CS));

  Serial.println("Initializing done.");

  connection = new Connection();
  connection->init_connection("BikeSensor");
  sd_manager = new SDManager();
  config = new Config(sd_manager, connection);
  datas = new Datas(sd_manager, config, connection);
  recorder = new Recorder(MAX_RECORD_RANGE, datas); 
  coder = new Coder();
}

void loop() {
  //coder->loop();
  recorder->update();
  delay(1);
  //connection->loop();
}

