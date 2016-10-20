#ifndef HYPERCUBE_H
#define HYPERCUBE_H 1
#include<axis.h>
#include <vector>

class hypercube{

  public:
    hypercube(){}
    hypercube(hypercube *hyper);
    hypercube(std::vector<axis>axes);
    void setAxes(std::vector<axis> axes);
    void setAxis(int idim, axis myaxis);
    axis getAxis(int idim);
    std::vector<axis> getAxes() const;
    long long getN123(){return n123;}
    std::vector<int> returnNs();
    void deallocate(){
         axes.clear();
    }
    ~hypercube(){
       this->deallocate();
    }
    
    void initNd(std::vector<axis> axes);
    std::vector<axis> returnAxes(int nmax) const;
    int getNdim(){return axes.size();}
    int getNdimG1();
    std::vector<axis> getAxes();
    bool sameSize(hypercube *other);
    
  protected:
    long long n123;
    std::vector<axis> axes;
 
};
#endif

