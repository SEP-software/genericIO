#ifndef rsf_PARAM_FUNC_H
#define rsf_PARAM_FUNC_H 1
#include "paramObj.h"
#include<string>
#include<stdbool.h>
#define  NO_BLAS 1
class rsfParam: public paramObj{
  public:
    rsfParam(const int argc, char **argv);
    virtual int getInt(const std::string arg);
    virtual int getInt(const std::string arg, const int def);
   
    virtual float getFloat(const std::string, const float def);
    virtual float getFloat(const std::string) ;
   
    virtual std::string getString(const std::string arg);
    virtual std::string getString(const std::string arg, const std::string def);
  
   
    virtual bool getBool(const std::string, const bool def);
    virtual bool getBool(const std::string);
   
   
    virtual std::vector<int> getInts(const std::string arg,int nvals);
    virtual std::vector<int> getInts(const std::string arg,std::vector<int> defs);
     
    virtual std::vector<float> getFloats(const std::string arg,int nvals);
    virtual std::vector<float> getFloats(const std::string arg,std::vector<float> defs);
       
    virtual void err(const std::string err) ;
    

    






};

#endif