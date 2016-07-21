#include "sep_reg_file.h"
extern "C" {
#include "seplib.h"
#include "sep3d.h"
}

sep_regfile::sep_regfile(const std::string tag,usage_code usage){
 _tag=tag;
 switch(usage){
    case usageIn:
      if(_tag!="in")
        auxin(_tag.c_str());
    case usageOut:
       if(tag!="out")
          auxout(_tag.c_str());
    case usageInOut:
       auxinout(_tag.c_str());
    case usageScr:
      auxscr(_tag.c_str());
  }
 
}

int sep_regfile::get_int(const std::string arg){
    int x;
    if(0==auxpar(arg.c_str(),"d",&x,_tag.c_str()))
      error(std::string("trouble grabbing parameter ")+arg+std::string(" from parameters"));
    return x;
}
int sep_regfile::get_int(const std::string arg, const int def){
   int x=def;
   int i=auxpar(arg.c_str(),"d",&x,_tag.c_str());
   return x;
}
   
float sep_regfile::get_float(const std::string arg, const float def){
  float x;
  int i=auxpar(arg.c_str(),"f",&x,_tag.c_str());
  return x;

}
float sep_regfile::get_float(const std::string arg){
  float x;
  if(0==auxpar(arg.c_str(),"f",&x,_tag.c_str()))
     error(std::string("trouble grabbing parameter ")+arg+std::string(" from parameters"));
  return x;
}
   
std::string sep_regfile::get_string(const std::string arg){
  char buf[10000];
  if(0==auxpar(arg.c_str(),"s",buf,_tag.c_str()))
      error(std::string("trouble grabbing parameter ")+arg+std::string(" from parameters"));
  return std::string(buf);


}
std::string sep_regfile::get_string(const std::string arg, const std::string def){

  char buf[10000];
  std::copy(def.begin(), def.end(), buf);
  int i=auxpar(arg.c_str(),"s",buf,_tag.c_str());
  return std::string(buf);

}
 
