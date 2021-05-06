#ifndef _RECORDER_H_
#define _RECORDER_H_


class Recorder{
public:
  //properties
  float* data {nullptr};
  int length;
  float sum {0};
  Recorder(int length_val = 0);

  //delete
  ~Recorder()
  {
    delete data;
  }

  // Method
  float at(int, float);
  float at(int);

  void update();
  
private:
  //properties
  int last_index {0};
  //methods
  int get_index(int);
  float record_value(float x);
  
  void update_index(){last_index = last_index % length;}
  void mean_data(int n);
};


#endif
