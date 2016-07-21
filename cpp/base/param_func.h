#ifndef PARAM_FUNC_H
#define PARAM_FUNC_H 1
#include<string>
#include<stdbool.h>
#include<vector>


class param_func {
  public:
  
    param_func(){;}
    virtual int get_int(const std::string arg);
    virtual int get_int(const std::string arg, const int def) 
       {if(arg=="" && def==0){;}; return 0;}
   
    virtual float get_float(const std::string arg,  float def)const { if(arg=="" && def==0.){;};return 0.;}
    virtual float get_float(const std::string arg) { if(arg==""){;}; return 0.;}
   
    virtual std::string get_string(const std::string arg){if(arg==""){;}; return "A";}
    virtual std::string get_string(const std::string arg, const std::string def){
      if(arg=="" && def=="") return "A";}
   
    virtual bool get_bool(const std::string arg, const bool def) { if(arg=="" && def){;};return 0.;}
    virtual bool get_bool(const std::string arg ) { if(arg==""){;}; return 0.;}
   
   
    virtual std::vector<int> get_ints(const std::string arg){
       if(arg=="" ) ;}
    virtual std::vector<int> get_ints(const std::string arg,std::vector<int> defs){
       if(arg==""  && defs[0]==0) ;}      
     
    virtual std::vector<float> get_floats(const std::string arg){
       if(arg=="" ) ;}
    virtual std::vector<float> get_floats(const std::string arg,std::vector<float> defs){
       if(arg==""  && defs[0]==0.) ;}   
       
    virtual void error(const std::string err) const {if(err==""){;};}
    
  
    virtual ~param_func(){};
 };
#endif

