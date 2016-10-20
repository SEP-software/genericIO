#ifndef JSON_IO_H
#define JSON_IO_H 1
#include "genericIO.h"
#include "jsonGenericFile.h"
#include "jsonParamObj.h"
#include <fstream>      // std::ifstream

class jsonGenericIO: public genericIO{
  public:
   jsonGenericIO( int argc, char **argv);
    virtual std::shared_ptr<genericRegFile> getRegFile(std::string name,usage_code usage);
    virtual std::shared_ptr<genericIrregFile> getIrregFile(std::string name, usage_code usage);
    virtual void close();
    
    private:
      std::ifstream inps;
      std::ofstream outs;
      std::shared_ptr<Json::Value> jsonArgs;
      


};
#endif