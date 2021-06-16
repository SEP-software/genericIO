#ifndef SEP_REG_FUNC_H
#define SEP_REG_FUNC_H 1
#include <stdbool.h>
#include <string>
#include "genericFile.h"
namespace SEP
{
  /*!
  Regular SEP object

*/
  class sepReg : public SEP::genericReg
  {
  public:

    sepReg(){;

    }

    /*!
     Remove file
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
    /*! Seek to a given position inot a file
  \param iv Relative location
  \param whence (0, begining; 1, current; 2, end )
  */
    virtual void seekTo(const long long iv, const int whence) override;
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
    virtual std::vector<float> getFloats(
        const std::string &arg, const std::vector<float> &defs) const override;
    /*!
     Output a message
     \param err Message to output
     */
    virtual void message(const std::string &err) const override;
    /*!
  Output a message and exit with an error
  \param err Message to output
  */
    virtual void error(const std::string &err) const override;

 /*!
    Read the description of the file
*/
    virtual void readDescription(const int ndimMax = -1) override;

    /*!
Write  the description of the file
*/
    virtual void writeDescription() override;

    /*!
   Put integer to file

   \param par Name of parameter
   \param val Value to write to file description
*/
    virtual void putInt(const std::string &par, const int val) override;
    /*!
 Put float to file description

 \param par Name of parameter
 \param val Value to write to file description
*/
    virtual void putFloat(const std::string &par, const float val) override;
    /*!
 Put string to file description

 \param par Name of parameter
 \param val Value to write to file description
*/
    virtual void putString(const std::string &par,
                           const std::string &val) override;
    /*!
 Put boolean to file description

 \param par Name of parameter
 \param val Value to write to file description
*/
    virtual void putBool(const std::string &par, const bool val) override;
    /*!
 Put ints to file description

 \param par Name of parameter
 \param val Value to write to file description
*/
    virtual void putInts(const std::string &par,
                         const std::vector<int> &val) override;
    /*!
 Put floats to file description

 \param par Name of parameter
 \param val Value to write to file description
*/
    virtual void putFloats(const std::string &par,
                           const std::vector<float> &val) override;


    /*!
     Grab the history of a given file */
    virtual Json::Value getDescription() override;

    /*!
    Put the content of JSON value into descrption file

    \param  title How to refer to in the file

    \param desc Description
    */
    void putDescription(const std::string &title,
                        const Json::Value &desc) override;

  protected:
    std::string _tag; ///< Tag associated with dataset
  };
} // namespace SEP

#endif
