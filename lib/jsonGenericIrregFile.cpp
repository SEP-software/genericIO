#include "jsonGenericIrregFile.h"
#include "stdio.h"
#include "string.h"
#include <cstdlib>
#include <exception>
#include <fstream>  // std::ifstream
#include <iostream> // std::cout
using namespace SEP;
jsonGenericIrregFile::jsonGenericIrregFile(const Json::Value &arg,
                                           const usage_code usage,
                                           const std::string &tag,
                                           const int reelH, const int traceH,
                                           const std::string &progName,
                                           const int ndim) {
  _usage = usage;
  setupJson(arg, tag);
  _reelH = reelH;
  _traceH = traceH;

  if (!_newFile) {
    readDescription(ndim);
    std::shared_ptr<myFileIO> x(
        new myFileIO(getDataFileName(), usage, reelH, traceH,
                     jsonArgs.get("esize", 4).asInt(),
                     jsonArgs.get("swapData", false).asBool(), getHyper()));
    myio = x;
  } else {
    std::string datapath = std::string("./");
    if (const char *env_p = std::getenv("DATAPATH"))
      datapath = std::string(env_p);
    _dataFile =
        datapath + std::string("/") + getJSONFileName() + std::string(".dat");
    jsonArgs["filename"] = _dataFile;
    // _binary = _dataFile;
  }
  jsonArgs["progName"] = progName;
}

// A Function to a vector of length [n][2] based on the second
bool sortFuncJSON(std::vector<int> i, std::vector<int> j) {
  return (i[1] < j[1]);
}

void jsonGenericIrregFile::setupJson(const Json::Value &arg,
                                     const std::string &tag,
                                     const std::string desFileDefault) {
  _tag = tag;

  if (arg[tag].isNull()) {
    _jsonFile = _tag + desFileDefault;
  } else {
    _jsonFile = arg[tag].asString();
  }
  _newFile = true;
  if (_usage == usageIn)
    _newFile = false;
  else if (_usage == usageInOut) {
    std::ifstream f(getJSONFileName());
    _newFile = !f.good();
    f.close();
  }

  if (_usage == usageIn || !_newFile) {
    std::ifstream inps;
    inps.open(getJSONFileName(), std::ifstream::in);
    if (!inps) {
      std::cerr << std::string("Trouble opening1 " + getJSONFileName())
                << std::endl;
      throw std::exception();
    }
    try {
      inps >> jsonArgs;
    } catch (int x) {
      std::cerr << std::string("Trouble parsing JSON file " + getJSONFileName())
                << std::endl;
      throw std::exception();
    }
    _dataFile = jsonArgs[std::string("filename")].asString();
    //  _binary = _dataFile;
  }
}
std::string jsonGenericIrregFile::getJSONFileName() const { return _jsonFile; }
std::string jsonGenericIrregFile::getDataFileName() const { return _dataFile; }
int jsonGenericIrregFile::getInt(const std::string &arg) const {
  int x;
  if (jsonArgs[arg].isNull())
    error(std::string("trouble grabbing parameter ") + arg +
          std::string(" from parameters"));
  x = jsonArgs.get(arg, 1).asInt();
  return x;
}
int jsonGenericIrregFile::getInt(const std::string &arg, const int def) const {
  int x = jsonArgs.get(arg, def).asInt();
  return x;
}
float jsonGenericIrregFile::getFloat(const std::string &arg,
                                     const float def) const {
  float x;
  x = jsonArgs.get(arg, def).asFloat();
  return x;
}

