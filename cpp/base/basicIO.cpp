#include "basicIO.h"
#include <assert.h>
#include <string.h>

myFileIO::myFileIO(std::string nm, usage_code usage,int reelH, int traceH,int esize,std::shared_ptr<hypercube>hyper){

  setFileParams(nm,usage,reelH,traceH,esize,hyper);
  std::string mode;
  if(_usage==usageIn || usage==usageInOut)  _myf=fopen(nm.c_str(),"r+");
  else _myf=fopen(nm.c_str(),"w+");
}
void basicIO::readWindow(std::vector<int> nw, std::vector<int> fw, std::vector<int> jw, void *data, void *head){
  long long optMin=256*1024,optMax=10*1024*1024;
  std::vector<axis> axes=_hyper->getAxes();
  if(_traceH+axes[0].n*_esize>optMin) optMin=_traceH+axes[0].n*_esize;
  long long blk=_esize*axes[0].n+_traceH;
  int naxes=1;
  bool breakL=false;
  while(naxes< nw.size()&& !breakL){
    long long btest=blk*(long long) axes[naxes].n;
    if(btest < optMin){
      naxes++;
      blk=btest;
    }
    else if(btest < optMax){
     if(blk > optMin){
        breakL=true;
     }
     else{
       naxes++;
       blk=btest;
     }
    }
    else breakL=true;
  }
  std::vector<int> nwi,fwi,jwi,nwo,fwo,jwo;
  nwi.assign(7,1); nwo.assign(7,1);
  jwi.assign(7,1); jwo.assign(7,1);
  fwi.assign(7,0); fwo.assign(7,0);
  for(int i=0; i < naxes; i++){
    fwi[i]=fw[i]; jwi[i]=jw[i]; nwi[i]=nw[i];
  }
  
  for(int i=naxes; i < nw.size(); i++){
    fwo[i-naxes]=fw[i]; jwo[i-naxes]=jw[i]; nwo[i-naxes]=nw[i];
  }

  readBlocks(nwo,fwo,jwo,nwi,fwi,jwi,blk,data,head);


}
void basicIO::writeWindow(std::vector<int> nw, std::vector<int> fw, std::vector<int> jw, void *data, void *head){
  long long optMin=256*1024,optMax=10*1024*1024;
  std::vector<axis> axes=_hyper->getAxes();
  if(_traceH+axes[0].n*_esize>optMin) optMin=_traceH+axes[0].n*_esize;
  long long blk=_esize*axes[0].n+_traceH;
  int naxes=1;
  bool breakL=false;
  while(naxes< nw.size()&& !breakL){
    long long btest=blk*(long long) axes[naxes].n;
    if(btest < optMin){
      naxes++;
      blk=btest;
    }
    else if(btest < optMax){
     if(blk > optMin){
        breakL=true;
     }
     else{
       naxes++;
       blk=btest;
     }
    }
    else breakL=true;
  }
  std::vector<int> nwi,fwi,jwi,nwo,fwo,jwo;
  nwi.assign(7,1); nwo.assign(7,1);
  jwi.assign(7,1); jwo.assign(7,1);
  fwi.assign(7,0); fwo.assign(7,0);
  for(int i=0; i < naxes; i++){
    fwi[i]=fw[i]; jwi[i]=jw[i]; nwi[i]=nw[i];
  }
  
  for(int i=naxes; i < nw.size(); i++){
    fwo[i-naxes]=fw[i]; jwo[i-naxes]=jw[i]; nwo[i-naxes]=nw[i];
  }

  writeBlocks(nwo,fwo,jwo,nwi,fwi,jwi,blk,data,head);


}
void basicIO::readBlocks(std::vector<int> nwo, std::vector<int>fwo, std::vector<int> jwo, std::vector<int> nwi,
  std::vector<int> fwi, std::vector<int> jwi, long long sz, void *dat, void *head){
    char *buf=new char[sz];
    std::vector<axis> axes=_hyper->getAxes();
    long long pto=0;
    std::vector<long long> blk;blk.push_back(sz);
    for(int i=0;i < 7; i++) blk[i]=blk[i-1]*(long long)axes[i].n;
    for(long long i6=0; i6 < nwo[6]; i6++){
      long long pt6=((long long)(fwo[6]+jwo[6]*i6))*blk[6];
      for(long long i5=0; i5 < nwo[5]; i5++){
        long long pt5=pt6+((long long)(fwo[5]+jwo[5]*i5))*blk[5];
        for(long long i4=0; i4< nwo[4]; i4++){
          long long pt4=pt5+((long long)(fwo[4]+jwo[4]*i4))*blk[4];
          for(long long i3=0; i3 < nwo[3]; i3++){
            long long pt3=pt4+((long long)(fwo[3]+jwo[3]*i3))*blk[3];
            for(long long i2=0; i2 < nwo[2]; i2++){
              long long pt2=pt3+((long long)(fwo[2]+jwo[2]*i2))*blk[2];
              for(long long i1=0; i1< nwo[1]; i1++){
                long long pt1=pt2+((long long)(fwo[1]+jwo[1]*i1))*blk[1];
                for(long long i0=0; i0< nwo[0]; i0++){
                  long long pti=pt1+((long long)(fwo[0]+jwo[0]*i0))*blk[0];
                    seekToPos(pti);
                    readStream(sz,buf);
                    blockToParts(nwi,fwi,jwi,buf,dat,head);
                }
              }
            }
          }
        }
      }
    }
    delete [] buf;
  }
  void basicIO::writeBlocks(std::vector<int> nwo, std::vector<int>fwo, std::vector<int> jwo, std::vector<int> nwi,
  std::vector<int> fwi, std::vector<int> jwi, long long sz, void *dat, void *head){
    char *buf=new char[sz];
    std::vector<axis> axes=_hyper->getAxes();
    long long pto=0;
    std::vector<long long> blk;blk.push_back(sz);
    for(int i=0;i < 7; i++) blk[i]=blk[i-1]*(long long)axes[i].n;
    for(long long i6=0; i6 < nwo[6]; i6++){
      long long pt6=((long long)(fwo[6]+jwo[6]*i6))*blk[6];
      for(long long i5=0; i5 < nwo[5]; i5++){
        long long pt5=pt6+((long long)(fwo[5]+jwo[5]*i5))*blk[5];
        for(long long i4=0; i4< nwo[4]; i4++){
          long long pt4=pt5+((long long)(fwo[4]+jwo[4]*i4))*blk[4];
          for(long long i3=0; i3 < nwo[3]; i3++){
            long long pt3=pt4+((long long)(fwo[3]+jwo[3]*i3))*blk[3];
            for(long long i2=0; i2 < nwo[2]; i2++){
              long long pt2=pt3+((long long)(fwo[2]+jwo[2]*i2))*blk[2];
              for(long long i1=0; i1< nwo[1]; i1++){
                long long pt1=pt2+((long long)(fwo[1]+jwo[1]*i1))*blk[1];
                for(long long i0=0; i0< nwo[0]; i0++){
                  long long pti=pt1+((long long)(fwo[0]+jwo[0]*i0))*blk[0];
                    partsToBlock(nwi,fwi,jwi,buf,dat,head);
                    seekToPos(pti);
                    writeStream(sz,buf);
                }
              }
            }
          }
        }
      }
    }
    delete [] buf;
  }
