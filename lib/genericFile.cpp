#include "regVector.h"

#include "genericFile.h"
using namespace SEP;
void genericReg::putInt(const std::string &par, const int val) {
  if (par == "" && val == 0)
    ;
}

std::string genericReg::getDataTypeString() {
  dataType x = getDataType();

  switch (x) {
  case DATA_FLOAT:
    return std::string("DATA_FLOAT");
    break;
  case DATA_BYTE:
    return std::string("DATA_BYTE");
    break;
  // case dataShort:
  // return std::string("DATA_SHORT");
  // break;
  case DATA_INT:
    return std::string("DATA_INT");
    break;
  case DATA_DOUBLE:
    return std::string("DATA_DOUBLE");
    break;
  case DATA_COMPLEX:
    return std::string("DATA_COMPLEX");
    break;
  case DATA_COMPLEXDOUBLE:
    return std::string("DATA_COMPLEXDOUBLE");
    break;
  default:
    return std::string("dataUndefined");
  }
}
std::string genericReg::getDescriptionString() {

  Json::Value x = getDescription();
  Json::FastWriter fast;
  return fast.write(x);
}

void genericReg::putDescriptionString(const std::string &title,
                                          const std::string &descrp) {
  Json::Value x;

  Json::Reader reader;
  if (!reader.parse(descrp.c_str(), x))
    throw SEPException("trouble parsing string");

  putDescription(title, x);
}

