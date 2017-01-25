#include "genericIO.h"
using namespace SEP;
void genericIO::filesClose(){
   fprintf(stderr,"in file close \n");
   for(auto i=_regFiles.begin(); i!=_regFiles.end(); ++i){
   
   fprintf(stderr,"in loop \n");
      i->second->close();
    }
 for(auto i=_irregFiles.begin(); i!=_irregFiles.end(); ++i){
       i->second->close();
    }

}