float jsonGenericIrregFile::getFloat(const std::string &arg) const {
  float x;
  if (jsonArgs[arg].isNull())
    error(std::string("trouble grabbing parameter ") + arg +
          std::string(" from parameters"));
  x = jsonArgs.get(arg, 1.).asFloat();
  return x;
}
std::string jsonGenericIrregFile::getString(const std::string &arg) const {
  if (jsonArgs[arg].isNull())
    error(std::string("trouble grabbing parameter ") + arg +
          std::string(" from parameters"));

  return jsonArgs.get(arg, "").asString();
}
std::string jsonGenericIrregFile::getString(const std::string &arg,
                                            const std::string &def) const {
  return jsonArgs.get(arg, def).asString();
}
bool jsonGenericIrregFile::getBool(const std::string &arg, bool def) const {
  return jsonArgs.get(arg, def).asBool();
}
bool jsonGenericIrregFile::getBool(const std::string &arg) const {
  if (jsonArgs[arg].isNull())
    error(std::string("trouble grabbing parameter ") + arg +
          std::string(" from parameters"));
  return jsonArgs.get(arg, false).asBool();
}
std::vector<int> jsonGenericIrregFile::getInts(const std::string &arg,
                                               const int nvals) const {
  if (jsonArgs[arg].isNull())
    error(std::string("trouble grabbing parameter ") + arg +
          std::string(" from parameters"));
  const Json::Value vals = jsonArgs[arg];

  std::vector<int> x;
  for (int i = 0; i < nvals; i++)
    x.push_back(vals[i].asInt());
  return x;
}
std::vector<int>
jsonGenericIrregFile::getInts(const std::string &arg,
                              const std::vector<int> &defs) const {
  std::vector<int> x;
  if (jsonArgs[arg].isNull()) {
    for (int i = 0; i < defs.size(); i++)
      x.push_back(defs[i]);
  } else {
    const Json::Value vals = jsonArgs[arg];
    for (int i = 0; i < defs.size(); i++)
      x.push_back(vals[i].asInt());
  }
  return x;
}
std::vector<float> jsonGenericIrregFile::getFloats(const std::string &arg,
                                                   const int nvals) const {
  if (jsonArgs[arg].isNull())
    error(std::string("trouble grabbing parameter ") + arg +
          std::string(" from parameters"));
  const Json::Value vals = jsonArgs[arg];

  std::vector<float> x;
  for (int i = 0; i < nvals; i++)
    x.push_back(vals[i].asFloat());
  return x;
}
std::vector<float>
jsonGenericIrregFile::getFloats(const std::string &arg,
                                const std::vector<float> &defs) const {
  std::vector<float> x;
  if (jsonArgs[arg].isNull()) {
    for (int i = 0; i < defs.size(); i++)
      x.push_back(defs[i]);
  } else {
    const Json::Value vals = jsonArgs[arg];
    for (int i = 0; i < defs.size(); i++)
      x.push_back(vals[i].asFloat());
  }
  return x;
}

void jsonGenericIrregFile::putInt(const std::string &par, const int val) {
  jsonArgs[par] = val;
}
void jsonGenericIrregFile::putFloat(const std::string &par, const float val) {
  jsonArgs[par] = val;
}
void jsonGenericIrregFile::putString(const std::string &par,
                                     const std::string &val) {
  jsonArgs[par] = val;
}
void jsonGenericIrregFile::putBool(const std::string &par, const bool val) {
  jsonArgs[par] = val;
}
void jsonGenericIrregFile::putInts(const std::string &par,
                                   const std::vector<int> &val) {
  Json::Value vals;
  for (int i = 0; i < val.size(); i++)
    vals.append(val[i]);
  jsonArgs[par] = vals;
}
void jsonGenericIrregFile::putFloats(const std::string &par,
                                     const std::vector<float> &val) {
  Json::Value vals;
  for (int i = 0; i < val.size(); i++)
    vals.append(val[i]);
  jsonArgs[par] = vals;
}
void jsonGenericIrregFile::readDescription(const int ndimMax) {
  int ndim;
  bool breakIt = false;
  int iax = 9;
  while (iax >= 1 && !breakIt) {
    std::string tmp;
    int n = getInt("n" + std::to_string(iax), 1);
    float o = getFloat("o" + std::to_string(iax), 0.);

    if (n > 1 || fabsf(o) > 1e-4)
      breakIt = true;
    else
      iax--;
  }
  if (iax == 0)
    error("couldn't find any axes");
  ndim = iax;

  std::vector<axis> axes;
  for (int i = 1; i <= ndim; i++) {
    int n = getInt(std::string("n") + std::to_string(i), 1);
    float o = getFloat(std::string("o") + std::to_string(i), 0.);
    float d = getFloat(std::string("d") + std::to_string(i), 1.);
    std::string label = getString(std::string("label") + std::to_string(i), "");
    axes.push_back(axis(n, o, d, label));
  }
  std::string dtyp = getString(std::string("dataType"), std::string("FLOAT"));
  if (dtyp == std::string("FLOAT"))
    setDataType(DATA_FLOAT);
  else if (dtyp == std::string("COMPLEX"))
    setDataType(DATA_COMPLEX);
  else if (dtyp == std::string("COMPLEXDOUBLE"))
    setDataType(DATA_COMPLEXDOUBLE);
  else if (dtyp == std::string("INTEGER"))
    setDataType(DATA_INT);
  else if (dtyp == std::string("DOUBLE"))
    setDataType(DATA_DOUBLE);
  else if (dtyp == std::string("BYTE"))
    setDataType(DATA_BYTE);

  std::shared_ptr<hypercube> hyper(new hypercube(axes));
  setHyper(hyper);
}
void jsonGenericIrregFile::setHistory(const Json::Value &input) {
  Json::Value hist;
  if (!input["history"].isNull()) {
    hist = input["history"];
  }
  Json::Value last;
  for (Json::Value::const_iterator itr = input.begin(); itr != input.end();
       itr++) {
    std::string key = itr.key().toStyledString();
    Json::Value value = (*itr);
    if (key == std::string("history")) {
      last[key] = value;
    }
  }
  hist.append(last);
  jsonArgs["history"] = hist;
}

