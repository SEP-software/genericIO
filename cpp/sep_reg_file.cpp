#include "sep_reg_file.h"
extern "C" {
#include "seplib.h"
#include "sep3d.h"
}

sepRegFile::sepRegFile(const std::string tag,usage_code usage){
 _tag=tag;
 switch(usage){
    case usageIn:
      if(_tag!="in")
        if(0==auxin(_tag.c_str())) error(std::string("can not open file ")+tag);
        readDescription();
        break;
    case usageOut:
       if(tag!="out")
          if(0==auxout(_tag.c_str())) error(std::string("can not open file ")+tag);
        break;
    case usageInOut:
       if(0==auxinout(_tag.c_str())) error(std::string("can not open file ")+tag);
       break;
    case usageScr:
      if(0==auxscr(_tag.c_str())) error(std::string("can not open file ")+tag);
      break;
      default:
      error("can't handle type");
  }
 
}

int sepRegFile::getInt(const std::string arg){
    int x;
    if(0==auxpar(arg.c_str(),"d",&x,_tag.c_str()))
      error(std::string("trouble grabbing parameter ")+arg+std::string(" from parameters"));
    return x;
}
int sepRegFile::getInt(const std::string arg, const int def){
   int x=def;
   int i=auxpar(arg.c_str(),"d",&x,_tag.c_str());
   return x;
}
   
float sepRegFile::getFloat(const std::string arg, const float def){
  float x=def;
fprintf(stderr,"in this %s %s \n",arg.c_str(),_tag.c_str());
  int i=auxpar(arg.c_str(),"f",&x,_tag.c_str());
  return x;

}
float sepRegFile::getFloat(const std::string arg){
  float x;
  if(0==auxpar(arg.c_str(),"f",&x,_tag.c_str()))
     error(std::string("trouble grabbing parameter ")+arg+std::string(" from parameters"));
  return x;
}
   
std::string sepRegFile::getString(const std::string arg){
  char buf[10000];
  if(0==auxpar(arg.c_str(),"s",buf,_tag.c_str()))
      error(std::string("trouble grabbing parameter ")+arg+std::string(" from parameters"));
  return std::string(buf);


}
std::string sepRegFile::getString(const std::string arg, const std::string def){

  char buf[10000];
  std::copy(def.begin(), def.end(), buf);
  int i=auxpar(arg.c_str(),"s",buf,_tag.c_str());
  return std::string(buf);

}
 