int genericReg::getDataEsize() {
  dataType x = getDataType();

  switch (x) {
  case DATA_FLOAT:
    return 4;
    break;
  case DATA_BYTE:
    return 1;
    break;
  case DATA_DOUBLE:
    return 8;
    break;
  case DATA_INT:
    return 4;
    break;
  case DATA_COMPLEX:
    return 8;
    break;
  case DATA_COMPLEXDOUBLE:
    return 16;
    break;
  default:
    return -1;
  }
}
bool genericReg::readFloatStream(
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
  std::vector<int> nw = vec->getHyper()->getNs();
  std::vector<int> fw(nw.size(), 0), jw(nw.size(), 1);
  readFloatWindow(nw, fw, jw, vec->getVals());
  return true;
}
bool genericReg::writeFloatStream(
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
  std::vector<int> nw = vec->getHyper()->getNs();
  std::vector<int> fw(nw.size(), 0), jw(nw.size(), 1);
  writeFloatWindow(nw, fw, jw, vec->getVals());
  return true;
}
bool genericReg::readFloatWindow(const std::vector<int> &nw,
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
bool genericReg::writeFloatWindow(
    const std::vector<int> &nw, const std::vector<int> &fw,
    const std::vector<int> &jw, const std::shared_ptr<SEP::floatHyper> vec) {
  std::shared_ptr<hypercube> hypV = vec->getHyper();
  if (vec->getSpaceOnly()) {
    std::cerr << "Trying to read in to a vector that has not been allocated"
              << std::endl;
    return false;
  }
  writeFloatWindow(nw, fw, jw, vec->getVals());
  return true;
}

bool genericReg::readByteStream(std::shared_ptr<SEP::byteHyper> vec) {
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

  readByteStream(vec->getVals(), n123);
  return true;
}
bool genericReg::writeByteStream(
    const std::shared_ptr<SEP::byteHyper> vec) {
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
  writeByteStream(vec->getVals(), n123);
  return true;
}
bool genericReg::readByteWindow(const std::vector<int> &nw,
                                    const std::vector<int> &fw,
                                    const std::vector<int> &jw,
                                    std::shared_ptr<SEP::byteHyper> vec) {
  std::shared_ptr<hypercube> hypV = vec->getHyper();
  if (vec->getSpaceOnly()) {
    std::cerr << "Trying to read in to a vector that has not been allocated"
              << std::endl;
    return false;
  }
  readByteWindow(nw, fw, jw, vec->getVals());
  return true;
}
bool genericReg::writeByteWindow(const std::vector<int> &nw,
                                     const std::vector<int> &fw,
                                     const std::vector<int> &jw,
                                     std::shared_ptr<SEP::byteHyper> vec) {
  std::shared_ptr<hypercube> hypV = vec->getHyper();
  if (vec->getSpaceOnly()) {
    std::cerr << "Trying to read in to a vector that has not been allocated"
              << std::endl;
    return false;
  }
  writeByteWindow(nw, fw, jw, vec->getVals());
  return true;
}

bool genericReg::readIntStream(std::shared_ptr<SEP::intHyper> vec) {
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

  readIntStream(vec->getVals(), n123);
  return true;
}
bool genericReg::writeIntStream(const std::shared_ptr<SEP::intHyper> vec) {
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
  writeIntStream(vec->getVals(), n123);
  return true;
}
bool genericReg::readIntWindow(const std::vector<int> &nw,
                                   const std::vector<int> &fw,
                                   const std::vector<int> &jw,
                                   std::shared_ptr<SEP::intHyper> vec) {
  std::shared_ptr<hypercube> hypV = vec->getHyper();
  if (vec->getSpaceOnly()) {
    std::cerr << "Trying to read in to a vector that has not been allocated"
              << std::endl;
    return false;
  }
  readIntWindow(nw, fw, jw, vec->getVals());
  return true;
}
bool genericReg::writeIntWindow(const std::vector<int> &nw,
                                    const std::vector<int> &fw,
                                    const std::vector<int> &jw,
                                    std::shared_ptr<SEP::intHyper> vec) {
  std::shared_ptr<hypercube> hypV = vec->getHyper();
  if (vec->getSpaceOnly()) {
    std::cerr << "Trying to read in to a vector that has not been allocated"
              << std::endl;
    return false;
  }
  writeIntWindow(nw, fw, jw, vec->getVals());
  return true;
}

bool genericReg::readDoubleStream(std::shared_ptr<SEP::doubleHyper> vec) {
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

  readDoubleStream(vec->getVals(), n123);
  return true;
}
bool genericReg::writeDoubleStream(
    const std::shared_ptr<SEP::doubleHyper> vec) {
  const std::shared_ptr<hypercube> hypV = vec->getHyper();
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
  writeDoubleStream(vec->getVals(), n123);
  return true;
}
bool genericReg::readDoubleWindow(const std::vector<int> &nw,
                                      const std::vector<int> &fw,
                                      const std::vector<int> &jw,
                                      std::shared_ptr<SEP::doubleHyper> vec) {
  std::shared_ptr<hypercube> hypV = vec->getHyper();
  if (vec->getSpaceOnly()) {
    std::cerr << "Trying to read in to a vector that has not been allocated"
              << std::endl;
    return false;
  }
  readDoubleWindow(nw, fw, jw, vec->getVals());
  return true;
}
bool genericReg::writeDoubleWindow(const std::vector<int> &nw,
                                       const std::vector<int> &fw,
                                       const std::vector<int> &jw,
                                       std::shared_ptr<SEP::doubleHyper> vec) {
  std::shared_ptr<hypercube> hypV = vec->getHyper();
  if (vec->getSpaceOnly()) {
    std::cerr << "Trying to read in to a vector that has not been allocated"
              << std::endl;
    return false;
  }
  writeDoubleWindow(nw, fw, jw, vec->getVals());
  return true;
}

// Complex
bool genericReg::readComplexStream(std::shared_ptr<SEP::complexHyper> vec) {
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

  readComplexStream(vec->getVals(), n123);
  return true;
}
bool genericReg::readComplexDoubleStream(
    std::shared_ptr<SEP::complexDoubleHyper> vec) {
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

  readComplexDoubleStream(vec->getVals(), n123);
  return true;
}

bool genericReg::writeComplexStream(
    const std::shared_ptr<SEP::complexHyper> vec) {
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
  writeComplexStream(vec->getVals(), n123);
  return true;
}

bool genericReg::writeComplexDoubleStream(
    const std::shared_ptr<SEP::complexDoubleHyper> vec) {
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
  writeComplexDoubleStream(vec->getVals(), n123);
  return true;
}

bool genericReg::readComplexWindow(const std::vector<int> &nw,
                                       const std::vector<int> &fw,
                                       const std::vector<int> &jw,
                                       std::shared_ptr<SEP::complexHyper> vec) {
  std::shared_ptr<hypercube> hypV = vec->getHyper();
  if (vec->getSpaceOnly()) {
    std::cerr << "Trying to read in to a vector that has not been allocated"
              << std::endl;
    return false;
  }
  readComplexWindow(nw, fw, jw, vec->getVals());
  return true;
}
bool genericReg::readComplexDoubleWindow(
    const std::vector<int> &nw, const std::vector<int> &fw,
    const std::vector<int> &jw, std::shared_ptr<SEP::complexDoubleHyper> vec) {
  std::shared_ptr<hypercube> hypV = vec->getHyper();
  if (vec->getSpaceOnly()) {
    std::cerr << "Trying to read in to a vector that has not been allocated"
              << std::endl;
    return false;
  }
  readComplexDoubleWindow(nw, fw, jw, vec->getVals());
  return true;
}
bool genericReg::writeComplexWindow(
    const std::vector<int> &nw, const std::vector<int> &fw,
    const std::vector<int> &jw, std::shared_ptr<SEP::complexHyper> vec) {
  std::shared_ptr<hypercube> hypV = vec->getHyper();
  if (vec->getSpaceOnly()) {
    std::cerr << "Trying to read in to a vector that has not been allocated"
              << std::endl;
    return false;
  }
  writeComplexWindow(nw, fw, jw, vec->getVals());
  return true;
}
bool genericReg::writeComplexDoubleWindow(
    const std::vector<int> &nw, const std::vector<int> &fw,
    const std::vector<int> &jw, std::shared_ptr<SEP::complexDoubleHyper> vec) {
  std::shared_ptr<hypercube> hypV = vec->getHyper();
  if (vec->getSpaceOnly()) {
    std::cerr << "Trying to read in to a vector that has not been allocated"
              << std::endl;
    return false;
  }
  writeComplexDoubleWindow(nw, fw, jw, vec->getVals());
  return true;
}
bool genericReg::readWindow(const std::vector<int> &nw,
                                const std::vector<int> &fw,
                                const std::vector<int> &jw,
                                const std::shared_ptr<SEP::regSpace> hyp) {
  std::shared_ptr<complexHyper> cp =
      std::dynamic_pointer_cast<complexHyper>(hyp);
  if (cp)
    return readComplexWindow(nw, fw, jw, cp);
  std::shared_ptr<complexDoubleHyper> zp =
      std::dynamic_pointer_cast<complexDoubleHyper>(hyp);
  if (zp)
    return readComplexDoubleWindow(nw, fw, jw, zp);

  std::shared_ptr<byteHyper> bp = std::dynamic_pointer_cast<byteHyper>(hyp);
  if (bp)
    return readByteWindow(nw, fw, jw, bp);

  std::shared_ptr<doubleHyper> dp = std::dynamic_pointer_cast<doubleHyper>(hyp);
  if (dp)
    return readDoubleWindow(nw, fw, jw, dp);

  std::shared_ptr<intHyper> ip = std::dynamic_pointer_cast<intHyper>(hyp);
  if (ip)
    return readIntWindow(nw, fw, jw, ip);

  std::shared_ptr<floatHyper> fp = std::dynamic_pointer_cast<floatHyper>(hyp);

  if (!fp)
    SEPException(std::string("Trouble with floatHyper cast"));

  return readFloatWindow(nw, fw, jw, fp);
}

bool genericReg::writeWindow(const std::vector<int> &nw,
                                 const std::vector<int> &fw,
                                 const std::vector<int> &jw,
                                 std::shared_ptr<SEP::regSpace> hyp) {
  const std::shared_ptr<complexHyper> cp =
      std::dynamic_pointer_cast<complexHyper>(hyp);
  if (cp)
    return writeComplexWindow(nw, fw, jw, cp);

  const std::shared_ptr<complexDoubleHyper> zp =
      std::dynamic_pointer_cast<complexDoubleHyper>(hyp);
  if (zp)
    return writeComplexDoubleWindow(nw, fw, jw, zp);

  const std::shared_ptr<byteHyper> bp =
      std::dynamic_pointer_cast<byteHyper>(hyp);
  if (bp)
    return writeByteWindow(nw, fw, jw, bp);

  const std::shared_ptr<doubleHyper> dp =
      std::dynamic_pointer_cast<doubleHyper>(hyp);
  if (dp)
    return writeDoubleWindow(nw, fw, jw, dp);

  const std::shared_ptr<intHyper> ip = std::dynamic_pointer_cast<intHyper>(hyp);
  if (ip)
    return writeIntWindow(nw, fw, jw, ip);

  const std::shared_ptr<floatHyper> fp =
      std::dynamic_pointer_cast<floatHyper>(hyp);
  return writeFloatWindow(nw, fw, jw, fp);
}
void genericReg::setHyper(const std::shared_ptr<SEP::hypercube> hyp) {
  _hyper = hyp->clone();
  if (_hyper == nullptr)
    throw SEPException(std::string("hypercube not defined after clone"));
}
