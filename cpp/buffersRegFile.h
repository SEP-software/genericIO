#ifndef BUFFERS_REGFILE_FUNC_H
#define BUFFERS_REGFILE_FUNC_H 1
#include <stdbool.h>
#include <string>
#include "basicIO.h"
#include "buffers.h"
#include "json.h"
#include "jsonGenericFile.h"
namespace SEP {
class buffersRegFile : public jsonGenericFile {
 public:
  // sepRegFile::sepRegFile(const std::string tag,usage_code usage){

  buffersRegFile() { ; }
  buffersRegFile(const Json::Value &arg, const SEP::usage_code usage,
                 const std::string &tag, const std::string &progName);

  virtual void close();
  virtual void writeDescription();
  virtual void readUCharStream(unsigned char *array, const long long npts) {
    error(std::string("can not stream buffer datasets, must use window"));
  }
  virtual void writeComplexStream(const std::complex<float> *array,
                                  const long long npts) {
    error(std::string("can not stream buffer datasets, must use window"));
  }
  virtual void readComplexStream(std::complex<float> *array,
                                 const long long npts) {
    error(std::string("can not stream buffer datasets, must use window"));
  }
  virtual void writeFloatStream(const float *array, const long long npts) {
    error(std::string("can not stream buffer datasets, must use window"));
  }
  virtual void readFloatStream(float *array, const long long npts) {
    error(std::string("can not stream buffer datasets, must use window"));
  }
  virtual void writeIntStream(const int *array, const long long npts) {
    error(std::string("can not stream buffer datasets, must use window"));
  }
  virtual void readIntStream(int *array, const long long npts) {
    error(std::string("can not stream buffer datasets, must use window"));
  }
  virtual void writeDoubleStream(const double *array, const long long npts) {
    error(std::string("can not stream buffer datasets, must use window"));
  }
  virtual void readDoubleStream(double *array, const long long npts) {
    error(std::string("can not stream buffer datasets, must use window"));
  }
  virtual void readUCharWindow(const std::vector<int> &nw,
                               const std::vector<int> &fw,
                               const std::vector<int> &jw,
                               unsigned char *array) {
    createBuffers();
    _bufs->getWindow(nw, fw, jw, (void *)array);
  }
  virtual void readFloatWindow(const std::vector<int> &nw,
                               const std::vector<int> &fw,
                               const std::vector<int> &jw, float *array) {
    createBuffers();

    _bufs->getWindow(nw, fw, jw, (void *)array);
  }
  virtual void writeFloatWindow(const std::vector<int> &nw,
                                const std::vector<int> &fw,
                                const std::vector<int> &jw,
                                const float *array) {
    createBuffers();
    _bufs->putWindow(nw, fw, jw, (void *)array);
  }
  virtual void readComplexWindow(const std::vector<int> &nw,
                                 const std::vector<int> &fw,
                                 const std::vector<int> &jw,
                                 std::complex<float> *array) {
    createBuffers();
    _bufs->getWindow(nw, fw, jw, (void *)array);
  }
  virtual void writeComplexWindow(const std::vector<int> &nw,
                                  const std::vector<int> &fw,
                                  const std::vector<int> &jw,
                                  const std::complex<float> *array) {
    createBuffers();
    _bufs->putWindow(nw, fw, jw, (void *)array);
  }
  virtual void readInrWindow(const std::vector<int> &nw,
                             const std::vector<int> &fw,
                             const std::vector<int> &jw, int *array) {
    createBuffers();
    _bufs->getWindow(nw, fw, jw, (void *)array);
  }
  virtual void writeIntWindow(const std::vector<int> &nw,
                              const std::vector<int> &fw,
                              const std::vector<int> &jw, const int *array) {
    createBuffers();
    _bufs->putWindow(nw, fw, jw, (void *)array);
  }
  virtual void readDoubleWindow(const std::vector<int> &nw,
                                const std::vector<int> &fw,
                                const std::vector<int> &jw, double *array) {
    createBuffers();
    _bufs->getWindow(nw, fw, jw, (void *)array);
  }
  virtual void writeDoubleWindow(const std::vector<int> &nw,
                                 const std::vector<int> &fw,
                                 const std::vector<int> &jw,
                                 const double *array) {
    createBuffers();
    _bufs->putWindow(nw, fw, jw, (void *)array);
  }
  void setMemoryUsage(std::shared_ptr<SEP::IO::memoryUsage> mem) {
    assert(_hyper);
    _mem = mem;
  }
  void setCompression(std::shared_ptr<SEP::IO::compress> com) { _comp = com; }
  void setBlocking(std::shared_ptr<SEP::IO::blocking> block) { _block = block; }
  void createBuffers();

 private:
  std::shared_ptr<SEP::IO::buffers> _bufs = nullptr;
  std::shared_ptr<SEP::IO::memoryUsage> _mem;
  std::shared_ptr<SEP::IO::compress> _comp;
  std::shared_ptr<SEP::IO::blocking> _block;

};  // namespace SEP
}  // namespace SEP

#endif