void jsonGenericIrregFile::writeDescription() {
  std::shared_ptr<hypercube> hyper = getHyper();
  std::vector<axis> axes = hyper->returnAxes(hyper->getNdim());
  for (int i = 1; i <= axes.size(); i++) {
    putInt(std::string("n") + std::to_string(i), axes[i - 1].n);
    putFloat(std::string("o") + std::to_string(i), axes[i - 1].o);
    putFloat(std::string("d") + std::to_string(i), axes[i - 1].d);
    putString(std::string("label") + std::to_string(i), axes[i - 1].label);
  }
}
void jsonGenericIrregFile::close() {
  myio->close();
  if (_usage == usageOut || _usage == usageInOut) {
    std::ofstream outps;
    outps.open(getJSONFileName(), std::ofstream::out);
    if (!outps) {
      std::cerr << std::string("Trouble opening for write") + getJSONFileName()
                << std::endl;
      throw std::exception();
    }
    try {
      outps << jsonArgs;
    } catch (int x) {
      std::cerr << std::string("Trouble writing JSON file ") + getJSONFileName()
                << std::endl;
      throw std::exception();
    }
  }
}
void jsonGenericIrregFile::message(const std::string &errm) const {
  std::cerr << errm << std::endl;
}
void jsonGenericIrregFile::error(const std::string &errm) const {
  std::cerr << errm << std::endl;
  throw std::exception();
}
std::vector<std::string> jsonGenericIrregFile::getHeaderKeyList() const {
  std::vector<std::string> lst;
  for (int i = 0; i < _keys.size(); i++) {
    lst.push_back(_keys[i]);
  }
  return lst;
}

std::map<std::string, std::string>
jsonGenericIrregFile::getHeaderKeyTypes() const {
  std::map<std::string, std::string> lst;
  for (auto k = _keyType.begin(); k != _keyType.end(); k++) {
    lst[k->first] = k->second;
  }
  return lst;
}

void jsonGenericIrregFile::putHeaderKeyList(
    const std::vector<std::string> &keylist) {
  _keys.clear();
  for (int i = 0; i < keylist.size(); i++) {
    _keys.push_back(keylist[i]);
  }
}
void jsonGenericIrregFile::putHeaderKeyTypes(
    const std::map<std::string, std::string> &typs) {
  _keyType.clear();
  for (auto k = typs.begin(); k != typs.end(); k++) {
    _keyType[k->first] = k->second;
  }
}

std::tuple<std::shared_ptr<byte2DReg>, std::shared_ptr<int1DReg>>
jsonGenericIrregFile::readHeaderWindow(const std::vector<int> &nwind,
                                       const std::vector<int> &fwind,
                                       const std::vector<int> &jwind) {
  std::vector<std::vector<int>> headerLocs =
      readHeaderLocs(nwind, fwind, jwind);
  size_t idone = 0;
  int nkeyIn = _keys.size();
  if (_drn > -1)
    nkeyIn += 1;
  std::shared_ptr<byte2DReg> headBuf(new byte2DReg(4 * nkeyIn, 100000));
  std::shared_ptr<byte2DReg> headers(
      new byte2DReg(4 * _keys.size(), headerLocs.size()));
  std::shared_ptr<int1DReg> drns(new int1DReg(headerLocs.size()));
  while (idone < headerLocs.size()) {
    int ifirst = headerLocs[idone][1];
    bool found = false;
    int imore = 1;
    while (!found && ifirst + imore < headerLocs.size()) {
      if (headerLocs[idone][1] != idone + ifirst) {
        found = true;
        int ii = idone + 1;
        // if (0 !=
        //   sep_get_val_headers(_tag.c_str(), &ii, &imore, headBuf->getVals()))
        // throw SEPException(std::string("Trouble reading headers"));
        extractDRN(headers, idone, imore, drns, headBuf);
        idone += imore;
      } else
        imore += 1;
    }
  }
  if (idone != headerLocs.size()) {
    int ii = idone + 1;
    int imore = headerLocs.size() - idone;
    // if (0 != sep_get_val_headers(_tag.c_str(), &ii, &imore,
    // headBuf->getVals())) throw SEPException(std::string("Trouble reading
    // headers"));
    extractDRN(headers, idone, headerLocs.size() - idone, drns, headBuf);
  }
  return std::make_tuple(headers, drns);
}

