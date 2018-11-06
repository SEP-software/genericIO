#ifndef SEP_REGFILE_FUNC_H
#define SEP_REGFILE_FUNC_H 1
#include <stdbool.h>
#include <string>
#include "genericFile.h"
namespace SEP {
class sepRegFile : public SEP::genericRegFile {
 public:
  // sepRegFile::sepRegFile(const std::string tag,usage_code usage){

  sepRegFile(const std::string &tg, const SEP::usage_code usage);
  virtual int getInt(const std::string &arg) const override;
  virtual int getInt(const std::string &arg, const int def) const override;

  virtual float getFloat(const std::string &, const float def) const override;
  virtual float getFloat(const std::string &) const override;

  virtual std::string getString(const std::string &arg) const override;
  virtual std::string getString(const std::string &arg,
                                const std::string &def) const override;

  virtual void seekTo(const long long iv, const int whence) override;
  virtual bool getBool(const std::string &, const bool def) const override;
  virtual bool getBool(const std::string &) const override;

  virtual std::vector<int> getInts(const std::string &arg,
                                   int nvals) const override;
  virtual std::vector<int> getInts(const std::string &arg,
                                   const std::vector<int> &defs) const override;

  virtual std::vector<float> getFloats(const std::string &arg,
                                       int nvals) const override;
  virtual std::vector<float> getFloats(
      const std::string &arg, const std::vector<float> &defs) const override;

  virtual void message(const std::string &err) const override;
  virtual void error(const std::string &err) const override;

  virtual void readUCharStream(unsigned char *array,
                               const long long npts) override;

  virtual void writeUCharStream(const unsigned char *array,
                                const long long npts) override;
  virtual void readComplexStream(std::complex<float> *array,
                                 const long long npts) override;
  virtual void writeComplexStream(const std::complex<float> *array,
                                  const long long npts) override;

  virtual void readFloatStream(float *array, const long long npts) override;
  virtual void writeFloatStream(const float *array,
                                const long long npts) override;

  virtual void readIntStream(int *array, const long long npts) override;
  virtual void writeIntStream(const int *array, const long long npts) override;

  virtual void readDoubleStream(double *array, const long long npts) override;
  virtual void writeDoubleStream(const double *array,
                                 const long long npts) override;

  virtual void readDoubleWindow(const std::vector<int> &nw,
                                const std::vector<int> &fw,
                                const std::vector<int> &jw,
                                double *array) override;

  virtual void writeDoubleWindow(const std::vector<int> &nw,
                                 const std::vector<int> &fw,
                                 const std::vector<int> &jw,
                                 const double *array) override;

  virtual void readIntWindow(const std::vector<int> &nw,
                             const std::vector<int> &fw,
                             const std::vector<int> &jw, int *array) override;

  virtual void writeIntWindow(const std::vector<int> &nw,
                              const std::vector<int> &fw,
                              const std::vector<int> &jw,
                              const int *array) override;

  virtual void readUCharWindow(const std::vector<int> &nw,
                               const std::vector<int> &fw,
                               const std::vector<int> &jw,
                               unsigned char *array) override;

  virtual void readFloatWindow(const std::vector<int> &nw,
                               const std::vector<int> &fw,
                               const std::vector<int> &jw,
                               float *array) override;
  virtual void writeUCharWindow(const std::vector<int> &nw,
                                const std::vector<int> &fw,
                                const std::vector<int> &jw,
                                const unsigned char *array) override;
  virtual void writeFloatWindow(const std::vector<int> &nw,
                                const std::vector<int> &fw,
                                const std::vector<int> &jw,
                                const float *array) override;
  virtual void readComplexWindow(const std::vector<int> &nw,
                                 const std::vector<int> &fw,
                                 const std::vector<int> &jw,
                                 std::complex<float> *array) override;

  virtual void writeComplexWindow(const std::vector<int> &nw,
                                  const std::vector<int> &fw,
                                  const std::vector<int> &jw,
                                  const std::complex<float> *array) override;

  virtual void readDescription() override;
  virtual void writeDescription() override;
  virtual void close() override;
  virtual void putInt(const std::string &par, const int val) override;
  virtual void putFloat(const std::string &par, const float val) override;
  virtual void putString(const std::string &par,
                         const std::string &val) override;
  virtual void putBool(const std::string &par, const bool val) override;
  virtual void putInts(const std::string &par,
                       const std::vector<int> &val) override;
  virtual void putFloats(const std::string &par,
                         const std::vector<float> &val) override;

 private:
  std::string _tag;
};
}  // namespace SEP

#endif
