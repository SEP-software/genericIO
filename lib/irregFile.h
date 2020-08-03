#ifndef IRREG_FILE_H
#define IRREG_FILE_H
#include "byte1DReg.h"
#include "byte2DReg.h"
#include "complex1DReg.h"
#include "complex2DReg.h"
#include "complexDouble1DReg.h"
#include "complexDouble2DReg.h"
#include "double1DReg.h"
#include "double2DReg.h"
#include "float1DReg.h"
#include "float2DReg.h"
#include "genericFile.h"
#include "int1DReg.h"
#include "int2DReg.h"
#include "short1DReg.h"

#include <utility>
namespace SEP
{

  class genericIrregFile
  {
  public:
    /*!
   Default initialization
*/
    genericIrregFile() { _type = DATA_UNKNOWN; }
    /*!
  Remove file from system
  */
    virtual void remove() { perror("must override remove"); }

    /*!
     Put integer to file

     \param par Name of parameter
     \param val Value to write to file description
  */

    virtual void putInt(const std::string &par, const int val) = 0;
    /*!
   Put float to file description

   \param par Name of parameter
   \param val Value to write to file description
*/
    virtual void putFloat(const std::string &par, const float val) = 0;
    /*!
   Put string to file description

   \param par Name of parameter
   \param val Value to write to file description
*/
    virtual void putString(const std::string &par, const std::string &val) = 0;
    /*!
   Put boolean to file description

   \param par Name of parameter
   \param val Value to write to file description
*/
    virtual void putBool(const std::string &par, const bool val) = 0;
    /*!
   Put ints to file description

   \param par Name of parameter
   \param val Value to write to file description
*/
    virtual void putInts(const std::string &par, const std::vector<int> &val) = 0;
    /*!
   Put floats to file description

   \param par Name of parameter
   \param val Value to write to file description
*/
    virtual void putFloats(const std::string &par,
                           const std::vector<float> &val) = 0;

    /*!
    Read the description of the file
*/
    virtual void readDescription(const int ndim = -1) = 0;

    /*!
   Grab the history from a file

*/
    virtual std::string grabHistory() = 0;

    /*!
   Put history from a file

   \param hist - History file to add to afile 

*/
    virtual std::string putHistory(const std::string &hist) = 0;

    /*!
Write  the description of the file
*/
    virtual void writeDescription() { ; }
    /*!
  Close a file
  */
    virtual void close() { ; }
    /*!
    Set the hypercube for the file
    \param hyp Hypercube describing regular file
    */
    void setHyper(const std::shared_ptr<SEP::hypercube> &hyp);
    /*!
    Return datatype of file
    */
    dataType getDataType() { return _type; }
    /*!
   Get an integer from a file

   \param arg Name of the parameter
  */
    virtual int getInt(const std::string &arg) const = 0;
    /*!
Get an integer from a file

\param arg Name of the parameter
\param def Default value (if not found in file)
*/
    virtual int getInt(const std::string &arg, const int def) const = 0;
    /*!
  Get a float from a file

  \param arg Name of the parameter
  \param def Default value (if not found in file)
 */
    virtual float getFloat(const std::string &, const float def) const = 0;

    virtual bool getBool(const std::string &) const = 0;
    /*!
  Get integer from a file

  \param arg Name of the prameter
  \param nvals Number of values
 */
    virtual std::vector<int> getInts(const std::string &arg, int nvals) const = 0;
    /*!
Get integers from a file

\param arg Name of the prameter
\param def Default value (if not found in file)
*/
    virtual std::vector<int> getInts(const std::string &arg,
                                     const std::vector<int> &defs) const = 0;
    /*!
  Get an floats from a file

  \param arg Name of the prameter
  \param nval Number of values to look for
 */
    virtual std::vector<float> getFloats(const std::string &arg,
                                         int nvals) const = 0;
    /*!
Get floats from a file

\param arg Name of the prameter
\param def Default value (if not found in file)
*/
    virtual std::vector<float>
    getFloats(const std::string &arg, const std::vector<float> &defs) const = 0;

    /*!
     Put integer to file

     \param par Name of parameter
     \param val Value to write to file description
  */
    ;
    /*!
     Output a message
     \param err Message to output
     */
    virtual void message(const std::string &err) const = 0;
    /*!
  Output a message and exit with an error
  \param err Message to output
  */
    virtual void error(const std::string &err) const = 0;
    /*!
     Put integer to file

     \param par Name of parameter
     \param val Value to write to file dqescription
  */
    /*!
 Get boolean from a file

 \param arg Name of the parameter
 \param def Default value (if not found in file)
 */
    virtual bool getBool(const std::string &, const bool def) const = 0;
    /*!
    Set usage of file
    \param usage Usage for file
  */
    void setUsage(const usage_code usage) { _usage = usage; }
    /*!
     Get usage for file
     */
    usage_code getUsage() { return _usage; }
    /*!
  Output a message and exit with an error
  \param err Message to output
  */
    /*!
Get a float from a file

\param arg Name of the prameter
*/
    virtual float getFloat(const std::string &) const = 0;
    /*!
  Get a string  from a file

  \param arg Name of the prameter
 */
    virtual std::string getString(const std::string &arg) const = 0;
    /*!
Get a string from a file

\param tag Name of the prameter
\param def Default value (if not found in file)
*/

