#ifndef gcp_buffers_reg_file_h
#define gcp_buffers_reg_file_h 1
#include <stdbool.h>
#include <string>
#include "basicIO.h"
#include "buffers.h"
#include "buffersRegFile.h"
#include "json.h"
namespace SEP {
/*!
Object for handling regular files broken into blocks and written to objects on
GCP
*/
class gcpBuffersRegFile : public buffersRegFile {
 public:
  // sepRegFile::sepRegFile(const std::string tag,usage_code usage){
  /*!
      Initialize the default GCP boject
  */
  gcpBuffersRegFile() { ; }
  /*!
    Initialize GCP regular file
      \param arg  JSON arguments
      \param usage Usage for file
      \param tag Tag associated with GCP file
      \param progName Program name
      \param ndimMax Minimum number of dimensions
*/
  gcpBuffersRegFile(const Json::Value &arg, const SEP::usage_code usage,
                    const std::string &tag, const std::string &progName,
		    const int ndimMax);
  /*!
    Setup GCP environment

    \param arg  Arguments (JSON) which describes file
    \param tag Tag associated with file
    */
  void setupGCP(const Json::Value &arg, const std::string &tag);
  /*!
    Close file
    */
  virtual void close();
  /*!
      Create buffers
  */
  void createBuffers();

 private:
  /*!
Setup GCP
*/
  void setupGCP();

};  // namespace SEP

}  // namespace SEP
#endif
