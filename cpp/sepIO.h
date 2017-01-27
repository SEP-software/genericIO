#ifndef SEP_IO_H
#define SEP_IO_H 1
#include "genericIO.h"
#include "sep_reg_file.h"
#include "sep3dFile.h"
#include "sep_params.h"
namespace SEP{
class sepIO: public genericIO{
  public:
   sepIO(int argc, char **argv);
    virtual std::shared_ptr<genericRegFile> getRegFile(const std::string name,const usage_code usage);
    virtual std::shared_ptr<genericIrregFile> getIrregFile(const std::string name,const usage_code usage);



};
}
#endif