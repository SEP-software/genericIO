#include "genericFile.h"
 void genericRegFile::putInt(const std::string par, const int val) {
   if(par=="" && val==0);
   }
   
std::string genericRegFile::getDataTypeString(){
  dataType x=getDataType();
  
  switch(x){
    case dataFloat:
      return std::string("dataFloat");
      break;
    case dataByte:
      return std::string("dataBytes");
      break;
    case dataShort:
      return std::string("dataShort");
      break;
    case dataInt:
      return std::string("dataInt");
      break;
    case dataComplex:
      return std::string("dataComplex");
      break;
    default:
      return std::string("dataUndefined");
  }
}  