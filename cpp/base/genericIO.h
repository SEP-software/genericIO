#ifndef GENERIC_IO_H
#define GENERIC_IO_H 1
#include"genericFile.h"
#include "paramObj.h"
#include<memory>
#include <assert.h>
class genericIO{
  public:
    genericIO(){;}
    virtual std::shared_ptr<genericRegFile> getRegFile(std::string name,usage_code usage){
        assert(name==std::string("") || usage==usageIn);
    }
    virtual std::shared_ptr<genericIrregFile> getIrregFile(std::string name, usage_code usage){
     assert(name==std::string("") || usage==usageIn);
    }
    virtual std::shared_ptr<paramObj>  getParamObj(){
      return _param;
    }
    void addRegFile(std::shared_ptr<genericRegFile> r){
      _regFiles.push_back(r);
    }
    void addIrregFile(std::shared_ptr<genericIrregFile> r){
      _irregFiles.push_back(r);
    }
    virtual void close(){
      filesClose();
    }
    ~genericIO(){
      close();
    }
    virtual void filesClose();
  protected:
    std::vector<std::shared_ptr<genericRegFile>> _regFiles;
    std::vector<std::shared_ptr<genericIrregFile>> _irregFiles;
    std::shared_ptr<paramObj> _param;
};
#endif