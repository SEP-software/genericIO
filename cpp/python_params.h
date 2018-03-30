#ifndef SEP_PARAM_FUNC_H
#define SEP_PARAM_FUNC_H 1
#include <stdbool.h>
#include <string>
#include "paramObj.h"
namespace SEP {
class pythonParam : public SEP::paramObj {
 public:
  pythonParams(std::map<std::string, std::string> pars);
  virtual int getInt(const std::string &arg) const;
  virtual int getInt(const std::string &arg, const int def) const;

  virtual float getFloat(const std::string &, const float def) const;
  virtual float getFloat(const std::string &) const;

  virtual std::string getString(const std::string &arg) const;
  virtual std::string getString(const std::string &arg,
                                const std::string &def) const;

  virtual bool getBool(const std::string &, const bool def) const;
  virtual bool getBool(const std::string &) const;

  virtual std::vector<int> getInts(const std::string &arg,
                                   const int nvals) const;
  virtual std::vector<int> getInts(const std::string &arg,
                                   const std::vector<int> &defs) const;

  virtual std::vector<float> getFloats(const std::string &arg,
                                       const int nvals) const;
  virtual std::vector<float> getFloats(const std::string &arg,
                                       const std::vector<float> &defs) const;

  virtual void error(const std::string &errm) const;
  virtual void message(const std::string &msg) const;

 private:
  std::map<std::string, std::string> _pars;
};
}  // namespace SEP

#endif
