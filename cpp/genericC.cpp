
#include"genericC.h"
#include "ioModes.h"
#include <string.h>
void initializeIO(int argc,  const int ns1, const int ns2,char *ar){

  std::vector<std::string> aout=fromChar1D(ns1,ns2,ar);
  char **argv=new char* [argc];
  for(int i=0; i < argc; i++){
    argv[i]=new char[aout[i].length()+1];
    std::copy(aout[i].begin(),aout[i].end(),argv[i]);
  }
  
ioModesFortran::setup(argc,argv);
 for(int i=0; i < argc; i++){
    delete [] argv[i];
  }
  delete [] argv;

}
void openRegFile(const char *name,const  char *usg){
    std::shared_ptr<genericIO> io=ioModesFortran::getInstance()->getIO()->getDefaultIO();
    usage_code x;
    if(strcmp("INOUT",usg)==0) x=usageInOut;
    else if(strcmp("OUT",usg)==0) x=usageOut;
    else if(strcmp("IN",usg)==0) x=usageIn;
    else if(strcmp("SCRATCH",usg)==0) x=usageScr;
    std::shared_ptr<genericRegFile> fle=io->getRegFile(std::string(name),x);
}
void openIrregFile(const char *name, const char *usg){
    std::shared_ptr<genericIO>io=ioModesFortran::getInstance()->getIO()->getDefaultIO();
    usage_code x;
    if(strcmp("INOUT",usg)==0) x=usageInOut;
    else if(strcmp("OUT",usg)==0) x=usageOut;
    else if(strcmp("IN",usg)==0) x=usageIn;
    else if(strcmp("SCRATCH",usg)==0) x=usageScr;
    std::shared_ptr<genericIrregFile> fle=io->getIrregFile(std::string(name),x);
}
void closeIO(){
    std::shared_ptr<genericIO> io=ioModesFortran::getInstance()->getIO()->getDefaultIO();
    io->close();
}
void getParamInt(const char *name, int *val,const  bool def){
    std::shared_ptr<paramObj> par=ioModesFortran::getInstance()->getIO()->getDefaultIO()->getParamObj();
    if(def) *val=par->getInt(std::string(name),*val);
    else *val=par->getInt(std::string(name));
}
void getParamFloat(const char *name, float *val,const  bool def){

    std::shared_ptr<paramObj> par=ioModesFortran::getInstance()->getIO()->getDefaultIO()->getParamObj();
    if(def) *val=par->getFloat(std::string(name),*val);
    else *val=par->getFloat(std::string(name));
}
void getParamString(const char *name, char *val, const bool def){
    std::shared_ptr<paramObj> par=ioModesFortran::getInstance()->getIO()->getDefaultIO()->getParamObj();
    std::string x;
    if(def) x=par->getString(std::string(name),std::string(val));
    else x=par->getString(std::string(name));
    std::copy(x.begin(), x.end(), val);
}
void getParamBool(const char *name, bool *val, const bool def){

    std::shared_ptr<paramObj> par=ioModesFortran::getInstance()->getIO()->getDefaultIO()->getParamObj();
    if(def) *val=par->getBool(std::string(name),*val);
    else *val=par->getBool(std::string(name));
}
void getParamInts(const char *name, const int num, int *val, const bool def){
    std::shared_ptr<paramObj> par=ioModesFortran::getInstance()->getIO()->getDefaultIO()->getParamObj();

   if(def){
      std::vector<int> x(val,val+num);
      std::vector<int> y=par->getInts(std::string(name),x);
      for(int i=0; i < std::min(y.size(),x.size()); i++) val[i]=y[i];
   }
   else{
     std::vector<int> y=par->getInts(std::string(name),num);
      for(int i=0; i < std::min((int)y.size(),num); i++) val[i]=y[i];
   }

}
void getParamFloats(const char *name,const int num, float *val,const  bool def){

    std::shared_ptr<paramObj> par=ioModesFortran::getInstance()->getIO()->getDefaultIO()->getParamObj();

   if(def){
      std::vector<float> x(val,val+num);
      std::vector<float> y=par->getFloats(std::string(name),x);
      for(int i=0; i < std::min(y.size(),x.size()); i++) val[i]=y[i];
   }
   else{
     std::vector<float> y=par->getFloats(std::string(name),num);
      for(int i=0; i < std::min((int)y.size(),num); i++) val[i]=y[i];
   }
}
void getFileInt(const char *tag, const char *name, int *val,const  bool def){
    std::shared_ptr<genericIO> io=ioModesFortran::getInstance()->getIO()->getDefaultIO();
    if(io->regFileExists(std::string(name))){
      std::shared_ptr<genericRegFile> par=io->getRegFile(std::string(name));
      if(def) *val=par->getInt(std::string(name),*val);
      else *val=par->getInt(std::string(name));
    }
    else if(io->irregFileExists(std::string(name))){
      std::shared_ptr<genericIrregFile> par=io->getIrregFile(std::string(name));
      if(def) *val=par->getInt(std::string(name),*val);
      else *val=par->getInt(std::string(name));
   }
   else io->getParamObj()->error(std::string(tag)+std::string(" has not been initialized"));

}
void getFileFloat(const char *tag,const  char *name, float *val, const bool def){
    std::shared_ptr<genericIO> io=ioModesFortran::getInstance()->getIO()->getDefaultIO();
    if(io->regFileExists(std::string(name))){
      std::shared_ptr<genericRegFile> par=io->getRegFile(std::string(name));
      if(def) *val=par->getFloat(std::string(name),*val);
      else *val=par->getInt(std::string(name));
    }
    else if(io->irregFileExists(std::string(name))){
      std::shared_ptr<genericIrregFile> par=io->getIrregFile(std::string(name));
      if(def) *val=par->getFloat(std::string(name),*val);
      else *val=par->getInt(std::string(name));
   }
   else io->getParamObj()->error(std::string(tag)+std::string(" has not been initialized"));


}
void getFileString(const char *tag, const char *name, char *val,const  bool def){

    std::shared_ptr<genericIO> io=ioModesFortran::getInstance()->getIO()->getDefaultIO();
    if(io->regFileExists(std::string(name))){
      std::shared_ptr<genericRegFile> par=io->getRegFile(std::string(name));
      std::string x;
      if(def) x=par->getString(std::string(name),std::string(val));
      else x=par->getString(std::string(name));
      std::copy(x.begin(), x.end(), val);
    }
    else if(io->irregFileExists(std::string(name))){
      std::shared_ptr<genericIrregFile> par=io->getIrregFile(std::string(name));
      std::string x;
      if(def) x=par->getString(std::string(name),std::string(val));
      else x=par->getString(std::string(name));
      std::copy(x.begin(), x.end(), val);
   }
   else io->getParamObj()->error(std::string(tag)+std::string(" has not been initialized"));



}
void getFileBool(const char *tag, const char *name, bool *val, const bool def){
    std::shared_ptr<genericIO> io=ioModesFortran::getInstance()->getIO()->getDefaultIO();
    if(io->regFileExists(std::string(name))){
      std::shared_ptr<genericRegFile> par=io->getRegFile(std::string(name));
      if(def) *val=par->getBool(std::string(name),*val);
      else *val=par->getInt(std::string(name));
    }
    else if(io->irregFileExists(std::string(name))){
      std::shared_ptr<genericIrregFile> par=io->getIrregFile(std::string(name));
      if(def) *val=par->getBool(std::string(name),*val);
      else *val=par->getInt(std::string(name));
   }
   else io->getParamObj()->error(std::string(tag)+std::string(" has not been initialized"));



}
void getFileInts(const char *tag, const char *name, const int num, int *val, const bool def){

    std::shared_ptr<genericIO> io=ioModesFortran::getInstance()->getIO()->getDefaultIO();
    if(io->regFileExists(std::string(name))){
       std::shared_ptr<genericRegFile> par=io->getRegFile(std::string(name));
       if(def){
         std::vector<int> x(val,val+num);
         std::vector<int> y=par->getInts(std::string(name),x);
         for(int i=0; i < std::min(y.size(),x.size()); i++) val[i]=y[i];
       }
       else{
         std::vector<int> y=par->getInts(std::string(name),num);
         for(int i=0; i < std::min((int)y.size(),num); i++) val[i]=y[i];
       }
    }
    else if(io->irregFileExists(std::string(name))){
      std::shared_ptr<genericIrregFile> par=io->getIrregFile(std::string(name));
       if(def){
         std::vector<int> x(val,val+num);
         std::vector<int> y=par->getInts(std::string(name),x);
         for(int i=0; i < std::min(y.size(),x.size()); i++) val[i]=y[i];
       }
       else{
         std::vector<int> y=par->getInts(std::string(name),num);
         for(int i=0; i < std::min((int)y.size(),num); i++) val[i]=y[i];
       }
   }
   else io->getParamObj()->error(std::string(tag)+std::string(" has not been initialized"));

}
void getFileFloats(const char *file,const char *name, const int num, float *val,const  bool def){

    std::shared_ptr<genericIO> io=ioModesFortran::getInstance()->getIO()->getDefaultIO();
    if(io->regFileExists(std::string(name))){
       std::shared_ptr<genericRegFile> par=io->getRegFile(std::string(name));
       if(def){
         std::vector<float> x(val,val+num);
         std::vector<float> y=par->getFloats(std::string(name),x);
         for(int i=0; i < std::min(y.size(),x.size()); i++) val[i]=y[i];
       }
       else{
         std::vector<float> y=par->getFloats(std::string(name),num);
         for(int i=0; i < std::min((int)y.size(),num); i++) val[i]=y[i];
       }
    }
    else if(io->irregFileExists(std::string(name))){
      std::shared_ptr<genericIrregFile> par=io->getIrregFile(std::string(name));
       if(def){
         std::vector<float> x(val,val+num);
         std::vector<float> y=par->getFloats(std::string(name),x);
         for(int i=0; i < std::min(y.size(),x.size()); i++) val[i]=y[i];
       }
       else{
         std::vector<float> y=par->getFloats(std::string(name),num);
         for(int i=0; i < std::min((int)y.size(),num); i++) val[i]=y[i];
       }
   }
   else io->getParamObj()->error(std::string(file)+std::string(" has not been initialized"));
}
void putFileInt(const char *tag,const  char *name, const int val){
    std::shared_ptr<genericIO> io=ioModesFortran::getInstance()->getIO()->getDefaultIO();
    if(io->regFileExists(std::string(name))){
      std::shared_ptr<genericRegFile> par=io->getRegFile(std::string(name));
      par->putInt(std::string(name),val);
    }
    else if(io->irregFileExists(std::string(name))){
      std::shared_ptr<genericIrregFile> par=io->getIrregFile(std::string(name));
      par->putInt(std::string(name),val);

   }
   else io->getParamObj()->error(std::string(tag)+std::string(" has not been initialized"));




}
void putFileFloat(const char *tag, const char *name,const  float val){

    std::shared_ptr<genericIO> io=ioModesFortran::getInstance()->getIO()->getDefaultIO();
    if(io->regFileExists(std::string(name))){
      std::shared_ptr<genericRegFile> par=io->getRegFile(std::string(name));
      par->putFloat(std::string(name),val);
    }
    else if(io->irregFileExists(std::string(name))){
      std::shared_ptr<genericIrregFile> par=io->getIrregFile(std::string(name));
      par->putFloat(std::string(name),val);

   }
   else io->getParamObj()->error(std::string(tag)+std::string(" has not been initialized"));





}
void putFileString(const char *tag,const  char *name,const  char *val){

    std::shared_ptr<genericIO> io=ioModesFortran::getInstance()->getIO()->getDefaultIO();
    if(io->regFileExists(std::string(name))){
      std::shared_ptr<genericRegFile> par=io->getRegFile(std::string(name));
      par->putString(std::string(name),std::string(val));
    }
    else if(io->irregFileExists(std::string(name))){
      std::shared_ptr<genericIrregFile> par=io->getIrregFile(std::string(name));
      par->putString(std::string(name),std::string(val));

   }
   else io->getParamObj()->error(std::string(tag)+std::string(" has not been initialized"));
}
void putFileBool(const char *tag,const  char *name, bool val){
    std::shared_ptr<genericIO> io=ioModesFortran::getInstance()->getIO()->getDefaultIO();
    if(io->regFileExists(std::string(name))){
      std::shared_ptr<genericRegFile> par=io->getRegFile(std::string(name));
      par->putBool(std::string(name),val);
    }
    else if(io->irregFileExists(std::string(name))){
      std::shared_ptr<genericIrregFile> par=io->getIrregFile(std::string(name));
      par->putBool(std::string(name),val);

   }
   else io->getParamObj()->error(std::string(tag)+std::string(" has not been initialized"));



}
void putFileInts(const char *tag,const  char *name, const int num, int *val){

    std::vector<int> v(val,val+num);
    std::shared_ptr<genericIO> io=ioModesFortran::getInstance()->getIO()->getDefaultIO();
    if(io->regFileExists(std::string(name))){
      std::shared_ptr<genericRegFile> par=io->getRegFile(std::string(name));
      par->putInts(std::string(name),v);
    }
    else if(io->irregFileExists(std::string(name))){
      std::shared_ptr<genericIrregFile> par=io->getIrregFile(std::string(name));
      par->putInts(std::string(name),v);

   }
   else io->getParamObj()->error(std::string(tag)+std::string(" has not been initialized"));

}
void puFileFloats(const char *file,const char *name,const int num, float *val){

    std::vector<float> v(val,val+num);
    std::shared_ptr<genericIO> io=ioModesFortran::getInstance()->getIO()->getDefaultIO();
    if(io->regFileExists(std::string(name))){
      std::shared_ptr<genericRegFile> par=io->getRegFile(std::string(name));
      par->putFloats(std::string(name),v);
    }
    else if(io->irregFileExists(std::string(name))){
      std::shared_ptr<genericIrregFile> par=io->getIrregFile(std::string(name));
      par->putFloats(std::string(name),v);

   }
   else io->getParamObj()->error(std::string(file)+std::string(" has not been initialized"));

}

