#ifndef file_buffers_reg_file_h
#define file_buffers_reg_file_h 1
#include <stdbool.h>
#include <string>
#include "basicIO.h"
#include "buffers.h"
#include "buffersIrregFile.h"
#include "buffersRegFile.h"
#include "json.h"
namespace SEP {
class fileBuffersRegFile : public buffersRegFile {
 public:
  // sepRegFile::sepRegFile(const std::string tag,usage_code usage){

  fileBuffersRegFile() { ; }
  fileBuffersRegFile(const Json::Value &arg, const SEP::usage_code usage,
                     const std::string &tag, const std::string &progName,
                     const int ndimMax = -1);

  virtual void close();

  void createBuffers();
};

class fileBuffersIrregFile : public buffersIrregFile {
 public:
  // sepRegFile::sepRegFile(const std::string tag,usage_code usage){

  fileBuffersIrregFile() { ; }
  fileBuffersIrregFile(const Json::Value &arg, const SEP::usage_code usage,
                       const std::string &tag, const std::string &progName,
                       const int ndimMax = -1);

  virtual void close();

  void createBuffers();

};  // namespace SEP

}  // namespace SEP

#endif
