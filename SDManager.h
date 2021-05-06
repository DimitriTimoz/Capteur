#include <Arduino.h>

#ifndef _SDMANAGER_H_
#define _SDMANAGER_H_

#include <SPI.h>
#include <SD.h>


class SDManager{
  public:
    static File current_file; 
    static void init_SD_load();
    static void load_file(String path);
    static String get_file_content_str();
    static byte* get_file_content_byte();
  private:
    static String actual_path;
    static bool load_mode;
    static bool read_mode;
};
#endif