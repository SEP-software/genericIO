#include "jsonGenericFile.h"
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
#include <exception>

jsonGenericFile::jsonGenericFile(std::shared_ptr<Json::Value> arg, usage_code usage,std::string tag, int reelH,int traceH){
  setupJson(arg,tag);
  _reelH=reelH;
  _traceH=traceH;
  _usage=usage;
  if(usage==usageIn){
    readDescription();
    std::shared_ptr<myFileIO> x(new myFileIO(getFileName(),usage,reelH,traceH,
     jsonArgs.get("esize",4).asInt(),getHyper()));
    myio=x;  
  }
  else{
  
  
  }
  
}
void jsonGenericFile::setupJson(std::shared_ptr<Json::Value> arg,std::string tag){
   if((*arg)[tag].isNull())
     error(std::string("can't find tag "+tag+" in JSON parameters"));
   _tag=tag;
   jsonArgs=(*arg)[tag];
}
std::string jsonGenericFile::getFileName(){

 if(jsonArgs["filename"].isNull())
       error(std::string("filename is not set in for tag ")+_tag);
  jsonArgs.get("filename","null").asString();
}
int jsonGenericFile::getInt(const std::string arg){
    int x;
    if(jsonArgs[arg].isNull())  
      error(std::string("trouble grabbing parameter ")+arg+std::string(" from parameters"));
     x=jsonArgs.get(arg,1).asInt();
    return x;
}
int jsonGenericFile::getInt(const std::string arg, const int def){
   int x=jsonArgs.get(arg,def).asInt();
   return x;
}
float jsonGenericFile::getFloat(const std::string arg, const float def){
  float x;
  x= jsonArgs.get(arg,def).asFloat();
  return x;

}
float jsonGenericFile::getFloat(const std::string arg){
  float x;
 if(jsonArgs[arg].isNull())  
      error(std::string("trouble grabbing parameter ")+arg+std::string(" from parameters"));
  x=jsonArgs.get(arg,1.).asFloat();
  return x;
}
std::string jsonGenericFile::getString(const std::string arg){
   if(jsonArgs[arg].isNull())  
      error(std::string("trouble grabbing parameter ")+arg+std::string(" from parameters"));
 
  return jsonArgs.get(arg,"").asString();


}
std::string jsonGenericFile::getString(const std::string arg, const std::string def){

  return  jsonArgs.get(arg,def).asString();

}
bool jsonGenericFile::getBool(const std::string arg,  bool def){
 return  jsonArgs.get(arg,def).asBool();
}
bool jsonGenericFile::getBool(const std::string arg){
  if(jsonArgs[arg].isNull())  
      error(std::string("trouble grabbing parameter ")+arg+std::string(" from parameters"));
  jsonArgs.get(arg,false).asBool();
}
std::vector<int> jsonGenericFile::getInts(const std::string arg,int nvals){
   if(jsonArgs[arg].isNull())  
    error(std::string("trouble grabbing parameter ")+arg+std::string(" from parameters"));
  const Json::Value vals = jsonArgs[arg];
  
  std::vector<int> x;
  for(int i=0; i < nvals; i++) x.push_back(vals[i].asInt());
  return x;
}
std::vector<int> jsonGenericFile::getInts(const std::string arg,std::vector<int> defs){
  std::vector<int> x;
   if(jsonArgs[arg].isNull())  {
     for(int i=0; i < defs.size(); i++) x.push_back(defs[i]);
  }
  else{
     const Json::Value vals = jsonArgs[arg];
      for(int i=0; i < defs.size(); i++) x.push_back(vals[i].asInt());
  }
  return x;
} 
std::vector<float> jsonGenericFile::getFloats(const std::string arg,int nvals){
  if(jsonArgs[arg].isNull())    
    error(std::string("trouble grabbing parameter ")+arg+std::string(" from parameters"));
  const Json::Value vals = jsonArgs[arg];
  
  std::vector<float> x;
  for(int i=0; i < nvals; i++) x.push_back(vals[i].asFloat());
  return x;

}
std::vector<float> jsonGenericFile::getFloats(const std::string arg,std::vector<float> defs){
  std::vector<float> x;
   if(jsonArgs[arg].isNull())   {
     for(int i=0; i < defs.size(); i++) x.push_back(defs[i]);
  }
  else{
     const Json::Value vals = jsonArgs[arg];
      for(int i=0; i < defs.size(); i++) x.push_back(vals[i].asFloat());
  }
  return x;

}
void jsonGenericFile::error(const std::string errm){
   std::cerr<<errm<<std::endl;
   throw std::exception();
}
void jsonGenericFile::putInt(const std::string par, const int val){
   jsonArgs[par]=val;
}
void jsonGenericFile::putFloat(const std::string par, const float val){
   jsonArgs[par]=val;

}
void jsonGenericFile::putString(const std::string par, const std::string val){
   jsonArgs[par]=val;

}
void jsonGenericFile::putBool(const std::string par, const bool val){
   jsonArgs[par]=val;


}
void jsonGenericFile::putInts(const std::string par, const  std::vector<int> val){
   Json::Value vals;
   for(int i =0; i < val.size(); i++) vals.append(val[i]);
   jsonArgs[par]=vals;

}
void jsonGenericFile::putFloats(const std::string par, const std::vector<float> val){
   Json::Value vals;
   for(int i =0; i < val.size(); i++) vals.append(val[i]);
   jsonArgs[par]=vals;
}
void jsonGenericFile::readDescription(){
  int ndim;
  bool breakIt=false;
  int iax=9;
  while(iax >=1 && !breakIt){
    std::string tmp;
    int n=getInt("n"+std::to_string(iax),1);
    if(n>1)  breakIt=true;
    iax--;
  }
  if(iax==0) error("couldn't find any axes");
  ndim=iax;
  std::vector<axis> axes;
  for(int i=1; i <= ndim; i++){
    int n=getInt(std::string("n")+std::to_string(i),1);
    float o=getFloat(std::string("o")+std::to_string(i),0.);
    float d=getFloat(std::string("d")+std::to_string(i),1.);
    std::string label=getString(std::string("label")+std::to_string(i),"");
    axes.push_back(axis(n,o,d,label));
    
  }
  std::shared_ptr<hypercube> hyper(new hypercube(axes));
  setHyper(hyper);
}
void jsonGenericFile::writeDescription(){
  std::shared_ptr<hypercube> hyper=getHyper();
  std::vector<axis> axes=hyper->returnAxes(hyper->getNdim());
  for(int i=1; i <= axes.size(); i++){
    putInt(std::string("n")+std::to_string(i),axes[i].n);
    putFloat(std::string("o")+std::to_string(i),axes[i].o);
    putFloat(std::string("d")+std::to_string(i),axes[i].d);
    putString(std::string("label")+std::to_string(i),axes[i].label);
  }


}
void jsonGenericFile::close(){

  myio->close();

}
void jsonGenericFile::readFloatStream( float *array,const long long npts){ 
   long long maxsize=10000000;
   long long nread=0;
   long long nptsT=npts*4;
   if(!myio){
     std::shared_ptr<myFileIO> iox(new myFileIO(getFileName(),_usage,_reelH,_traceH,4,getHyper()));
     myio=iox;
  }
  myio->readTraceStream(npts,array);


}
void jsonGenericFile::readUCharStream( unsigned char *array,const long long npts){ 
   long long maxsize=10000000;
   long long nread=0;
   if(!myio){
     std::shared_ptr<myFileIO> iox(new myFileIO(getFileName(),_usage,_reelH,_traceH,1,getHyper()));
     myio=iox;
  }
  myio->readTraceStream(npts,array);


}

