#ifndef MEMORY_IO_H
#define MEMORY_IO_H 1
#include "dictParams.h"
#include "genericIO.h"
#include "memoryFile.h"

namespace SEP
{
  /*!  Class for handling old-stype SEP regular IO

*/
  class memoryIO : public genericIO
  {
  public:
    /*!
Initialize IO with command line arguments

\param dict dictionary containing arguments
*/
    memoryIO(std::map<std::string, std::string>);
    /*!
   Return a genericReg object

  \param tag Tag used to access dataset
  \param name Name of dataset
  \param usage Usage for file (in,out,scratch)
  \param ndimMax Output file should have ndimMax axes
*/
    virtual std::shared_ptr<SEP::genericReg> getRegTag(
        const std::string &tag, const std::string &name,
        const SEP::usage_code usage, const int ndim = -1) override;
    /*!
 Return a genericIrregFile object

\param tag Tag used to access dataset
\param name Name of dataset
\param usage Usage for file (in,out,scratch)
\param ndimMax Output file should have ndimMax axes

*/
    virtual std::shared_ptr<SEP::genericIrreg> getIrregTag(
        const std::string &tag, const std::string &name,
        const SEP::usage_code usage, const int ndimMax = -1) override;

    /*!
     Return file type

    \param name  Return file type (invalid,regularFile,irregularFile)
  */
    virtual SEP::file_type getType(const std::string &name) override
    {
      return SEP::regular;
    }
  };
} // namespace SEP
#endif
