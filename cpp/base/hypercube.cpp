#include<hypercube.h>
#include <assert.h>
hypercube::hypercube(hypercube *hyper){

  std::vector<axis> axes;
  axes=hyper->getAxes();
  initNd(axes);

}
hypercube::hypercube(std::vector<axis> axes){
  initNd(axes);
}
void hypercube::initNd(std::vector<axis> ax){

  this->n123=1;
  for(int i=0; i < ax.size(); i++){   
     axes.push_back(ax[i]);
     this->n123=this->n123*(long long)ax[i].n;
  }
}
void hypercube::setAxis(int idim, axis myaxis){
  if(idim<1 || idim>axes.size()) {
    fprintf(stderr,"IDIM=%d axes.size()=%d \n",idim,(int)axes.size());
    assert(1==2);
  }
  this->axes[idim-1]=myaxis;
}
void hypercube::setAxes(std::vector<axis> axes){
  this->initNd(axes);
}
std::vector<axis> hypercube::returnAxes(int nmax) const{
  std::vector<axis> ax;
  for(int i=0; i < nmax; i++){
    if(i+1 <= this->axes.size()){
       ax.push_back(axes[i]);
    }
    else {
      ax.push_back(axis(1));
    }
  }
  return ax;
}
axis hypercube::getAxis(int idim){

  if(idim<1 || idim >this->axes.size()) {
    fprintf(stderr,"IDIM=%d axes.size()=%d \n",idim,(int)this->axes.size());
    assert(1==2);
  }
  axis myaxis=this->axes[idim-1];
  return myaxis;
}
int hypercube::getNdimG1(){
int nd=this->axes.size();
for(int i=this->axes.size()-1; i>=0; i--){
   if(axes[i].n>1) return nd;
    nd--;
}

 return nd;

}
std::vector<axis> hypercube::getAxes(){
  return returnAxes(axes.size());
}
std::vector<int> hypercube::returnNs(){
  int i;
  std::vector<int> n;
  for(i=0; i < this->axes.size(); i++) n.push_back(axes[i].n);
  return n;
}
bool hypercube::sameSize(hypercube *other){
  if(this->getNdim() != other->getNdim()) return false;
  for(int i=0; i < this->getNdim(); i++){
    axis ax1=this->getAxis(i+1);
    axis ax2=other->getAxis(i+1);
    if(ax1.n!=ax2.n) return false; 
  }
  return true;
}
