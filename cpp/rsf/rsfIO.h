#ifndef SEP_IO_H
#define SEP_IO_H 1
#include "genericIO.h"
#include "rsfRegFiles.h"
#include "rsfParams.h"

class rsfIO: public genericIO{
  public:
    rsfIO(int argc, char **argv);
    virtual std::shared_ptr<genericRegFile> getRegFile(std::string name,usage_code usage);
    virtual std::shared_ptr<genericIrregFile> getIrregFile(std::string name, usage_code usage){
       assert(1==2);
    }
  


};
#endif