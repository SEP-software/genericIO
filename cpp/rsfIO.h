#ifndef RSF_IO_H
#define RSF_IO_H 1
#include "genericIO.h"
#include "rsfParams.h"
#include "rsfRegFiles.h"

class rsfIO : public genericIO {
 public:
  rsfIO(int argc, char **argv);
  virtual std::shared_ptr<genericRegFile> getRegFileTag(
      const std::string &tag, const std::string &name, const usage_code usage,
      const int ndimMax = -1) override;
  virtual std::shared_ptr<genericIrregFile> getIrregFileTag(
      const std::string &tag, const std::string &name, const usage_code usage,
      const int ndimMax = -1) override {
    throw SEPException(std::string("Undefined getIrregFileTag"));
  }
};
#endif