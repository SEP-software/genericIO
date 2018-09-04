#ifndef BUFFERS_IO
#define BUFFERS_IO_H 1
#include "buffersRegFile.h"
#include "jsonGenericIO.h"
namespace SEP {
class buffersIO : public jsonGenericIO {
 public:
  buffersIO() { ; }
  buffersIO(const int argc, char **argv) { initJsonPars(argc, argv); }

  virtual std::shared_ptr<genericRegFile> getRegFileTag(const std::string &tag,
                                                        const std::string &name,
                                                        const usage_code usage);
  virtual std::shared_ptr<genericIrregFile> getIrregFileTag(
      const std::string &tag, const std::string &name, const usage_code usage);
  virtual void close();
  virtual std::shared_ptr<paramObj> getParamObj();

 private:
  std::shared_ptr<Json::Value> jsonArgs;
  bool _init;
};
}  // namespace SEP
#endif
