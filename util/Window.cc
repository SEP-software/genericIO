#include<ioModes.h>
using namespace SEP;
std::shared_ptr<hypercube> calc_params(std::shared_ptr<paramObj> par,
  std::shared_ptr<hypercube> hyperIn, const std::vector<int> ng,
  std::vector<int>&nw,std::vector<int>&fw,std::vector<int>&jw){
   
  int ndim=(int)ng.size();
  std::vector<axis> axes;
  for(int idim=0,i=1; idim<ndim; idim++,i++){
    axis ain=hyperIn->getAxis(idim);
    nw[idim]=par->getInt(std::string("n")+std::to_string(i),nw[idim]);
    fw[idim]=par->getInt(std::string("f")+std::to_string(i),nw[idim]);
    jw[idim]=par->getInt(std::string("j")+std::to_string(i),nw[idim]);
    if(fw[idim] >= ng[idim]) par->error(std::string("Invalid f")+
     std::to_string(i));
    if(nw[idim] > ng[idim]) par->error(std::string("Invalid n")+
      std::to_string(i));
    if(jw[idim] ==-1) jw[idim]=1;
    if(nw[idim] ==-1) {
      if(fw[idim]==-1){
        fw[idim]==0;
      }
      nw[idim]=(ng[idim]-1-fw[idim])/jw[idim]+1;
    }
    else if(fw[idim]==-1) fw[idim]=0;
    if(ng[idim] < 1+ fw[idim] +jw[idim]*(nw[idim]-1))
       par->error(std::string("Invalid window parameters axis ")+std::to_string(i));

    float o=fw[idim]*ain.d+ain.o;
    float d=jw[idim]*ain.d;
    axes.push_back(axis(nw[idim],o,d,ain.label));
  }
  std::shared_ptr<hypercube> h(new hypercube(axes));
  return h;
}
int main(int argc, char **argv){

  ioModes modes(argc,argv);

  std::shared_ptr<genericIO>  io=modes.getDefaultIO();
  std::shared_ptr<paramObj> par=io->getParamObj();

  std::string in=par->getString(std::string("input"));
  std::string out=par->getString(std::string("output"));
  std::shared_ptr<genericRegFile> inp=io->getRegFile(in,usageIn);
  std::shared_ptr<hypercube> hyperIn=inp->getHyper();
  std::vector<int> ng=hyperIn->returnNs();

  int ndim=(int)ng.size();

  if(ndim>8) par->error("Currently handle maximum of 8 dimensons");
  std::vector<int> nw(ndim,-1),fw(ndim,-1),jw(ndim,-1);

  std::shared_ptr<hypercube> hyperOut=calc_params(par,hyperIn,ng,nw,fw,jw);
  
  std::shared_ptr<genericRegFile> outp=io->getRegFile(out,usageOut);
  outp->setHyper(hyperOut);
  outp->writeDescription();

  int maxSize=par->getInt(std::string("maxsize"),8);
  long long maxS=(long long) maxSize*1024*1024*1024;
   
  std::vector<int> nloop(8,1);
  std::vector<int> fsend=fw,jsend=jw,nsend=nw;


  long long n123= hyperOut->getN123();
   int iaxis=ndim-1; 
   while(n123 > maxS){ 
     n123=n123/(long long) ng[iaxis]; 
     nloop[iaxis]=nw[iaxis];
     iaxis--;
   }
   float *buf=new float[n123];
   for(int i8=0; i8 < nloop[7]; i8++){
     fsend[7]=i8*jw[7]+fw[7]; nsend[7]=1;
   for(int i7=0; i7 < nloop[6]; i7++){
     fsend[6]=i7*jw[6]+fw[6]; nsend[6]=1;
   for(int i6=0; i6 < nloop[5]; i6++){
     fsend[5]=i6*jw[5]+fw[5]; nsend[5]=1;
   for(int i5=0; i5 < nloop[4]; i5++){
     fsend[4]=i5*jw[4]+fw[4]; nsend[4]=1;
   for(int i4=0; i4 < nloop[3]; i4++){
     fsend[3]=i4*jw[3]+fw[3];  nsend[3]=1;
   for(int i3=0; i3 < nloop[2]; i3++){
     fsend[2]=i3*jw[2]+fw[2];  nsend[2]=1;
   for(int i2=0; i2 < nloop[1]; i2++){
     fsend[1]=i2*jw[1]+fw[1]; nsend[1]=1;
     inp->readFloatWindow(nsend,fsend,jsend,buf); 
     outp->writeFloatStream(buf,n123);
   }}}}}}}


}
 
