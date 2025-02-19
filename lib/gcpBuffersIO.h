#ifndef gcp_buffers_io_h
#define gcp_buffers_io_h 1
#include "gcpBuffersRegFile.h"
#include "jsonGenericIO.h"
namespace SEP {
/*!
Class for handling IO operations when writing to multiple objects on GCP
*/
class gcpBuffersIO : public jsonGenericIO {
 public:
  /*!
 Default object, does nothing
*/
  gcpBuffersIO() { ; }
  /*!
  Initialize IO with command line arguments

  \param argc C number of command line arguments
  \param argv List of command line arguments
*/
  gcpBuffersIO(const int argc, char **argv) { initJsonPars(argc, argv);
  _type="GCP Buffers"; }
  /*!
     Return a genericReg object

    \param tag Tag used to access dataset
    \param name Name of dataset
    \param usage Usage for file (in,out,scratch)
    \param ndimMax Output file should have ndimMax axes
  */
  virtual std::shared_ptr<genericReg> getRegTag(
      const std::string &tag, const std::string &name, const usage_code usage,
      const int ndimMax = -1) override;
  /*!
 Return a genericIrregFile object

\param tag Tag used to access dataset
\param name Name of dataset
\param usage Usage for file (in,out,scratch)
\param ndimMax Output file should have ndimMax axes

*/
  virtual std::shared_ptr<genericIrreg> getIrregTag(
      const std::string &tag, const std::string &name, const usage_code usage,
      const int ndimMax = -1) override;
  /*!
  Close all files

*/
  virtual void close();
  /*!
 Get parameter object

*/
  virtual std::shared_ptr<paramObj> getParamObj();

 private:
  bool _init = false;  ///< Whether or not IO type has been initalized
};
}  // namespace SEP
#endif