void basicIO::readTraceStream(long long sz, void *dat, void *head){
   long long cp=getCurrentPos();
   long long n=_hyper->getAxis(0).n;
   if(_traceH >0){
     assert((cp-(long long)_reelH)%(n+_traceH)==0);
     assert(sz%n==0);
     long long ntrace=sz/n;
     long long nH=_traceH+n*_esize;
     long long sz2=ntrace*nH;
     char *buf=new char [sz2];
     readStream(sz2,buf);
     char *headC=(char*)head;
     char *datC=(char*) dat;
     for(long long i2=0; i2 < ntrace; i2++){
       if(head!=0)
         memcpy(&headC[i2*_traceH],&buf[nH*i2],_traceH);
       memcpy(&datC[i2*n],&buf[nH*i2+_traceH], n*_esize);
    }
    delete [] buf;

}
   else readStream(sz,dat);
}
void basicIO::writeTraceStream(long long sz, const void *dat, const void *head){
   long long cp=getCurrentPos();
   long long n=_hyper->getAxis(0).n;
   if(_traceH >0){
     assert((cp-(long long)_reelH)%(n+_traceH)==0);
     assert(sz%n==0);
     long long ntrace=sz/n;
     long long nH=_traceH+n*_esize;
     long long sz2=ntrace*nH;
     char *buf=new char [sz2];
     char *headC;
     if(head!=0)headC=(char*)head;
     else headC=new char[ntrace*_traceH];
     char *datC=(char*) dat;
     for(long long i2=0; i2 < ntrace; i2++){
       memcpy(&buf[nH*i2],&headC[i2*_traceH],_traceH);
       memcpy(&buf[nH*i2+_traceH],&datC[i2*n], n*_esize);
    }
    if(head==0) delete [] headC;
    writeStream(sz2,buf);
    delete [] buf;
   }
   else writeStream(sz,dat);
}
void basicIO::writeReelHead(void *reelH){
     assert(_reelH==fwrite(reelH,1,_reelH,_myf));
}
void myFileIO::readStream(long long sz, void *data){
     
     assert(sz==fread(data,1,sz,_myf));        
  }