    virtual std::string getString(const std::string &arg,
                                  const std::string &def) const = 0;

    /*!
  Check to make sure tue window parameters make sense

  nwind,fwind,jwind - Window parameters
  hyper - Hypercube
  */
    void checkWindow(const std::vector<int> &nwind, const std::vector<int> &fwind,
                     const std::vector<int> &jwind,
                     std::shared_ptr<SEP::hypercube> hyper);
    /*!
   Get the size of each element (float-4,complex-8,etc)
  */
    int getDataEsize();
    /*!
    Set the data type

    \param type Datatype
  */
    void setDataType(const dataType typ) { _type = typ; }
    /*!
    Set the data type
     \param typ (String describing datatype)
     */
    void setDataType(const std::string &typ)
    {
      setDataType(SEP::toElementType(typ));
    }
    /*!
    Get the data type as a string
    */
    std::string getDataTypeString();

    /*!
     Get usage for file

  */
    usage_code getUsageCode() { return _usage; }

    virtual void putDataDescription(const Json::Value &descrp) = 0;
    virtual void putDataDescriptionString(const std::string &descrp);
    virtual Json::Value getDataDescription() = 0;
    virtual std::string getDataDescriptionString();

    virtual void putDescription(const std::string &title,
                                const Json::Value &desc) = 0;
    virtual std::string getDescriptionString();
    virtual Json::Value getDescription() = 0;
    virtual void putDescriptionString(const std::string &title,
                                      const std::string &desc);
    /*!
   Return hypercube describing dataset
   */
    std::shared_ptr<SEP::hypercube> getHyperData()
    {
      if (_hyperData == nullptr)
        throw SEPException(std::string("hypercube not defined"));

      return _hyperData;
    }

    /*!
 Return hypercube describing headers
 */
    std::shared_ptr<SEP::hypercube> getHyperHeader()
    {
      if (_hyperHeader == nullptr)
        throw SEPException(std::string("hypercube  for header not defined"));

      return _hyperHeader;
    }
    /*!
   Return hypercube describing dataset
   */
    std::shared_ptr<SEP::hypercube> getHyper()
    {
      if (_hyper == nullptr)
        throw SEPException(std::string("hypercube not defined"));

      return _hyper;
    }
    /*!
    Delete irregularFile
    */
    virtual ~genericIrregFile() { ; }

    /*!
     Return headerKeys

     @vector<string>
  */
    virtual std::vector<std::string> getHeaderKeyList() const = 0;

    /*!
    Return headerkey Type
    */
    virtual std::map<std::string, std::string> getHeaderKeyTypes() const = 0;
    /*!
    keyList List of keys in the order they should be written
    */
    virtual void putHeaderKeyList(const std::vector<std::string> &keylist) = 0;
    /*!
    keyTypes Map of key types
    */
    virtual void
    putHeaderKeyTypes(const std::map<std::string, std::string> &keyType) = 0;

    /*!
    Read header window

    nwind,fwind,jwind - Window parameters
  */
    virtual std::tuple<std::shared_ptr<byte2DReg>, std::shared_ptr<int1DReg>,
                       std::shared_ptr<byte1DReg>>
    readHeaderWindow(const std::vector<int> &nwind, const std::vector<int> &fwind,
                     const std::vector<int> &jwind) = 0;
    /*!
    Read float trace window

    nwind,fwind,jwind - Window parameters

    @return tuple<headers,drn,float data>

  */
    virtual std::tuple<std::shared_ptr<byte2DReg>, std::shared_ptr<float2DReg>,
                       std::shared_ptr<byte1DReg>>
    readFloatTraceWindow(const std::vector<int> &nwind,
                         const std::vector<int> &fwind,
                         const std::vector<int> &jwind) = 0;

