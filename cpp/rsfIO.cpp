
#include "rsfIO.h"

rsfIO::rsfIO(int argc,  char **argv){
  std::shared_ptr<rsfParam> x(new rsfParam(argc,argv));
  _param=x;
}


std::shared_ptr<genericRegFile> rsfIO::getRegFile(const std::string name,const usage_code usage){
    std::shared_ptr<rsfRegFile> x(new rsfRegFile(name, usage));
    addRegFile(name,x);
    return x;
}

 
