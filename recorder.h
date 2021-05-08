
#ifndef _RECORDER_H_
#define _RECORDER_H_

#include "data.h"


class Recorder{
public:
  //properties
  Data* actual_data {nullptr};
  Datas* all_data {nullptr};
  float* data {nullptr};
  float actual{0.0};
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
  float at(int, float);
  float at(int);

  void update();
private:
  //properties
  int last_index {0};
  float sum {0};

  bool decline {false};
  int count {0};
  float sum_variation{0.0};
  int variation_count{0};
  //methods
  int get_index(int);
  float record_value(float x);
  
  void update_index(){last_index = last_index % length;}
  void mean_data(int n);
  void variation_calcul();
  void min_and_max_calcul();
};


#endif
