#pragma once
#include <stdbool.h>
#include <string>
#include "basicIO.h"
#include "buffers.h"
#include "buffersRegFile.h"
#include "json.h"
namespace SEP {
class gcpBuffersRegFile : public buffersRegFile {
 public:
  // sepRegFile::sepRegFile(const std::string tag,usage_code usage){

  gcpBuffersRegFile() { ; }
  gcpBuffersRegFile(const Json::Value &arg, const SEP::usage_code usage,
                    const std::string &tag, const std::string &progName);

  void setupGCP(const Json::Value &arg, const std::string &tag);
  virtual void close();

  void setupGCP(const std::string arg, const std::string tag);
  void createBuffers();

 private:
  void setupGCP();

};  // namespace SEP

}  // namespace SEP
