#ifndef HYPERCUBE_H
#define HYPERCUBE_H 1
#include<axis.h>
#include<memory>
#include <vector>
#include <sstream>
namespace SEP{
class hypercube{

  public:
    hypercube(){}
    hypercube(const hypercube &hyper);
    hypercube(const std::shared_ptr<hypercube>& hyper);
    hypercube(const std::vector<SEP::axis>&axes);
    void setAxes(const std::vector<SEP::axis>& axes) ;
    void setAxis(const int idim, const SEP::axis &ax);
    SEP::axis getAxis(int idim) const;
    long long getN123() const {return n123;}
    void infoStream(std::stringstream &x);
    std::vector<int> getNs() const;
    void deallocate(){
         axes.clear();
    }
    ~hypercube(){
       this->deallocate();
    }
    
    void initNd(const std::vector<SEP::axis>& axes);
    std::vector<SEP::axis> returnAxes(const int nmax) const;
    int getNdim() const {return axes.size();}
    int getNdimG1() const;
    std::vector<SEP::axis> getAxes() const;
    std::vector<SEP::axis> getAxes(const int nmin)const;
    bool sameSize(const hypercube &other) const;
    bool sameSize(const std::shared_ptr<hypercube>&other) const;

  protected:
    long long n123;
    std::vector<SEP::axis> axes;
 
};

}
#endif

