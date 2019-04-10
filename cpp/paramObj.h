#ifndef PARAM_OBJ_H
#define PARAM_OBJ_H 1
#include <stdbool.h>
#include <iostream>
#include <string>
#include <vector>
#include "SEPException.h"

namespace SEP {
/*!
  Basic parameter object (virtual)
  */
class paramObj {
 public:
  std::string _type;  ///< Parameter type

  /*!
     Default param object
     */
  paramObj() { _type = "NONE"; }
  /*!
Output a message and exit with an error
\param err Message to output
*/
  virtual void error(const std::string& err) const { throw SEPException(err); }
  /*!
   Output a message
   \param err Message to output
   */
  virtual void message(const std::string& msg) const {
    std::cerr << msg << std::endl;
  }
  /*!
Get an integer from a file

\param arg Name of the prameter
*/
  virtual int getInt(const std::string& arg) const {
    error("Undefined getInt");
    return 0;
  }
  /*!
Get an integer from a file

\param arg Name of the prameter
\param def Default value (if not found in file)
*/
  virtual int getInt(const std::string& arg, const int def) const {
    error("Undefined getInt");
    return 0;
  }
  /*!
  Get a float from a file

  \param arg Name of the prameter
  \param def Default value (if not found in file)
 */
  virtual float getFloat(const std::string& arg, const float def) const {
    error("Undefined getFloat");
    return 0.;
  }
  /*!
Get a float from a file

\param arg Name of the prameter
*/
  virtual float getFloat(const std::string& arg) const {
    error("Undefined getFlot");
    return 0.;
  }
  /*!
Get a string  from a file

\param arg Name of the prameter
*/
  virtual std::string getString(const std::string& arg) const {
    error("Undefined getString");
    std::string a = std::string(" ");
    return a;
  }
  /*!
Get a string from a file

\param tag Name of the prameter
\param def Default value (if not found in file)
*/
  virtual std::string getString(const std::string& arg,
                                const std::string& def) const {
    error("Undefined getString");
    std::string a = std::string(" ");
    return a;
  }

  /*!
Get boolean from a file

\param arg Name of the prameter
\param def Default value (if not found in file)
*/
  virtual bool getBool(const std::string& arg, const bool def) const {
    error("Undefined getBoll");
    return true;
  }
  /*!
Get a boolean from a file

\param arg Name of the prameter
*/
  virtual bool getBool(const std::string& arg) const {
    error("Undefined getBol");
    return true;
  }
  /*!
Get integer from a file

\param arg Name of the prameter
\param nvals Number of values
*/
  virtual std::vector<int> getInts(const std::string& arg,
                                   const int nvals) const {
    error("Undefined getInts");
    std::vector<int> a;
    return a;
  }
  /*!
Get integer from a file

\param arg Name of the prameter
\param defs Default values
*/
  virtual std::vector<int> getInts(const std::string& arg,
                                   const std::vector<int>& defs) const {
    error("Undefined getInts");
    std::vector<int> a;
    return a;
  }
  /*!
  Get an floats from a file

  \param arg Name of the prameter
  \param nval Number of values to look for
 */
  virtual std::vector<float> getFloats(const std::string& arg,
                                       int nvals) const {
    error("Undefined getFloata");
    std::vector<float> a;
    return a;
  }
  /*!
Get floats from a file

\param arg Name of the prameter
\param def Default value (if not found in file)
*/
  virtual std::vector<float> getFloats(const std::string& arg,
                                       const std::vector<float>& defs) const {
    error("Undefined getFloats");
    std::vector<float> a;
    return a;
  }
};
}  // namespace SEP

#endif