void readFloatStream(const char *tag,const  long long npts, float *array){
    std::shared_ptr<genericIO> io=ioModesFortran::getInstance()->getIO()->getDefaultIO();

    if(io->regFileExists(std::string(tag))){
      std::shared_ptr<genericRegFile> par=io->getRegFile(std::string(tag));
      par->readFloatStream(npts,array);
            par->setDataType(dataFloat);

   }
    else if(io->irregFileExists(std::string(tag))){
      std::shared_ptr<genericIrregFile> par=io->getIrregFile(std::string(tag));
      par->readFloatStream(npts,array);
            par->setDataType(dataFloat);

  }
  else io->getParamObj()->error(std::string(tag)+std::string(" has not been initialized"));
}
void writeFloatStream(const char *tag,const  long long npts, const float *array){
    std::shared_ptr<genericIO> io=ioModesFortran::getInstance()->getIO()->getDefaultIO();

    if(io->regFileExists(std::string(tag))){
      std::shared_ptr<genericRegFile> par=io->getRegFile(std::string(tag));
      par->writeFloatStream(npts,array);
            par->setDataType(dataFloat);

   }
    else if(io->irregFileExists(std::string(tag))){
      std::shared_ptr<genericIrregFile> par=io->getIrregFile(std::string(tag));
      par->writeFloatStream(npts,array);
            par->setDataType(dataFloat);

  }
  else io->getParamObj()->error(std::string(tag)+std::string(" has not been initialized"));
}
void readFloatWindow(const char *tag,const  int ndim,const  int *nw,const  int *fw, const int *jw, float *ar){
  std::vector<int> n_w(nw,nw+ndim),f_w(fw,fw+ndim);
  std::vector<int>  j_w(jw,jw+ndim);

     std::shared_ptr<genericIO> io=ioModesFortran::getInstance()->getIO()->getDefaultIO();
    if(io->regFileExists(std::string(tag))){
      std::shared_ptr<genericRegFile> par=io->getRegFile(std::string(tag));
      par->readFloatWindow(n_w,f_w,j_w,ar);
            par->setDataType(dataFloat);

   }
    else if(io->irregFileExists(std::string(tag))){
      std::shared_ptr<genericIrregFile> par=io->getIrregFile(std::string(tag));
      par->readFloatWindow(n_w,f_w,j_w,ar);
            par->setDataType(dataFloat);

   }
   else io->getParamObj()->error(std::string(tag)+std::string(" has not been initialized"));

}
void writeFloatWindow(const char *tag, const int ndim,const  int *nw,const  int *fw, const int *jw, const float *ar){

  std::vector<int> n_w(nw,nw+ndim),f_w(fw,fw+ndim), j_w(jw,jw+ndim);
     std::shared_ptr<genericIO> io=ioModesFortran::getInstance()->getIO()->getDefaultIO();
    if(io->regFileExists(std::string(tag))){
      std::shared_ptr<genericRegFile> par=io->getRegFile(std::string(tag));
      par->writeFloatWindow(n_w,f_w,j_w,ar);
       par->setDataType(dataFloat);
   }
    else if(io->irregFileExists(std::string(tag))){
      std::shared_ptr<genericIrregFile> par=io->getIrregFile(std::string(tag));
      par->writeFloatWindow(n_w,f_w,j_w,ar);   
       par->setDataType(dataFloat);
   }
   else io->getParamObj()->error(std::string(tag)+std::string(" has not been initialized"));
}
void readDescription(const char *tag){
    std::shared_ptr<genericIO> io=ioModesFortran::getInstance()->getIO()->getDefaultIO();

   if(io->regFileExists(std::string(tag))){
      io->getRegFile(std::string(tag))->readDescription();
      
   }
   else if(io->irregFileExists(std::string(tag))){
      io->getIrregFile(std::string(tag))->readDescription();
  }
  else io->getParamObj()->error(std::string(tag)+std::string(" has not been initialized"));
}
void writeDescription(const char *tag){
    std::shared_ptr<genericIO> io=ioModesFortran::getInstance()->getIO()->getDefaultIO();

   if(io->regFileExists(std::string(tag))){
      io->getRegFile(std::string(tag))->writeDescription();
      
   }
   else if(io->irregFileExists(std::string(tag))){
      io->getIrregFile(std::string(tag))->writeDescription();
  }
  else io->getParamObj()->error(std::string(tag)+std::string(" has not been initialized"));
}
void getDataType(const char *tag, char *typ){
    std::shared_ptr<genericIO> io=ioModesFortran::getInstance()->getIO()->getDefaultIO();

   dataType x;
   if(io->regFileExists(std::string(tag))){
      x=io->getRegFile(std::string(tag))->getDataType();
      
   }
   else if(io->irregFileExists(std::string(tag))){
      x=io->getIrregFile(std::string(tag))->getDataType();
  }
  else io->getParamObj()->error(std::string(tag)+std::string(" has not been initialized"));
  switch(x){
    case dataFloat:
      strcpy(typ,"Float");
      break;
     case dataComplex:
      strcpy(typ,"Complex");
      break;
    case dataByte:
          strcpy(typ,"Byte");
      break;
    case dataShort:
          strcpy(typ,"Short");
      break;
    case dataInt:
          strcpy(typ,"Int");
      break;
    case dataUndefined:
          strcpy(typ,"Undefined");
      break;
      
  }

}
void setDataType(const char *tag, const char *typ){
     std::shared_ptr<genericIO> io=ioModesFortran::getInstance()->getIO()->getDefaultIO();

  dataType t;
  if(strcmp(typ,"Float")==0)  t=dataFloat;
  else if(strcmp(typ,"Byte")==0)  t=dataByte;
  else if(strcmp(typ,"Complex")==0)  t=dataComplex;
  else if(strcmp(typ,"Short")==0)  t=dataShort;
  else if(strcmp(typ,"Int")==0)  t=dataInt;
  else if(strcmp(typ,"Undefined")==0)  t=dataUndefined;
   if(io->regFileExists(std::string(tag))){
     io->getRegFile(std::string(tag))->setDataType(t);
      
   }
   else if(io->irregFileExists(std::string(tag))){
     io->getIrregFile(std::string(tag))->setDataType(t);
  }
  else io->getParamObj()->error(std::string(tag)+std::string(" has not been initialized"));
      
  }
