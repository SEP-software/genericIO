#include "memoryFile.h"
#include <sstream>
#include "SEPException.h"
#include "basicIO.h"
#include "string.h"
using namespace SEP;
memoryRegFile::memoryRegFile(const std::string &tag, const usage_code usage,
                             const int ndim) {}

int memoryRegFile::getInt(const std::string &arg) const {
  if (0 == _dict.count(arg))
    error(std::string("trouble grabbing parameter ") + arg +
          std::string(" from parameters"));
  return stoi(_dict.at(arg));
}
int memoryRegFile::getInt(const std::string &arg, const int def) const {
  if (0 == _dict.count(arg)) return def;
  return stoi(_dict.at(arg));
}

float memoryRegFile::getFloat(const std::string &arg, const float def) const {
  if (0 == _dict.count(arg)) return def;
  return stof(_dict.at(arg));
}
float memoryRegFile::getFloat(const std::string &arg) const {
  if (0 == _dict.count(arg))
    error(std::string("trouble grabbing parameter ") + arg +
          std::string(" from parameters"));
  return stof(_dict.at(arg));
}

std::string memoryRegFile::getString(const std::string &arg) const {
  if (0 == _dict.count(arg))
    error(std::string("trouble grabbing parameter ") + arg +
          std::string(" from parameters"));
  return _dict.at(arg);
}
std::string memoryRegFile::getString(const std::string &arg,
                                     const std::string &def) const {
  if (0 == _dict.count(arg)) return def;
  return _dict.at(arg);
}

bool memoryRegFile::getBool(const std::string &arg, const bool def) const {
  if (0 == _dict.count(arg)) return def;
  bool b;
  std::istringstream(_dict.at(arg)) >> b;

  return b;
}
bool memoryRegFile::getBool(const std::string &arg) const {
  bool x;
  if (0 == _dict.count(arg))
    error(std::string("trouble grabbing parameter ") + arg +
          std::string(" from parameters"));

  bool b;
  std::istringstream(_dict.at(arg)) >> b;

  return b;
}

std::vector<int> memoryRegFile::getInts(const std::string &arg, int num) const {
  if (0 == _dict.count(arg))
    error(std::string("trouble grabbing parameter ") + arg +
          std::string(" from parameters"));
  std::vector<std::string> tmp = splitString(_dict.at(arg));
  std::vector<int> x;
  for (int i = 0; i < tmp.size(); i++) x.push_back(stoi(tmp[i]));
  return x;
}
std::vector<int> memoryRegFile::getInts(const std::string &arg,
                                        const std::vector<int> &defs) const {
  std::vector<int> x = defs;

  if (0 == _dict.count(arg)) return defs;
  std::vector<std::string> tmp = splitString(_dict.at(arg));

  for (int i = 0; i < tmp.size(); i++) x[i] = stoi(tmp[i]);
  return x;
}

std::vector<float> memoryRegFile::getFloats(const std::string &arg,
                                            int num) const {
  if (0 == _dict.count(arg))
    error(std::string("trouble grabbing parameter ") + arg +
          std::string(" from parameters"));
  std::vector<std::string> tmp = splitString(_dict.at(arg));
  std::vector<float> x(tmp.size());
  for (int i = 0; i < tmp.size(); i++) x[i] = stof(tmp[i]);
  return x;
}
std::vector<float> memoryRegFile::getFloats(
    const std::string &arg, const std::vector<float> &defs) const {
  std::vector<float> x = defs;

  if (0 == _dict.count(arg)) return defs;
  std::vector<std::string> tmp = splitString(_dict.at(arg));
  for (int i = 0; i < tmp.size(); i++) x.push_back(stof(tmp[i]));
  return x;
}
void memoryRegFile::close() { return; }
void memoryRegFile::error(const std::string &err) const {
  throw SEPException(err.c_str());
}

void memoryRegFile::putInt(const std::string &par, const int val) {
  std::string x = std::to_string(val);
  _dict[par] = x;
}
void memoryRegFile::putFloat(const std::string &par, const float val) {
  std::string x = std::to_string(val);
  _dict[par] = x;
}
void memoryRegFile::putString(const std::string &par, const std::string &val) {
  _dict[par] = val;
}

