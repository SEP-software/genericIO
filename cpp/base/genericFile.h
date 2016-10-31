#ifndef GENERIC_FILE 
#define GENERIC_FILE 1
#include<vector>
#include "paramObj.h"
#include "hypercube.h"
#include<memory>

enum usage_code {
    usageIn,
    usageOut,
    usageInOut,
    usageScr
};
enum dataType{
   dataFloat,
   dataByte,
   dataShort,
   dataInt,
   dataUndefined
};


class genericRegFile: public paramObj{
  public:
    genericRegFile(){ _type=dataUndefined;}
    
    virtual void putInt(const std::string par, const int val) ;
    virtual void putFloat(const std::string par, const float val){if(par=="" && val==0){;}}
    virtual void putString(const std::string par, const std::string val){if(par=="" && val==""){;}}
    virtual void putBool(const std::string par, const bool val){if(par=="" && val==0) {;}}
    virtual void putInts(const std::string par, const  std::vector<int> val){if(par=="" && val[0]==0){;}}
    virtual void putFloats(const std::string par, const std::vector<float> val) {if(par=="" && val[0]==0){;}}
    virtual void readUCharStream(const long long npts, unsigned char *array){ if(npts==0 && array==0){;}}
    virtual void readFloatStream(const long long npts, float *array){ if(npts==0 && array==0){;}}
    virtual void writeFloatStream(const long long npts, const float *array){if(npts==0 && array==0){;}}
    virtual void readUCharWindow(const std::vector<int> nw, const std::vector<int> fw,
      const std::vector<int> jw, unsigned char *array){
              if(nw[0]==0 && fw[0]==0 && jw[0]==0 && array==0){;}
    }
    virtual void readFloatWindow(const std::vector<int> nw, const std::vector<int> fw, 
      const std::vector<int> jw,  float *array){
        if(nw[0]==0 && fw[0]==0 && jw[0]==0 && array==0){;}}
    virtual void writeFloatWindow(const std::vector<int> nw, const std::vector<int> fw, 
      const std::vector<int> jw, const float *array){
        if(nw[0]==0 && fw[0]==0 && jw[0]==0 && array==0){;}}
    virtual void readDescription(){ ;}
    virtual void writeDescription(){;}
    virtual void close(){;}
    void setHyper(std::shared_ptr<hypercube> hyp){
      _hyper=hyp;
    }
    dataType getDataType(){return _type;}
    void setDataType(dataType typ){ _type=typ;}
    std::shared_ptr<hypercube> getHyper(){
      if(!_hyper) readDescription();
      return _hyper;
    }
  protected:
    std::shared_ptr<hypercube> _hyper;
    dataType _type;
};

union headerType{
  int i;
  short s;
  long long l;
  double d;
  float f;
};
class genericIrregFile: public genericRegFile{
  public:
  genericIrregFile(){}
  virtual int getHeaderIndex(std::string keyname){
  if(keyname==std::string("")){;}
  return 0;}
  virtual std::vector<headerType> getTraceHeader(long long index){
    if(index==0){;}
    std::vector<headerType> x; return x;}
  virtual std::vector<std::string> getHeaderTypes(){
    std::vector<std::string> a; return a;}


};



#endif 