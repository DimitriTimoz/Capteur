
#ifndef _SDMANAGER_H_
#define _SDMANAGER_H_

#include <Arduino.h>
#include <SPI.h>
#include <SD.h>


class SDManager{
  public:
    File current_file; 
    void load_file(String *path, char mode = 'r');
    String get_file_content_str();
    size_t get_file_content_byte(char *buffer, size_t length);
    String read_file(String* path);

    void save_file(String* content, String* path);
    void create_file(String* path);
    void write_file(String* path, String *content, bool reload = true);
    void add_in_file(String *path, String *content);

    inline void close_file(){if(current_file){current_file.close();} return;}
    bool exist(String path);
  private:
    String actual_path;
    bool write_mode;
    bool read_mode;
};
#endif
