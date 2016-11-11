#include "ioModes.h"
#include "ioConfig.h"
#include "segyIO.h"
#ifdef USE_RSF
#include "rsfIO.h"
#endif
#ifdef USE_SEP
#include "sepIO.h"
#endif 

void ioModes::setup( int argc,  char **argv){

std::shared_ptr<jsonGenericIO> a(new jsonGenericIO(argc,argv));
_ios["JSON"]=a; 
std::shared_ptr<segyIO> d(new segyIO(argc,argv));
_ios["SEGY"]=d;
#ifdef USE_RSF
std::shared_ptr<rsfIO> b(new rsfIO(argc,argv));
_ios["RSF"]=b; 
#endif
#ifdef USE_SEP
std::shared_ptr<sepIO> c(new sepIO(argc,argv));
_ios["SEP"]=c;
#endif
_defaultType=DEFAULTIO;
_defaultIO=_ios[_defaultType];


}
   std::shared_ptr<genericIO>  ioModes::getDefaultIO(){
   
       return getIO(_defaultType);
   }

std::shared_ptr<genericIO> ioModes::getIO(std::string def){

   if(_ios.count(def)==0)
     _par->error(def+" io has not been defined and/or built");
   return _ios[def];

   
}
std::shared_ptr<genericRegFile> ioModes::getRegFile(std::string def,std::string name,
   usage_code usage){
   
    if(_ios.count(def)==0)
     _par->error(def+" io has not been defined and/or built");
    if(!_ios[def]->getValid()) _par->error(def+std::string(" has not been initialized correctly"));
   return _ios[def]->getRegFile(name,usage);

   
   
}
std::shared_ptr<genericRegFile> ioModes::getGenericRegFile(std::string name,usage_code usage){
   
   _defaultIO->getRegFile(name,usage);
   
}

void ioModesFortran::setup(int argc, char **argv){
   std::shared_ptr<ioModes> x(new ioModes(argc,argv));
   getIO()=x;
}