#include "genericIO.h"
using namespace SEP;
void genericIO::filesClose(){
   for(auto i=_regFiles.begin(); i!=_regFiles.end(); ++i){
   
      i->second->close();
    }
 for(auto i=_irregFiles.begin(); i!=_irregFiles.end(); ++i){
       i->second->close();
    }

}
