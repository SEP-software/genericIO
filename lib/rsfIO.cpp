
#include "rsfIO.h"

rsfIO::rsfIO(const int argc,  const char **argv){
  std::shared_ptr<rsfParam> x(new rsfParam(argc,argv));
  _param=x;
  _type="RSF";
  setValid(true);
}


std::shared_ptr<genericReg> rsfIO::getReg(const std::string &tag,const std::string &name,const usage_code usage){
    std::shared_ptr<rsfRegFile> x(new rsfRegFile(name, usage));
    addRegFile(tag,x);
    return x;
}

 
