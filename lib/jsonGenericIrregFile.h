#ifndef JSON_IRREGFILE_FUNC_H
#define JSON_IRREGFILE_FUNC_H 1
#include "basicIO.h"
#include "genericFile.h"
#include "ioTypes.h"
#include "irregFile.h"
#include "json.h"
#include <stdbool.h>
#include <string>
namespace SEP {

/*!
   Irregular file described by JSON
*/
class jsonGenericIrregFile : public genericIrregFile {
public:
  // sepRegFile::sepRegFile(const std::string tag,usage_code usage){
  /*!
   Default initialization
*/
  jsonGenericIrregFile() { ; }
  /*!
    \param arg JSON arguments
    \param usage Usage for file
    \param traceH Length of trace headers
    \param progName Name of program
    \param Minimum number of dimensions for dataset
    */
  jsonGenericIrregFile(const Json::Value &arg, const SEP::usage_code usage,
                       const std::string &tag, const int reelH,
                       const int traceH, const std::string &progName,
                       const int ndim = -1);
  /*!
     Setup JSON environmnet
    \param jsonArgs Arguments described by JSON
    \param tag Tag for dataset
    \param desFileDefault Default name for output description file
  */
  void setupJson(const Json::Value &jsonArgs, const std::string &tag,
                 const std::string desFileDefault = std::string(""));
  /*!
   Get an integer from a file

   \param arg Name of the prameter
  */

  /*!
  Remove all files associated with a dataset
  */
  virtual void remove() override;
  /*!
   Get an integer from a file

   \param arg Name of the prameter
  */
  virtual int getInt(const std::string &arg) const override;
  /*!
Get an integer from a file

\param arg Name of the prameter
\param def Default value (if not found in file)
*/
  virtual int getInt(const std::string &arg, const int def) const override;
  /*!
  Get a float from a file

  \param arg Name of the prameter
  \param def Default value (if not found in file)
 */
  virtual float getFloat(const std::string &, const float def) const override;

  /*!
Get a float from a file

\param arg Name of the prameter
*/
  virtual float getFloat(const std::string &) const override;
  /*!
  Get a string  from a file

  \param arg Name of the prameter
 */
  virtual std::string getString(const std::string &arg) const override;
  /*!
Get a string from a file

\param tag Name of the prameter
\param def Default value (if not found in file)
*/

  virtual std::string getString(const std::string &arg,
                                const std::string &def) const override;

  /*!
Get boolean from a file

\param arg Name of the prameter
\param def Default value (if not found in file)
*/
  virtual bool getBool(const std::string &, const bool def) const override;

  /*!
Get a boolean from a file

\param arg Name of the prameter
*/
  virtual bool getBool(const std::string &) const override;
  /*!
  Get integer from a file

  \param arg Name of the prameter
  \param nvals Number of values
 */
  virtual std::vector<int> getInts(const std::string &arg,
                                   int nvals) const override;
  /*!
Get integers from a file

\param arg Name of the prameter
\param def Default value (if not found in file)
*/
  virtual std::vector<int> getInts(const std::string &arg,
                                   const std::vector<int> &defs) const override;
  /*!
  Get an floats from a file

  \param arg Name of the prameter
  \param nval Number of values to look for
 */
  virtual std::vector<float> getFloats(const std::string &arg,
                                       int nvals) const override;
  /*!
Get floats from a file

\param arg Name of the prameter
\param def Default value (if not found in file)
*/
  virtual std::vector<float>
  getFloats(const std::string &arg,
            const std::vector<float> &defs) const override;
  /*!
     Output a message
     \param err Message to output
     */
  virtual void message(const std::string &err) const override;

  Json::Value getArgs() { return jsonArgs; }
  /*!
  Output a message and exit with an error
  \param err Message to output
  */
  virtual void error(const std::string &err) const override;
  /*!
     Put integer to file

     \param par Name of parameter
     \param val Value to write to file description
  */

  virtual void putInt(const std::string &par, const int val) override;
  ;
  /*!
   Put float to file description

   \param par Name of parameter
   \param val Value to write to file description
*/
  virtual void putFloat(const std::string &par, const float val) override;
  ;
  /*!
   Put string to file description

   \param par Name of parameter
   \param val Value to write to file description
*/
  virtual void putString(const std::string &par,
                         const std::string &val) override;
  ;
  /*!
   Put boolean to file description

   \param par Name of parameter
   \param val Value to write to file description
*/
  virtual void putBool(const std::string &par, const bool val) override;
  ;
  /*!
   Put ints to file description

   \param par Name of parameter
   \param val Value to write to file description
*/
  virtual void putInts(const std::string &par,
                       const std::vector<int> &val) override;
  ;
  /*!
   Put floats to file description

   \param par Name of parameter
   \param val Value to write to file description
*/
  virtual void putFloats(const std::string &par,
                         const std::vector<float> &val) override;
  ;

