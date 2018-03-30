#include "genericFile.h"
using namespace SEP;
void genericRegFile::putInt(const std::string &par, const int val) {
  if (par == "" && val == 0)
    ;
}

std::string genericRegFile::getDataTypeString() {
  dataType x = getDataType();

  switch (x) {
    case dataFloat:
      return std::string("dataFloat");
      break;
    case dataByte:
      return std::string("dataByte");
      break;
    case dataShort:
      return std::string("dataShort");
      break;
    case dataInt:
      return std::string("dataInt");
      break;
    case dataComplex:
      return std::string("dataComplex");
      break;
    default:
      return std::string("dataUndefined");
  }
}

int genericRegFile::getDataEsize() {
  dataType x = getDataType();

  switch (x) {
    case dataFloat:
      return 4;
      break;
    case dataByte:
      return 1;
      break;
    case dataShort:
      return 2;
      break;
    case dataInt:
      return 4;
      break;
    case dataComplex:
      return 8;
      break;
    default:
      return -1;
  }
}
#ifdef USE_SEPVECTOR
bool genericRegFile::readFloatStream(std::shared_ptr<SEP::floatHyper> vec) {
  std::shared_ptr<hypercube> hypV = vec->getHyper();
  if (vec->getSpaceOnly()) {
    std::cerr << "Trying to read in to a vector that has not been allocated"
              << std::endl;
    return false;
  }
  long long n123 = hypV->getN123();
  if (n123 > getHyper()->getN123()) {
    std::cerr << "Trying to read beyond specified file size" << std::endl;
    return false;
  }

  readFloatStream(vec->getVals(), n123);
  return true;
}
bool genericRegFile::writeFloatStream(
    const std::shared_ptr<SEP::floatHyper> vec) {
  std::shared_ptr<hypercube> hypV = vec->getHyper();
  if (vec->getSpaceOnly()) {
    std::cerr << "Trying to read in to a vector that has not been allocated"
              << std::endl;
    return false;
  }
  long long n123 = hypV->getN123();
  if (n123 > getHyper()->getN123()) {
    std::cerr << "Trying to read beyond specified file size" << std::endl;
    return false;
  }
  writeFloatStream(vec->getVals(), n123);
  return true;
}
bool genericRegFile::readFloatWindow(const std::vector<int> &nw,
                                     const std::vector<int> &fw,
                                     const std::vector<int> &jw,
                                     std::shared_ptr<SEP::floatHyper> vec) {
  std::shared_ptr<hypercube> hypV = vec->getHyper();
  if (vec->getSpaceOnly()) {
    std::cerr << "Trying to read in to a vector that has not been allocated"
              << std::endl;
    return false;
  }
  readFloatWindow(nw, fw, jw, vec->getVals());
  return true;
}
bool genericRegFile::writeFloatWindow(const std::vector<int> &nw,
                                      const std::vector<int> &fw,
                                      const std::vector<int> &jw,
                                      std::shared_ptr<SEP::floatHyper> vec) {
  std::shared_ptr<hypercube> hypV = vec->getHyper();
  if (vec->getSpaceOnly()) {
    std::cerr << "Trying to read in to a vector that has not been allocated"
              << std::endl;
    return false;
  }
  writeFloatWindow(nw, fw, jw, vec->getVals());
  return true;
}

#endif