void jsonGenericFile::writeFloatStream( const float *array,const long long npts){
   long long maxsize=10000000;
   long long nwrite=0;
   long long nptsT=npts*4;
     setDataType(dataFloat);

   if(!myio){
     std::shared_ptr<myFileIO> iox(new myFileIO(getFileName(),_usage,_reelH,_traceH,4,getHyper()));
     myio=iox;
  }
  myio->writeTraceStream(npts,array);
}
 void jsonGenericFile::readFloatWindow(const std::vector<int> nw, const std::vector<int> fw, 
      const std::vector<int> jw,  float *array){
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
   if(!myio){
     std::shared_ptr<myFileIO> iox(new myFileIO(getFileName(),_usage,_reelH,_traceH,4,getHyper()));
     myio=iox;
  }
  myio->readWindow(nw,fw,jw,array);

    
}

 void jsonGenericFile::readUCharWindow(const std::vector<int> nw, const std::vector<int> fw, 
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
   if(!myio){
     std::shared_ptr<myFileIO> iox(new myFileIO(getFileName(),_usage,_reelH,_traceH,1,getHyper()));
     myio=iox;
  }
  myio->readWindow(nw,fw,jw,array);
    
}
 void jsonGenericFile::writeFloatWindow(const std::vector<int> nw, const std::vector<int> fw, 
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
   if(!myio){
     std::shared_ptr<myFileIO> iox(new myFileIO(getFileName(),_usage,_reelH,_traceH,4,getHyper()));
     myio=iox;
  }
  myio->writeWindow(nw,fw,jw,array);
      
}

    
    
void jsonGenericFile::readComplexStream( float _Complex *array,const long long npts){ 
   long long maxsize=10000000;
   long long nread=0;
   long long nptsT=npts*4;
        setDataType(dataComplex);

   if(!myio){
     std::shared_ptr<myFileIO> iox(new myFileIO(getFileName(),_usage,_reelH,_traceH,8,getHyper()));
     myio=iox;
  }
  myio->readTraceStream(npts,array);


}    
 void jsonGenericFile::writeComplexStream( const float  _Complex *array,const long long npts){
   long long maxsize=10000000;
   long long nwrite=0;
   long long nptsT=npts*4;
        setDataType(dataComplex);

   if(!myio){
     std::shared_ptr<myFileIO> iox(new myFileIO(getFileName(),_usage,_reelH,_traceH,8,getHyper()));
     myio=iox;
  }
  myio->writeTraceStream(npts,array);
}
 void jsonGenericFile::readComplexWindow(const std::vector<int> nw, const std::vector<int> fw, 
      const std::vector<int> jw,  float _Complex  *array){
  std::shared_ptr<hypercube> hyper=getHyper();
  std::vector<int> ng=hyper->returnNs();
          setDataType(dataComplex);

  if(ng.size() >nw.size()){
    for(int i=nw.size(); i < ng.size(); i++){
      if(ng[i]>1) error("number of dimension does not equal data size");
    }
  }
  if(nw.size()< ng.size() || fw.size() < ng.size() || jw.size()< jw.size()){
     error("number of dimensions does not equal data size");
  }
   if(!myio){
     std::shared_ptr<myFileIO> iox(new myFileIO(getFileName(),_usage,_reelH,_traceH,8,getHyper()));
     myio=iox;
  }
  myio->readWindow(nw,fw,jw,array);

    
}
 void jsonGenericFile::writeComplexWindow(const std::vector<int> nw, const std::vector<int> fw, 
      const std::vector<int> jw, float  _Complex *array){
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
   if(!myio){
     std::shared_ptr<myFileIO> iox(new myFileIO(getFileName(),_usage,_reelH,_traceH,8,getHyper()));
     myio=iox;
  }
  myio->writeWindow(nw,fw,jw,array);
      
}