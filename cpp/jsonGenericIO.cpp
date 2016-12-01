#include "jsonGenericIO.h"
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
#include <exception>

void jsonGenericIO::initJsonPars(  int argc,  char **argv){

  setValid(false);
  bool foundIn=false, foundOut=false;
  std::string fileIn,fileOut;
  int i=0;
  /*Looking for jsonIn and jsonOut"*/
  while(i < argc && (!foundIn || !foundOut)){
    fprintf(stderr,"CGEC ME %d %d  %s \n",i,argc,argv[i]);
     std::string arg=std::string(argv[i]);
     if(arg.length() > 8){
       if(arg.substr(0,7)==std::string("jsonIn=")){
         fileIn=arg.substr(7); foundIn=true;
       }
       else if(arg.substr(0,8)==std::string("jsonOut=")){
         fileOut=arg.substr(8); foundOut=true;
       }
      }
    i++;
  }
  if(!foundIn || !foundOut){
   return;
    std::cerr<<std::string("Expecting jsonIn=file jsonOut=file on the command line")<<std::endl;
       throw std::exception();
  }
  inps.open(fileIn,std::ifstream::in);
  std::shared_ptr<Json::Value> v(new Json::Value());
  jsonArgs=v;
  if(!inps){
       std::cerr<<std::string("Trouble opening "+std::string(fileIn))<<std::endl;
       throw std::exception();
   }
   try{
      inps>>(*jsonArgs); 
   }
   catch(int x){
     std::cerr<<std::string("Trouble parsing JSON file "+std::string(fileIn))<<std::endl;
     throw std::exception();
     
   }
   outs.open(fileOut,std::ofstream::out);
   if(!outs) {
     std::cerr<<std::string("Trouble opening file "+std::string(fileOut))<<std::endl;
        throw std::exception();
    }
    std::shared_ptr<jsonParamObj> x(new jsonParamObj(jsonArgs));
   _param=x;
   setValid(true);
}
std::shared_ptr<genericRegFile>  jsonGenericIO::getRegFile(const std::string name,const usage_code usage){


}
std::shared_ptr<genericIrregFile>  jsonGenericIO::getIrregFile(const std::string name, const usage_code usage){



}
void jsonGenericIO::close(){
    for(auto i=_irregFiles.begin(); i !=_irregFiles.end(); ++i){
     std::shared_ptr <jsonGenericFile> x= std::static_pointer_cast<jsonGenericFile>(i->second);
     (*jsonArgs)[i->first]=x->getArgs();
   }
    for(auto i=_regFiles.begin(); i !=_regFiles.end(); ++i){
     std::shared_ptr <jsonGenericFile> x= std::static_pointer_cast<jsonGenericFile>(i->second);
     (*jsonArgs)[i->first]=x->getArgs();
   }
    outs<<jsonArgs;
    filesClose();
    
}

 /*
    std::static_pointer_cast<DerivedClass>(ptr_to_base)->f(); // OK
    // (constructs a temporary shared_ptr, then calls operator->)
 
    static_cast<DerivedClass*>(ptr_to_base.get())->f(); // also OK
    // (direct cast, does not construct a temporary shared_ptr)
    
    */