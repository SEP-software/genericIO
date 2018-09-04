#ifndef GENERIC_FILE
#define GENERIC_FILE 1
#include <assert.h>
#include <complex.h>
#include <memory>
#include <vector>
#include "byteHyper.h"
#include "complexHyper.h"
#include "doubleHyper.h"
#include "floatHyper.h"
#include "hypercube.h"
#include "intHyper.h"
#include "ioConfig.h"
#include "ioTypes.h"
#include "paramObj.h"

namespace SEP {
enum usage_code { usageIn, usageOut, usageInOut, usageScr };

class genericRegFile : public paramObj {
 public:
  genericRegFile() { _type = DATA_UNKNOWN; }

  virtual void putInt(const std::string &par, const int val);
  virtual void putFloat(const std::string &par, const float val) {
    if (par == "" && val == 0) {
      ;
    }
  }
  virtual void putString(const std::string &par, const std::string &val) {
    if (par == "" && val == "") {
      ;
    }
  }
  virtual void putBool(const std::string &par, const bool val) {
    if (par == "" && val == 0) {
      ;
    }
  }
  virtual void putInts(const std::string &par, const std::vector<int> &val) {
    if (par == "" && val[0] == 0) {
      ;
    }
  }
  virtual void putFloats(const std::string &par,
                         const std::vector<float> &val) {
    if (par == "" && val[0] == 0) {
      ;
    }
  }
  bool readFloatStream(std::shared_ptr<SEP::floatHyper> hyp);
  bool writeFloatStream(const std::shared_ptr<SEP::floatHyper> hyp);
  bool writeUCharStream(const std::shared_ptr<SEP::byteHyper> hyp);

  bool readFloatWindow(const std::vector<int> &nw, const std::vector<int> &fw,
                       const std::vector<int> &jw,
                       std::shared_ptr<SEP::floatHyper> hyp);
  bool writeFloatWindow(const std::vector<int> &nw, const std::vector<int> &fw,
                        const std::vector<int> &jw,
                        std::shared_ptr<SEP::floatHyper> hyp);

  bool readByteStream(std::shared_ptr<SEP::byteHyper> hyp);
  bool writeByteStream(const std::shared_ptr<SEP::byteHyper> hyp);
  bool readByteWindow(const std::vector<int> &nw, const std::vector<int> &fw,
                      const std::vector<int> &jw,
                      std::shared_ptr<SEP::byteHyper> hyp);
  bool writeByteWindow(const std::vector<int> &nw, const std::vector<int> &fw,
                       const std::vector<int> &jw,
                       std::shared_ptr<SEP::byteHyper> hyp);

  bool readIntStream(std::shared_ptr<SEP::intHyper> hyp);
  bool writeIntStream(const std::shared_ptr<SEP::intHyper> hyp);
  bool readIntWindow(const std::vector<int> &nw, const std::vector<int> &fw,
                     const std::vector<int> &jw,
                     std::shared_ptr<SEP::intHyper> hyp);
  bool writeIntWindow(const std::vector<int> &nw, const std::vector<int> &fw,
                      const std::vector<int> &jw,
                      std::shared_ptr<SEP::intHyper> hyp);

  bool readComplexStream(std::shared_ptr<SEP::complexHyper> hyp);
  bool writeComplexStream(const std::shared_ptr<SEP::complexHyper> hyp);
  bool readComplexWindow(const std::vector<int> &nw, const std::vector<int> &fw,
                         const std::vector<int> &jw,
                         std::shared_ptr<SEP::complexHyper> hyp);
  bool writeComplexWindow(const std::vector<int> &nw,
                          const std::vector<int> &fw,
                          const std::vector<int> &jw,
                          std::shared_ptr<SEP::complexHyper> hyp);

  bool readDoubleStream(std::shared_ptr<SEP::doubleHyper> hyp);
  bool writeDoubleStream(const std::shared_ptr<SEP::doubleHyper> hyp);
  bool readDoubleWindow(const std::vector<int> &nw, const std::vector<int> &fw,
                        const std::vector<int> &jw,
                        std::shared_ptr<SEP::doubleHyper> hyp);
  bool writeDoubleWindow(const std::vector<int> &nw, const std::vector<int> &fw,
                         const std::vector<int> &jw,
                         std::shared_ptr<SEP::doubleHyper> hyp);