void memoryRegFile::putBool(const std::string &par, const bool val) {
  std::string x = "0";
  if (val) x = "1";
  _dict[par] = x;
}
void memoryRegFile::putInts(const std::string &par,
                            const std::vector<int> &val) {
  std::string x;
  for (int i = 0; i < val.size() - 1; i++)
    x += std::to_string(val[i]) + std::string(",");

  x += std::to_string(val[val.size() - 1]);
  _dict[par] = x;
}
void memoryRegFile::putFloats(const std::string &par,
                              const std::vector<float> &val) {
  std::string x;
  for (int i = 0; i < val.size() - 1; i++)
    x += std::to_string(val[i]) + std::string(",");

  x += std::to_string(val[val.size() - 1]);
  _dict[par] = x;
}
void memoryRegFile::readFloatStream(float *array, const long long npts) {
  if (_hyper == nullptr) throw SEPException(std::string("Must set hyper"));

  long long nptsT = npts * 4;
  if (nptsT + _pos > _buf.size()) error(std::string("outside array"));
  memcpy(array, _buf.data() + _pos, nptsT);
  _pos += nptsT;
}
void memoryRegFile::readIntStream(int *array, const long long npts) {
  if (_hyper == nullptr) throw SEPException(std::string("Must set hyper"));

  long long nptsT = npts * 4;
  if (nptsT + _pos > _buf.size()) error(std::string("outside array"));
  memcpy(array, _buf.data() + _pos, nptsT);
  _pos += nptsT;
}
void memoryRegFile::readDoubleStream(double

                                         *array,
                                     const long long npts) {
  if (_hyper == nullptr) throw SEPException(std::string("Must set hyper"));

  long long nptsT = npts * 8;
  if (nptsT + _pos > _buf.size()) error(std::string("outside array"));
  memcpy(array, _buf.data() + _pos, nptsT);
  _pos += nptsT;
}
void memoryRegFile::readComplexStream(std::complex<float> *array,
                                      const long long npts) {
  if (_hyper == nullptr) throw SEPException(std::string("Must set hyper"));

  long long nptsT = npts * 8;
  if (nptsT + _pos > _buf.size()) error(std::string("outside array"));
  memcpy(array, _buf.data() + _pos, nptsT);
  _pos += nptsT;
}
void memoryRegFile::readByteStream(unsigned char *array, const long long npts) {
  if (_hyper == nullptr) throw SEPException(std::string("Must set hyper"));

  long long nptsT = npts * 1;
  if (nptsT + _pos > _buf.size()) error(std::string("outside array"));
  memcpy(array, _buf.data() + _pos, nptsT);
  _pos += nptsT;
}

void memoryRegFile::writeFloatStream(const float *array, const long long npts) {
  if (_hyper == nullptr) throw SEPException(std::string("Must set hyper"));

  long long nptsT = npts * 4;
  if (nptsT + _pos > _buf.size()) error(std::string("outside array"));
  memcpy(_buf.data() + _pos, array, nptsT);
  _pos += nptsT;
}
void memoryRegFile::writeByteStream(const unsigned char *array,
                                    const long long npts) {
  if (_hyper == nullptr) throw SEPException(std::string("Must set hyper"));

  long long nptsT = npts * 1;
  if (nptsT + _pos > _buf.size()) error(std::string("outside array"));
  memcpy(_buf.data() + _pos, array, nptsT);
  _pos += nptsT;
}
void memoryRegFile::writeIntStream(const int *array, const long long npts) {
  if (_hyper == nullptr) throw SEPException(std::string("Must set hyper"));

  long long nptsT = npts * 4;
  if (nptsT + _pos > _buf.size()) error(std::string("outside array"));
  memcpy(_buf.data() + _pos, array, nptsT);
  _pos += nptsT;
}
void memoryRegFile::writeDoubleStream(const double *array,
                                      const long long npts) {
  if (_hyper == nullptr) throw SEPException(std::string("Must set hyper"));

  long long nptsT = npts * 8;
  if (nptsT + _pos > _buf.size()) error(std::string("outside array"));
  memcpy(_buf.data() + _pos, array, nptsT);
  _pos += nptsT;
}

void memoryRegFile::readFloatWindow(const std::vector<int> &nw,
                                    const std::vector<int> &fw,
                                    const std::vector<int> &jw, float *array) {
  if (_hyper == nullptr) throw SEPException(std::string("Must set hyper"));

  std::shared_ptr<hypercube> hyper = getHyper();
  std::vector<int> ng = hyper->getNs();

  setDataType(DATA_FLOAT);

  if (ng.size() > nw.size()) {
    for (int i = nw.size(); i < ng.size(); i++) {
      if (ng[i] > 1) error("number of dimension does not equal data size");
    }
  }
  if (nw.size() < ng.size() || fw.size() < ng.size() || jw.size() < jw.size()) {
    error("number of dimensions does not equal data size");
  }

  int ndim = ng.size();

  SEP::blockToParts(hyper, 0, 4, nw, fw, jw, _buf.data(), array, array);
}

