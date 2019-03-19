#ifndef buffers_irreg_file_h
#define buffers_irreg_file_h 1
#include <stdbool.h>
#include <string>
#include "basicIO.h"
#include "buffers.h"
#include "json.h"
#include "jsonGenericIrregFile.h"
namespace SEP {
class buffersIrregFile : public jsonGenericIrregFile {
 public:
  // sepRegFile::sepRegFile(const std::string tag,usage_code usage){

  buffersIrregFile() { ; }

  virtual void writeDescription();

  void setMemoryUsage(std::shared_ptr<SEP::IO::memoryUsage> mem) {
    if (!_hyper) throw SEPException(std::string("Hypercube has not been set"));
    _mem = mem;
  }
  void setCompression(std::shared_ptr<SEP::IO::compress> com) { _comp = com; }
  void setBlocking(std::shared_ptr<SEP::IO::blocking> block) { _block = block; }

  virtual void createBuffers() = 0;

 protected:
  std::shared_ptr<SEP::IO::buffers> _bufs = nullptr;
  std::shared_ptr<SEP::IO::memoryUsage> _mem = nullptr;
  std::shared_ptr<SEP::IO::compress> _comp = nullptr;
  std::shared_ptr<SEP::IO::blocking> _block = nullptr;

};  // namespace SEP

}  // namespace SEP
#endif