void jsonGenericIrregFile::extractDRN(std::shared_ptr<byte2DReg> outV,
                                      const int ifirst, const int ntransfer,
                                      std::shared_ptr<int1DReg> drns,
                                      std::shared_ptr<byte2DReg> &temp) {
  int end = 0, beg = 4 * _keys.size();
  int n1out = beg, n1in = beg;
  if (_drn >= 0) {
    beg = 4 * _drn;
    end = 4 * (_keys.size() - _drn);
    n1in += 4;
  }

  unsigned char *in = temp->getVals();
  unsigned char *out = outV->getVals();
  int *rns = drns->getVals();
  for (int i = 0; i < ntransfer; i++) {
    memcpy(out + n1out * (ifirst + i), in + n1in * i, beg);
    if (_drn >= 0)
      memcpy(rns + ifirst + i, in + n1in * i + beg, 4);
    if (end > 0)
      memcpy(out + n1out * (ifirst + i) + beg, in + n1in * i + beg + 4, end);
  }
}

std::vector<std::vector<int>>
jsonGenericIrregFile::readHeaderLocs(const std::vector<int> &nwind,
                                     const std::vector<int> &fwind,
                                     const std::vector<int> &jwind) {

  if (_haveGrid) {
    std::vector<int> ng, nw = nwind, fw = fwind, jw = jwind;

    nw[0] = 1;
    fw[0] = 0;
    jw[0] = 1;
    long long n123 = 1;
    ng = getHyper()->getNs();
    checkWindow(nw, fw, jw, _hyper);
    for (int i = 0; i < nw.size(); i++)
      n123 *= (long long)nw[i];
    std::vector<int> grid(n123);
    int ndim = ng.size();
    //  if (0 != sep_get_grid_window(_tag.c_str(), &ndim, &ng[1], &nw[1],
    //  &fw[1],
    //                             &jw[1], &grid[0]))
    //  throw SEPException("Trouble reading grid");

    int ireal = 0;
    for (auto i = 0; i < n123; i++)
      if (grid[i] >= 0)
        ireal++;
    std::vector<std::vector<int>> headPos(ireal, std::vector<int>(2));
    ireal = 0;
    for (auto i = 0; i < n123; i++) {
      if (grid[i] >= 0) {
        headPos[ireal][0] = ireal;
        headPos[ireal][1] = grid[i] - 1;
        ireal++;
      }
    }
    std::sort(headPos.begin(), headPos.end(), sortFuncJSON);
    return headPos;
  } else {
    std::vector<int> bs(1, 1);
    std::vector<int> ns = _hyperHeader->getNs();
    for (auto i = 1; i < ns.size(); i++)
      bs.push_back(bs[i - 1] * ns[i]);

    std::vector<std::vector<int>> headPos(bs[ns.size()], std::vector<int>(2));

    for (auto i = 0; i < headPos.size(); i++) {
      headPos[i][0] = i;
      headPos[i][1] = i;
    }
    return headPos;
  }
}
void jsonGenericIrregFile::readArrangeTraces(
    std::vector<std::vector<int>> &itrs, const int n1, void *temp, void *data) {

  int idone = 0;
  while (idone < itrs.size()) {
    bool found = false;
    int iread = 1;
    while (!found && idone + iread < itrs.size()) {
      if (itrs[idone + iread][1] != itrs[idone][1] + iread || iread > 9999) {
        found = true;
        //   if (iread * n1 != sreed(_tag.c_str(), temp, iread * n1))
        //    throw SEPException("trouble reading data");
        for (int i = 0; i < iread; i++) {
          memcpy((char *)data + itrs[idone + i][0] * n1, (char *)temp + i * n1,
                 n1);
        }
        found = true;
        idone += iread;
      }
    }
  }
}

std::pair<std::shared_ptr<byte2DReg>, std::shared_ptr<float2DReg>>
jsonGenericIrregFile::readFloatTraceWindow(const std::vector<int> &nwind,
                                           const std::vector<int> &fwind,
                                           const std::vector<int> &jwind) {
  if (getDataType() != DATA_FLOAT)
    throw SEPException("Attempt to read float from a non-float file");
  std::pair<std::shared_ptr<byte2DReg>, std::shared_ptr<int1DReg>> head_drn =
      readHeaderWindow(nwind, fwind, jwind);
  std::shared_ptr<int1DReg> drn = std::get<1>(head_drn);

  int ntr = drn->getHyper()->getN123();
  std::shared_ptr<float2DReg> data(
      new float2DReg(_hyperData->getAxis(1).n, ntr));

  std::vector<std::vector<int>> headPos(ntr, std::vector<int>(2));
  for (int i = 0; i < ntr; i++) {
    headPos[i][0] = i;
    headPos[i][1] = (*drn->_mat)[i];
  }
  int n1 = _hyperData->getAxis(1).n;
  std::sort(headPos.begin(), headPos.end(), sortFuncJSON);
  std::shared_ptr<float2DReg> temp(new float2DReg(n1, 10000));
  readArrangeTraces(headPos, n1 * 4, (void *)temp->getVals(),
                    (void *)data->getVals());
  return std::make_pair(std::get<0>(head_drn), data);
}

