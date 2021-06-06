#include "recorder.h"
#include "data.h"
#include "BluetoothSerial.h"
#include "connection.h"
#include "configuration.h"
#include "manager.h"

#include "SDManager.h"

// recorder object
Recorder* recorder {nullptr};
// datas loaded
Datas* datas {nullptr};

SDManager* sd_manager{nullptr};

Connection* connection {nullptr};

Manager* manager {nullptr};



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
  manager = new Manager(sd_manager);
  connection->add_components(manager);
  datas = new Datas(sd_manager, manager, connection);
  manager->add_components(datas);

  recorder = new Recorder(MAX_RECORD_RANGE, datas); 
}

void loop() {
  if(manager->is_recording()){
    recorder->update();
    manager->updated();

  }
  delay(1);
  connection->loop();
  manager->TimeOut();
}
