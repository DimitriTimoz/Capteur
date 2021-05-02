#include "recorder.h"
#include "data.h"
#include "BluetoothSerial.h"
#include "FS.h"
#include "SD_MMC.h"


#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

Recorder* recorder {nullptr};
Datas* datas {nullptr};


void init_SD_Load(){
  if(!SD_MMC.begin()){
      Serial.println("Card Mount Failed");
      return;
  }

  uint8_t cardType = SD_MMC.cardType();

  if(cardType == CARD_NONE){
      Serial.println("No SD_MMC card attached");
      return;
  }

}

void send_data(String id){
  
}

bool is_updated(){
  return false;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  init_SD_Load();

  SerialBT.begin("BikeSensor"); 

  if(!is_updated()){
    send_data("sds");
  }
  recorder = new Recorder(100);
}

void loop() {
  // put your main code here, to run repeatedly:
  recorder->update();
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    Serial.write(SerialBT.read());
  }
  delay(20);
}
