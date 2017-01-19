#ifndef GENERIC_IO_H
#define GENERIC_IO_H 1
#include"genericFile.h"
#include "paramObj.h"
#include<memory>
#include<map>
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
    void addRegFile(std::string x,std::shared_ptr<genericRegFile> r){
      _regFiles[x]=r;
    }
    void addIrregFile(std::string x, std::shared_ptr<genericIrregFile> r){
      _irregFiles[x]=r;
    }
    std::shared_ptr<genericRegFile> getRegFile(const std::string x){
      if(!regFileExists(x))
         _param->error(std::string("Requested unknown file ")+x);
      return _regFiles[x]; 
   }
   bool regFileExists(const std::string name){
     if(_regFiles.count(name)==0) return false;
     return true; 
  }
   bool irregFileExists(const std::string name){
     if(_irregFiles.count(name)==0) return false;
     return true; 
  }
     
   std::shared_ptr<genericIrregFile> getIrregFile(const std::string x){
      if(_irregFiles.count(x)==0) 
         _param->error(std::string("Requested unknown file ")+x);
      return _irregFiles[x]; 
   }
   void setValid(const bool x){_valid=x;}
   bool getValid(){ return _valid;}
     
    virtual void close(){
      filesClose();
    }
    
    ~genericIO(){
      close();
    }
    virtual void filesClose();
  protected:
    std::map<std::string,std::shared_ptr<genericRegFile>> _regFiles;
    std::map<std::string, std::shared_ptr<genericIrregFile>> _irregFiles;
    std::shared_ptr<paramObj> _param;
    bool _valid;
    };
#endif