  /*!
    Read the description of the file
*/
  virtual void readDescription(const int ndim = -1) override;

  /*!
Write  the description of the file
*/
  virtual void writeDescription() override;
  /*!
  Close a file
  */
  virtual void close() override;

  /*!
     Get usage for file

  */
  usage_code getUsageCode() { return _usage; }

  /*!
    Delete irregularFile
    */
  virtual ~jsonGenericIrregFile() { ; }

  /*!
  Ge the name of the data file*/
  std::string getDataFileName() const;

  /*!
     Return headerKeys

     @vector<string>
  */
  virtual std::vector<std::string> getHeaderKeyList() const override;

  /*!
    Return headerkey Type
    */
  virtual std::map<std::string, std::string> getHeaderKeyTypes() const override;
  /*!
    keyList List of keys in the order they should be written
    */
  virtual void
  putHeaderKeyList(const std::vector<std::string> &keylist) override;
  /*!
    keyTypes Map of key types
    */
  virtual void
  putHeaderKeyTypes(const std::map<std::string, std::string> &keyType) override;

  /*!
    Read header window

    nwind,fwind,jwind - Window parameters
  */
  virtual std::pair<std::shared_ptr<byte2DReg>, std::shared_ptr<int1DReg>>
  readHeaderWindow(const std::vector<int> &nwind, const std::vector<int> &fwind,
                   const std::vector<int> &jwind) override;
  /*!
      Read the header locations

      nwind,fwind, jwind - Windowing parameters
      @2-D array ([iheader,ipos],nheaders)

  */
  std::vector<std::vector<int>> readHeaderLocs(const std::vector<int> &nwind,
                                               const std::vector<int> &fwind,
                                               const std::vector<int> &jwind);

  /*!
  Extract DRN from a header block

  out - Output headers
  ifirst  - First location for output header and drn
  ntransfer - Number of locations to transfer
  drns - Data Record Number
  temp - Input buffer
  */
  void extractDRN(std::shared_ptr<byte2DReg> out, const int ifirst,
                  const int ntransfer, std::shared_ptr<int1DReg> drns,
                  std::shared_ptr<byte2DReg> &temp);
  /*!
   Take DRN out of a header block and implace into 2-D array

    n1 - Number of bytes in a trace
    temp - Temp array
    data - Data array
    */

  void addtDRN(std::shared_ptr<byte2DReg> in, const int ifirst,
               const int ntransfer, std::shared_ptr<int1DReg> drns,
               std::shared_ptr<byte2DReg> &out);
  /*!
    Add DRN to a header block

    n1 - Number of bytes in a trace
    in - Input array
    out - Output array
    */
  void readArrangeTraces(std::vector<std::vector<int>> &itrs, const int n1,
                         void *temp, void *data);

  /*!
    Read float trace window

    nwind,fwind,jwind - Window parameters

    @return pair<headers,drn,float data>

  */
  virtual std::pair<std::shared_ptr<byte2DReg>, std::shared_ptr<float2DReg>>
  readFloatTraceWindow(const std::vector<int> &nwind,
                       const std::vector<int> &fwind,
                       const std::vector<int> &jwind) override;

  /*!
  Read int trace window

  nwind,fwind,jwind - Window parameters

*/
  virtual std::pair<std::shared_ptr<byte2DReg>, std::shared_ptr<int2DReg>>
  readIntTraceWindow(const std::vector<int> &nwind,
                     const std::vector<int> &fwind,
                     const std::vector<int> &jwind) override;
  /*!
  Read double trace window

  nwind,fwind,jwind - Window parameters

*/
  virtual std::pair<std::shared_ptr<byte2DReg>, std::shared_ptr<double2DReg>>
  readDoubleTraceWindow(const std::vector<int> &nwind,
                        const std::vector<int> &fwind,
                        const std::vector<int> &jwind) override;
  /*!
Read byte trace window

nwind,fwind,jwind - Window parameters

*/
  virtual std::pair<std::shared_ptr<byte2DReg>, std::shared_ptr<byte2DReg>>
  readByteTraceWindow(const std::vector<int> &nwind,
                      const std::vector<int> &fwind,
                      const std::vector<int> &jwind) override;
  /*!
Read complex trace window

nwind,fwind,jwind - Window parameters

*/
  virtual std::pair<std::shared_ptr<byte2DReg>, std::shared_ptr<complex2DReg>>
  readComplexTraceWindow(const std::vector<int> &nwind,
                         const std::vector<int> &fwind,
                         const std::vector<int> &jwind) override;
  /*!
Read complex double trace window

nwind,fwind,jwind - Window parameters

*/
  virtual std::pair<std::shared_ptr<byte2DReg>,
                    std::shared_ptr<complexDouble2DReg>>
  readComplexDoubleTraceWindow(const std::vector<int> &nwind,
                               const std::vector<int> &fwind,
                               const std::vector<int> &jwind) override;

