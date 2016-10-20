
#include "sepIO.h"

sepIO::sepIO(int argc, char **argv){
 std::shared_ptr<sepParam> x(new sepParam(argc,argv));
  _param=x;
}


std::shared_ptr<genericRegFile> sepIO::getRegFile(std::string name,usage_code usage){
    std::shared_ptr<sepRegFile> x(new sepRegFile(name,usage));
    addRegFile(x);
    return x;
    
}
std::shared_ptr<genericIrregFile> sepIO::getIrregFile(std::string name, usage_code usage){
    std::shared_ptr<sep3dFile> x(new sep3dFile(name,usage));
    addIrregFile(x);
    return x;
}
 