void myFileIO::writeStream(long long sz,const void *data){
     assert(sz==fwrite(data,1,sz,_myf));
  }
void basicIO::blockToParts(std::vector<int> nwo, std::vector<int> fwo, std::vector<int> jwo, void *in, void *out, void *head){
   std::vector<axis> axes=_hyper->getAxes();
   char *inH=(char*)in, *outH=(char*)out, *headH=(char*)head;
   long long ih=0,id=0;
   std::vector<long long> blk; blk.push_back(_esize);
   for(int i=0;i < 7; i++) blk[i]=blk[i-1]*(long long)axes[i].n;
    for(long long i6=0; i6 < nwo[6]; i6++){
      long long pt6=((long long)(fwo[6]+jwo[6]*i6))*blk[6];
      for(long long i5=0; i5 < nwo[5]; i5++){
        long long pt5=pt6+((long long)(fwo[5]+jwo[5]*i5))*blk[5];
        for(long long i4=0; i4< nwo[4]; i4++){
          long long pt4=pt5+((long long)(fwo[4]+jwo[4]*i4))*blk[4];
          for(long long i3=0; i3 < nwo[3]; i3++){
            long long pt3=pt4+((long long)(fwo[3]+jwo[3]*i3))*blk[3];
            for(long long i2=0; i2 < nwo[2]; i2++){
              long long pt2=pt3+((long long)(fwo[2]+jwo[2]*i2))*blk[2];
              for(long long i1=0; i1< nwo[1]; i1++){
                long long pt1=pt2+((long long)(fwo[1]+jwo[1]*i1))*blk[1];
                /* we are now at the trace level*/
                if(head!=0){
                  memcpy(&headH[ih],&inH[pt1],_traceH);
                  ih+=_traceH;
                }
                pt1+=_traceH;
                for(int i0=0; i0 < nwo[0]; i0++,id++){
                  memcpy(&outH[id],&inH[pt1+(fwo[0]+jwo[0]*i0)*blk[0]],_esize); 
                }
              }
            }
          }
        }
      }
   }
}
void basicIO::partsToBlock(std::vector<int> nwo, std::vector<int> fwo, std::vector<int> jwo, void *in, void *out, void *head){
   std::vector<axis> axes=_hyper->getAxes();
   char *inH=(char*)in, *outH=(char*)out, *headH=(char*)head;
   long long ih=0,id=0;
   
   assert(_traceH==0);
   std::vector<long long> blk; blk.push_back(_esize);
   for(int i=0;i < 7; i++) blk[i]=blk[i-1]*(long long)axes[i].n;
    for(long long i6=0; i6 < nwo[6]; i6++){
      long long pt6=((long long)(fwo[6]+jwo[6]*i6))*blk[6];
      for(long long i5=0; i5 < nwo[5]; i5++){
        long long pt5=pt6+((long long)(fwo[5]+jwo[5]*i5))*blk[5];
        for(long long i4=0; i4< nwo[4]; i4++){
          long long pt4=pt5+((long long)(fwo[4]+jwo[4]*i4))*blk[4];
          for(long long i3=0; i3 < nwo[3]; i3++){
            long long pt3=pt4+((long long)(fwo[3]+jwo[3]*i3))*blk[3];
            for(long long i2=0; i2 < nwo[2]; i2++){
              long long pt2=pt3+((long long)(fwo[2]+jwo[2]*i2))*blk[2];
              for(long long i1=0; i1< nwo[1]; i1++){
                long long pt1=pt2+((long long)(fwo[1]+jwo[1]*i1))*blk[1];
                /* we are now at the trace level*/
                if(head!=0){
                  memcpy(&headH[ih],&inH[pt1],_traceH);
                  ih+=_traceH;
                }
                pt1+=_traceH;
                for(int i0=0; i0 < nwo[0]; i0++,id++){
                  memcpy(&inH[pt1+(fwo[0]+jwo[0]*i0)*blk[0]],&outH[id],_esize); 
                }
              }
            }
          }
        }
      }
   }
}
void basicIO::setFileParams(std::string nm,  usage_code usage, int reelH, int traceH, int esize, std::shared_ptr<hypercube>hyper){
   
  _nm=nm;
  _usage=usage;
  _reelH=reelH;
  _traceH=traceH;
  _esize=esize;
  _hyper=hyper;

}
  