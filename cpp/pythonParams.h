#ifndef SEP_PARAM_FUNC_H
#define SEP_PARAM_FUNC_H 1
#include <stdbool.h>
#include <map>
#include <string>
#include "paramObj.h"
namespace SEP {
class pythonParams : public SEP::paramObj {
 public:
  pythonParams(std::map<std::string, std::string> pars);
  virtual int getInt(const std::string &arg) const override;
  virtual int getInt(const std::string &arg, const int def) const override;

  virtual float getFloat(const std::string &, const float def) const override;
  virtual float getFloat(const std::string &) const override;

  virtual std::string getString(const std::string &arg) const override;
  virtual std::string getString(const std::string &arg,
                                const std::string &def) const override;

  virtual bool getBool(const std::string &, const bool def) const override;
  virtual bool getBool(const std::string &) const override;

  virtual std::vector<int> getInts(const std::string &arg,
                                   const int nvals) const override;
  virtual std::vector<int> getInts(const std::string &arg,
                                   const std::vector<int> &defs) const override;

  virtual std::vector<float> getFloats(const std::string &arg,
                                       const int nvals) const override;
  virtual std::vector<float> getFloats(
      const std::string &arg, const std::vector<float> &defs) const override;

  virtual void error(const std::string &errm) const override;
  virtual void message(const std::string &msg) const override;
  std::vector<std::string> splitString(const std::string &in) const;

 private:
  std::map<std::string, std::string> _pars;
};
}  // namespace SEP

#endif
