#include "pythonParams.h"
#include "SEPException.h"
using namespace SEP;

pythonParams::pythonParams(std::map<std::string, std::string> pars) {
  _pars = pars;
}

int pythonParams::getInt(const std::string &arg) const {
  if (_pars.count(arg) == 1) return std::stoi(_pars.at(arg));
  error(std::string("1trouble grabbing parameter ") + arg +
        std::string(" from parameters"));
  return 0;
}
int pythonParams::getInt(const std::string &arg, const int def) const {
  if (_pars.count(arg) == 1) return std::stoi(_pars.at(arg));
  return def;
}

float pythonParams::getFloat(const std::string &arg, const float def) const {
  if (_pars.count(arg) == 1) return std::stof(_pars.at(arg));
  return def;
}
float pythonParams::getFloat(const std::string &arg) const {
  if (_pars.count(arg) == 1) return std::stof(_pars.at(arg));

  error(std::string("trouble grabbing parameter ") + arg +
        std::string(" from parameters"));
  return 0.;
}
void pythonParams::message(const std::string &arg) const {
  std::cerr << arg << std::endl;
}

std::string pythonParams::getString(const std::string &arg) const {
  if (_pars.count(arg) == 1) return _pars.at(arg);

  error(std::string("trouble grabbing parameter ") + arg +
        std::string(" from parameters"));
  return "null";
}
std::string pythonParams::getString(const std::string &arg,
                                    const std::string &def) const {
  if (_pars.count(arg) == 1) return _pars.at(arg);
  if (_pars.count(arg) == 1) return _pars.at(arg);
  return def;
}

bool pythonParams::getBool(const std::string &arg, bool def) const {
  if (_pars.count(arg) == 1) {
    if (_pars.at(arg).at(0) == 'y' || _pars.at(arg).at(0) == 'Y' ||
        _pars.at(arg).at(0) == '1')
      return true;
    return false;
  }
  return def;
}
bool pythonParams::getBool(const std::string &arg) const {
  if (_pars.count(arg) == 1) {
    if (_pars.at(arg).at(0) == 'y' || _pars.at(arg).at(0) == 'Y' ||
        _pars.at(arg).at(0) == '1')
      return true;
    return false;
  }
  error(std::string("trouble grabbing parameter ") + arg +
        std::string(" from parameters"));
  return false;
}
std::vector<std::string> pythonParams::splitString(
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

std::vector<int> pythonParams::getInts(const std::string &arg,
                                       const int nvals) const {
  if (_pars.count(arg) == 0) {
    error(std::string("trouble grabbing parameter ") + arg +
          std::string(" from parameters"));
  }

  std::vector<int> array;
  std::vector<std::string> strs = splitString(_pars.at(arg));
  for (auto i = 0; std::min((int)strs.size(), nvals); i++) {
    array.push_back(std::stoi(strs[i]));
  }
  return array;
}
std::vector<int> pythonParams::getInts(const std::string &arg,
                                       const std::vector<int> &defs) const {
  if (_pars.count(arg) == 0) {
    return defs;
  }

  std::vector<int> array;
  std::vector<std::string> strs = splitString(_pars.at(arg));
  for (auto i = 0; strs.size(); i++) {
    array.push_back(std::stoi(strs[i]));
  }
  return array;
}

std::vector<float> pythonParams::getFloats(const std::string &arg,
                                           const int nvals) const {
  if (_pars.count(arg) == 0) {
    error(std::string("trouble grabbing parameter ") + arg +
          std::string(" from parameters"));
  }

  std::vector<float> array;
  std::vector<std::string> strs = splitString(_pars.at(arg));
  for (auto i = 0; std::min((int)strs.size(), nvals); i++) {
    array.push_back(std::stof(strs[i]));
  }
  return array;
}
std::vector<float> pythonParams::getFloats(
    const std::string &arg, const std::vector<float> &defs) const {
  if (_pars.count(arg) == 0) {
    return defs;
  }

  std::vector<float> array;
  std::vector<std::string> strs = splitString(_pars.at(arg));
  for (auto i = 0; strs.size(); i++) {
    array.push_back(std::stof(strs[i]));
  }
  return array;
}

void pythonParams::error(const std::string &errm) const {
  throw SEPException(errm);
}
