
#ifndef _RECORDER_H_
#define _RECORDER_H_

#include "data.h"
#include "coder.h"

class Recorder{
public:
  //properties
  Data* actual_data {nullptr};
  Datas* all_data {nullptr};
  short *data {nullptr};
  short actual{0};
  int length;
  Recorder(int, Datas*);

  //delete
  ~Recorder()
  {
    delete actual_data;
    delete data;
    delete all_data;
  }

  // Method
  short at(int, short);
  short at(int);

  void update(void);
private:
  //properties
  Coder coder;
  int last_index {0};
  int sum {0};

  bool decline {false};
  int count {0};
  int sum_variation{0};
  int variation_count{0};
  //methods
  int get_index(int);
  short record_value(float x);
  
  void update_index(){last_index = last_index % length;}
  void mean_data(int n);
  void variation_calcul(void);
  void min_and_max_calcul(void);
};


#endif
