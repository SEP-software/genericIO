#include "ioModes.h"
#include <iostream>
#include "buffersConfig.h"
#include "fileBuffersIO.h"
#include "ioConfig.h"
#include "segyIO.h"
#ifdef USE_RSF
#include "rsfIO.h"
#endif
#ifdef USE_SEP
#include "sepIO.h"
#endif
#ifdef USE_GCP
#include "gcpBuffersIO.h"
#endif
using namespace SEP;
void ioModes::setup(const int argc, char **argv) {
  std::shared_ptr<jsonGenericIO> a(new jsonGenericIO(argc, argv));

  _ios["JSON"] = a;

  std::shared_ptr<segyIO> d(new segyIO(argc, argv));
  _ios["SEGY"] = d;

  std::shared_ptr<fileBuffersIO> m(new fileBuffersIO(argc, argv));
  _ios["FILEBUFFERS"] = m;

#ifdef BUILD_GCP
  std::shared_ptr<gcpBuffersIO> m(new gcpBuffersIO(argc, argv));
  _ios["GCPBUFFERS"] = m;
#endif

#ifdef USE_RSF
  std::shared_ptr<rsfIO> b(new rsfIO(argc, argv));
  _ios["RSF"] = b;
#endif
#ifdef USE_SEP

  std::shared_ptr<sepIO> c(new sepIO(argc, argv));
  _ios["SEP"] = c;
#else
#endif

  _defaultType = DEFAULTIO;
  _defaultIO = _ios[_defaultType];
}
std::shared_ptr<genericIO> ioModes::getDefaultIO() {
  return getIO(_defaultType);
}

std::shared_ptr<genericIO> ioModes::getIO(const std::string &def) {
  if (_ios.count(def) != 1)
    _par->error(def + " io has not been defined and/or built");
  return _ios[def];
}
std::shared_ptr<genericRegFile> ioModes::getRegFileTag(
    const std::string &tag, const std::string &ioname, const std::string &name,
    usage_code usage) {
  if (_ios.count(def) == 0)
    _par->error(def + " io has not been defined and/or built");
  if (!_ios[def]->getValid())
    _par->error(def + std::string(" has not been initialized correctly"));
  return _ios[def]->getRegFile(name, usage);
}
std::shared_ptr<genericRegFile> ioModes::getGenericRegFile(
    const std::string &name, const usage_code usage) {
  return _defaultIO->getRegFile(name, usage);
}
std::shared_ptr<ioModesFortran> ioModesFortran::instance = nullptr;
void ioModesFortran::setup(const int argc, char **argv) {
  std::shared_ptr<ioModes> x(new ioModes(argc, argv));
  _io = x;
}
