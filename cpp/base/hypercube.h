#ifndef HYPERCUBE_H
#define HYPERCUBE_H 1
#include<axis.h>
#include<memory>
#include <vector>

class hypercube{

  public:
    hypercube(){}
    hypercube(const hypercube *hyper);
    hypercube(const std::vector<axis>axes);
    void setAxes(const std::vector<axis> axes) ;
    void setAxis(const int idim, const axis myaxis);
    axis getAxis(int idim) const;
    long long getN123() const {return n123;}
    std::vector<int> returnNs() const;
    void deallocate(){
         axes.clear();
    }
    ~hypercube(){
       this->deallocate();
    }
    
    void initNd(const std::vector<axis> axes);
    std::vector<axis> returnAxes(const int nmax) const;
    int getNdim() const {return axes.size();}
    int getNdimG1() const;
    std::vector<axis> getAxes() const;
    std::vector<axis> getAxes(const int nmin)const;
    bool sameSize(const hypercube &other) const;
    bool sameSize(const std::shared_ptr<hypercube>other) const;

  protected:
    long long n123;
    std::vector<axis> axes;
 
};
#endif

