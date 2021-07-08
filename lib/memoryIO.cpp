
#include "memoryIO.h"
using namespace SEP;
memoryIO::memoryIO(std::map<std::string, std::string> dict) {
  std::shared_ptr<dictParams> x(new dictParams(dict));
  _param = x;
  _type="MEMORY";
  setValid(true);
}

std::shared_ptr<genericReg> memoryIO::getRegTag(
    const std::string &tag, const std::string &name,
    const SEP::usage_code usage, const int ndimMax) {
  std::shared_ptr<memoryRegFile> x(new memoryRegFile(name, usage));
  addRegFile(tag, x);
  return x;
}

std::shared_ptr<genericIrreg> memoryIO::getIrregTag(
    const std::string &tag, const std::string &name,
    const SEP::usage_code usage, const int ndimMax) {
  // std::shared_ptr<memoryIrregFile> x(new memoryIrregFile(name, usage));
  // addRegFile(tag, x);
  // return x;
}
