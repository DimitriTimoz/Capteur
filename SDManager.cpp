
#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include "configuration.h"
#include "SDManager.h"



void SDManager::load_file(String *path, char mode){
    if(current_file){
      close_file();
    }
    if(!SD.exists(*path) && mode == 'r'){
      create_file(path);
    }
    if(mode == 'r'){
      current_file =  SD.open(*path, FILE_READ);
      read_mode = true;
      write_mode = false;
    }else if(mode == 'w') {
      current_file = SD.open(*path, FILE_WRITE);
      read_mode = false;
      write_mode = true;
    }else{
      return;
    }
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
  if(SD.exists(*path)){
    SD.remove(*path);
  }
  String name = *path;
  current_file = SD.open(name, FILE_APPEND);
  close_file();
}

void SDManager::write_file(String* path, String *content, bool reload){
  if(reload)
    load_file(path, 'w');
  current_file.print(*content);
  if(reload)
    close_file();
}

String SDManager::read_file(String *path){
  load_file(path, 'r');
  String content = get_file_content_str();
  close_file();
  return content;

}
void SDManager::add_in_file(String *path, String *content){
  write_file(path, content);

}

void SDManager::save_file(String *content, String *path){
  create_file(path);
  write_file(path, content);
}

bool SDManager::exist(String path){
  return SD.exists(path);
}
