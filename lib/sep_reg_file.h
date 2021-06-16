#ifndef SEP_REGFILE_FUNC_H
#define SEP_REGFILE_FUNC_H 1
#include <stdbool.h>
#include <string>
#include "sep_reg.h"
namespace SEP
{
  /*!
  Regular file object for old-style SEP files

*/
  class sepRegFile : public SEP::sepReg
  {
  public:
    /*!
      Create a regular file object
       \param tg Tag for dataset
       \param usage Usage for file
       \param ndimMax Minimum number of dimensions for file
  */
    sepRegFile(const std::string &tg, const SEP::usage_code usage,
               const int ndimMax = -1);

    /*!
     Remove file
     */
    virtual void remove() override;

    /*!
Read entire file

\param hyp byteHyper (from sepVector) to grab file contents from
*/
    virtual void readByteStream(unsigned char *array,
                                const long long npts) override;
    /*!
Write entire file

\param hyp byteHyper (from sepVector) to grab file contents from
*/
    virtual void writeByteStream(const unsigned char *array,
                                 const long long npts) override;
    /*!
Read entire file

\param hyp complexHyper (from sepVector) to grab file contents from
*/
    virtual void readComplexStream(std::complex<float> *array,
                                   const long long npts) override;

    /*!
Read entire file

\param hyp complexDoubleHyper (from sepVector) to grab file contents from
*/
    virtual void readComplexDoubleStream(std::complex<double> *array,
                                         const long long npts) override;

    /*!
Read a portion of file based on window parameters

\param nw,fw,jw Standard window parameters
\param hyp complexHyper (from sepVector) storage
*/
    virtual void writeComplexStream(const std::complex<float> *array,
                                    const long long npts) override;

    /*!
Read a portion of file based on window parameters

\param nw,fw,jw Standard window parameters
\param hyp complexHyper (from sepVector) storage
*/
    virtual void writeComplexDoubleStream(const std::complex<double> *array,
                                          const long long npts) override;

    /*!
Read a float stream

\param array Array to read into
\param npts Number of values to read
*/
    virtual void readFloatStream(float *array, const long long npts) override;
    /*!
Write a float stream

\param array Array to read into
\param npts Number of values to read
*/
    virtual void writeFloatStream(const float *array,
                                  const long long npts) override;
    /*!
Read entire file

\param hyp byteHyper (from sepVector) to grab file contents from
*/
    virtual void readIntStream(int *array, const long long npts) override;
    /*!
Read a portion of file based on window parameters

\param nw,fw,jw Standard window parameters
\param hyp byteHyper (from sepVector) storage
*/
    virtual void writeIntStream(const int *array, const long long npts) override;
    /*!
Read entire file

\param hyp doubleHyper (from sepVector) to grab file contents from
*/
    virtual void readDoubleStream(double *array, const long long npts) override;
    /*!
Read a portion of file based on window parameters

\param nw,fw,jw Standard window parameters
\param hyp doubleHyper (from sepVector) storage
*/
    virtual void writeDoubleStream(const double *array,
                                   const long long npts) override;
    /*!
Read a portion of file based on window parameters

\param nw,fw,jw Standard window parameters
\param hyp doubleHyper (from sepVector) storage
*/
    virtual void readDoubleWindow(const std::vector<int> &nw,
                                  const std::vector<int> &fw,
                                  const std::vector<int> &jw,
                                  double *array) override;
    /*!
Write a portion of file based on window parameters

\param nw,fw,jw Standard window parameters
\param hyp doubleHyper (from sepVector) storage
*/
    virtual void writeDoubleWindow(const std::vector<int> &nw,
                                   const std::vector<int> &fw,
                                   const std::vector<int> &jw,
                                   const double *array) override;
    /*!
Read a portion of file based on window parameters

\param nw,fw,jw Standard window parameters
\param hyp byteHyper (from sepVector) storage
*/
    virtual void readIntWindow(const std::vector<int> &nw,
                               const std::vector<int> &fw,
                               const std::vector<int> &jw, int *array) override;
    /*!
Write a portion of file based on window parameters

\param nw,fw,jw Standard window parameters
\param hyp intHyper (from sepVector) storage
*/
    virtual void writeIntWindow(const std::vector<int> &nw,
                                const std::vector<int> &fw,
                                const std::vector<int> &jw,
                                const int *array) override;
    /*!
Read a portion of file based on window parameters

\param nw,fw,jw Standard window parameters
\param hyp byteHyper (from sepVector) storage
*/
    virtual void readByteWindow(const std::vector<int> &nw,
                                const std::vector<int> &fw,
                                const std::vector<int> &jw,
                                unsigned char *array) override;
    /*!
 Read a portion of file based on window parameters

 \param nw,fw,jw Standard window parameters
 \param hyp Floathyper (from sepVector) storage
*/
    virtual void readFloatWindow(const std::vector<int> &nw,
                                 const std::vector<int> &fw,
                                 const std::vector<int> &jw,
                                 float *array) override;
    /*!
Write a portion of file based on window parameters

\param nw,fw,jw Standard window parameters
\param hyp byteHyper (from sepVector) storage
*/
    virtual void writeByteWindow(const std::vector<int> &nw,
                                 const std::vector<int> &fw,
                                 const std::vector<int> &jw,
                                 const unsigned char *array) override;
    /*!
Write a portion of file based on window parameters

\param nw,fw,jw Standard window parameters
\param hyp Floathyper (from sepVector) storage
*/
    virtual void writeFloatWindow(const std::vector<int> &nw,
                                  const std::vector<int> &fw,
                                  const std::vector<int> &jw,
                                  const float *array) override;
    /*!
Read a portion of file based on window parameters

\param nw,fw,jw Standard window parameters
\param hyp complexHyper (from sepVector) storage
*/
    virtual void readComplexWindow(const std::vector<int> &nw,
                                   const std::vector<int> &fw,
                                   const std::vector<int> &jw,
                                   std::complex<float> *array) override;
    /*!
Read a portion of file based on window parameters

\param nw,fw,jw Standard window parameters
\param hyp complexDoubleHyper (from sepVector) storage
*/
    virtual void readComplexDoubleWindow(const std::vector<int> &nw,
                                         const std::vector<int> &fw,
                                         const std::vector<int> &jw,
                                         std::complex<double> *array) override;

    /*!
Read a portion of file based on window parameters

\param nw,fw,jw Standard window parameters
\param hyp complexHyper (from sepVector) storage
*/
    virtual void writeComplexWindow(const std::vector<int> &nw,
                                    const std::vector<int> &fw,
                                    const std::vector<int> &jw,
                                    const std::complex<float> *array) override;
    /*!
Read a portion of file based on window parameters

\param nw,fw,jw Standard window parameters
\param hyp complexDoubleHyper (from sepVector) storage
*/
    virtual void writeComplexDoubleWindow(const std::vector<int> &nw,
                                          const std::vector<int> &fw,
                                          const std::vector<int> &jw,
                                          const std::complex<double> *array) override;

   
    /*!
  Close a file
  */
    virtual void close() override;
 
     /*!
    Read the description of the file
*/
    virtual void readDescription(const int ndimMax = -1) override;
void seekTo(const long long iv, const int whence);
    /*!
Write  the description of the file
*/
    virtual void writeDescription() override;

  };
} // namespace SEP

#endif