  /*!
    Write header window without a grid

    nwind,fwind,jwind - Window parameters
    drn - Data record number
    headers - Headers
  */

  virtual void writeHeaderWindow(
      const std::vector<int> &nwind, const std::vector<int> &fwind,
      const std::vector<int> &jwind, const std::shared_ptr<int1DReg> &drn,
      const std::shared_ptr<byte2DReg> &headers,
      const std::shared_ptr<byte1DReg> &byte) override;
  /*!
  Write out grid
   nwind,fwind,jwind - Windowing parameters
     headers - Headers
     grid - Grid
     */
  void writeGrid(const std::vector<int> &nwind, const std::vector<int> &fwind,
                 const std::vector<int> &jwind,
                 const std::shared_ptr<byte2DReg> &headers,
                 const std::shared_ptr<byte1DReg> &grid

  );
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
      const std::shared_ptr<byte1DReg> &grid) override;

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
      const std::shared_ptr<byte1DReg> &grid) override;

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
      const std::shared_ptr<byte1DReg> &grid) override;

  /*!
Write int trace window

nwind,fwind,jwind - Window parameters
head - Headers
data -Data
grid -Grid
*/
  virtual void writeIntTraceWindow(
      const std::vector<int> &nwind, const std::vector<int> &fwind,
      const std::vector<int> &jwind, const std::shared_ptr<byte2DReg> &head,
      const std::shared_ptr<int2DReg> &data,
      const std::shared_ptr<byte1DReg> &grid) override;

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
      const std::shared_ptr<byte1DReg> &grid) override;

  /*!
Write byte trace window

nwind,fwind,jwind - Window parameters
head - Headers
data -Data
grid -Grid
*/
  virtual void writeByteTraceWindow(
      const std::vector<int> &nwind, const std::vector<int> &fwind,
      const std::vector<int> &jwind, const std::shared_ptr<byte2DReg> &head,
      const std::shared_ptr<byte2DReg> &data,
      const std::shared_ptr<byte1DReg> &grid) override;

  /*!

  Set that the data is out of orde

  */
  virtual void setOutOfOrder() override;

  virtual Json::Value getDescription() override { return jsonArgs; }
  /*!

    \param title Name to give the history

    \param desc Description to putDescription
*/

  virtual void putDescription(const std::string &title,
                              const Json::Value &desc) override {
    jsonArgs[title] = desc;
  }

  /*!
      Get the description of the grid file

    @return JSON file representations
  */

  /*!
      Get the description of the data file

    @return JSON file representations
  */
  virtual Json::Value getDataDescription() override;

  /*!
      Put the description of the data file

      desc - Desciprition
  */
  virtual void putDataDescription(const Json::Value &desc) override;

  /*!
Get the name of the JSON file
*/
  virtual std::string getJSONFileName() const;
  /*!
Get the name of the JSON file, no path
*/
  virtual std::string getJSONFileBaseName() const;
  /*!
Set the history file file
*/
  void setHistory(const Json::Value &hist);

protected:
  Json::Value jsonArgs; ///< JSON values
  bool _newFile;        ///< Whether or not a new file
  dataType _dtype;      ///< Datatype associated with the dataset

  std::string _tag;               ///< Tag assicated with the dataset
  usage_code _usage;              ///< Usage file
  std::string _jsonFile;          ///< Description file
  std::string _dataFile;          ///< Binary data file
  std::shared_ptr<myFileIO> myio; ///< Basic IO ovject
  int _reelH;                     ///< Reel header
  int _traceH;                    ///< Trace header
  std::vector<std::string> _keys;
  std::map<std::string, std::string> _keyType;
  std::vector<long long> _drns;
  long long _writeLastH = 0, _writeLastG = -1;
  bool _inOrder = true;
  bool _haveGrid = false;
  int _drn = -1;
}; // namespace SEP
} // namespace SEP

#endif