  virtual void readUCharStream(unsigned char *array, const long long npts) = 0;
  virtual void readFloatStream(float *array, const long long npts) = 0;
  virtual void writeFloatStream(const float *array, const long long npts) = 0;
  virtual void writeUCharStream(const unsigned char *array,
                                const long long npts) = 0;

  virtual void readUCharWindow(const std::vector<int> &nw,
                               const std::vector<int> &fw,
                               const std::vector<int> &jw,
                               unsigned char *array) = 0;
  virtual void seekTo(const long long iv, const int whence) {
    if (whence == iv) {
      ;
    }
  }
  virtual void readComplexStream(std::complex<float> *array,
                                 const long long npts) = 0;
  virtual void writeComplexStream(const std::complex<float> *array,
                                  const long long npts) = 0;
  virtual void readComplexWindow(const std::vector<int> &nw,
                                 const std::vector<int> &fw,
                                 const std::vector<int> &jw,
                                 std::complex<float> *array) = 0;
  virtual void writeComplexWindow(const std::vector<int> &nw,
                                  const std::vector<int> &fw,
                                  const std::vector<int> &jw,
                                  const std::complex<float> *array) = 0;

  virtual long long getDataSize() { assert(1 == 2); }
  virtual void readFloatWindow(const std::vector<int> &nw,
                               const std::vector<int> &fw,
                               const std::vector<int> &jw, float *array) = 0;
  virtual void writeFloatWindow(const std::vector<int> &nw,
                                const std::vector<int> &fw,
                                const std::vector<int> &jw,
                                const float *array) = 0;

  virtual void readDoubleStream(double *array, const long long npts) = 0;
  virtual void writeDoubleStream(const double *array, const long long npts) = 0;

  virtual void readDoubleWindow(const std::vector<int> &nw,
                                const std::vector<int> &fw,
                                const std::vector<int> &jw, double *array) = 0;

  virtual void writeDoubleWindow(const std::vector<int> &nw,
                                 const std::vector<int> &fw,
                                 const std::vector<int> &jw,
                                 const double *array) = 0;

  virtual void readIntStream(int *array, const long long npts) = 0;
  virtual void writeIntStream(const int *array, const long long npts) = 0;
  virtual void readIntWindow(const std::vector<int> &nw,
                             const std::vector<int> &fw,
                             const std::vector<int> &jw, int *array) = 0;
  virtual void writeIntWindow(const std::vector<int> &nw,
                              const std::vector<int> &fw,
                              const std::vector<int> &jw, const int *array) = 0;
  virtual void writeUCharWindow(const std::vector<int> &nw,
                                const std::vector<int> &fw,
                                const std::vector<int> &jw,
                                const unsigned char *array) = 0;
  virtual void readDescription() { ; }
  virtual void writeDescription() { ; }
  virtual void close() { ; }
  void setHyper(std::shared_ptr<SEP::hypercube> hyp) { _hyper = hyp; }
  dataType getDataType() { return _type; }
  int getDataEsize();
  void setDataType(const dataType typ) { _type = typ; }
  std::string getDataTypeString();
  const std::shared_ptr<SEP::hypercube> getHyper() {
    if (!_hyper) error(std::string("Hypercube has not been setup"));
    return _hyper;
  }

 protected:
  std::shared_ptr<SEP::hypercube> _hyper;
  dataType _type;
};

union headerType {
  int i;
  short s;
  long long l;
  double d;
  float f;
};
class genericIrregFile : public genericRegFile {
 public:
  genericIrregFile() {}
  virtual int getHeaderIndex(std::string keyname) {
    if (keyname == std::string("")) {
      ;
    }
    return 0;
  }
  virtual std::vector<headerType> getTraceHeader(long long index) {
    if (index == 0) {
      ;
    }
    std::vector<headerType> x;
    return x;
  }
  virtual std::vector<std::string> getHeaderTypes() {
    std::vector<std::string> a;
    return a;
  }
};
}  // namespace SEP

#endif
