#ifndef PARAM_OBJ_H
#define PARAM_OBJ_H 1
#include<string>
#include<stdbool.h>
#include<vector>

namespace SEP{
class paramObj {
  public:
  
    paramObj(){;}
    virtual int getInt(const std::string arg) const ;
    virtual int getInt(const std::string arg, const int def) const 
       {if(arg=="" && def==0){;}; return 0;}
   
    virtual float getFloat(const std::string arg, const  float def)const { 
    if(arg=="" && def==0.){;};return 0.;}
    virtual float getFloat(const std::string arg)const  { if(arg==""){;}; return 0.;}
   
    virtual std::string getString(const std::string arg)const {if(arg==""){;}; return "A";}
    virtual std::string getString(const std::string arg, const std::string def)const {
      if(arg=="" && def=="" ) {;} return "A";}
   
    virtual bool getBool(const std::string arg, const bool def) const { if(arg=="" && def){;};return 0.;}
    virtual bool getBool(const std::string arg )const  { if(arg==""){;}; return 0.;}
    
   
    virtual std::vector<int> getInts(const std::string arg,int nvals)const {
       if(arg=="" && nvals==0) {;}  std::vector<int> a; return a;}
    virtual std::vector<int> getInts(const std::string arg,std::vector<int> defs)const {
       if(arg==""  && defs[0]==0 ) {;} std::vector<int> a; return a;}      
     
    virtual std::vector<float> getFloats(const std::string arg,int nvals)const {
       if(arg==""  && nvals==0) {;} std::vector<float> a; return a;;}
    virtual std::vector<float> getFloats(const std::string arg,std::vector<float> defs)const {
       if(arg==""  && defs[0]==0.) {;}std::vector<float> a; return a;}   
    virtual void error(std::string)const {;}
    virtual void message(const std::string)const{;}
       
};
}

#endif