    /*!
  Read int trace window

  nwind,fwind,jwind - Window parameters

*/
    virtual std::tuple<std::shared_ptr<byte2DReg>, std::shared_ptr<int2DReg>,
                       std::shared_ptr<byte1DReg>>
    readIntTraceWindow(const std::vector<int> &nwind,
                       const std::vector<int> &fwind,
                       const std::vector<int> &jwind) = 0;
    /*!
  Read double trace window

  nwind,fwind,jwind - Window parameters

*/
    virtual std::tuple<std::shared_ptr<byte2DReg>, std::shared_ptr<double2DReg>,
                       std::shared_ptr<byte1DReg>>
    readDoubleTraceWindow(const std::vector<int> &nwind,
                          const std::vector<int> &fwind,
                          const std::vector<int> &jwind) = 0;
    /*!
Read byte trace window

nwind,fwind,jwind - Window parameters

*/
    virtual std::tuple<std::shared_ptr<byte2DReg>, std::shared_ptr<byte2DReg>,
                       std::shared_ptr<byte1DReg>>
    readByteTraceWindow(const std::vector<int> &nwind,
                        const std::vector<int> &fwind,
                        const std::vector<int> &jwind) = 0;
    /*!
Read complex trace window

nwind,fwind,jwind - Window parameters

*/
    virtual std::tuple<std::shared_ptr<byte2DReg>, std::shared_ptr<complex2DReg>,
                       std::shared_ptr<byte1DReg>>
    readComplexTraceWindow(const std::vector<int> &nwind,
                           const std::vector<int> &fwind,
                           const std::vector<int> &jwind) = 0;
    /*!
Read complex double trace window

nwind,fwind,jwind - Window parameters

*/
    virtual std::tuple<std::shared_ptr<byte2DReg>,
                       std::shared_ptr<complexDouble2DReg>,
                       std::shared_ptr<byte1DReg>>
    readComplexDoubleTraceWindow(const std::vector<int> &nwind,
                                 const std::vector<int> &fwind,
                                 const std::vector<int> &jwind) = 0;

    /*!
    Write header window without a grid

    nwind,fwind,jwind - Window parameters
    drn - Data record number
    headers - Headers
    grid - Grid
  */

    virtual void writeHeaderWindow(const std::vector<int> &nwind,
                                   const std::vector<int> &fwind,
                                   const std::vector<int> &jwind,
                                   const std::shared_ptr<int1DReg> &drn,
                                   const std::shared_ptr<byte2DReg> &headers,
                                   const std::shared_ptr<byte1DReg> &grid) = 0;
    /*!
Write complex double trace window

nwind,fwind,jwind - Window parameters
head - Headers
data -Data
grid -Grid

*/
    virtual void writeComplexDoubleTraceWindow(
        const std::vector<int> &nwind, const std::vector<int> &fwind,
        const std::vector<int> &jwind, std::shared_ptr<byte2DReg> &head,
        std::shared_ptr<complexDouble2DReg> &data,
        const std::shared_ptr<byte1DReg> &grid) = 0;

    /*!
Write complex double trace window

nwind,fwind,jwind - Window parameters
head - Headers
data -Data
grid -Grid
*/
    virtual void writeComplexTraceWindow(
        const std::vector<int> &nwind, const std::vector<int> &fwind,
        const std::vector<int> &jwind, const std::shared_ptr<byte2DReg> &head,
        const std::shared_ptr<complex2DReg> &data,
        const std::shared_ptr<byte1DReg> &grid) = 0;

    /*!
Write double trace window

nwind,fwind,jwind - Window parameters
head - Headers
data -Data
grid -Grid
*/
    virtual void writeDoubleTraceWindow(
        const std::vector<int> &nwind, const std::vector<int> &fwind,
        const std::vector<int> &jwind, const std::shared_ptr<byte2DReg> &head,
        const std::shared_ptr<double2DReg> &data,
        const std::shared_ptr<byte1DReg> &grid) = 0;

    /*!
Write int trace window

nwind,fwind,jwind - Window parameters
head - Headers
data -Data
grid -Grid
*/
    virtual void writeIntTraceWindow(const std::vector<int> &nwind,
                                     const std::vector<int> &fwind,
                                     const std::vector<int> &jwind,
                                     const std::shared_ptr<byte2DReg> &head,
                                     const std::shared_ptr<int2DReg> &data,
                                     const std::shared_ptr<byte1DReg> &grid) = 0;

    /*!
Write float trace window

nwind,fwind,jwind - Window parameters
head - Headers
data -Data
grid -Grid
*/
    virtual void writeFloatTraceWindow(
        const std::vector<int> &nwind, const std::vector<int> &fwind,
        const std::vector<int> &jwind, const std::shared_ptr<byte2DReg> &head,
        const std::shared_ptr<float2DReg> &data,
        const std::shared_ptr<byte1DReg> &grid) = 0;

