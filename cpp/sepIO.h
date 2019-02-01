#ifndef SEP_IO_H
#define SEP_IO_H 1
#include "genericIO.h"
#include "sep3dFile.h"
#include "sep_params.h"
#include "sep_reg_file.h"
namespace SEP {
class sepIO : public genericIO {
 public:
  sepIO(int argc, char **argv);
  virtual std::shared_ptr<SEP::genericRegFile> getRegFileTag(
      const std::string &tag, const std::string &name,
      const SEP::usage_code usage, const int ndim = -1) override;
  virtual std::shared_ptr<SEP::genericIrregFile> getIrregFileTag(
      const std::string &tag, const std::string &name,
      const SEP::usage_code usage, const int ndimMax = -1) override;
};
}  // namespace SEP
#endif
