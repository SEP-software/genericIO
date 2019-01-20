#ifndef GENERIC_FILE
#define GENERIC_FILE 1
#include <complex.h>
#include <memory>
#include <vector>
#include "byteHyper.h"
#include "complexHyper.h"
#include "doubleHyper.h"
#include "floatHyper.h"
#include "header.h"
#include "hypercube.h"
#include "intHyper.h"
#include "ioConfig.h"
#include "ioTypes.h"
#include "paramObj.h"
#include "sepVectorConfig.h"
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
  std::shared_ptr<regSpace> read();

  bool readFloatStream(std::shared_ptr<SEP::floatHyper> hyp);
  bool writeFloatStream(const std::shared_ptr<SEP::floatHyper> hyp);

  bool readFloatWindow(const std::vector<int> &nw, const std::vector<int> &fw,
                       const std::vector<int> &jw,
                       std::shared_ptr<SEP::floatHyper> hyp);
  bool writeFloatWindow(const std::vector<int> &nw, const std::vector<int> &fw,
                        const std::vector<int> &jw,
                        std::shared_ptr<SEP::floatHyper> hyp);
#ifdef USE_BYTE
  bool writeUCharStream(const std::shared_ptr<SEP::byteHyper> hyp);
  bool readByteStream(std::shared_ptr<SEP::byteHyper> hyp);
  bool writeByteStream(const std::shared_ptr<SEP::byteHyper> hyp);
  bool readByteWindow(const std::vector<int> &nw, const std::vector<int> &fw,
                      const std::vector<int> &jw,
                      std::shared_ptr<SEP::byteHyper> hyp);
  bool writeByteWindow(const std::vector<int> &nw, const std::vector<int> &fw,
                       const std::vector<int> &jw,
                       std::shared_ptr<SEP::byteHyper> hyp);
#endif
#ifdef USE_INT
  bool readIntStream(std::shared_ptr<SEP::intHyper> hyp);
  bool writeIntStream(const std::shared_ptr<SEP::intHyper> hyp);
  bool readIntWindow(const std::vector<int> &nw, const std::vector<int> &fw,
                     const std::vector<int> &jw,
                     const std::shared_ptr<SEP::intHyper> hyp);
  bool writeIntWindow(const std::vector<int> &nw, const std::vector<int> &fw,
                      const std::vector<int> &jw,
                      std::shared_ptr<SEP::intHyper> hyp);
#endif
#ifdef USE_COMPLEX
  bool readComplexStream(std::shared_ptr<SEP::complexHyper> hyp);
  bool writeComplexStream(const std::shared_ptr<SEP::complexHyper> hyp);
  bool readComplexWindow(const std::vector<int> &nw, const std::vector<int> &fw,
                         const std::vector<int> &jw,
                         std::shared_ptr<SEP::complexHyper> hyp);
  bool writeComplexWindow(const std::vector<int> &nw,
                          const std::vector<int> &fw,
                          const std::vector<int> &jw,
                          std::shared_ptr<SEP::complexHyper> hyp);

#endif
#ifdef USE_DOUBLE
  bool readDoubleStream(std::shared_ptr<SEP::doubleHyper> hyp);
  bool writeDoubleStream(const std::shared_ptr<SEP::doubleHyper> hyp);
  bool readDoubleWindow(const std::vector<int> &nw, const std::vector<int> &fw,
                        const std::vector<int> &jw,
                        const std::shared_ptr<SEP::doubleHyper> hyp);
  bool writeDoubleWindow(const std::vector<int> &nw, const std::vector<int> &fw,
                         const std::vector<int> &jw,
                         std::shared_ptr<SEP::doubleHyper> hyp);