void memoryRegFile::readDoubleWindow(const std::vector<int> &nw,
                                     const std::vector<int> &fw,
                                     const std::vector<int> &jw,
                                     double *array) {
  if (_hyper == nullptr) throw SEPException(std::string("Must set hyper"));

  std::shared_ptr<hypercube> hyper = getHyper();
  std::vector<int> ng = hyper->getNs();

  setDataType(DATA_DOUBLE);

  if (ng.size() > nw.size()) {
    for (int i = nw.size(); i < ng.size(); i++) {
      if (ng[i] > 1) error("number of dimension does not equal data size");
    }
  }
  if (nw.size() < ng.size() || fw.size() < ng.size() || jw.size() < jw.size()) {
    error("number of dimensions does not equal data size");
  }

  SEP::blockToParts(hyper, 0, 8, nw, fw, jw, _buf.data(), array, array);
}
void memoryRegFile::readIntWindow(const std::vector<int> &nw,
                                  const std::vector<int> &fw,
                                  const std::vector<int> &jw, int *array) {
  if (_hyper == nullptr) throw SEPException(std::string("Must set hyper"));

  std::shared_ptr<hypercube> hyper = getHyper();
  std::vector<int> ng = hyper->getNs();

  setDataType(DATA_INT);

  SEP::blockToParts(hyper, 0, 4, nw, fw, jw, _buf.data(), array, array);
}

void memoryRegFile::readComplexWindow(const std::vector<int> &nw,
                                      const std::vector<int> &fw,
                                      const std::vector<int> &jw,
                                      std::complex<float> *array) {
  if (_hyper == nullptr) throw SEPException(std::string("Must set hyper"));

  std::shared_ptr<hypercube> hyper = getHyper();
  std::vector<int> ng = hyper->getNs();

  setDataType(DATA_COMPLEX);

  if (ng.size() > nw.size()) {
    for (int i = nw.size(); i < ng.size(); i++) {
      if (ng[i] > 1) error("number of dimension does not equal data size");
    }
  }
  if (nw.size() < ng.size() || fw.size() < ng.size() || jw.size() < jw.size()) {
    error("number of dimensions does not equal data size");
  }

  SEP::blockToParts(hyper, 0, 8, nw, fw, jw, _buf.data(), array, array);
}

void memoryRegFile::writeComplexStream(const std::complex<float> *array,
                                       const long long npts) {
  if (_hyper == nullptr) throw SEPException(std::string("Must set hyper"));

  long long nptsT = npts * 8;
  if (nptsT + _pos > _buf.size()) error(std::string("outside array"));
  memcpy(_buf.data() + _pos, array, nptsT);
  _pos += nptsT;
}

void memoryRegFile::writeComplexWindow(const std::vector<int> &nw,
                                       const std::vector<int> &fw,
                                       const std::vector<int> &jw,
                                       const std::complex<float> *array) {
  if (_hyper == nullptr) throw SEPException(std::string("Must set hyper"));

  setDataType(DATA_COMPLEX);

  std::shared_ptr<hypercube> hyper = getHyper();
  std::vector<int> ng = hyper->getNs();

  if (ng.size() > nw.size()) {
    for (int i = nw.size(); i < ng.size(); i++) {
      if (ng[i] > 1) error("number of dimension does not equal data size");
    }
  }
  if (nw.size() < ng.size() || fw.size() < ng.size() || jw.size() < jw.size()) {
    error("number of dimensions does not equal data size");
  }
  int ndim = ng.size();
  SEP::partsToBlock(hyper, 0, 8, nw, fw, jw, _buf.data(), array, _buf.data());
}

