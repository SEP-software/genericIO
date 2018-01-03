#ifndef PARAM_OBJ_H
#define PARAM_OBJ_H 1
#include<string>
#include<assert.h>
#include<stdbool.h>
#include<vector>
#include<iostream>

namespace SEP{
class paramObj {
  public:
  
    paramObj(){;}
    virtual void error(const std::string&err)const { std::cerr<<err<<std::endl; assert(1==2); }
    virtual void message(const std::string&msg) const { std::cerr<< msg<<std::endl;}
    virtual int getInt(const std::string &arg) const { error("Undefined getInt"); return 0;}
    virtual int getInt(const std::string& arg, const int def) const{ error("Undefined getInt");return 0;}
   
    virtual float getFloat(const std::string& arg, const  float def)const { error("Undefined getFloat");return 0.;}
    virtual float getFloat(const std::string& arg)const { error("Undefined getFlot"); return 0.;}
    virtual std::string getString(const std::string &arg)const { error("Undefined getString"); std::string a=std::string(" ");return a;}
    virtual std::string getString(const std::string &arg, const std::string &def)const{ error("Undefined getString"); std::string a=std::string(" ");return a;}
    virtual bool getBool(const std::string &arg, const bool def) const{ error("Undefined getBoll"); return true;}
    virtual bool getBool(const std::string& arg )const { error("Undefined getBol"); return true;}
    virtual std::vector<int> getInts(const std::string &arg,const int nvals)const { error("Undefined getInts");std::vector<int> a; return a;}
    virtual std::vector<int> getInts(const std::string& arg,std::vector<int>& defs)const { error("Undefined getInts");
std::vector<int> a; return a;}   
     
    virtual std::vector<float> getFloats(const std::string &arg,int nvals)const { error("Undefined getFloata");
std::vector<float> a; return a;}
    virtual std::vector<float> getFloats(const std::string& arg,std::vector<float>& defs){ error("Undefined getFloats");
std::vector<float> a; return a;}

       
};
}

#endif

