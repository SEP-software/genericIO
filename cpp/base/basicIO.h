#ifndef BASIC_IOH
#define BASIC_IOH 1
#include <stdio.h>
#include <memory>
#include "genericFile.h"
#include <assert.h>
/*this is very rudimentary class for file io */
class basicIO{
  public:
    basicIO(){;}
    void readWindow(std::vector<int> nw, std::vector<int> fw, std::vector<int> jw,void *data, void *head=0);
    void writeWindow(std::vector<int> nw, std::vector<int> fw, std::vector<int> jw,void *data, void *head=0);
    virtual void readStream(long long sz, const void *data){assert(1==2);}
    virtual void writeStream(long long sz, const void *dat){assert(1==2);}
    virtual void readTraceStream(long long sz, void *dat, void *head=0);
    virtual void writeTraceStream(long long sz, const void *dat, const void *head=0);
    virtual void writeReelHead(void *reelH);
    void readBlocks(std::vector<int> nwo, std::vector<int> fwo, std::vector<int> jwo, 
    std::vector<int> nwi, std::vector<int> fwi, std::vector<int> jwi,
    long long buf, void *data,void *head);
        void writeBlocks(std::vector<int> nwo, std::vector<int> fwo, std::vector<int> jwo, 
    std::vector<int> nwi, std::vector<int> fwi, std::vector<int> jwi,
    long long buf, void *data,void *head);
    virtual void partsToBlock(std::vector<int> nw, std::vector<int> fw, std::vector<int> jw, void *in, void *out, void *head);
        virtual void blockToParts(std::vector<int> nw, std::vector<int> fw, std::vector<int> jw, void *in, void *out, void *head);
    long long getCurrentPos(){assert(1==2);}
    inline void seekToPos(long long pos){ assert(1==2);

    }  
   void setFileParams(std::string nm,  usage_code usage, int reelH, int traceH, 
   int esize, std::shared_ptr<hypercube> hyper);
  protected:
    usage_code _usage;
    FILE *_myf;
    long long _reelH,_traceH;
    long long _esize;
    std::string _nm;
    std::shared_ptr<hypercube> _hyper;
};
class myFileIO: public basicIO{
 public:
   myFileIO(std::string nm, usage_code usage,int reelH, int traceH,int esize,std::shared_ptr<hypercube> hyper);
  virtual inline void seekToPos(long long pos){
       long long ft=getCurrentPos();
       long long bg=1024*1024*1024;
       long long diff=pos-ft;
       while(diff!=0){    
         long long dst;   
         if(diff>0) dst=std::min(bg,diff);
         else dst=-std::min(-diff,bg);
         fseek(_myf,dst,SEEK_CUR);
         diff-=dst;
      }  
  }
  virtual long long getCurrentPos(){
    return ftell(_myf);
  }
  virtual void readStream(long long sz, void *data);
  virtual void writeStream(long long sz,const void *data);
  virtual void close(){ fclose(myf);}
  ~myFileIO(){ close();}
  FILE *myf;
};



#endif