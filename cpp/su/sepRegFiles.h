#ifndef SEP_REGFILE_FUNC_H
#define SEP_REGFILE_FUNC_H 1
#include<string>
#include<stdbool.h>
#include "genericFile.h"

class sepRegFile: public genericRegFile{
  public:
  
 // sepRegFile::sepRegFile(const std::string tag,usage_code usage){

    sepRegFile(std::string tg, usage_code usage);
    virtual int getInt(const std::string arg);
    virtual int getInt(const std::string arg, const int def);
   
    virtual float getFloat(const std::string, const float def);
    virtual float getFloat(const std::string) ;
   
    virtual std::string getString(const std::string arg);
    virtual std::string getString(const std::string arg, const std::string def);
  
   
    virtual bool getBool(const std::string, const bool def);
    virtual bool getBool(const std::string);
   
   
    virtual std::vector<int> getInts(const std::string arg);
    virtual std::vector<int> getInts(const std::string arg,std::vector<int> defs);
     
    virtual std::vector<float> getFloats(const std::string arg);
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
    virtual void err(std::string a);
     virtual void putInt(const std::string par, const int val) ;
    virtual void putFloat(const std::string par, const float val);
    virtual void putString(const std::string par, const std::string val);
    virtual void putBool(const std::string par, const bool val);
    virtual void putInts(const std::string par, const  std::vector<int> val);
    virtual void putFloats(const std::string par, const std::vector<float> val) ;
  private:
    std::string _tag;
};









#endif