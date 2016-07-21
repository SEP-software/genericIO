#include<hypercube.h>
#include <assert.h>
hypercube::hypercube(hypercube *hyper){

  std::vector<axis> axes;
  axes=hyper->get_axes();
  init_nd(axes);

}
hypercube::hypercube(std::vector<axis> axes){
  init_nd(axes);
}
void hypercube::init_nd(std::vector<axis> ax){

  this->n123=1;
  for(int i=0; i < ax.size(); i++){   
     axes.push_back(ax[i]);
     this->n123=this->n123*(long long)ax[i].n;
  }
}

void hypercube::set_axis(int idim, axis myaxis){
  if(idim<1 || idim>axes.size()) {
    fprintf(stderr,"IDIM=%d axes.size()=%d \n",idim,(int)axes.size());
    assert(1==2);
  }
  this->axes[idim-1]=myaxis;
}
void hypercube::set_axes(std::vector<axis> axes){
  this->init_nd(axes);
}

std::vector<axis> hypercube::return_axes(int nmax) const{
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
axis hypercube::get_axis(int idim){

  if(idim<1 || idim >this->axes.size()) {
    fprintf(stderr,"IDIM=%d axes.size()=%d \n",idim,(int)this->axes.size());
    assert(1==2);
  }
  axis myaxis=this->axes[idim-1];
  return myaxis;
}
int hypercube::get_ndim_g1(){
int nd=this->axes.size();
for(int i=this->axes.size()-1; i>=0; i--){
   if(axes[i].n>1) return nd;
    nd--;
}

 return nd;

}
std::vector<axis> hypercube::get_axes(){
  return return_axes(axes.size());
}
std::vector<int> hypercube::return_ns(){
  int i;
  std::vector<int> n;
  for(i=0; i < this->axes.size(); i++) n.push_back(axes[i].n);
  return n;
}

bool hypercube::same_size(hypercube *other){
  if(this->get_ndim() != other->get_ndim()) return false;
  for(int i=0; i < this->get_ndim(); i++){
    axis ax1=this->get_axis(i+1);
    axis ax2=other->get_axis(i+1);
    if(ax1.n!=ax2.n) return false; 
  }
  return true;
}
