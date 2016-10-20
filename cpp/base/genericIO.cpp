#include "genericIO.h"

void genericIO::filesClose(){
  
   for(int i=0; i < _regFiles.size(); i++){
      _regFiles[i]->close();
    }
    for(int i=0;i< _irregFiles.size(); i++){
      _irregFiles[i]->close();
    }

}