std::pair<std::shared_ptr<byte2DReg>, std::shared_ptr<int2DReg>>
jsonGenericIrregFile::readIntTraceWindow(const std::vector<int> &nwind,
                                         const std::vector<int> &fwind,
                                         const std::vector<int> &jwind) {
  if (getDataType() != DATA_INT)
    throw SEPException("Attempt to read int from a non-float file");
  std::pair<std::shared_ptr<byte2DReg>, std::shared_ptr<int1DReg>> head_drn =
      readHeaderWindow(nwind, fwind, jwind);
  std::shared_ptr<int1DReg> drn = std::get<1>(head_drn);

  int ntr = drn->getHyper()->getN123();
  std::shared_ptr<int2DReg> data(new int2DReg(_hyperData->getAxis(1).n, ntr));
  int n1 = _hyperData->getAxis(1).n;

  std::vector<std::vector<int>> headPos(ntr, std::vector<int>(2));
  for (int i = 0; i < ntr; i++) {
    headPos[i][0] = i;
    headPos[i][1] = (*drn->_mat)[i];
  }
  std::sort(headPos.begin(), headPos.end(), sortFuncJSON);
  std::shared_ptr<int2DReg> temp(new int2DReg(n1, 10000));
  readArrangeTraces(headPos, n1 * 4, (void *)temp->getVals(),
                    (void *)data->getVals());
  return std::make_pair(std::get<0>(head_drn), data);
}

std::pair<std::shared_ptr<byte2DReg>, std::shared_ptr<double2DReg>>
jsonGenericIrregFile::readDoubleTraceWindow(const std::vector<int> &nwind,
                                            const std::vector<int> &fwind,
                                            const std::vector<int> &jwind) {
  if (getDataType() != DATA_DOUBLE)
    throw SEPException("Attempt to read int from a non-float file");
  std::pair<std::shared_ptr<byte2DReg>, std::shared_ptr<int1DReg>> head_drn =
      readHeaderWindow(nwind, fwind, jwind);
  std::shared_ptr<int1DReg> drn = std::get<1>(head_drn);

  int ntr = drn->getHyper()->getN123();
  std::shared_ptr<double2DReg> data(
      new double2DReg(_hyperData->getAxis(1).n, ntr));
  int n1 = _hyperData->getAxis(1).n;

  std::vector<std::vector<int>> headPos(ntr, std::vector<int>(2));
  for (int i = 0; i < ntr; i++) {
    headPos[i][0] = i;
    headPos[i][1] = (*drn->_mat)[i];
  }
  std::sort(headPos.begin(), headPos.end(), sortFuncJSON);
  std::shared_ptr<double2DReg> temp(new double2DReg(n1, 10000));
  readArrangeTraces(headPos, n1 * 8, (void *)temp->getVals(),
                    (void *)data->getVals());
  return std::make_pair(std::get<0>(head_drn), data);
}
std::pair<std::shared_ptr<byte2DReg>, std::shared_ptr<byte2DReg>>
jsonGenericIrregFile::readByteTraceWindow(const std::vector<int> &nwind,
                                          const std::vector<int> &fwind,
                                          const std::vector<int> &jwind) {

  if (getDataType() != DATA_DOUBLE)
    throw SEPException("Attempt to read int from a non-float file");
  std::pair<std::shared_ptr<byte2DReg>, std::shared_ptr<int1DReg>> head_drn =
      readHeaderWindow(nwind, fwind, jwind);
  std::shared_ptr<int1DReg> drn = std::get<1>(head_drn);

  int ntr = drn->getHyper()->getN123();
  std::shared_ptr<byte2DReg> data(new byte2DReg(_hyperData->getAxis(1).n, ntr));

  std::vector<std::vector<int>> headPos(ntr, std::vector<int>(2));
  for (int i = 0; i < ntr; i++) {
    headPos[i][0] = i;
    headPos[i][1] = (*drn->_mat)[i];
  }
  int n1 = _hyperData->getAxis(1).n;

  std::sort(headPos.begin(), headPos.end(), sortFuncJSON);
  std::shared_ptr<byte2DReg> temp(new byte2DReg(n1, 10000));
  readArrangeTraces(headPos, n1 * 1, (void *)temp->getVals(),
                    (void *)data->getVals());
  return std::make_pair(std::get<0>(head_drn), data);
}

