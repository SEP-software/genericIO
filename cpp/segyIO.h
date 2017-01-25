#ifndef SEGY_H 
#define SEGY_H 1
#include "jsonGenericIO.h"
namespace SEP{
class segyIO:public jsonGenericIO{
  public:
  segyIO( int argc,  char **argv){initJsonPars(argc,argv);}
  virtual std::shared_ptr<genericRegFile> getRegFile(const std::string name,const usage_code usage);
    virtual std::shared_ptr<genericIrregFile> getIrregFile(const std::string name, const usage_code usage){
       assert(1==2);
    }
  




};

}
#endif
