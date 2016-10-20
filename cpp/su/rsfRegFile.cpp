#include "rsfRegFiles.h"
extern "C" {
#include "rsf.h"

}
#include "basicIO.h"
rsfRegFile::rsfRegFile(const std::string tag,usage_code usage){
 _tag=tag;
 switch(usage){
    case usageIn:
      _file=sf_input(_tag.c_str());
    case usageOut:
      _file=sf_output(_tag.c_str());
    case usageInOut:
       err("undefined usageInOut for rsf");
    case usageScr:
      err("undefined usageSrc for rsf");
  }
  myio=0;
  _usage=usage;
 
}

int rsfRegFile::getInt(const std::string arg){
    int x;
    if(!sf_histint(_file,arg.c_str(),&x))
      err(std::string("trouble grabbing parameter ")+arg+std::string(" from parameters"));
    return x;
}
int rsfRegFile::getInt(const std::string arg, const int def){
   int x=def;
   sf_histint(_file,arg.c_str(),&x);
   return x;
}
   
float rsfRegFile::getFloat(const std::string arg, const float def){
  float x;
   sf_histfloat(_file,arg.c_str(),&x);
  return x;

}
float rsfRegFile::getFloat(const std::string arg){
  float x;
  if(! sf_histfloat(_file,arg.c_str(),&x))
     err(std::string("trouble grabbing parameter ")+arg+std::string(" from parameters"));
  return x;
}
   
std::string rsfRegFile::getString(const std::string arg){
   char *buf;
   
   buf=sf_histstring(_file,arg.c_str());
   if(buf==NULL);
      err(std::string("trouble grabbing parameter ")+arg+std::string(" from parameters"));
  std::string y= std::string(buf);
  free(buf);
  return y;

}
std::string rsfRegFile::getString(const std::string arg, const std::string def){

  char *buf=sf_histstring(_file,arg.c_str());
  if(buf==NULL) return def;
  
  std::string y=std::string(buf);
  free(buf);
  return y;
}
 
bool rsfRegFile::getBool(const std::string arg, const bool def){
  bool x=def;
  sf_histbool(_file,arg.c_str(),&x);
  return x;

}
bool rsfRegFile::getBool(const std::string arg){
 bool x;
  if(!sf_histbool(_file,arg.c_str(),&x)){
    err(std::string("trouble grabbing parameter ")+arg+std::string(" from parameters"));
  }
  return x;

}
   
   
std::vector<int> rsfRegFile::getInts(const std::string arg,int n){
  int tmp[10000];
  bool ierr=sf_histints(_file,arg.c_str(),tmp,n);
  if(!ierr) 
     err(std::string("trouble grabbing parameter ")+arg+std::string(" from parameters"));
  std::vector<int> x;
  for(int i=0; i < n; i++) x.push_back(tmp[i]);
  return x;
}
std::vector<int> rsfRegFile::getInts(const std::string arg,std::vector<int> defs){
  int tmp[10000];
  for(int i=0; i < defs.size(); i++){
    tmp[i]=defs[i];
  }
 bool ierr=sf_histints(_file,arg.c_str(),tmp,defs.size());
  std::vector<int> x;
  if(ierr){  
    for(int i=0; i < defs.size(); i++) x.push_back(tmp[i]);
  }
  else{
    for(int i=0; i < defs.size(); i++) x.push_back(defs[i]);
  }
  return x;
}
     
std::vector<float> rsfRegFile::getFloats(const std::string arg,int n){
  float tmp[10000];
  bool ierr=sf_histfloats(_file,arg.c_str(),tmp,n);
  if(!ierr) 
     err(std::string("trouble grabbing parameter ")+arg+std::string(" from parameters"));
  std::vector<float> x;
  for(int i=0; i < n; i++) x.push_back(tmp[i]);
  return x;


}
std::vector<float> rsfRegFile::getFloats(const std::string arg,std::vector<float> defs){

  float tmp[10000];
  for(int i=0; i < defs.size(); i++){
    tmp[i]=defs[i];
  }
  bool ierr=sf_histfloats(_file,arg.c_str(),tmp,defs.size());

  std::vector<float> x;
  if(ierr){  
    for(int i=0; i < defs.size(); i++) x.push_back(tmp[i]);
  }
  else{
    for(int i=0; i < defs.size(); i++) x.push_back(defs[i]);
  }
  return x;
}


void rsfRegFile::err(const std::string err){
   sf_error(err.c_str());
}
    
void rsfRegFile::putInt(const std::string par, const int val){
   sf_putint(_file,par.c_str(),val);

}
void rsfRegFile::putFloat(const std::string par, const float val){

   sf_putfloat(_file,par.c_str(),val);
}
void rsfRegFile::putString(const std::string par, const std::string val){
   sf_putstring(_file,par.c_str(),val.c_str());
}

void rsfRegFile::putBool(const std::string par, const bool val){
      int i=1;
      if(!val) i=0;
      sf_putint(_file,par.c_str(),i);
  

}
void rsfRegFile::putInts(const std::string par, const  std::vector<int> val){

/*
   int *tmp=new int[val.size()];
   for(int i=0; i < val.size(); i++) tmp[i]=val[i];
  sf_putints(_file,par.c_str(),tmp,val.size());
   delete [] tmp;
   */
}
void rsfRegFile::putFloats(const std::string par, const std::vector<float> val){
   
   /*
   float *tmp=new float[val.size()];
   for(int i=0; i < val.size(); i++) tmp[i]=val[i];
   sf_putfloats(_file,par.c_str(),tmp,val.size());
   delete [] tmp;
   */

}
void rsfRegFile::readFloatStream( float *array,const long long npts){ 
   long long maxsize=10000000;
   long long nread=0;
   long long nptsT=npts*4;
   while(nptsT >nread){
      long long toReadL=std::min(maxsize,nptsT-nread);
      sf_floatread(array,toReadL,_file);
     
      nread+=(long long)toReadL;
  }   

}
void rsfRegFile::readUCharStream( unsigned char *array,const long long npts){ 
   long long maxsize=10000000;
   long long nread=0;
   while(npts >nread){
      long long toReadL=std::min(maxsize,npts-nread);
      sf_ucharread(array,toReadL,_file);
      nread+=(long long)toReadL;

  }   

}