Json::Value jsonGenericIrregFile::getDataDescription() {
  Json::Value x;
  return x;
}
void jsonGenericIrregFile::putDataDescription(const Json::Value &desc) {
  if (desc["a"].asInt() == 4)
    ;
  ;
}
void jsonGenericIrregFile::remove() { ; }
std::pair<std::shared_ptr<byte2DReg>, std::shared_ptr<complex2DReg>>
jsonGenericIrregFile::readComplexTraceWindow(const std::vector<int> &nwind,
                                             const std::vector<int> &fwind,
                                             const std::vector<int> &jwind) {
  if (getDataType() != DATA_COMPLEX)
    throw SEPException("Attempt to read int from a non-float file");
  std::pair<std::shared_ptr<byte2DReg>, std::shared_ptr<int1DReg>> head_drn =
      readHeaderWindow(nwind, fwind, jwind);
  std::shared_ptr<int1DReg> drn = std::get<1>(head_drn);

  int ntr = drn->getHyper()->getN123();
  std::shared_ptr<complex2DReg> data(
      new complex2DReg(_hyperData->getAxis(1).n, ntr));

  std::vector<std::vector<int>> headPos(ntr, std::vector<int>(2));
  for (int i = 0; i < ntr; i++) {
    headPos[i][0] = i;
    headPos[i][1] = (*drn->_mat)[i];
  }
  int n1 = _hyperData->getAxis(1).n;

  std::sort(headPos.begin(), headPos.end(), sortFuncJSON);
  std::shared_ptr<complex2DReg> temp(new complex2DReg(n1, 10000));
  readArrangeTraces(headPos, n1 * 8, (void *)temp->getVals(),
                    (void *)data->getVals());
  return std::make_pair(std::get<0>(head_drn), data);
}
std::pair<std::shared_ptr<byte2DReg>, std::shared_ptr<complexDouble2DReg>>
jsonGenericIrregFile::readComplexDoubleTraceWindow(
    const std::vector<int> &nwind, const std::vector<int> &fwind,
    const std::vector<int> &jwind) {
  if (getDataType() != DATA_COMPLEXDOUBLE)
    throw SEPException("Attempt to read int from a non-float file");
  std::pair<std::shared_ptr<byte2DReg>, std::shared_ptr<int1DReg>> head_drn =
      readHeaderWindow(nwind, fwind, jwind);
  std::shared_ptr<int1DReg> drn = std::get<1>(head_drn);

  int ntr = hdrn->getHyper()->getN123();
  std::shared_ptr<complexDouble2DReg> data(
      new complexDouble2DReg(_hyperData->getAxis(1).n, ntr));
  int n1 = _hyperData->getAxis(1).n;

  std::vector<std::vector<int>> headPos(ntr, std::vector<int>(2));
  for (int i = 0; i < ntr; i++) {
    headPos[i][0] = i;
    headPos[i][1] = (*drn->_mat)[i];
  }
  std::sort(headPos.begin(), headPos.end(), sortFuncJSON);
  std::shared_ptr<complexDouble2DReg> temp(new complexDouble2DReg(n1, 10000));
  readArrangeTraces(headPos, n1 * 16, (void *)temp->getVals(),
                    (void *)data->getVals());
  return std::make_pair(std::get<0>(head_drn), data);
}
void jsonGenericIrregFile::addtDRN(std::shared_ptr<byte2DReg> inV,
                                   const int ifirst, const int ntransfer,
                                   std::shared_ptr<int1DReg> drns,
                                   std::shared_ptr<byte2DReg> &outV) {
  int n1in = inV->getHyper()->getAxis(1).n * 4;
  int n1out = outV->getHyper()->getAxis(1).n * 4;

  unsigned char *in = inV->getVals();
  unsigned char *out = outV->getVals();

  int *rns = drns->getVals();
  for (int i = 0; i < ntransfer; i++) {
    memcpy(out + n1out * i, in + n1in * i, n1in);
    memcpy(out + n1out * i + n1in, rns + i, 4);
  }
}
void jsonGenericIrregFile::writeGrid(const std::vector<int> &nwind,
                                     const std::vector<int> &fwind,
                                     const std::vector<int> &jwind,
                                     const std::shared_ptr<byte2DReg> &headers,
                                     const std::shared_ptr<byte1DReg> &byte

) {

  long long first = 0, last = 0;
  long long sz = 1;
  checkWindow(nwind, fwind, jwind, _hyper);
  if (!_haveGrid)
    throw SEPException("Can not write dataset that doesn't have a grid");
  std::vector<int> ns = _hyper->getNs();
  for (auto i = 0; i < nwind.size(); i++) {
    first += fwind[i] * sz;
    last += (fwind[i] + jwind[i] * nwind[i]) * sz;
    sz = sz * (long long)nwind[i];
  }
  if (_writeLastG + 1 != first)
    throw SEPException("Non-consecutive read of grid");
  int n2h = 0;
  for (auto i = 0; i < byte->getHyper()->getN123(); i++) {
    if ((*byte->_mat)[i] > 0)
      n2h += 1;
  }
  if (n2h != headers->getHyper()->getAxis(2).n)
    throw SEPException(
        "Number of headers does not match number of non-zero grid elements");
  int ih = 0;
  std::shared_ptr<int1DReg> grid(new int1DReg(byte->getHyper()->getN123()));
  for (auto i = 0; i < byte->getHyper()->getN123(); i++) {
    if ((*byte->_mat)[i] != 0) {
      ih++;
      (*grid->_mat)[i] = _writeLastH + ih;
    }
  }
  std::vector<int> ng = _hyper->getNs();
  int ndim = ng.size();

  // if (0 != sep_put_grid_window(_tag.c_str(), &ndim, &ng[1], &nwind[1],
  //                           &fwind[1], &jwind[1], grid->getVals()))
  // throw SEPException("Trouble writing grid");

  _writeLastG = last;
}
void jsonGenericIrregFile::writeHeaderWindow(
    const std::vector<int> &nwind, const std::vector<int> &fwind,
    const std::vector<int> &jwind, const std::shared_ptr<int1DReg> &drn,
    const std::shared_ptr<byte2DReg> &headers,
    const std::shared_ptr<byte1DReg> &grid) {

  writeGrid(nwind, fwind, jwind, headers, grid);
  std::vector<int> ns = headers->getHyper()->getNs();

  if (_inOrder) {
    int ifirst = _writeLastH + 1;
    int nblock = ns[1];

    // if (0 !=
    //   sep_put_val_headers(_tag.c_str(), &ifirst, &nblock,
    //   headers->getVals()))
    // throw SEPException("Trouble writing headers");
  }

  else {
    std::shared_ptr<byte2DReg> temp(
        new byte2DReg(ns[0] + 4, std::min(100000, ns[1])));
    int idone = 0;
    while (idone < ns[1]) {
      int nblock = (ns[1] - idone, 100000);
      int ifirst = _writeLastH + idone + 1;
      // if (0 !=
      //    sep_put_val_headers(_tag.c_str(), &ifirst, &nblock,
      //    temp->getVals()))
      // throw SEPException("Trouble writing "
      //                   "headers");
      idone += nblock;
    }

    _writeLastH += ns[1];
  }
}
void jsonGenericIrregFile::writeComplexDoubleTraceWindow(
    const std::vector<int> &nwind, const std::vector<int> &fwind,
    const std::vector<int> &jwind, std::shared_ptr<byte2DReg> &headers,
    std::shared_ptr<complexDouble2DReg> &data,
    const std::shared_ptr<byte1DReg> &grid) {

  if (getDataType() != DATA_COMPLEXDOUBLE)
    throw SEPException("Expecting datatype complex double");

  writeGrid(nwind, fwind, jwind, headers, grid);
  std::vector<int> ns = headers->getHyper()->getNs();

  int ifirst = _writeLastH + 1;
  int nblock = ns[1];

  // if (0 !=
  //   sep_put_val_headers(_tag.c_str(), &ifirst, &nblock, headers->getVals()))
  //  throw SEPException("Trouble writing headers");
  // if (16 * ns[1] * data->getHyper()->getAxis(1).n !=
  //    srite(_tag.c_str(), data->getVals(),
  //        16 * ns[1] * data->getHyper()->getAxis(1).n))
  // throw SEPException("Trouble writing data");
}

