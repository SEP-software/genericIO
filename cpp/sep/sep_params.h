#ifndef SEP_PARAM_FUNC_H
#define SEP_PARAM_FUNC_H 1
#include "param_func.h"
#include<string>
#include<stdbool.h>

class sep_param: public param_func{
  public:
    sep_param(const int argc, char **argv);
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
    

    






};

#endif