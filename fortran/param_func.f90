#ifndef PARAM_FUNC_H
#define PARAM_FUNC_H 1
#include<string>
#include<stdbool.h>


class param_func {
  public:
  
    param_func(){;}
    virtual int get_int(const std::string arg) { if(arg==0){;} return 0;}
    virtual int get_int(const std::string arg, const int def)  {if(arg==0 && def==0){;}; return 0;}
   
    virtual float get_float(const std::string,  float def)const { if(arg==0 && def==0.){;};return 0.;}
    virtual float get_float(const std::string) { if(arg==0){;}; return 0.;}
   
    virtual std::string get_string(const std::string arg){if(arg==0){;}; return "A";}
    virtual std::string get_string(const std::string arg, const std::string def){if(arg==0 && def==0){;};
      return "A";}
   
    virtual bool get_bool(const std::string, const bool def) { if(arg==0 && def){;};return 0.;}
    virtual bool get_bool(const std::string) { if(arg==0){;}; return 0.;}
   
   
    virtual std::vector<int> get_ints(const std::string arg){
       if(arg=="" ) ;}
    virtual std::vector<int> get_ints(const std::string arg,std::vector<int> defs){
       if(arg==""  && def[0]==0) ;}      
     
    virtual std::vector<float> get_floats(const std::string arg){
       if(arg=="" ) ;}
    virtual std::vector<float> get_floats(const std::string arg,std::vector<float> defs){
       if(arg==""  && def[0]==0.) ;}   
       
    virtual void error(const std::string err) const {if(err==""){;};}
    
  
    virtual ~param_func(){};
 };
#endif