void memoryRegFile::readByteWindow(const std::vector<int> &nw,
                                   const std::vector<int> &fw,
                                   const std::vector<int> &jw,
                                   unsigned char *array) {
  if (_hyper == nullptr) throw SEPException(std::string("Must set hyper"));

  std::shared_ptr<hypercube> hyper = getHyper();
  std::vector<int> ng = getHyper()->getNs();

  if (ng.size() > nw.size()) {
    for (int i = nw.size(); i < ng.size(); i++) {
      if (ng[i] > 1) error("number of dimension does not equal data size");
    }
  }
  if (nw.size() < ng.size() || fw.size() < ng.size() || jw.size() < jw.size()) {
    error("number of dimensions does not equal data size");
  }
  SEP::partsToBlock(hyper, 0, 1, nw, fw, jw, array, _buf.data(), array);
}
void memoryRegFile::writeFloatWindow(const std::vector<int> &nw,
                                     const std::vector<int> &fw,
                                     const std::vector<int> &jw,
                                     const float *array) {
  if (_hyper == nullptr) throw SEPException(std::string("Must set hyper"));

  setDataType(DATA_FLOAT);

  std::shared_ptr<hypercube> hyper = getHyper();
  std::vector<int> ng = getHyper()->getNs();

  if (ng.size() > nw.size()) {
    for (int i = nw.size(); i < ng.size(); i++) {
      if (ng[i] > 1) error("number of dimension does not equal data size");
    }
  }
  if (nw.size() < ng.size() || fw.size() < ng.size() || jw.size() < jw.size()) {
    error("number of dimensions does not equal data size");
  }
  SEP::partsToBlock(hyper, 0, 4, nw, fw, jw, _buf.data(), array, _buf.data());
}
void memoryRegFile::writeByteWindow(const std::vector<int> &nw,
                                    const std::vector<int> &fw,
                                    const std::vector<int> &jw,
                                    const unsigned char *array) {
  if (_hyper == nullptr) throw SEPException(std::string("Must set hyper"));

  setDataType(DATA_BYTE);

  std::shared_ptr<hypercube> hyper = getHyper();
  std::vector<int> ng = getHyper()->getNs();

  if (ng.size() > nw.size()) {
    for (int i = nw.size(); i < ng.size(); i++) {
      if (ng[i] > 1) error("number of dimension does not equal data size");
    }
  }
  if (nw.size() < ng.size() || fw.size() < ng.size() || jw.size() < jw.size()) {
    error("number of dimensions does not equal data size");
  }
  SEP::partsToBlock(hyper, 0, 1, nw, fw, jw, _buf.data(), array, _buf.data());
}

void memoryRegFile::writeDoubleWindow(const std::vector<int> &nw,
                                      const std::vector<int> &fw,
                                      const std::vector<int> &jw,
                                      const double *array) {
  if (_hyper == nullptr) throw SEPException(std::string("Must set hyper"));

  setDataType(DATA_DOUBLE);

  std::shared_ptr<hypercube> hyper = getHyper();
  std::vector<int> ng = getHyper()->getNs();

  if (ng.size() > nw.size()) {
    for (int i = nw.size(); i < ng.size(); i++) {
      if (ng[i] > 1) error("number of dimension does not equal data size");
    }
  }
  if (nw.size() < ng.size() || fw.size() < ng.size() || jw.size() < jw.size()) {
    error("number of dimensions does not equal data size");
  }
  SEP::partsToBlock(hyper, 0, 8, nw, fw, jw, _buf.data(), array, _buf.data());
}
void memoryRegFile::writeIntWindow(const std::vector<int> &nw,
                                   const std::vector<int> &fw,
                                   const std::vector<int> &jw,
                                   const int *array) {
  if (_hyper == nullptr) throw SEPException(std::string("Must set hyper"));

  setDataType(DATA_INT);

  std::shared_ptr<hypercube> hyper = getHyper();
  std::vector<int> ng = hyper->getNs();
  if (ng.size() > nw.size()) {
    for (int i = nw.size(); i < ng.size(); i++) {
      if (ng[i] > 1) error("number of dimension does not equal data size");
    }
  }
  if (nw.size() < ng.size() || fw.size() < ng.size() || jw.size() < jw.size()) {
    error("number of dimensions does not equal data size");
  }
  SEP::partsToBlock(hyper, 0, 4, nw, fw, jw, _buf.data(), array, _buf.data());
}

void memoryRegFile::message(const std::string &arg) const {
  std::cerr << arg << std::endl;
}
void memoryRegFile::seekTo(const long long iv, const int whence) {
  if (whence == 0)
    _pos = iv;
  else if (whence == 1)
    _pos += iv;
  else
    _pos = _buf.size() + iv;
}

std::vector<std::string> memoryRegFile::splitString(
    const std::string &str) const {
  std::string delim = ",";
  std::vector<std::string> tokens;
  size_t prev = 0, pos = 0;
  do {
    pos = str.find(delim, prev);
    if (pos == std::string::npos) pos = str.length();
    std::string token = str.substr(prev, pos - prev);
    if (!token.empty()) tokens.push_back(token);
    prev = pos + delim.length();
  } while (pos < str.length() && prev < str.length());
  return tokens;
}
