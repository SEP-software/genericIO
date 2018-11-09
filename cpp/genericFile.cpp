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
#ifdef USE_BOOL
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

  readUCharStream(vec->getVals(), n123);
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
  writeUCharStream(vec->getVals(), n123);
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
  readUCharWindow(nw, fw, jw, vec->getVals());
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
  writeUCharWindow(nw, fw, jw, vec->getVals());
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
  bool genericRegFile::readIntWindow(
      const std::vector<int> &nw, const std::vector<int> &fw,
      const std::vector<int> &jw, std::shared_ptr<SEP::intHyper> vec) {
    std::shared_ptr<hypercube> hypV = vec->getHyper();
    if (vec->getSpaceOnly()) {
      std::cerr << "Trying to read in to a vector that has not been allocated"
                << std::endl;
      return false;
    }
    readIntWindow(nw, fw, jw, vec->getVals());
    return true;
  }
  bool genericRegFile::writeIntWindow(
      const std::vector<int> &nw, const std::vector<int> &fw,
      const std::vector<int> &jw, std::shared_ptr<SEP::intHyper> vec) {
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
  bool genericRegFile::readDoubleWindow(
      const std::vector<int> &nw, const std::vector<int> &fw,
      const std::vector<int> &jw, std::shared_ptr<SEP::doubleHyper> vec) {
    std::shared_ptr<hypercube> hypV = vec->getHyper();
    if (vec->getSpaceOnly()) {
      std::cerr << "Trying to read in to a vector that has not been allocated"
                << std::endl;
      return false;
    }
    readDoubleWindow(nw, fw, jw, vec->getVals());
    return true;
  }
  bool genericRegFile::writeDoubleWindow(
      const std::vector<int> &nw, const std::vector<int> &fw,
      const std::vector<int> &jw, std::shared_ptr<SEP::doubleHyper> vec) {
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
  bool genericRegFile::readComplexStream(
      std::shared_ptr<SEP::complexHyper> vec) {
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
  bool genericRegFile::readComplexWindow(
      const std::vector<int> &nw, const std::vector<int> &fw,
      const std::vector<int> &jw, std::shared_ptr<SEP::complexHyper> vec) {
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
