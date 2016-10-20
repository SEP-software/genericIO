#ifndef JSON_PARAM_OBJ
#define JSON_PARAM_OBJ 1
#include "json.h"
#include "paramObj.h"
#include <memory>
class jsonParamObj: public paramObj{
  public:
    jsonParamObj(std::shared_ptr<Json::Value> inp);
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
       
    virtual void error(const std::string err) ;

  protected:
   std::shared_ptr<Json::Value> jsonArgs;

};


#endif