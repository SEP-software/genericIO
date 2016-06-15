#include "sep_params.h"
extern "C" {
#include "seplib.h"
}

sep_param::sep_param(const int argc, char **argv){
 initpar(argc,argv);
}

int sep_param::get_int(const std::string arg){
    int x;
    if(0==getch(arg.c_str(),"d",&x))
      error(str("trouble grabbing parameter ")+arg+str(" from parameters"));
    return x;
}
int sep_param::get_int(const std::string arg, const int def){
   int x=def;
   int i=getch(arg.c_str(),"d",&x);
   return x;
}
   
float sep_param::get_float(const std::string, const float def){
  float x;
  int i=getch(arg.c_str(),"f",&x);
  return x;

}
float sep_param::get_float(const std::string){
  float x;
  if(0==getch(arg.c_str(),"f",&x))
     error(str("trouble grabbing parameter ")+arg+str(" from parameters"));
  return x;
}
   
std::string sep_param::get_string(const std::string arg){
  char buf[10000];
  if(0==getch(arg.c_str(),"s",buf))
      error(str("trouble grabbing parameter ")+arg+str(" from parameters"));
  return str(buf);


}
std::string sep_param::get_string(const std::string arg, const std::string def){

  char buf[10000];
  std::copy(def.begin(), def.end(), buf);
  int i=getch(arg.c_str(),"s",buf);
  return str(buf);

}
 
bool sep_param::get_bool(const std::string, const bool def){
  bool x=def;
  int i=getch(arg.c_str(),"l",x);
  return x;

}
bool sep_param::get_bool(const std::string){
 bool x;
  if(0==getch(arg.c_str(),"l",x)){
    error(str("trouble grabbing parameter ")+arg+str(" from parameters"));
  }
  return x;

}
   
   
std::vector<int> sep_param::get_ints(const std::string arg){
  int tmp[10000];
  ierr=getch(arg.c_str(),"d",tmp);
  if(ierr==0) 
     error(str("trouble grabbing parameter ")+arg+str(" from parameters"));
  std::vector<int> x;
  for(int i=0; i < ierr; i++) x.push_back(tmp[i]);
  return x;
}
std::vector<int> sep_param::get_ints(const std::string arg,std::vector<int> defs){
  int tmp[10000];
  for(int i=0; i < defs.size(); i++){
    tmp[i]=defs[i];
  }
  ierr=getch(arg.c_str(),"d",tmp);
  if(ierr==0) 
     error(str("trouble grabbing parameter ")+arg+str(" from parameters"));
  std::vector<int> x;
  if(ierr>0){  
    for(int i=0; i < ierr; i++) x.push_back(tmp[i]);
  }
  else{
    for(int i=0; i < defs.size(); i++) x.push_back(defs[i]);
  }
  return x;
}
     
std::vector<float> sep_param::get_floats(const std::string arg){
  float tmp[10000];
  ierr=getch(arg.c_str(),"f",tmp);
  if(ierr==0) 
     error(str("trouble grabbing parameter ")+arg+str(" from parameters"));
  std::vector<float> x;
  for(int i=0; i < ierr; i++) x.push_back(tmp[i]);
  return x;


}
std::vector<float> sep_param::get_floats(const std::string arg,std::vector<float> defs){

  float tmp[10000];
  for(int i=0; i < defs.size(); i++){
    tmp[i]=defs[i];
  }
  ierr=getch(arg.c_str(),"f",tmp);
  if(ierr==0) 
     error(str("trouble grabbing parameter ")+arg+str(" from parameters"));
  std::vector<float> x;
  if(ierr>0){  
    for(int i=0; i < ierr; i++) x.push_back(tmp[i]);
  }
  else{
    for(int i=0; i < defs.size(); i++) x.push_back(defs[i]);
  }
  return x;
}


void sep_param::error(const std::string err){
   seperr(err.c_str());
}
    
void sep_param::put_int(const std::string par, const int val){

   putch(par.c_str(),"d",&val);

}
void sep_param::put_float(const std::string par, const float val){

   putch(par.c_str(),"f",&val);
}
void sep_param::put_string(const std::string par, const std::string val){
  putch(par.c_str(),"s",val.c_str());
}

void sep_param::put_bool(const std::string par, const bool val){
   int x=0;
   if(val) x=1;
   putch(par.c_str(),"l",&x);    

}
void sep_param::put_ints(const std::string par, const  std::vector<int> val){
   int *tmp=new int[val.size()];
   for(int i=0; i < val.size(); i++) tmp[i]=val[i];
   putch(par.c_str(),"d",tmp);
   delete [] tmp;
}
void sep_param::put_floats(const std::string par, const std::vector<float> val){
   float *tmp=new int[val.size()];
   for(int i=0; i < val.size(); i++) tmp[i]=val[i];
   putch(par.c_str(),"f",tmp);
   delete [] tmp;

}
    


