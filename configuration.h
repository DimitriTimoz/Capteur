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
  #define MAX_COUNT_FILE 100
#endif
// the number of data to use for the mean
#define MEAN_COUNT 5
// the number of up record to comfirm up
#define RANGE 4
// the number of data in a range
#define MAX_RECORD_RANGE 500
#endif
