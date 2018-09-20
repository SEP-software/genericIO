#ifndef JSON_REGFILE_FUNC_H
#define JSON_REGFILE_FUNC_H 1
#include <stdbool.h>
#include <string>
#include "basicIO.h"
#include "genericFile.h"
#include "ioTypes.h"
#include "json.h"
namespace SEP {
class jsonGenericFile : public genericIrregFile {
 public:
  // sepRegFile::sepRegFile(const std::string tag,usage_code usage){

  jsonGenericFile() { ; }
  jsonGenericFile(const Json::Value &arg, const SEP::usage_code usage,
                  const std::string &tag, const int reelH, const int traceH,
                  const std::string &progName);
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
  virtual void close();
  void setUsage(const usage_code usage) { _usage = usage; }
  void setHistory(const Json::Value &hist);
  usage_code getUsage() { return _usage; }
  virtual std::string getJSONFileName() const;
  std::string getDataFileName() const;
  virtual void readDescription();
  virtual void writeDescription();
  virtual void putInt(const std::string &par, const int val);
  virtual void putFloat(const std::string &par, const float val);
  virtual void putString(const std::string &par, const std::string &val);
  virtual void putBool(const std::string &par, const bool val);
  virtual void putInts(const std::string &par, const std::vector<int> &val);
  virtual void putFloats(const std::string &par, const std::vector<float> &val);
  virtual void readFloatStream(float *array, const long long npts);
  virtual void readUCharStream(unsigned char *array, const long long npts);
  virtual void seekTo(const long long iv, const int whence);

  virtual void writeFloatStream(const float *array,
                                const long long npts) override;
  virtual void writeUCharStream(const unsigned char *array,
                                const long long npts) override;

  virtual void readUCharWindow(const std::vector<int> &nw,
                               const std::vector<int> &fw,
                               const std::vector<int> &jw,
                               unsigned char *array) override;
  virtual void writeUCharWindow(const std::vector<int> &nw,
                                const std::vector<int> &fw,
                                const std::vector<int> &jw,
                                const unsigned char *array) override;
  virtual void readFloatWindow(const std::vector<int> &nw,
                               const std::vector<int> &fw,
                               const std::vector<int> &jw, float *array);
  virtual long long getDataSize();
  virtual void writeFloatWindow(const std::vector<int> &nw,
                                const std::vector<int> &fw,
                                const std::vector<int> &jw, const float *array);
  virtual void readComplexWindow(const std::vector<int> &nw,
                                 const std::vector<int> &fw,
                                 const std::vector<int> &jw,
                                 std::complex<float> *array) override;

  virtual void writeComplexWindow(const std::vector<int> &nw,
                                  const std::vector<int> &fw,
                                  const std::vector<int> &jw,
                                  const std::complex<float> *array);
  virtual void writeComplexStream(const std::complex<float> *array,
                                  const long long npts) override;
  virtual void readComplexStream(std::complex<float> *array,
                                 const long long npts);

  virtual void writeDoubleStream(const double *array,
                                 const long long npts) override;
  virtual void readDoubleStream(double *array, const long long npts) override;
  virtual void readDoubleWindow(const std::vector<int> &nw,
                                const std::vector<int> &fw,
                                const std::vector<int> &jw,
                                double *array) override;
  virtual void writeDoubleWindow(const std::vector<int> &nw,
                                 const std::vector<int> &fw,
                                 const std::vector<int> &jw,
                                 const double *array) override;

  virtual void writeIntStream(const int *array, const long long npts) override;
  virtual void readIntStream(int *array, const long long npts) override;
  virtual void readIntWindow(const std::vector<int> &nw,
                             const std::vector<int> &fw,
                             const std::vector<int> &jw, int *array) override;
  virtual void writeIntWindow(const std::vector<int> &nw,
                              const std::vector<int> &fw,
                              const std::vector<int> &jw,
                              const int *array) override;

 protected:
  Json::Value jsonArgs;
  bool _newFile;
  dataType _dtype;

 private:
  std::string _tag;
  usage_code _usage;
  std::string _jsonFile, _dataFile;
  std::shared_ptr<myFileIO> myio;
  int _reelH, _traceH;
};
}  // namespace SEP

#endif
