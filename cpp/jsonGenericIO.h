#ifndef JSON_IO_H
#define JSON_IO_H 1
#include <fstream>  // std::ifstream
#include "genericIO.h"
#include "jsonGenericIrregFile.h"
#include "jsonGenericRegFile.h"

#include "jsonParamObj.h"
namespace SEP {
class jsonGenericIO : public genericIO {
 public:
  jsonGenericIO() { ; }
  jsonGenericIO(const int argc, char **argv) { initJsonPars(argc, argv); }
  void initJsonPars(const int argc, char **argv);
  Json::Value getArgs() { return jsonArgs; }
  virtual std::shared_ptr<genericRegFile> getRegFileTag(
      const std::string &tag, const std::string &name, const usage_code usage,
      const int ndimMax = -1) override;

  virtual std::shared_ptr<genericIrregFile> getIrregFileTag(
      const std::string &tag, const std::string &name, const usage_code usage,
      const int ndimMax = -1) override;

  virtual void close();
  virtual std::shared_ptr<paramObj> getParamObj() override;

 protected:
  std::string _progName;
  Json::Value jsonArgs;
  bool _sentError = false;

 private:
  std::ifstream inps;
  bool _init;
};
}  // namespace SEP
#endif
