#include "recorder.h"
#include "data.h"
#include "BluetoothSerial.h"
#include "connection.h"
#include "configuration.h"
#include "manager.h"

#include "SDManager.h"
#include "coder.h"

// recorder object
Recorder* recorder {nullptr};
// datas loaded
Datas* datas {nullptr};

SDManager* sd_manager{nullptr};

Connection* connection {nullptr};

Coder* coder {nullptr};

Manager* config {nullptr};



void setup(void) {
  #if DEVELOPPEMENT
  Serial.begin(SERIAL_BAUD);
  #endif
  Serial.begin(115200);

  
  while (!SD.begin(SD_CS));

  Serial.println("Initializing done.");

  connection = new Connection();
  connection->init_connection("BikeSensor");
  sd_manager = new SDManager();
  config = new Manager(sd_manager);
  connection->add_components(config);
  datas = new Datas(sd_manager, config, connection);
  config->add_components(datas);
  recorder = new Recorder(MAX_RECORD_RANGE, datas); 
  coder = new Coder();
}

void loop() {
  coder->loop();
  if(config->is_recording()){
    recorder->update();
  }
  delay(1);
  connection->loop();

}