void jsonGenericIrregFile::writeComplexTraceWindow(
    const std::vector<int> &nwind, const std::vector<int> &fwind,
    const std::vector<int> &jwind, const std::shared_ptr<byte2DReg> &headers,
    const std::shared_ptr<complex2DReg> &data,
    const std::shared_ptr<byte1DReg> &grid) {
  if (getDataType() != DATA_COMPLEXDOUBLE)
    throw SEPException("Expecting datatype complex ");

  writeGrid(nwind, fwind, jwind, headers, grid);
  std::vector<int> ns = headers->getHyper()->getNs();

  int ifirst = _writeLastH + 1;
  int nblock = ns[1];

  // if (0 !=
  //    sep_put_val_headers(_tag.c_str(), &ifirst, &nblock, headers->getVals()))
  //  throw SEPException("Trouble writing headers");
  // if (8 * ns[1] * data->getHyper()->getAxis(1).n !=
  //    srite(_tag.c_str(), data->getVals(),
  //         8 * ns[1] * data->getHyper()->getAxis(1).n))
  // throw SEPException("Trouble writing data");
}
void jsonGenericIrregFile::writeDoubleTraceWindow(
    const std::vector<int> &nwind, const std::vector<int> &fwind,
    const std::vector<int> &jwind, const std::shared_ptr<byte2DReg> &headers,
    const std::shared_ptr<double2DReg> &data,
    const std::shared_ptr<byte1DReg> &grid) {
  if (getDataType() != DATA_DOUBLE)
    throw SEPException("Expecting datatype double");

  writeGrid(nwind, fwind, jwind, headers, grid);
  std::vector<int> ns = headers->getHyper()->getNs();

  int ifirst = _writeLastH + 1;
  int nblock = ns[1];
  /*
    if (0 !=
        sep_put_val_headers(_tag.c_str(), &ifirst, &nblock, headers->getVals()))
      throw SEPException("Trouble writing headers");
    if (8 * ns[1] * data->getHyper()->getAxis(1).n !=
        srite(_tag.c_str(), data->getVals(),
              8 * ns[1] * data->getHyper()->getAxis(1).n))
      throw SEPException("Trouble writing data");
      */
}
void jsonGenericIrregFile::writeIntTraceWindow(
    const std::vector<int> &nwind, const std::vector<int> &fwind,
    const std::vector<int> &jwind, const std::shared_ptr<byte2DReg> &headers,
    const std::shared_ptr<int2DReg> &data,
    const std::shared_ptr<byte1DReg> &grid) {
  if (getDataType() != DATA_INT)
    throw SEPException("Expecting datatype int");

  writeGrid(nwind, fwind, jwind, headers, grid);
  std::vector<int> ns = headers->getHyper()->getNs();

  int ifirst = _writeLastH + 1;
  int nblock = ns[1];
  /*
    if (0 !=
        sep_put_val_headers(_tag.c_str(), &ifirst, &nblock, headers->getVals()))
      throw SEPException("Trouble writing headers");
    if (4 * ns[1] * data->getHyper()->getAxis(1).n !=
        srite(_tag.c_str(), data->getVals(),
              4 * ns[1] * data->getHyper()->getAxis(1).n))
      throw SEPException("Trouble writing data");
  */
}
void jsonGenericIrregFile::writeFloatTraceWindow(
    const std::vector<int> &nwind, const std::vector<int> &fwind,
    const std::vector<int> &jwind, const std::shared_ptr<byte2DReg> &headers,
    const std::shared_ptr<float2DReg> &data,
    const std::shared_ptr<byte1DReg> &grid) {
  if (getDataType() != DATA_FLOAT)
    throw SEPException("Expecting datatype complex double");

  writeGrid(nwind, fwind, jwind, headers, grid);
  std::vector<int> ns = headers->getHyper()->getNs();

  int ifirst = _writeLastH + 1;
  int nblock = ns[1];
  /*
    if (0 !=
        sep_put_val_headers(_tag.c_str(), &ifirst, &nblock, headers->getVals()))
      throw SEPException("Trouble writing headers");
    if (4 * ns[1] * data->getHyper()->getAxis(1).n !=
        srite(_tag.c_str(), data->getVals(),
              4 * ns[1] * data->getHyper()->getAxis(1).n))
      throw SEPException("Trouble writing data");
  */
}

