#include "SDManager.h"

#include "Arduino.h"
#include <SPI.h>
#include <SD.h>
#include "configuration.h"



static void init_SD_load(){
  Serial.print("Initializing SD card...");

  if (!SD.begin(SD_CS)) {

    Serial.println("initialization failed!");

    while (1);

  }
}
/*static void load_file(String path);
static String get_file_content_str();
static byte* get_file_content_byte();
*/