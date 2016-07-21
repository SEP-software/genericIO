#ifndef SEP_REGFILE_FUNC_H
#define SEP_REGFILE_FUNC_H 1
#include<string>
#include<stdbool.h>
#include "genericFile.h"
enum usage_code {
    usageIn,
    usageOut,
    usageInOut,
    usageScr
};

class sep_regfile: public generic_reg_file{
  public:
  
 // sep_regfile::sep_regfile(const std::string tag,usage_code usage){

    sep_regfile(std::string tg, usage_code usage);
    virtual int get_int(const std::string arg);
    virtual int get_int(const std::string arg, const int def);
   
    virtual float get_float(const std::string, const float def);
    virtual float get_float(const std::string) ;
   
    virtual std::string get_string(const std::string arg);
    virtual std::string get_string(const std::string arg, const std::string def);
  
   
    virtual bool get_bool(const std::string, const bool def);
    virtual bool get_bool(const std::string);
   
   
    virtual std::vector<int> get_ints(const std::string arg);
    virtual std::vector<int> get_ints(const std::string arg,std::vector<int> defs);
     
    virtual std::vector<float> get_floats(const std::string arg);
    virtual std::vector<float> get_floats(const std::string arg,std::vector<float> defs);
       
    virtual void error(const std::string err) ;
    
    virtual void read_float_stream(const long long npts, float *array);

    virtual void write_float_stream(const long long npts, const float *array);

    virtual void read_float_window(const std::vector<int> nw, const std::vector<int> fw, 
      const std::vector<int> jw,  float *array);

    virtual void write_float_window(const std::vector<int> nw, const std::vector<int> fw, 
      const std::vector<int> jw,  float *array);
     virtual void readDescription();
    virtual void writeDescription();
     virtual void put_int(const std::string par, const int val) ;
    virtual void put_float(const std::string par, const float val);
    virtual void put_string(const std::string par, const std::string val);
    virtual void put_bool(const std::string par, const bool val);
    virtual void put_ints(const std::string par, const  std::vector<int> val);
    virtual void put_floats(const std::string par, const std::vector<float> val) ;
  private:
    std::string _tag;
    




};

#endif