void jsonGenericIrregFile::writeByteTraceWindow(
    const std::vector<int> &nwind, const std::vector<int> &fwind,
    const std::vector<int> &jwind, const std::shared_ptr<byte2DReg> &headers,
    const std::shared_ptr<byte2DReg> &data,
    const std::shared_ptr<byte1DReg> &grid) {
  if (getDataType() != DATA_BYTE)
    throw SEPException("Expecting datatype byte");

  writeGrid(nwind, fwind, jwind, headers, grid);
  std::vector<int> ns = headers->getHyper()->getNs();

  int ifirst = _writeLastH + 1;
  int nblock = ns[1];
  /*
    if (0 !=
        sep_put_val_headers(_tag.c_str(), &ifirst, &nblock, headers->getVals()))
      throw SEPException("Trouble writing headers");
    if (1 * ns[1] * data->getHyper()->getAxis(1).n !=
        srite(_tag.c_str(), data->getVals(),
              1 * ns[1] * data->getHyper()->getAxis(1).n))
      throw SEPException("Trouble writing data");
  */
}

/*!

Set that the data is out of order


*/
void jsonGenericIrregFile::setOutOfOrder() { _inOrder = false; }

std::string jsonGenericIrregFile::getJSONFileBaseName() const {

  char seperator = '/';
  std::string filePath = getJSONFileName();
  std::size_t sepPos = filePath.rfind(seperator);

  if (sepPos != std::string::npos) {
    return filePath.substr(sepPos + 1, filePath.size());
  }
  return filePath;
}