    /*!
Write byte trace window

nwind,fwind,jwind - Window parameters
head - Headers
data -Data
grid -Grid
*/
    virtual void writeByteTraceWindow(const std::vector<int> &nwind,
                                      const std::vector<int> &fwind,
                                      const std::vector<int> &jwind,
                                      const std::shared_ptr<byte2DReg> &head,
                                      const std::shared_ptr<byte2DReg> &data,
                                      const std::shared_ptr<byte1DReg> &grid) = 0;

    /*!

  Set that the data is out of order


  */
    virtual void setOutOfOrder() = 0;

    /*!
     Set the hypercube for the data
  */
    void setHyperData(std::shared_ptr<SEP::hypercube> hyp) { _hyperData = hyp; }

    /*!
     Set the hypercube for the headers
  */
    void setHyperHeader(std::shared_ptr<SEP::hypercube> hyp)
    {
      _hyperHeader = hyp;
    }
    /*!
  Create maps of key offset and sizes
     @returns
      pair mapOffset,mapSize
  */
    std::pair<std::map<std::string, int>, std::map<std::string, int>>
    createOffsetMap() const;

    std::shared_ptr<byte1DReg> extractByte(std::shared_ptr<byte2DReg> buf,
                                           const int off) const;

    std::shared_ptr<short1DReg> extractShort(std::shared_ptr<byte2DReg> buf,
                                             const int off) const;

    std::shared_ptr<float1DReg> extractFloat(std::shared_ptr<byte2DReg> buf,
                                             const int off) const;

    std::shared_ptr<int1DReg> extractInt(std::shared_ptr<byte2DReg> buf,
                                         const int off) const;

    std::shared_ptr<complex1DReg> extractComplex(std::shared_ptr<byte2DReg> buf,
                                                 const int off) const;

    std::shared_ptr<double1DReg> extractDouble(std::shared_ptr<byte2DReg> buf,
                                               const int off) const;

    std::shared_ptr<complexDouble1DReg>
    extractComplexDouble(std::shared_ptr<byte2DReg> buf, const int off) const;
    void insertValue(void *outb, void *inb, const int off, const int sz,
                     const int n1, const int n2) const;
    void insertValue(std::shared_ptr<byte2DReg> outb,
                     std::shared_ptr<byte1DReg> inb, const int off, const int sz,
                     const int n1, const int n2) const
    {
      insertValue(outb->getVals(), inb->getVals(), off, sz, n1, n2);
    }
    void insertValue(std::shared_ptr<byte2DReg> outb,
                     std::shared_ptr<short1DReg> inb, const int off, const int sz,
                     const int n1, const int n2) const
    {
      insertValue(outb->getVals(), inb->getVals(), off, sz, n1, n2);
    }
    void insertValue(std::shared_ptr<byte2DReg> outb,
                     std::shared_ptr<int1DReg> inb, const int off, const int sz,
                     const int n1, const int n2) const
    {
      insertValue(outb->getVals(), inb->getVals(), off, sz, n1, n2);
    }
    void insertValue(std::shared_ptr<byte2DReg> outb,
                     std::shared_ptr<float1DReg> inb, const int off, const int sz,
                     const int n1, const int n2) const
    {
      insertValue(outb->getVals(), inb->getVals(), off, sz, n1, n2);
    }
    void insertValue(std::shared_ptr<byte2DReg> outb,
                     std::shared_ptr<double1DReg> inb, const int off,
                     const int sz, const int n1, const int n2) const
    {
      insertValue(outb->getVals(), inb->getVals(), off, sz, n1, n2);
    }
    void insertValue(std::shared_ptr<byte2DReg> outb,
                     std::shared_ptr<complex1DReg> inb, const int off,
                     const int sz, const int n1, const int n2) const
    {
      insertValue(outb->getVals(), inb->getVals(), off, sz, n1, n2);
    }
    void insertValue(std::shared_ptr<byte2DReg> outb,
                     std::shared_ptr<complexDouble1DReg> inb, const int off,
                     const int sz, const int n1, const int n2) const
    {
      insertValue(outb->getVals(), inb->getVals(), off, sz, n1, n2);
    }

    void setHaveGrid(const bool gr);
    void setInOrder(const bool ord) { _inOrder = ord; }
    bool getInOrder() const { return _inOrder; }
    bool getHaveGrid() const { return _haveGrid; }

  protected:
    std::shared_ptr<SEP::hypercube> _hyper =
        nullptr; ///< Hypercube describing the controling structure
    std::shared_ptr<SEP::hypercube>
        _hyperData,                     ///< Hypercube for the data and headers
        _hyperHeader;                   ///< Hypercube for the headers
    dataType _type = SEP::DATA_UNKNOWN; ///< The dataype for for the RSF
    usage_code _usage;
    long long _writeLastH = 0, _writeLastG = -1;
    bool _haveGrid = false;
    bool _inOrder = true;
  };

} // namespace SEP
#endif