void cError( const char *err){
     ioModesFortran::getInstance()->getIO()->getDefaultIO()->getParamObj()->error(std::string(err));


  }
void getHyper(const char *tag,const int ndimin, int *ndimout, int *n, float *o, float *d, const int ns1, const int ns2, char *big){

     std::shared_ptr<genericIO> io=ioModesFortran::getInstance()->getIO()->getDefaultIO();
     std::shared_ptr<hypercube> h;
    if(io->regFileExists(std::string(tag))){
      std::shared_ptr<genericRegFile> par=io->getRegFile(std::string(tag));
      h=par->getHyper();
   }
    else if(io->irregFileExists(std::string(tag))){
      std::shared_ptr<genericIrregFile> par=io->getIrregFile(std::string(tag));
      h=par->getHyper();
   }
   else io->getParamObj()->error(std::string(tag)+std::string(" has not been initialized"));

   int ndim=h->getNdim();
   std::vector<std::string> labels;
   if(ndim > ndimin) io->getParamObj()->error(std::string(tag)+std::string(" has ")+std::to_string(ndim)+" only provided space for "+std::to_string(ndimin));
   for(int i=0; i < ndim; i++){
     axis a=h->getAxis(i);
     n[i]=a.n; o[i]=a.o; d[i]=a.d;
     labels.push_back(a.label);
   }
   toChar1D(labels,ns1,ns2,big);
   *ndimout=ndim;
}
void setHyper(const char *tag,const int ndim,const  int *n,const  float *o, const float *d,const  int ns1, const int ns2, const char *lin){
   std::vector<axis> axes;
   
   
   std::vector<std::string> label=fromChar1D(ns1,ns2,lin);
   
   for(int i=0; i < ndim; i++)
      axes.push_back(axis(n[i],o[i],d[i],std::string(label[i])));
   std::shared_ptr<hypercube> h(new hypercube(axes));
   std::shared_ptr<genericIO> io=ioModesFortran::getInstance()->getIO()->getDefaultIO();
   if(io->regFileExists(std::string(tag))){
      std::shared_ptr<genericRegFile> par=io->getRegFile(std::string(tag));
      par->setHyper(h);
   }
    else if(io->irregFileExists(std::string(tag))){
      std::shared_ptr<genericIrregFile> par=io->getIrregFile(std::string(tag));
      par->setHyper(h);
   }
   else io->getParamObj()->error(std::string(tag)+std::string(" has not been initialized"));
}
std::vector<std::string> fromChar1D(const int n1,const  int n2,const  char *val){
   std::vector<std::string> out;
   for(int i2=0; i2< n2;i2++){
    int i1=0; while(val[i2*n1+i1]!='\0') i1++;
    out.push_back(std::string(val+i2*n1,val+i2*n1+i1));
   }
   return out;

}
void toChar1D(const std::vector<std::string> in,const  int n1,const  int n2, char *val){
   for(int i2=0; i2 < n2;i2++){
      std::copy(in[i2].begin(),in[i2].end(),&val[i2*n1]);
      for(int i1=i2*n1+in[i2].length(); i2 < n1+i2*n1; i2++) val[i1]='\0';
    }

}

