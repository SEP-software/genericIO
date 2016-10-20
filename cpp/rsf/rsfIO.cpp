
#include "rsfIO.h"

rsfIO::rsfIO(int argc, char **argv){
  std::shared_ptr<rsfParam> x(new rsfParam(argc,argv));
  _param=x;
}


std::shared_ptr<genericRegFile> rsfIO::getRegFile(std::string name,usage_code usage){
    std::shared_ptr<rsfRegFile> x(new rsfRegFile(name,usage));
    addRegFile(x);
    return x;
}

 