bool sep_regfile::get_bool(const std::string arg, const bool def){
  bool x=def;
  int i=auxpar(arg.c_str(),"l",&x,_tag.c_str());
  return x;

}
bool sep_regfile::get_bool(const std::string arg){
 bool x;
  if(0==auxpar(arg.c_str(),"l",&x,_tag.c_str())){
    error(std::string("trouble grabbing parameter ")+arg+std::string(" from parameters"));
  }
  return x;

}
   
   
std::vector<int> sep_regfile::get_ints(const std::string arg){
  int tmp[10000];
  int ierr=auxpar(arg.c_str(),"d",tmp,_tag.c_str());
  if(ierr==0) 
     error(std::string("trouble grabbing parameter ")+arg+std::string(" from parameters"));
  std::vector<int> x;
  for(int i=0; i < ierr; i++) x.push_back(tmp[i]);
  return x;
}
std::vector<int> sep_regfile::get_ints(const std::string arg,std::vector<int> defs){
  int tmp[10000];
  for(int i=0; i < defs.size(); i++){
    tmp[i]=defs[i];
  }
  int ierr=auxpar(arg.c_str(),"d",tmp,_tag.c_str());
  if(ierr==0) 
     error(std::string("trouble grabbing parameter ")+arg+std::string(" from parameters"));
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
  int ierr=auxpar(arg.c_str(),"f",tmp,_tag.c_str());
  if(ierr==0) 
     error(std::string("trouble grabbing parameter ")+arg+std::string(" from parameters"));
  std::vector<float> x;
  for(int i=0; i < ierr; i++) x.push_back(tmp[i]);
  return x;


}
std::vector<float> sep_regfile::get_floats(const std::string arg,std::vector<float> defs){

  float tmp[10000];
  for(int i=0; i < defs.size(); i++){
    tmp[i]=defs[i];
  }
  int ierr=auxpar(arg.c_str(),"f",tmp,_tag.c_str());
  if(ierr==0) 
     error(std::string("trouble grabbing parameter ")+arg+std::string(" from parameters"));
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
   float *tmp=new float[val.size()];
   for(int i=0; i < val.size(); i++) tmp[i]=val[i];
   auxputch(par.c_str(),"f",tmp,_tag.c_str());
   delete [] tmp;

}
void sep_regfile::read_float_stream(const long long npts, float *array){ 
   long long maxsize=10000000;
   long long nread=0;
   while(npts >nread){
      long long toReadL=std::min(maxsize,npts-nread);
      int ierr=sreed(_tag.c_str(),&array[nread],(int)toReadL);
      nread+=(long long)ierr;
      if(ierr!=toReadL)
        error(std::string("Trouble reading from ")+_tag+std::string(" after ")+
          std::to_string(nread)+std::string(" bytes"));
  }   

}
void sep_regfile::write_float_stream(const long long npts, const float *array){
   long long maxsize=10000000;
   long long nwrite=0;
   while(npts >nwrite){
      long long toWriteL=std::min(maxsize,npts-nwrite);
      int ierr=sreed(_tag.c_str(),(void*)(array+nwrite),(int)toWriteL);
      nwrite+=(long long)ierr;
      if(ierr!=toWriteL)
        error(std::string("Trouble reading from ")+_tag+std::string(" after ")+std::to_string(nwrite)+std::string(" bytes"));
  }   

}
 void sep_regfile::read_float_window(const std::vector<int> nw, const std::vector<int> fw, 
      const std::vector<int> jw,  float *array){
  hypercube *hyper=getHyper();
  std::vector<int> ng=hyper->return_ns();
  if(ng.size() >nw.size()){
    for(int i=nw.size(); i < ng.size(); i++){
      if(ng[i]>1) error("number of dimension does not equal data size");
    }
  }
  if(nw.size()< ng.size() || fw.size() < ng.size() || jw.size()< jw.size()){
     error("number of dimensions does not equal data size");
  }
  int ndim=ng.size();
  if(0!=sreed_window(_tag.c_str(),&ndim,ng.data(),nw.data(),fw.data(),
    jw.data(),4,array))
   error(std::string("trouble reading data from tag ")+_tag);
    
}
 void sep_regfile::write_float_window(const std::vector<int> nw, const std::vector<int> fw, 
      const std::vector<int> jw, float *array){
      
        hypercube *hyper=getHyper();
  std::vector<int> ng=hyper->return_ns();
  if(ng.size() >nw.size()){
    for(int i=nw.size(); i < ng.size(); i++){
      if(ng[i]>1) error("number of dimension does not equal data size");
    }
  }
  if(nw.size()< ng.size() || fw.size() < ng.size() || jw.size()< jw.size()){
     error("number of dimensions does not equal data size");
  }
  int ndim=ng.size();
  if(0!=srite_window(_tag.c_str(),&ndim,ng.data(),nw.data(),fw.data(),
    jw.data(),4,array))
   error(std::string("trouble writing data to tag ")+_tag);  
      
}
void sep_regfile::readDescription(){
  int ndim;
  sep_get_number_data_axes(_tag.c_str(),&ndim);
  std::vector<axis> axes;
  for(int i=1; i <= ndim; i++){
    int n;
    float o,d;
    char label[1024];
    sep_get_data_axis_par(_tag.c_str(),&i,&n,&o,&d,label);
    axes.push_back(axis(n,o,d,std::string(label)));
  }
  hypercube *hyper=new hypercube(axes);
  setHyper(hyper);
  delete hyper;
}
void sep_regfile::writeDescription(){
  hypercube *hyper=getHyper();
  std::vector<axis> axes=hyper->return_axes(hyper->get_ndim());
  for(int i=1; i <= axes.size(); i++){
     int n=axes[i].n; float o=axes[i].o; float d=axes[i].d;
     char label[1024];  std::copy(axes[i].label.begin(), axes[i].label.end(), label);
     sep_put_data_axis_par(_tag.c_str(),&i,&n,&o,&d,label);
  }


}