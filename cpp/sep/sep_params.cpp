#include "sep_params.h"
extern "C" {
#include "seplib.h"
}

sepParam::sepParam(const int argc, char **argv){
 initpar(argc,argv);
}

int sepParam::getInt(const std::string arg){
    int x;
    if(0==getch(arg.c_str(),"d",&x))
      err(std::string("trouble grabbing parameter ")+arg+std::string(" from parameters"));
    return x;
}
int sepParam::getInt(const std::string arg, const int def){
   int x=def;
   int i=getch(arg.c_str(),"d",&x);
   return x;
}
   
float sepParam::getFloat(const std::string arg, const float def){
  float x;
  int i=getch(arg.c_str(),"f",&x);
  return x;

}
float sepParam::getFloat(const std::string arg){
  float x;
  if(0==getch(arg.c_str(),"f",&x))
     err(std::string("trouble grabbing parameter ")+arg+std::string(" from parameters"));
  return x;
}
   
std::string sepParam::getString(const std::string arg){
  char buf[10000];
  if(0==getch(arg.c_str(),"s",buf))
      err(std::string("trouble grabbing parameter ")+arg+std::string(" from parameters"));
  return std::string(buf);


}
std::string sepParam::getString(const std::string arg, const std::string def){

  char buf[10000];
  std::copy(def.begin(), def.end(), buf);
  int i=getch(arg.c_str(),"s",buf);
  return std::string(buf);

}
 
bool sepParam::getBool(const std::string arg,  bool def){
  bool x=def;
  int i=getch(arg.c_str(),"l",&x);
  return x;

}
bool sepParam::getBool(const std::string arg){
 bool x;
  if(0==getch(arg.c_str(),"l",&x)){
    err(std::string("trouble grabbing parameter ")+arg+std::string(" from parameters"));
  }
  return x;

}
   
   
std::vector<int> sepParam::getInts(const std::string arg,int nvals){
  int tmp[10000];
  int ierr=getch(arg.c_str(),"d",tmp);
  if(ierr==0) 
     err(std::string("trouble grabbing parameter ")+arg+std::string(" from parameters"));
  std::vector<int> x;
  for(int i=0; i < ierr; i++) x.push_back(tmp[i]);
  return x;
}
std::vector<int> sepParam::getInts(const std::string arg,std::vector<int> defs){
  int tmp[10000];
  for(int i=0; i < defs.size(); i++){
    tmp[i]=defs[i];
  }
  int ierr=getch(arg.c_str(),"d",tmp);
 
  std::vector<int> x;
  if(ierr>0){  
    for(int i=0; i < ierr; i++) x.push_back(tmp[i]);
  }
  else{
    for(int i=0; i < defs.size(); i++) x.push_back(defs[i]);
  }
  return x;
}
     
std::vector<float> sepParam::getFloats(const std::string arg,int nvals){
  float tmp[10000];
  int ierr=getch(arg.c_str(),"f",tmp);
  if(ierr==0) 
     err(std::string("trouble grabbing parameter ")+arg+std::string(" from parameters"));
  std::vector<float> x;
  for(int i=0; i < ierr; i++) x.push_back(tmp[i]);
  return x;


}
std::vector<float> sepParam::getFloats(const std::string arg,std::vector<float> defs){

  float tmp[10000];
  for(int i=0; i < defs.size(); i++){
    tmp[i]=defs[i];
  }
  int ierr=getch(arg.c_str(),"f",tmp);
  std::vector<float> x;
  if(ierr>0){  
    for(int i=0; i < ierr; i++) x.push_back(tmp[i]);
  }
  else{
    for(int i=0; i < defs.size(); i++) x.push_back(defs[i]);
  }
  return x;
}


void sepParam::err(const std::string errm){
   seperr(errm.c_str());
}
    

    


