#include "segyIO.h"

  

std::shared_ptr<genericRegFile> segyIO::getRegFile(const std::string name,const usage_code usage){
  
  std::shared_ptr<jsonGenericFile> x(new jsonGenericFile(getArgs(),usage,name,3600,240));
  return x;
  
}

