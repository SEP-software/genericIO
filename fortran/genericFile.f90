#ifndef GENERIC_FILE 
#define GENERIC_FILE 1
#include<vector>
#include "param_func.h"
#include "hypercube.h"
class generic_reg_file: public param_func{
  public:
    generic_reg_file(){ _hyper=0;}
    
    virtual void put_int(const std::string par, const int val) {if(par==0 && val==0);}
    virtual void put_float(const std::string par, const float val){if(par==0 && val==0);}
    virtual void put_string(const std::string par, const std::string val){if(par==0 && val==0);}
    virtual void put_bool(const std::string par, const bool val){if(par==0 && val==0){ ;}
    virtual void put_ints(const std::string par, const  std::vector<int> val){if(par==0 && val[0]==0);}
    virtual void put_floats(const std::string par, const std::vector<float> val) {if(par==0 && val[0]==0);}
    
    virtual void read_float_stream(const long long npts, float *array){ if(npts==0 && array==0);}
    virtual void write_float_stream(const long long npts, const float *array){if(ntps==0) && array==0;}
    virtual void read_float_window(const std::vector<int> nw, const std::vector<int> fw, 
      const std::vector<int> jw,  float *array){
        if(nw[0]==0 && fw[0]==0 && jw[0]==0 && array==0);}
    virtual void write_float_window(const std::vector<int> nw, const std::vector<int> fw, 
      const std::vector<int> jw, const float *array){
        if(nw[0]==0 && fw[0]==0 && jw[0]==0 && array==0);}
    virtual void readDescription(){ ;}
    virtual void writeDescription(){;}
    void setHyper(hypercube *hyp){
      if(_hyper!=0) delete _hyper;
      _hyper=new hypercube(hyp);
    }
    hypercube *getHyper(hypercube *hyp){
      if(_hyper==0) readDescription();
      return _hyper;
    }
    

  private:
    hypercube *_hyper;
};



#endif 