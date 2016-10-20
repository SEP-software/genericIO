#ifndef rsf_REGFILE_FUNC_H
#define rsf_REGFILE_FUNC_H 1
#include<string>
#include<stdbool.h>
#include "genericFile.h"
#include "basicIO.h"
#define  NO_BLAS 1
extern "C" {
#include <rsf.h>
}

class rsfBasic: public basicIO{
 public:
  rsfBasic(sf_file file){_file=file;}
  virtual inline void seekToPos(long long pos){
       long long ft=ftell(_myf);
       long long bg=1024*1024*1024;
       long long diff=pos-ft;
       while(diff!=0){    
         long long dst;   
         if(diff>0) dst=std::min(bg,diff);
         else dst=-std::min(-diff,bg);
         sf_seek(_file,dst,SEEK_CUR);
         diff-=dst;
      }  
  }
  virtual void readStream(long long sz, void *data){
      sf_ucharread((unsigned char*)data,sz,_file);
  
  }
  virtual void writeStream(long long sz, void *data){
  
        sf_ucharwrite((unsigned char*)data,sz,_file);

  }
  
      sf_file _file;

};
class rsfRegFile: public genericRegFile{
  public:
  
 // rsfRegFile::rsfRegFile(const std::string tag,usage_code usage){

    rsfRegFile(std::string tg, usage_code usage);
    virtual int getInt(const std::string arg);
    virtual int getInt(const std::string arg, const int def);
   
    virtual float getFloat(const std::string, const float def);
    virtual float getFloat(const std::string) ;
   
    virtual std::string getString(const std::string arg);
    virtual std::string getString(const std::string arg, const std::string def);
  
   
    virtual bool getBool(const std::string, const bool def);
    virtual bool getBool(const std::string);
   
   
    virtual std::vector<int> getInts(const std::string arg,int num);
    virtual std::vector<int> getInts(const std::string arg,std::vector<int> defs);
     
    virtual std::vector<float> getFloats(const std::string arg,int num);
    virtual std::vector<float> getFloats(const std::string arg,std::vector<float> defs);
       
    virtual void error(const std::string err) ;
    
    virtual void readFloatStream(float *array,const long long npts);
    virtual void readUCharStream(unsigned char *array,const long long npts);

    virtual void writeFloatStream( const float *array,const long long npts);
    virtual void readUCharWindow(const std::vector<int> nw, const std::vector<int> fw, 
      const std::vector<int> jw,  unsigned char *array);
    virtual void readFloatWindow(const std::vector<int> nw, const std::vector<int> fw, 
      const std::vector<int> jw,  float *array);

    virtual void writeFloatWindow(const std::vector<int> nw, const std::vector<int> fw, 
      const std::vector<int> jw,  float *array);
     virtual void readDescription();
    virtual void writeDescription();
     virtual void putInt(const std::string par, const int val) ;
    virtual void putFloat(const std::string par, const float val);
    virtual void putString(const std::string par, const std::string val);
    virtual void putBool(const std::string par, const bool val);
    virtual void putInts(const std::string par, const  std::vector<int> val);
    virtual void putFloats(const std::string par, const std::vector<float> val) ;
    virtual void close(){
      sf_fileclose(_file);
     }


  private:
    usage_code _usage;
    std::string _tag;
    sf_file _file;
    std::shared_ptr<rsfBasic> myio;
    int _esize;
};









#endif