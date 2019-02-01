#pragma once
#include "fileBuffersRegFile.h"
#include "jsonGenericIO.h"
namespace SEP {
class fileBuffersIO : public jsonGenericIO {
 public:
  fileBuffersIO() { ; }
  fileBuffersIO(const int argc, char **argv) { initJsonPars(argc, argv); }

  virtual std::shared_ptr<genericRegFile> getRegFileTag(
      const std::string &tag, const std::string &name, const usage_code usage,
      const int ndimMax = -1) override;
  virtual std::shared_ptr<genericIrregFile> getIrregFileTag(
      const std::string &tag, const std::string &name, const usage_code usage,
      const int ndimMax = -1) override;
  virtual void close();
  virtual std::shared_ptr<paramObj> getParamObj();

 private:
  bool _init = false;
};
}  // namespace SEP
