


#include "sep_regfiles.h"
extern "C" {
#include "seplib.h"
}

sep_regfile::sep_regfile(const std::string tag,usage_code usage){
 _tag=tag;
 switch(usage){
    case usageIn:
      if(_tag!="in")
        auxin(_tag);
    case usageOut:
       if(!tag!="out")
          auxout(_tag);
    case usageInOut:
       auxinout(_tag);
    case usageScr:
      auxscr(_tag);
  }
 
}

int sep_regfile::get_int(const std::string arg){
    int x;
    if(0==auxpar(arg.c_str(),"d",&x,_tag.c_str()))
      error(str("trouble grabbing parameter ")+arg+str(" from parameters"));
    return x;
}
int sep_regfile::get_int(const std::string arg, const int def){
   int x=def;
   int i=auxpar(arg.c_str(),"d",&x,_tag.c_str());
   return x;
}
   
float sep_regfile::get_float(const std::string, const float def){
  float x;
  int i=auxpar(arg.c_str(),"f",&x,_tag.c_str());
  return x;

}
float sep_regfile::get_float(const std::string){
  float x;
  if(0==auxpar(arg.c_str(),"f",&x,_tag.c_str()))
     error(str("trouble grabbing parameter ")+arg+str(" from parameters"));
  return x;
}
   
std::string sep_regfile::get_string(const std::string arg){
  char buf[10000];
  if(0==auxpar(arg.c_str(),"s",buf,_tag.c_str()))
      error(str("trouble grabbing parameter ")+arg+str(" from parameters"));
  return str(buf);


}
std::string sep_regfile::get_string(const std::string arg, const std::string def){

  char buf[10000];
  std::copy(def.begin(), def.end(), buf);
  int i=auxpar(arg.c_str(),"s",buf,_tag.c_str());
  return str(buf);

}
 
bool sep_regfile::get_bool(const std::string, const bool def){
  bool x=def;
  int i=auxpar(arg.c_str(),"l",x,_tag.c_str());
  return x;

}
bool sep_regfile::get_bool(const std::string){
 bool x;
  if(0==auxpar(arg.c_str(),"l",x,_tag.c_str())){
    error(str("trouble grabbing parameter ")+arg+str(" from parameters"));
  }
  return x;

}
   
   
std::vector<int> sep_regfile::get_ints(const std::string arg){
  int tmp[10000];
  ierr=auxpar(arg.c_str(),"d",tmp,_tag.c_str());
  if(ierr==0) 
     error(str("trouble grabbing parameter ")+arg+str(" from parameters"));
  std::vector<int> x;
  for(int i=0; i < ierr; i++) x.push_back(tmp[i]);
  return x;
}
std::vector<int> sep_regfile::get_ints(const std::string arg,std::vector<int> defs){
  int tmp[10000];
  for(int i=0; i < defs.size(); i++){
    tmp[i]=defs[i];
  }
  ierr=auxpar(arg.c_str(),"d",tmp,_tag.c_str());
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
     
std::vector<float> sep_regfile::get_floats(const std::string arg){
  float tmp[10000];
  ierr=auxpar(arg.c_str(),"f",tmp,_tag.c_str());
  if(ierr==0) 
     error(str("trouble grabbing parameter ")+arg+str(" from parameters"));
  std::vector<float> x;
  for(int i=0; i < ierr; i++) x.push_back(tmp[i]);
  return x;


}
std::vector<float> sep_regfile::get_floats(const std::string arg,std::vector<float> defs){

  float tmp[10000];
  for(int i=0; i < defs.size(); i++){
    tmp[i]=defs[i];
  }
  ierr=auxpar(arg.c_str(),"f",tmp,_tag.c_str());
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


void sep_regfile::error(const std::string err){
   seperr(err.c_str());
}
    
void sep_regfile::put_int(const std::string par, const int val){

   auxputch(par.c_str(),"d",&val,_tag.c_str());

}
void sep_regfile::put_float(const std::string par, const float val){

   auxputch(par.c_str(),"f",&val,_tag.c_str());
}
void sep_regfile::put_string(const std::string par, const std::string val){
  auxputch(par.c_str(),"s",val.c_str(),_tag.c_str());
}

void sep_regfile::put_bool(const std::string par, const bool val){
   int x=0;
   if(val) x=1;
   auxputch(par.c_str(),"l",&x,_tag.c_str());    

}
void sep_regfile::put_ints(const std::string par, const  std::vector<int> val){
   int *tmp=new int[val.size()];
   for(int i=0; i < val.size(); i++) tmp[i]=val[i];
   auxputch(par.c_str(),"d",tmp,_tag.c_str());
   delete [] tmp;
}
void sep_regfile::put_floats(const std::string par, const std::vector<float> val){
   float *tmp=new int[val.size()];
   for(int i=0; i < val.size(); i++) tmp[i]=val[i];
   auxputch(par.c_str(),"f",tmp,_tag.c_str());
   delete [] tmp;

}
void sep_regfile::read_float_stream(const long long npts, float *array){ 
   int maxsize=10000000;
   long long nread=0;
   while(npts >nread){
      long long toReadL=std::min(maxsize,npts-nread);
      ierr=sreed(_tag.c_str(),&array[nread],(int)toReadL);
      nread+=(long long)ierr;
      if(ierr!=toReadL)
        seperr(str("Trouble reading from ")+_tag+str(" after ")+std::to_string(nread)+str(" bytes"));
  }   

}
virtual void sep_regfile::write_float_stream(const long long npts, const float *array){
   int maxsize=10000000;
   long long nwrite=0;
   while(npts >nwrite){
      long long toWriteL=std::min(maxsize,npts-nwrite);
      ierr=sreed(_tag.c_str(),&array[nread],(int)toWriteL);
      nwrite+=(long long)ierr;
      if(ierr!=toWriteL)
        seperr(str("Trouble reading from ")+_tag+str(" after ")+std::to_string(nwrite)+str(" bytes"));
  }   

}
 void sep_regfile::read_float_window(const std::vector<int> nw, const std::vector<int> fw, 
      const std::vector<int> jw,  float *array){
  hypercube *hyper=getHyper();
  std::vector<int> ng=hyper->return_ns();

}
 void sep_regfile::write_float_window(const std::vector<int> nw, const std::vector<int> fw, 
      const std::vector<int> jw, const float *array){
      
      
}
void sep_regfile::readDescription(){


}
void sep_regfile::writeDescription(){


}