void readComplexStream(const char *tag,const  long long npts, float  _Complex *array){
    std::shared_ptr<genericIO> io=ioModesFortran::getInstance()->getIO()->getDefaultIO();
            

    if(io->regFileExists(std::string(tag))){
      std::shared_ptr<genericRegFile> par=io->getRegFile(std::string(tag));
      par->readComplexStream(npts,array);
      par->setDataType(dataComplex);
   }
    else if(io->irregFileExists(std::string(tag))){
      std::shared_ptr<genericIrregFile> par=io->getIrregFile(std::string(tag));
      par->readComplexStream(npts,array);
        par->setDataType(dataComplex);
  }
  else io->getParamObj()->error(std::string(tag)+std::string(" has not been initialized"));
}
void writeComplexStream(const char *tag,const  long long npts, const float  _Complex *array){
    std::shared_ptr<genericIO> io=ioModesFortran::getInstance()->getIO()->getDefaultIO();
    if(io->regFileExists(std::string(tag))){
           

      std::shared_ptr<genericRegFile> par=io->getRegFile(std::string(tag));
      par->writeComplexStream(npts,array);
      par->setDataType(dataComplex);
   }
    else if(io->irregFileExists(std::string(tag))){
      std::shared_ptr<genericIrregFile> par=io->getIrregFile(std::string(tag));
      par->writeComplexStream(npts,array);
      par->setDataType(dataComplex);
  }
  else io->getParamObj()->error(std::string(tag)+std::string(" has not been initialized"));
}
void readComplexWindow(const char *tag,const  int ndim,const  int *nw,const  int *fw, const int *jw, float  _Complex *ar){
  std::vector<int> n_w(nw,nw+ndim),f_w(fw,fw+ndim);
  std::vector<int>  j_w(jw,jw+ndim);

     std::shared_ptr<genericIO> io=ioModesFortran::getInstance()->getIO()->getDefaultIO();
    if(io->regFileExists(std::string(tag))){
      std::shared_ptr<genericRegFile> par=io->getRegFile(std::string(tag));
      par->readComplexWindow(n_w,f_w,j_w,ar);
      par->setDataType(dataComplex);

   }
    else if(io->irregFileExists(std::string(tag))){
      std::shared_ptr<genericIrregFile> par=io->getIrregFile(std::string(tag));
      par->readComplexWindow(n_w,f_w,j_w,ar); 
            par->setDataType(dataComplex);
  
   }
   else io->getParamObj()->error(std::string(tag)+std::string(" has not been initialized"));

}
void writeComplexWindow(const char *tag, const int ndim,const  int *nw,const  int *fw, const int *jw, const float _Complex *ar){
  std::vector<int> n_w(nw,nw+ndim),f_w(fw,fw+ndim), j_w(jw,jw+ndim);

     std::shared_ptr<genericIO> io=ioModesFortran::getInstance()->getIO()->getDefaultIO();
    if(io->regFileExists(std::string(tag))){
      std::shared_ptr<genericRegFile> par=io->getRegFile(std::string(tag));
      par->writeComplexWindow(n_w,f_w,j_w,ar);
            par->setDataType(dataComplex);

   }
    else if(io->irregFileExists(std::string(tag))){
      std::shared_ptr<genericIrregFile> par=io->getIrregFile(std::string(tag));
      par->writeComplexWindow(n_w,f_w,j_w,ar);   
            par->setDataType(dataComplex);

   }
   else io->getParamObj()->error(std::string(tag)+std::string(" has not been initialized"));
}

