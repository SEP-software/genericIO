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
    if (arg == "")
      ;
  }
  /*!
Get an integer from a file

\param arg Name of the prameter
\param def Default value (if not found in file)
*/
  virtual int getInt(const std::string& arg, const int def) const {
    if (arg == "" || def == 0)
      ;
  }
  /*!
  Get a float from a file

  \param arg Name of the prameter
  \param def Default value (if not found in file)
 */
  virtual float getFloat(const std::string& arg, const float def) const {
    if (arg == "" || def == 0)
      ;
  }
  /*!
Get a float from a file

\param arg Name of the prameter
*/
  virtual float getFloat(const std::string& arg) const {
    if (arg == "")
      ;
  }
  /*!
Get a string  from a file

\param arg Name of the prameter
*/
  virtual std::string getString(const std::string& arg) const {
    if (arg == "")
      ;
  }
  /*!
Get a string from a file

\param tag Name of the prameter
\param def Default value (if not found in file)
*/
  virtual std::string getString(const std::string& arg,
                                const std::string& def) const {
    if (arg == def)
      ;
  }
  /*!
Get boolean from a file

\param arg Name of the prameter
\param def Default value (if not found in file)
*/
  virtual bool getBool(const std::string& arg, const bool def) const {
    if (arg == "" || def == 0)
      ;
  }
  /*!
  Get a boolean from a file

  \param arg Name of the prameter
  */
  virtual bool getBool(const std::string& arg) const {
    if (arg == "")
      ;
  }
  /*!
  Get integer from a file

  \param arg Name of the prameter
  \param nvals Number of values
  */
  virtual std::vector<int> getInts(const std::string& arg,
                                   const int nvals) const {
    if (arg == "" || nvals == 0)
      ;
  }
  /*!
  Get integer from a file

  \param arg Name of the prameter
  \param defs Default values
  */
  virtual std::vector<int> getInts(const std::string& arg,
                                   const std::vector<int>& defs) const {
    if (arg == "" && defs.size() == -1)
      ;
  }
  /*!
  Get an floats from a file

  \param arg Name of the prameter
  \param nval Number of values to look for
  */
  virtual std::vector<float> getFloats(const std::string& arg,
                                       int nvals) const {
    if (arg == "" || nvals == 0)
      ;
  }
  /*!
  Get floats from a file

  \param arg Name of the prameter
  \param def Default value (if not found in file)
  */
  virtual std::vector<float> getFloats(const std::string& arg,
                                       const std::vector<float>& defs) const {
    if (arg == "" || defs.size() == -1)
      ;
  }

  /*!
  Get an integer from a file

  \param arg Name of the prameter

  \param doc Documentation for parameter
  */
  virtual int getDocInt(const std::string& arg, const std::string& doc);
  /*!
  Get an integer from a file

  \param arg Name of the prameter

  \param doc Documentation for parameter

  \param def Default value (if not found in file)
  */
  virtual int gettDocInt(const std::string& arg, const std::string& doc,
                         const int def);
  /*!
  Get a float from a file

  \param arg Name of the prameter

  \param doc Documentation for parameter

  \param def Default value (if not found in file)
  */
  virtual float gettDocFloat(const std::string& arg, const std::string& doc,
                             const float def);
  /*!
  Get a float from a file

  \param arg Name of the prameter

  \param doc Documentation for parameter

  */
  virtual float gettDocFloat(const std::string& arg, const std::string& doc);
  /*!
  Get a string  from a file

  \param arg Name of the prameter

  \param doc Documentation for parameter

  */
  virtual std::string gettDocString(const std::string& arg,
                                    const std::string& doc);
  /*!
  Get a string from a file

  \param tag Name of the prameter

  \param doc Documentation for parameter

  \param def Default value (if not found in file)
  */
  virtual std::string gettDocString(const std::string& arg,
                                    const std::string& doc,
                                    const std::string& def);

  /*!
  Get boolean from a file

  \param arg Name of the prameter

  \param doc Documentation for parameter

  \param def Default value (if not found in file)
  */
  virtual bool gettDocBool(const std::string& arg, const std::string& doc,
                           const bool def);
  /*!
  Get a boolean from a file

  \param arg Name of the prameter

  \param doc Documentation for parameter

  */
  virtual bool gettDocBool(const std::string& arg, const std::string& doc);
  /*!
  Get integer from a file

  \param arg Name of the prameter

  \param doc Documentation for parameter

  \param nvals Number of values
  */
  virtual std::vector<int> gettDocInts(const std::string& arg,
                                       const std::string& doc, const int nvals);
  /*!
  Get integer from a file

  \param arg Name of the prameter

  \param doc Documentation for parameter

  \param defs Default values
  */
  virtual std::vector<int> gettDocInts(const std::string& arg,
                                       const std::string& doc,
                                       const std::vector<int>& defs);
  /*!
  Get an floats from a file

  \param arg Name of the prameter

  \param doc Documentation for parameter

  \param nval Number of values to look for
  */
  virtual std::vector<float> gettDocFloats(const std::string& arg,
                                           const std::string& doc, int nvals);
  /*!
  Get floats from a file

  \param arg Name of the prameter

  \param doc Documentation for parameter

  \param def Default value (if not found in file)
  */
  virtual std::vector<float> gettDocFloats(const std::string& arg,
                                           const std::string& doc,
                                           const std::vector<float>& defs);
};  // namespace SEP
}  // namespace SEP

#endif
