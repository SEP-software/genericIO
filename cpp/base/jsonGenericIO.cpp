#include "jsonGenericIO.h"
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
#include <exception>

jsonGenericIO::jsonGenericIO( int argc, char **argv){
 if(argc!=3) {
      std::cerr<<std::string("Expecting two arguments, JSON in and out files")<<std::endl;
       throw std::exception();
  }
  inps.open(argv[1],std::ifstream::in);
  std::shared_ptr<Json::Value> v(new Json::Value());
  jsonArgs=v;
  if(!inps){
       std::cerr<<std::string("Trouble opening "+std::string(argv[1]))<<std::endl;
       throw std::exception();
   }
   try{
      inps>>(*jsonArgs); 
   }
   catch(int x){
     std::cerr<<std::string("Trouble parsing JSON file "+std::string(argv[1]))<<std::endl;
     throw std::exception();
     
   }
   outs.open(argv[2],std::ofstream::out);
   if(outs) {
     std::cerr<<std::string("Trouble opening file "+std::string(argv[2]))<<std::endl;
        throw std::exception();
    }
    std::shared_ptr<jsonParamObj> x(new jsonParamObj(jsonArgs));
   _param=x;
}
std::shared_ptr<genericRegFile>  jsonGenericIO::getRegFile(std::string name,usage_code usage){


}
std::shared_ptr<genericIrregFile>  jsonGenericIO::getIrregFile(std::string name, usage_code usage){



}
void jsonGenericIO::close(){
    for(int i=0; i < _irregFiles.size(); i++){
      std::shared_ptr<genericIrregFile> m=_irregFiles[i];
      std::shared_ptr <jsonGenericFile> x= std::static_pointer_cast<jsonGenericFile>(m);
      //jsonArgs[x->getTag()]=x->getArgs();
      (*jsonArgs)["junk"]=x->getArgs();
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