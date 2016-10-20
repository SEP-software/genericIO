#ifndef PARAM_FUNC_H
#define PARAM_FUNC_H 1
#include<string>
#include<stdbool.h>
#include<vector>


class paramObj {
  public:
  
    paramObj(){;}
    virtual int getInt(const std::string arg);
    virtual int getInt(const std::string arg, const int def) 
       {if(arg=="" && def==0){;}; return 0;}
   
    virtual float getFloat(const std::string arg,  float def)const { if(arg=="" && def==0.){;};return 0.;}
    virtual float getFloat(const std::string arg) { if(arg==""){;}; return 0.;}
   
    virtual std::string getString(const std::string arg){if(arg==""){;}; return "A";}
    virtual std::string getString(const std::string arg, const std::string def){
      if(arg=="" && def=="") return "A";}
   
    virtual bool getBool(const std::string arg, const bool def) { if(arg=="" && def){;};return 0.;}
    virtual bool getBool(const std::string arg ) { if(arg==""){;}; return 0.;}
   
   
    virtual std::vector<int> getInts(const std::string arg,int nvals){
       if(arg=="" ) ;}
    virtual std::vector<int> getInts(const std::string arg,std::vector<int> defs){
       if(arg==""  && defs[0]==0) ;}      
     
    virtual std::vector<float> getFloats(const std::string arg,int nvals){
       if(arg=="" ) ;}
    virtual std::vector<float> getFloats(const std::string arg,std::vector<float> defs){
       if(arg==""  && defs[0]==0.) ;}   
    virtual void error(std::string);

       
};

#endif