bool sepRegFile::getBool(const std::string arg, const bool def){
  bool x=def;
  int i=auxpar(arg.c_str(),"l",&x,_tag.c_str());
  return x;

}
bool sepRegFile::getBool(const std::string arg){
 bool x;
  if(0==auxpar(arg.c_str(),"l",&x,_tag.c_str())){
    error(std::string("trouble grabbing parameter ")+arg+std::string(" from parameters"));
  }
  return x;

}
   
   
std::vector<int> sepRegFile::getInts(const std::string arg,int num){
  int tmp[10000];
  int ierr=auxpar(arg.c_str(),"d",tmp,_tag.c_str());
  if(ierr==0) 
     error(std::string("trouble grabbing parameter ")+arg+std::string(" from parameters"));
  std::vector<int> x;
  for(int i=0; i < ierr; i++) x.push_back(tmp[i]);
  return x;
}
std::vector<int> sepRegFile::getInts(const std::string arg,std::vector<int> defs){
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
     
std::vector<float> sepRegFile::getFloats(const std::string arg, int num){
  float tmp[10000];
  int ierr=auxpar(arg.c_str(),"f",tmp,_tag.c_str());
  if(ierr==0) 
     error(std::string("trouble grabbing parameter ")+arg+std::string(" from parameters"));
  std::vector<float> x;
  for(int i=0; i < ierr; i++) x.push_back(tmp[i]);
  return x;


}
std::vector<float> sepRegFile::getFloats(const std::string arg,std::vector<float> defs){

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


void sepRegFile::error(const std::string err){
   seperr(err.c_str());
}
    
void sepRegFile::putInt(const std::string par, const int val){

   auxputch(par.c_str(),"d",&val,_tag.c_str());

}
void sepRegFile::putFloat(const std::string par, const float val){

   auxputch(par.c_str(),"f",&val,_tag.c_str());
}
void sepRegFile::putString(const std::string par, const std::string val){
  auxputch(par.c_str(),"s",val.c_str(),_tag.c_str());
}

void sepRegFile::putBool(const std::string par, const bool val){
   int x=0;
   if(val) x=1;
   auxputch(par.c_str(),"l",&x,_tag.c_str());    

}
void sepRegFile::putInts(const std::string par, const  std::vector<int> val){
   int *tmp=new int[val.size()];
   for(int i=0; i < val.size(); i++) tmp[i]=val[i];
   auxputch(par.c_str(),"d",tmp,_tag.c_str());
   delete [] tmp;
}
void sepRegFile::putFloats(const std::string par, const std::vector<float> val){
   float *tmp=new float[val.size()];
   for(int i=0; i < val.size(); i++) tmp[i]=val[i];
   auxputch(par.c_str(),"f",tmp,_tag.c_str());
   delete [] tmp;

}
void sepRegFile::readFloatStream( float *array,const long long npts){ 
   long long maxsize=10000000;
   long long nread=0;
   long long nptsT=npts*4;
   while(nptsT >nread){
      long long toReadL=std::min(maxsize,nptsT-nread);
      int ierr=sreed(_tag.c_str(),&array[nread],(int)toReadL);
      nread+=(long long)ierr;
      if(ierr!=toReadL)
        error(std::string("Trouble reading from ")+_tag+std::string(" after ")+
          std::to_string(nread)+std::string(" bytes"));
  }   

}
void sepRegFile::readComplexStream( float _Complex *array,const long long npts){ 
   long long maxsize=10000000;
   long long nread=0;
   long long nptsT=npts*8;
        setDataType(dataComplex);

   while(nptsT >nread){
      long long toReadL=std::min(maxsize,nptsT-nread);
      int ierr=sreed(_tag.c_str(),&array[nread],(int)toReadL);
      nread+=(long long)ierr;
      if(ierr!=toReadL)
        error(std::string("Trouble reading from ")+_tag+std::string(" after ")+
          std::to_string(nread)+std::string(" bytes"));
  }   

}
void sepRegFile::readUCharStream( unsigned char *array,const long long npts){ 
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

void sepRegFile::writeFloatStream( const float *array,const long long npts){
   long long maxsize=10000000;
   long long nwrite=0;
   long long nptsT=npts*4;
     setDataType(dataFloat);

   while(nptsT >nwrite){
      long long toWriteL=std::min(maxsize,nptsT-nwrite);
      int ierr=sreed(_tag.c_str(),(void*)(array+nwrite),(int)toWriteL);
      nwrite+=(long long)ierr;
      if(ierr!=toWriteL)
        error(std::string("Trouble reading from ")+_tag+std::string(" after ")+std::to_string(nwrite)+std::string(" bytes"));
  }   

}
 void sepRegFile::readFloatWindow(const std::vector<int> nw, const std::vector<int> fw, 
      const std::vector<int> jw,  float *array){
  std::shared_ptr<hypercube> hyper=getHyper();
  std::vector<int> ng=hyper->returnNs();
  
       setDataType(dataFloat);

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

 void sepRegFile::readComplexWindow(const std::vector<int> nw, const std::vector<int> fw, 
      const std::vector<int> jw,  float _Complex *array){
  std::shared_ptr<hypercube> hyper=getHyper();
       setDataType(dataComplex);

  std::vector<int> ng=hyper->returnNs();
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
    jw.data(),8,array))
   error(std::string("trouble reading data from tag ")+_tag);
    
}

void sepRegFile::writeComplexStream( const float _Complex *array,const long long npts){
   long long maxsize=10000000;
   long long nwrite=0;
   long long nptsT=npts*8;
     setDataType(dataComplex);

   while(nptsT >nwrite){
      long long toWriteL=std::min(maxsize,nptsT-nwrite);
      int ierr=sreed(_tag.c_str(),(void*)(array+nwrite),(int)toWriteL);
      nwrite+=(long long)ierr;
      if(ierr!=toWriteL)
        error(std::string("Trouble reading from ")+_tag+std::string(" after ")+std::to_string(nwrite)+std::string(" bytes"));
  }   

}

 void sepRegFile::writeComplexWindow(const std::vector<int> nw, const std::vector<int> fw, 
      const std::vector<int> jw, float _Complex *array){
        setDataType(dataComplex);

  std::shared_ptr<hypercube> hyper=getHyper();
  std::vector<int> ng=hyper->returnNs();
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
    jw.data(),8,array))
   error(std::string("trouble writing data to tag ")+_tag);  
      
}

 void sepRegFile::readUCharWindow(const std::vector<int> nw, const std::vector<int> fw, 
      const std::vector<int> jw,  unsigned char *array){
  std::shared_ptr<hypercube> hyper=getHyper();
  std::vector<int> ng=hyper->returnNs();
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
    jw.data(),1,array))
   error(std::string("trouble reading data from tag ")+_tag);
    
}
 void sepRegFile::writeFloatWindow(const std::vector<int> nw, const std::vector<int> fw, 
      const std::vector<int> jw, float *array){
        setDataType(dataFloat);

  std::shared_ptr<hypercube> hyper=getHyper();
  std::vector<int> ng=hyper->returnNs();
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
void sepRegFile::readDescription(){
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
  std::shared_ptr<hypercube> hyper(new hypercube(axes));
  setHyper(hyper);
   int esize=getInt("esize",4);
  if(esize==1) setDataType(dataByte);
  else if(esize==4){
     std::string format=getString(std::string("data_format"),
        std::string("xdr_float"));
     if(format==std::string("xdr_float") ||
       format==std::string("native_float")) setDataType(dataFloat);
     else if (format==std::string("xdr_int") ||
       format==std::string("native_int")) setDataType(dataInt);
     else
       error(std::string("Unknown data type "+format));
  }
  else
    error(std::string("Only know about esize=4 or 1"));
}
void sepRegFile::writeDescription(){
  std::shared_ptr<hypercube> hyper=getHyper();
  std::vector<axis> axes=hyper->returnAxes(hyper->getNdim());
  for(int i=1; i <= axes.size(); i++){
     int n=axes[i].n; float o=axes[i].o; float d=axes[i].d;
     char label[1024];  std::copy(axes[i].label.begin(), axes[i].label.end(), label);
     sep_put_data_axis_par(_tag.c_str(),&i,&n,&o,&d,label);
  }


}
