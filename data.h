#ifndef _DATA_H_
#define _DATA_H_

class Data{
public:
  float max{0};
  float min{0};

  float grow_rate{0};
  float decline_rate{0};

  Data(float min_val, float max_val, float grow_val, float decline_val){
    max = max_val;
    min = min_val;
    grow_rate = grow_val;
    decline_rate = decline_val;
  }

  Data(){
    
  }
}; 

class Datas{
public:
  Data* datas;
  int length {0};
  
  Datas(){
    datas = new Data[length];
  }

  ~Datas(){
    delete [] datas;
  }
  bool add_data(); 
  bool save(); 
  bool load();

private:
  int index {0};

};


#endif