void rsfRegFile::writeFloatStream( const float *array,const long long npts){
   long long maxsize=10000000;
   long long nwrite=0;
   long long nptsT=npts*4;
   while(nptsT >nwrite){
      long long toWriteL=std::min(maxsize,nptsT-nwrite);
      sf_floatwrite((float*)array,toWriteL,_file);
      nwrite+=(long long)toWriteL;
  }   

}
 void rsfRegFile::readFloatWindow(const std::vector<int> nw, const std::vector<int> fw, 
      const std::vector<int> jw,  float *array){
  hypercube *hyper=getHyper();
  std::vector<int> ng=hyper->returnNs();
  if(ng.size() >nw.size()){
    for(int i=nw.size(); i < ng.size(); i++){
      if(ng[i]>1) err("number of dimension does not equal data size");
    }
  }
  if(nw.size()< ng.size() || fw.size() < ng.size() || jw.size()< jw.size()){
     err("number of dimensions does not equal data size");
  }
  if(myio=0){
    myio=new rsfBasic(_file);
    myio->setFileParams(_tag,_usage,0,0,4,getHyper());
  }
  myio->readWindow(nw,fw,jw,array);

    
}

 void rsfRegFile::readUCharWindow(const std::vector<int> nw, const std::vector<int> fw, 
      const std::vector<int> jw,  unsigned char *array){
  hypercube *hyper=getHyper();
  std::vector<int> ng=hyper->returnNs();
  if(ng.size() >nw.size()){
    for(int i=nw.size(); i < ng.size(); i++){
      if(ng[i]>1) err("number of dimension does not equal data size");
    }
  }
  if(nw.size()< ng.size() || fw.size() < ng.size() || jw.size()< jw.size()){
     err("number of dimensions does not equal data size");
  }
  if(myio=0){
    myio=new rsfBasic(_file);
    myio->setFileParams(_tag,_usage,0,0,1,getHyper());
  }
  myio->readWindow(nw,fw,jw,array);
    
}
 void rsfRegFile::writeFloatWindow(const std::vector<int> nw, const std::vector<int> fw, 
      const std::vector<int> jw, float *array){
      
        hypercube *hyper=getHyper();
  std::vector<int> ng=hyper->returnNs();
  if(ng.size() >nw.size()){
    for(int i=nw.size(); i < ng.size(); i++){
      if(ng[i]>1) err("number of dimension does not equal data size");
    }
  }
  if(nw.size()< ng.size() || fw.size() < ng.size() || jw.size()< jw.size()){
     err("number of dimensions does not equal data size");
  }
  if(myio=0){
    myio=new rsfBasic(_file);
    myio->setFileParams(_tag,_usage,0,0,4,getHyper());
  }
  myio->writeWindow(nw,fw,jw,array);
      
}
void rsfRegFile::readDescription(){
  int ndim;
  bool breakIt=false;
  int iax=9;
  while(iax >=1 && !breakIt){
    std::string tmp;
    int n=1;
    tmp="n"+std::to_string(iax);
    sf_histint(_file,tmp.c_str(),&n);
    if(n>1)  breakIt=true;
    iax--;
  }
  if(iax==0) err("couldn't find any axes");
  ndim=iax;
  std::vector<axis> axes;
  for(int i=1; i <= ndim; i++){
    int n=1;
    float o=0.,d=1.;
    std::string tmp;
    tmp="n"+std::to_string(i); sf_histint(_file,tmp.c_str(),&n);
    tmp="o"+std::to_string(i); 
    sf_histfloat(_file,tmp.c_str(),&o);
    tmp="d"+std::to_string(i); sf_histfloat(_file,tmp.c_str(),&d);
    tmp="label"+std::to_string(i); 
    char *mm=sf_histstring(_file,tmp.c_str());
    std::string label;
    if(mm==NULL) label=std::string("none");
    else{
       label=std::string(mm);
       free(mm);
    }
    axes.push_back(axis(n,o,d,label));
    
  }
  hypercube *hyper=new hypercube(axes);
  setHyper(hyper);
  delete hyper;
}
void rsfRegFile::writeDescription(){
  hypercube *hyper=getHyper();
  std::vector<axis> axes=hyper->returnAxes(hyper->getNdim());
  for(int i=1; i <= axes.size(); i++){
     int n=axes[i].n; float o=axes[i].o; float d=axes[i].d;
     char label[1024];  std::copy(axes[i].label.begin(), axes[i].label.end(), label); 
    std::string tmp;
    tmp="n"+std::to_string(i); sf_putint(_file,tmp.c_str(),n);
    tmp="o"+std::to_string(i); sf_putfloat(_file,tmp.c_str(),o);
    tmp="d"+std::to_string(i); sf_putfloat(_file,tmp.c_str(),d);
    tmp="label"+std::to_string(i); sf_putstring(_file,tmp.c_str(),label);
  }


}