#ifndef JSON_IRREGFILE_FUNC_H
#define JSON_IRREGFILE_FUNC_H 1
#include <stdbool.h>
#include <string>
#include "basicIO.h"
#include "genericFile.h"
#include "ioTypes.h"
#include "json.h"
namespace SEP {
class jsonGenericIrregFile : public genericIrregFile {
 public:
  // sepRegFile::sepRegFile(const std::string tag,usage_code usage){

  jsonGenericIrregFile() { ; }
  jsonGenericIrregFile(const Json::Value &arg, const SEP::usage_code usage,
                       const std::string &tag, const int reelH,
                       const int traceH, const std::string &progName,
                       const int ndim = -1);
  void setupJson(const Json::Value &jsonArgs, const std::string &tag,
                 const std::string desFileDefault = std::string(""));
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
                                   int nvals) const override;
  virtual std::vector<int> getInts(const std::string &arg,
                                   const std::vector<int> &defs) const override;

  virtual std::vector<float> getFloats(const std::string &arg,
                                       const int nvals) const override;
  virtual std::vector<float> getFloats(
      const std::string &arg, const std::vector<float> &defs) const override;
  virtual void message(const std::string &err) const override;

  virtual void error(const std::string &err) const override;
  Json::Value getArgs() { return jsonArgs; }
  std::string getTag() { return _tag; }
  virtual void close() override;
  void setUsage(const usage_code usage) { _usage = usage; }
  void setHistory(const Json::Value &hist);
  usage_code getUsage() { return _usage; }
  virtual std::string getJSONFileName() const;
  std::string getDataFileName() const;
  virtual void readDescription(const int ndimMax) override;
  virtual void writeDescription() override;
  virtual void putInt(const std::string &par, const int val) override;
  virtual void putFloat(const std::string &par, const float val) override;
  virtual void putString(const std::string &par,
                         const std::string &val) override;
  virtual void putBool(const std::string &par, const bool val) override;
  virtual void putInts(const std::string &par,
                       const std::vector<int> &val) override;
  virtual void putFloats(const std::string &par,
                         const std::vector<float> &val) override;
  virtual std::shared_ptr<genericHeaderObj> readHeaderWindow(
      const std::vector<int> &nw, const std::vector<int> &fw,
      const std::vector<int> &jw) override {
    ;
  }
  virtual void writeHeaderWindow(const std::vector<int> &nw,
                                 const std::vector<int> &fw,
                                 const std::vector<int> &jw,
                                 std::shared_ptr<genericHeaderObj> header,
                                 std::vector<bool> &exists) override {
    ;
  }

 protected:
  Json::Value jsonArgs;
  bool _newFile;
  dataType _dtype;

  std::string _tag;
  usage_code _usage;
  std::string _jsonFile, _dataFile;
  std::shared_ptr<myFileIO> myio;
  int _reelH, _traceH;
};
}  // namespace SEP

#endif
