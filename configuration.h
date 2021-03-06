#ifndef _CONFIGURATION_H_
#define _CONFIGURATION_H_


// true: is in developpement mode
#define DEVELOPPEMENT false
//Pin SD_CS is the CS pin on the card 
#define SD_CS 5
//Serial baud
#define SERIAL_BAUD 115200
// the max number of datas in a file
#if DEVELOPPEMENT
  #define MAX_COUNT_FILE 20
#else
  #define MAX_COUNT_FILE 250
#endif
// the number of data to use for the mean
#define MEAN_COUNT 8
// the number of up record to comfirm up
#define RANGE 5
// the number of data in a range
#define MAX_RECORD_RANGE 500

#define PIN_LEFT 12
#define PIN_CODDER 27
#define PIN_RIGHT 14


#define PIN_BUTTON 17

#endif