#endif
  bool readWindow(const std::vector<int> &nw, const std::vector<int> &fw,
                  const std::vector<int> &jw,
                  std::shared_ptr<SEP::regSpace> hyp);
  bool writeWindow(const std::vector<int> &nw, const std::vector<int> &fw,
                   const std::vector<int> &jw,
                   std::shared_ptr<SEP::regSpace> hyp);

  virtual void readUCharStream(unsigned char *array, const long long npts) {
    if (array == 0 && npts == 0)
      ;
    throw SEPException(std::string("readUCharStream is undefined"));
  }
  virtual void readFloatStream(float *array, const long long npts) {
    if (array == 0 && npts == 0)
      ;
    throw SEPException(std::string("readFloatStream is undefined"));
  }
  virtual void writeFloatStream(const float *array, const long long npts) {
    if (array == 0 && npts == 0)
      ;
    throw SEPException(std::string("writeFloatStream is undefined"));
  }
  virtual void writeUCharStream(const unsigned char *array,
                                const long long npts) {
    if (array == 0 && npts == 0)
      ;
    throw SEPException(std::string("writeUCharStream is undefined"));
  }

  virtual void readUCharWindow(const std::vector<int> &nw,
                               const std::vector<int> &fw,
                               const std::vector<int> &jw,
                               unsigned char *array) {
    if (nw.size() == 0 && fw.size() == 0 && jw.size() == 0 && array != 0)
      ;
    throw SEPException(std::string("readUCharWindow is undefined"));
  }
  virtual void seekTo(const long long iv, const int whence) {
    if (whence == iv) {
      ;
    }
  }
  virtual void readComplexStream(std::complex<float> *array,
                                 const long long npts) {
    if (array == 0 && npts == 0)
      ;
    throw SEPException(std::string("readComplexStream is undefined"));
  }
  virtual void writeComplexStream(const std::complex<float> *array,
                                  const long long npts) {
    if (array == 0 && npts == 0)
      ;
    throw SEPException(std::string("writeComplexStream is undefined"));
  }
  virtual void readComplexWindow(const std::vector<int> &nw,
                                 const std::vector<int> &fw,
                                 const std::vector<int> &jw,
                                 std::complex<float> *array) {
    if (nw.size() == 0 && fw.size() == 0 && jw.size() == 0 && array != 0)
      ;
    throw SEPException(std::string("readComplexWindow is undefined"));
  }
  virtual void writeComplexWindow(const std::vector<int> &nw,
                                  const std::vector<int> &fw,
                                  const std::vector<int> &jw,
                                  const std::complex<float> *array) {
    if (nw.size() == 0 && fw.size() == 0 && jw.size() == 0 && array != 0)
      ;
    throw SEPException(std::string("writeComplexWindow is undefined"));
  }

  virtual long long getDataSize() {
    throw SEPException(std::string("getDataSize is undefined"));
  }
  virtual void readFloatWindow(const std::vector<int> &nw,
                               const std::vector<int> &fw,
                               const std::vector<int> &jw, float *array) {
    if (nw.size() == 0 && fw.size() == 0 && jw.size() == 0 && array != 0)
      ;
    throw SEPException(std::string("readFloatWindow is undefined"));
  }
  virtual void writeFloatWindow(const std::vector<int> &nw,
                                const std::vector<int> &fw,
                                const std::vector<int> &jw,
                                const float *array) {
    if (nw.size() == 0 && fw.size() == 0 && jw.size() == 0 && array != 0)
      ;
    throw SEPException(std::string("writeFloatWindow is undefined"));
  }

  virtual void readDoubleStream(double *array, const long long npts) {
    if (array == 0 && npts == 0)
      ;
    throw SEPException(std::string("readDoubleStream is undefined"));
  }
  virtual void writeDoubleStream(const double *array, const long long npts) {
    if (array == 0 && npts == 0)
      ;
    throw SEPException(std::string("writeDoubleStream is undefined"));
  }

  virtual void readDoubleWindow(const std::vector<int> &nw,
                                const std::vector<int> &fw,
                                const std::vector<int> &jw, double *array) {
    if (nw.size() == 0 && fw.size() == 0 && jw.size() == 0 && array != 0)
      ;
    throw SEPException(std::string("readDoubleWindow is undefined"));
  }

  virtual void writeDoubleWindow(const std::vector<int> &nw,
                                 const std::vector<int> &fw,
                                 const std::vector<int> &jw,
                                 const double *array) {
    if (nw.size() == 0 && fw.size() == 0 && jw.size() == 0 && array != 0)
      ;
    throw SEPException(std::string("writeDoubleWindow is undefined"));
  }

  virtual void readIntStream(int *array, const long long npts) {
    if (array == 0 && npts == 0)
      ;
    throw SEPException(std::string("readIntStream is undefined"));
  }
  virtual void writeIntStream(const int *array, const long long npts) {
    if (array == 0 && npts == 0)
      ;
    throw SEPException(std::string("writeIntStream is undefined"));
  }
  virtual void readIntWindow(const std::vector<int> &nw,
                             const std::vector<int> &fw,
                             const std::vector<int> &jw, int *array) {
    if (nw.size() == 0 && fw.size() == 0 && jw.size() == 0 && array != 0)
      ;
    throw SEPException(std::string("readIntWindow is undefined"));
  }
  virtual void writeIntWindow(const std::vector<int> &nw,
                              const std::vector<int> &fw,
                              const std::vector<int> &jw, const int *array) {
    if (nw.size() == 0 && fw.size() == 0 && jw.size() == 0 && array != 0)
      ;
    throw SEPException(std::string("writeIntWindow is undefined"));
  }
  virtual void writeUCharWindow(const std::vector<int> &nw,
                                const std::vector<int> &fw,
                                const std::vector<int> &jw,
                                const unsigned char *array) {
    if (nw.size() == 0 && fw.size() == 0 && jw.size() == 0 && array != 0)
      ;
    throw SEPException(std::string("writeUCharWindow is undefined"));
  }
  virtual void readDescription() { ; }
  virtual void writeDescription() { ; }
  virtual void close() { ; }
  virtual void setHyper(std::shared_ptr<SEP::hypercube> hyp) {
    if (_hyper) throw SEPException(std::string("hypercube not defined"));
    _hyper = hyp->clone();
  }
  dataType getDataType() { return _type; }
  int getDataEsize();
  void setDataType(const dataType typ) { _type = typ; }
  void setDataType(const std::string &typ) {
    setDataType(SEP::toElementType(typ));
  }
  std::string getDataTypeString();
  const std::shared_ptr<SEP::hypercube> getHyper() {
    if (_hyper) throw SEPException(std::string("hypercube not defined"));

    return _hyper;
  }

 protected:
  std::shared_ptr<SEP::hypercube> _hyper = 0;
  dataType _type = SEP::DATA_UNKNOWN;
};

class genericIrregFile : public genericRegFile {
 public:
  genericIrregFile() {}
  /*
  virtual std::shared_ptr<header> readHeaderWindow(const std::vector<int> &nw,
                                                   const std::vector<int> &fw,
                                                   const std::vector<int> &jw);
  virtual void writeHeaderWindow(const std::vector<int> &nw,
                                 const std::vector<int> &fw,
                                 const std::vector<int> &jw,
                                 std::shared_ptr<header> &header,
                                 std::vector<bool> &exists);
  virtual void readFloatData(std::shared_ptr<header> header, float *buf);
  virtual void readByteData(std::shared_ptr<header> header, unsigned char *buf);
  virtual void readDoubleData(std::shared_ptr<header> header, double *buf);
  virtual void readComplexData(std::shared_ptr<header> header,
                               std::complex<float> *buf);
  virtual void writeFloatData(std::shared_ptr<header> header, const float *buf);
  virtual void writeByteData(std::shared_ptr<header> header,
                             const unsigned char *buf);
  virtual void writeDoubleData(std::shared_ptr<header> header,
                               const double *buf);
  virtual void writeComplexData(std::shared_ptr<header> header,
                                const std::complex<float> *buf);
                              */
};
}  // namespace SEP

#endif
