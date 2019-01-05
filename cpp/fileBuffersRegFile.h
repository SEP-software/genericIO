#pragma once
#include <stdbool.h>
#include <string>
#include "basicIO.h"
#include "buffers.h"
#include "buffersRegFile.h"
#include "json.h"
namespace SEP {
class fileBuffersRegFile : public buffersRegFile {
 public:
  // sepRegFile::sepRegFile(const std::string tag,usage_code usage){

  fileBuffersRegFile() { ; }
  fileBuffersRegFile(const Json::Value &arg, const SEP::usage_code usage,
                     const std::string &tag, const std::string &progName);

  virtual void close();

  void createBuffers();

};  // namespace SEP

}  // namespace SEP
