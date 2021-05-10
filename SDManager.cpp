
#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include "configuration.h"
#include "SDManager.h"



void SDManager::init_SD_load(){
  
  Serial.println("Initializing SD card...");

  if (!SD.begin(SD_CS)) {

    Serial.println("initialization failed!");

    while (1);

  }
  Serial.println("Initializing done.");

}
void SDManager::load_file(String *path, char mode){
  
    if(mode == 'r'){
      if(SD.exists(*path)){
        current_file = SD.open(*path, FILE_READ);
        read_mode = true;
        write_mode = false;
      }else{
        Serial.println("The file " + *path + " doesn't exist.");
        return;
      }
    }else if(mode == 'w') {
      current_file = SD.open(*path, FILE_WRITE);
      read_mode = false;
      write_mode = true;
    }else{
      Serial.println(*path + " can't be open, the open mode is not correctly specified.");
      return;
    }
    Serial.println(*path + " was correctly opened.");
    return;
  
}
String SDManager::get_file_content_str(){
  if(read_mode){
    return current_file.readString();
  }
  return "";
}

size_t SDManager::get_file_content_byte(char *buffer, size_t length){
   if(read_mode){
     return current_file.readBytes(buffer, length);
   }
 }

void SDManager::create_file(String* path){
  current_file = SD.open(*path, FILE_APPEND);
  close_file();
}

void SDManager::write_file(String* path, String *content){
  load_file(path, 'w');
  current_file.print(*content);
  close_file();
}

String SDManager::read_file(String *path){
  load_file(path, 'r');
  String content = get_file_content_str();
  close_file();
  return content;

}
void SDManager::save_file(String *content, String *path){
  create_file(path);
  write_file(path, content);
  Serial.println("File saved.");

}
