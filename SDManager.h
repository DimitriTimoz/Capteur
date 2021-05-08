
#ifndef _SDMANAGER_H_
#define _SDMANAGER_H_

#include <Arduino.h>
#include <SPI.h>
#include <SD.h>


class SDManager{
  public:
    File current_file; 
    void init_SD_load();
    void load_file(String path, char mode = 'r');
    String get_file_content_str();
    size_t get_file_content_byte(char *buffer, size_t length);
    void save_file(String* content, String* file_name);
    inline void close_file(){ if(current_file ){current_file.close();} return;}
  private:
    String actual_path;
    bool write_mode;
    bool read_mode;
};
#endif
