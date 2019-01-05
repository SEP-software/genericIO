#pragma once
#include "gcpBuffersRegFile.h"
#include "jsonGenericIO.h"
namespace SEP {
class gcpBuffersIO : public jsonGenericIO {
 public:
  gcpBuffersIO() { ; }
  gcpBuffersIO(const int argc, char **argv) { initJsonPars(argc, argv); }

  virtual std::shared_ptr<genericRegFile> getRegFileTag(const std::string &tag,
                                                        const std::string &name,
                                                        const usage_code usage);
  virtual std::shared_ptr<genericIrregFile> getIrregFileTag(
      const std::string &tag, const std::string &name, const usage_code usage);
  virtual void close();
  virtual std::shared_ptr<paramObj> getParamObj();

 private:
  bool _init = false;
};
}  // namespace SEP
