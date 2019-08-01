#include "regVector.h"

#include "genericFile.h"
using namespace SEP;
void genericRegFile::putInt(const std::string &par, const int val) {
  if (par == "" && val == 0)
    ;
}

std::string genericRegFile::getDataTypeString() {
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
    default:
      return std::string("dataUndefined");
  }
}

int genericRegFile::getDataEsize() {
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
    default:
      return -1;
  }
}
bool genericRegFile::readFloatStream(
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
  std::vector<int> nw = vec->getHyper()->getNs();
  std::vector<int> fw(nw.size(), 0), jw(nw.size(), 1);
  writeFloatWindow(nw, fw, jw, vec->getVals());
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
bool genericRegFile::writeFloatWindow(
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

// BYTE
#ifdef USE_BYTE
bool genericRegFile::readByteStream(std::shared_ptr<SEP::byteHyper> vec) {
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
bool genericRegFile::writeByteStream(
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
bool genericRegFile::readByteWindow(const std::vector<int> &nw,
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
bool genericRegFile::writeByteWindow(const std::vector<int> &nw,
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
#endif

#ifdef USE_INT
bool genericRegFile::readIntStream(std::shared_ptr<SEP::intHyper> vec) {
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
bool genericRegFile::writeIntStream(const std::shared_ptr<SEP::intHyper> vec) {
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
bool genericRegFile::readIntWindow(const std::vector<int> &nw,
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
bool genericRegFile::writeIntWindow(const std::vector<int> &nw,
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
#endif
#ifdef USE_DOUBLE
bool genericRegFile::readDoubleStream(std::shared_ptr<SEP::doubleHyper> vec) {
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
bool genericRegFile::writeDoubleStream(
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
bool genericRegFile::readDoubleWindow(const std::vector<int> &nw,
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
bool genericRegFile::writeDoubleWindow(const std::vector<int> &nw,
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

#endif

#ifdef USE_COMPLEX
// Complex
bool genericRegFile::readComplexStream(std::shared_ptr<SEP::complexHyper> vec) {
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
bool genericRegFile::writeComplexStream(
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
bool genericRegFile::readComplexWindow(const std::vector<int> &nw,
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

bool genericRegFile::writeComplexWindow(
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
#endif
bool genericRegFile::readWindow(const std::vector<int> &nw,
                                const std::vector<int> &fw,
                                const std::vector<int> &jw,
                                const std::shared_ptr<SEP::regSpace> hyp) {
#ifdef USE_COMPLEX
  std::shared_ptr<complexHyper> cp =
      std::dynamic_pointer_cast<complexHyper>(hyp);
  if (cp) return readComplexWindow(nw, fw, jw, cp);
#endif

#ifdef USE_BYTE
  std::shared_ptr<byteHyper> bp = std::dynamic_pointer_cast<byteHyper>(hyp);
  if (bp) return readByteWindow(nw, fw, jw, bp);
#endif

#ifdef USE_DOUBLE
  std::shared_ptr<doubleHyper> dp = std::dynamic_pointer_cast<doubleHyper>(hyp);
  if (dp) return readDoubleWindow(nw, fw, jw, dp);
#endif

#ifdef USE_INT
  std::shared_ptr<intHyper> ip = std::dynamic_pointer_cast<intHyper>(hyp);
  if (ip) return readIntWindow(nw, fw, jw, ip);
#endif

  std::shared_ptr<floatHyper> fp = std::dynamic_pointer_cast<floatHyper>(hyp);
  if (!fp) SEPException(std::string("Trouble with floatHyper cast"));
  return readFloatWindow(nw, fw, jw, fp);
}

bool genericRegFile::writeWindow(const std::vector<int> &nw,
                                 const std::vector<int> &fw,
                                 const std::vector<int> &jw,
                                 std::shared_ptr<SEP::regSpace> hyp) {
#ifdef USE_COMPLEX
  const std::shared_ptr<complexHyper> cp =
      std::dynamic_pointer_cast<complexHyper>(hyp);
  if (cp) return writeComplexWindow(nw, fw, jw, cp);
#endif

#ifdef USE_BYTE
  const std::shared_ptr<byteHyper> bp =
      std::dynamic_pointer_cast<byteHyper>(hyp);
  if (bp) return writeByteWindow(nw, fw, jw, bp);
#endif

#ifdef USE_DOUBLE
  const std::shared_ptr<doubleHyper> dp =
      std::dynamic_pointer_cast<doubleHyper>(hyp);
  if (dp) return writeDoubleWindow(nw, fw, jw, dp);
#endif

#ifdef USE_INT
  const std::shared_ptr<intHyper> ip = std::dynamic_pointer_cast<intHyper>(hyp);
  if (ip) return writeIntWindow(nw, fw, jw, ip);
#endif

  const std::shared_ptr<floatHyper> fp =
      std::dynamic_pointer_cast<floatHyper>(hyp);
  return writeFloatWindow(nw, fw, jw, fp);
}
