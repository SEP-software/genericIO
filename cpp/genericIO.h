#ifndef GENERIC_IO_H
#define GENERIC_IO_H 1
#include <assert.h>
#include <map>
#include <memory>
#include "genericFile.h"
#include "paramObj.h"
namespace SEP {
/** Abstract Class for different types IO*/
class genericIO {
 public:
  genericIO() { _type = "NONE"; }

  /**
     @brief Return genericRegFile object for this IO (abstract)
     @param name The filetag/name
     @param usage Usage for file
   */
  std::shared_ptr<SEP::genericRegFile> getRegFile(const std::string &name,
                                                  const SEP::usage_code usage);
  std::shared_ptr<SEP::genericIrregFile> getIrregFile(
      const std::string &name, const SEP::usage_code usage);
  virtual std::shared_ptr<SEP::genericRegFile> getRegFileTag(
      const std::string &tag, const std::string &name,
      const SEP::usage_code usage) = 0;
  virtual std::shared_ptr<SEP::genericRegFile> getRegFile(
      const std::string &name, const std::string usage) {
    SEP::usage_code code;
    if (usage == std::string("UsageIn")) {
      code = usageIn;
    } else if (usage == std::string("UsageInOut"))
      code = usageInOut;
    else if (usage == std::string("UsageOut"))
      code = usageOut;
    else if (usage == std::string("UsageScr"))
      code = usageScr;
    else {
      _param->error(std::string("Unknown code ") + usage);
    }
    return getRegFile(name, code);
  }

  virtual std::shared_ptr<SEP::genericIrregFile> getIrregFileTag(
      const std::string &tag, const std::string &name,
      const SEP::usage_code usage) = 0;
  virtual std::shared_ptr<paramObj> getParamObj() { return _param; }
  void addRegFile(std::string x, std::shared_ptr<genericRegFile> r) {
    _regFiles[x] = r;
  }
  void addIrregFile(std::string x, std::shared_ptr<genericIrregFile> r) {
    _irregFiles[x] = r;
  }
  std::shared_ptr<genericRegFile> getRegFile(const std::string x) {
    if (!regFileExists(x))
      _param->error(std::string("Requested unknown file ") + x);
    return _regFiles[x];
  }
  bool regFileExists(const std::string name) {
    if (_regFiles.count(name) == 0) return false;
    return true;
  }
  bool irregFileExists(const std::string name) {
    if (_irregFiles.count(name) == 0) return false;
    return true;
  }
  void fileDebug(const std::string, const float *data, const int n1,
                 const int n2);
  void fileDebug(const std::string, const float *data, const int n1,
                 const int n2, const int n3);

  std::shared_ptr<genericIrregFile> getIrregFile(const std::string x) {
    if (_irregFiles.count(x) == 0)
      _param->error(std::string("Requested unknown file ") + x);
    return _irregFiles[x];
  }
  void setValid(const bool x) { _valid = x; }
  bool getValid() { return _valid; }

  virtual void close() { filesClose(); }

  ~genericIO() { close(); }
  virtual void filesClose();
  std::string _type;

 protected:
  std::map<std::string, std::shared_ptr<genericRegFile> > _regFiles;
  std::map<std::string, std::shared_ptr<genericIrregFile> > _irregFiles;
  std::shared_ptr<paramObj> _param;
  bool _valid;
};  // namespace SEP
}  // namespace SEP
#endif
