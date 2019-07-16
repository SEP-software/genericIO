#include <pybind11/chrono.h>
#include <pybind11/complex.h>
#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "dictParams.h"
#include "floatHyper.h"
#include "genericFile.h"
#include "genericIO.h"
#include "ioModes.h"

namespace py = pybind11;
namespace giee {
using namespace SEP;

/*

      */

PYBIND11_MODULE(pyGenericIO, clsGeneric) {
  py::enum_<usage_code>(clsGeneric, "usage_code")
      .value("usageIn", usage_code::usageIn)
      .value("usageOut", usage_code::usageOut)
      .value("usageInOut", usage_code::usageInOut)
      .value("usageScr", usage_code::usageScr);

  py::enum_<dataType>(clsGeneric, "dataType")
      .value("dataFloat", dataType::DATA_FLOAT)
      .value("dataByte", dataType ::DATA_BYTE)
      .value("dataDouble", dataType ::DATA_DOUBLE)
      .value("dataShort", dataType ::DATA_SHORT)
      .value("dataInt", dataType::DATA_INT)
      .value("dataComplex", dataType::DATA_COMPLEX)
      .value("dataUndefined", dataType::DATA_UNKNOWN);

  py::class_<paramObj, std::shared_ptr<paramObj>>(clsGeneric,
                                                  "paramObj")  //
      .def(py::init<>(), "Initlialize a new paramObj")
      .def("error",
           (void (paramObj::*)(const std::string &) const) & paramObj::error,
           "Throw an error")
      .def("message",
           (void (paramObj::*)(const std::string &) const) & paramObj::message,
           "Output a message to stderr")
      .def("getInt",
           (int (paramObj::*)(const std::string &) const) & paramObj::getInt,
           "Get a required integer parameters")
      .def("getInt",
           (int (paramObj::*)(const std::string &, const int) const) &
               paramObj::getInt,
           "Get an integer parameter, if not specified use the default")
      .def(
          "getFloat",
          (float (paramObj::*)(const std::string &) const) & paramObj::getFloat,
          "Get a required float parameters")
      .def("getFloat",
           (float (paramObj::*)(const std::string &, const float) const) &
               paramObj::getFloat,
           "Get a float parameter, if not specified use the default")
      .def("getString",
           (std::string(paramObj::*)(const std::string &) const) &
               paramObj::getString,
           "Get a required string parameters")
      .def("getString",
           (std::string(paramObj::*)(const std::string &, const std::string &)
                const) &
               paramObj::getString,
           "Get a string parameter, if not specified use the default")
      .def("getBool",
           (bool (paramObj::*)(const std::string &) const) & paramObj::getBool,
           "Get a required bool parameter")
      .def("getBool",
           (bool (paramObj::*)(const std::string &, const bool) const) &
               paramObj::getBool,
           "Get a boolean parameter, if not specified use the default")
      .def("getInts",
           (std::vector<int>(paramObj::*)(const std::string &, const int)
                const) &
               paramObj::getInts,
           "Get a required  list of integeres parameter")
      .def("getInts",
           (std::vector<int>(paramObj::*)(const std::string &,
                                          const std::vector<int> &) const) &
               paramObj::getInts,
           "Get a series of intergers, if not specified use the default")
      .def("getFloats",
           (std::vector<float>(paramObj::*)(const std::string &, const int)
                const) &
               paramObj::getFloats,
           "Get a required  list of floats parameter")
      .def("getFloats",
           (std::vector<float>(paramObj::*)(const std::string &,
                                            const std::vector<float> &) const) &
               paramObj::getFloats,
           "Get a series of floats, if not specified use the default");

  py::class_<dictParams, paramObj, std::shared_ptr<dictParams>>(clsGeneric,
                                                                "pythonParams")
      .def(py::init<std::map<std::string, std::string>>(),
           "Initialize a pythonParams object")
      .def("resetParams",
           (void (dictParams::*)(const std::map<std::string, std::string>)) &
               dictParams::resetParams,
           "Reset parameters")
      .def("addParams",
           (void (dictParams::*)(const std::map<std::string, std::string>)) &
               dictParams::addParams,
           "Add parameters");

  py::class_<genericRegFile, paramObj, std::shared_ptr<genericRegFile>>(
      clsGeneric, "genericRegFile")
      // .def(py::init<>(), "Initlialize a genericRegFile (don't use this)")
      .def("putInt",
           (void (genericRegFile::*)(const std::string &, const int) const) &
               genericRegFile::putInt,
           "Write an integer parameters")

      .def("putFloat",
           (void (genericRegFile::*)(const std::string &, const float) const) &
               genericRegFile::putFloat,
           "Write a float parameters")

      .def("putString",
           (void (genericRegFile::*)(const std::string &, const std::string)
                const) &
               genericRegFile::putFloat,
           "Write a string parameters")

      .def("putBool",
           (void (genericRegFile::*)(const std::string &, const bool) const) &
               genericRegFile::putBool,
           "Write a boolean parameters")

      .def("putInts",
           (void (genericRegFile::*)(const std::string &,
                                     const std::vector<int> &) const) &
               genericRegFile::putInts,
           "Write  a vector or integer parameters")

      .def("putFloats",
           (void (genericRegFile::*)(const std::string &,
                                     const std::vector<float> &) const) &
               genericRegFile::putFloats,
           "Write  a vector or float parameters")

      .def("readByteStream",
           (void (genericRegFile ::*)(unsigned char *, const long long)) &
               genericRegFile::readByteStream,
           "Read a stream of unisigned chars")

      .def("readFloatStream",
           (void (genericRegFile ::*)(float *, const long long)) &
               genericRegFile::readFloatStream,
           "Read a stream of floats")
      .def("readDoubleStream",
           (void (genericRegFile ::*)(double *, const long long)) &
               genericRegFile::readDoubleStream,
           "Read a stream of doubles")
      .def("readIntStream",
           (void (genericRegFile ::*)(int *, const long long)) &
               genericRegFile::readIntStream,
           "Read a stream of ints")

      .def("readComplexStream",
           (void (genericRegFile ::*)(std::complex<float> *, const long long)) &
               genericRegFile::readComplexStream,
           "Read a stream of complex numbers")
      .def("writeByteStream",
           (void (genericRegFile ::*)(const unsigned char *, const long long)) &
               genericRegFile::writeByteStream,
           "Write a stream of complex")
      .def("writeComplexStream",
           (void (genericRegFile ::*)(const std::complex<float> *,
                                      const long long)) &
               genericRegFile::writeComplexStream,
           "Write a stream of complex")
      .def("writeFloatStream",
           (void (genericRegFile ::*)(const float *, const long long)) &
               genericRegFile::writeFloatStream,
           "Write a stream of floats")
      .def("writeDoubleStream",
           (void (genericRegFile ::*)(const double *, const long long)) &
               genericRegFile::writeDoubleStream,
           "Write a stream of floats")

      .def("close", (void (genericRegFile ::*)()) & genericRegFile::close,
           "Close file")
      .def("readByteWindow",
           (void (genericRegFile ::*)(
               const std::vector<int> &, const std::vector<int> &,
               const std::vector<int> &, unsigned char *)) &
               genericRegFile::readByteWindow,
           "Read a window of unsigned chars")
      .def("readFloatWindow",
           (void (genericRegFile ::*)(const std::vector<int> &,
                                      const std::vector<int> &,
                                      const std::vector<int> &, float *)) &
               genericRegFile::readFloatWindow,
           "Read a window of floats")

      .def(
          "writeFloatStream",
          (bool (genericRegFile ::*)(const std::shared_ptr<giee::floatHyper>)) &
              genericRegFile::writeFloatStream,
          "Write a float stream into a sepVector")

      .def("writeDoubleStream",
           (bool (genericRegFile ::*)(
               const std::shared_ptr<giee::doubleHyper>)) &
               genericRegFile::writeDoubleStream,
           "Write a double stream into a sepVector")
      .def("writeComplexStream",
           (bool (genericRegFile ::*)(
               const std::shared_ptr<giee::complexHyper>)) &
               genericRegFile::writeComplexStream,
           "Write a complex stream into a sepVector")
      .def("writeByteStream",
           (bool (genericRegFile ::*)(const std::shared_ptr<giee::byteHyper>)) &
               genericRegFile::writeByteStream,
           "Write a byte stream into a sepVector")
      .def("readFloatStream",
           (bool (genericRegFile ::*)(std::shared_ptr<giee::floatHyper>)) &
               genericRegFile::readFloatStream,
           "Read  a float stream into a sepVector")
      .def("readDoubleStream",
           (bool (genericRegFile ::*)(std::shared_ptr<giee::doubleHyper>)) &
               genericRegFile::readDoubleStream,
           "Read  a double stream into a sepVector")
      .def("readIntStream",
           (bool (genericRegFile ::*)(std::shared_ptr<giee::intHyper>)) &
               genericRegFile::readIntStream,
           "Read  a int stream into a sepVector")
      .def("readComplexStream",
           (bool (genericRegFile ::*)(std::shared_ptr<giee::complexHyper>)) &
               genericRegFile::readComplexStream,
           "Read  a complex stream into a sepVector")
      .def("readByteStream",
           (bool (genericRegFile ::*)(std::shared_ptr<giee::byteHyper>)) &
               genericRegFile::readByteStream,
           "Read  a byte stream into a sepVector")
      .def("readFloatWindow",
           (bool (genericRegFile ::*)(
               const std::vector<int> &, const std::vector<int> &,
               const std::vector<int> &, std::shared_ptr<giee::floatHyper>)) &
               genericRegFile::readFloatWindow,
           "Read  a window of floats  into a sepVector")
      .def("writeFloatWindow",
           (bool (genericRegFile ::*)(
               const std::vector<int> &, const std::vector<int> &,
               const std::vector<int> &,
               const std::shared_ptr<giee::floatHyper>)) &
               genericRegFile::writeFloatWindow,
           "Write  a window of floats  into a sepVector")
      .def("readComplexWindow",
           (void (genericRegFile ::*)(
               const std::vector<int> &, const std::vector<int> &,
               const std::vector<int> &, std::complex<float> *)) &
               genericRegFile::readComplexWindow,
           "Read a window of complex")
      .def("writeFloatWindow",
           (void (genericRegFile ::*)(
               const std::vector<int> &, const std::vector<int> &,
               const std::vector<int> &, const float *)) &
               genericRegFile::writeFloatWindow,
           "Write a window of floats")

      .def("writeComplexWindow",
           (void (genericRegFile ::*)(
               const std::vector<int> &, const std::vector<int> &,
               const std::vector<int> &, const std::complex<float> *)) &
               genericRegFile::writeComplexWindow,
           "Write a window of complex")

      .def("readDescription", (void (genericRegFile::*)(const int)) &
                                  genericRegFile::readDescription)
      .def("writeDescription",
           (void (genericRegFile::*)()) & genericRegFile::writeDescription)

      .def("setHyper",
           (void (genericRegFile::*)(std::shared_ptr<SEP::hypercube>)) &
               genericRegFile::setHyper)
      .def("getHyper",
           (std::shared_ptr<hypercube>(genericRegFile::*)()) &
               genericRegFile::getHyper,
           "Set the hyper")
      .def_property("_hyper", &genericRegFile::getHyper,
                    &genericRegFile::setHyper,
                    py::return_value_policy::reference)
      .def("getDataType",
           (dataType(genericRegFile::*)()) & genericRegFile::getDataType)
      .def("setDataType", (void (genericRegFile::*)(const dataType)) &
                              genericRegFile::setDataType);

  py::class_<genericIO, std::shared_ptr<genericIO>>(clsGeneric, "genericIO")

      .def("getRegFile",
           (std::shared_ptr<SEP::genericRegFile>(genericIO::*)(
               const std::string &, const SEP::usage_code, const int)) &
               genericIO::getRegFile)
      .def("getRegFile",
           (std::shared_ptr<SEP::genericRegFile>(genericIO::*)(
               const std::string &, const std::string, const int)) &
               genericIO::getRegFile)
      .def("fileDebug", (void (genericIO::*)(const std::string, const float *,
                                             const int, const int)) &
                            genericIO::fileDebug)
      .def("fileDebug", (void (genericIO::*)(const std::string, const float *,
                                             const int, const int, const int)) &
                            genericIO::fileDebug)
      .def("getParamObj", (std::shared_ptr<paramObj>(genericIO::*)()) &
                              genericIO::getParamObj);
  py::class_<ioModes>(clsGeneric, "ioModes")
      .def(py::init<std::vector<std::string>>(), "Initlialize a new IO")
      .def("getInputIO",
           (std::shared_ptr<genericIO>(ioModes::*)()) & ioModes::getInputIO)
      .def("getOutputIO",
           (std::shared_ptr<genericIO>(ioModes::*)()) & ioModes::getOutputIO)
      .def("getParamObj",
           (std::shared_ptr<paramObj>(ioModes::*)()) & ioModes::getParamObj)
      .def("getDefaultIO",
           (std::shared_ptr<genericIO>(ioModes::*)()) & ioModes::getDefaultIO)
      .def("getIO", (std::shared_ptr<genericIO>(ioModes::*)(std::string)) &
                        ioModes::getIO);
}
}  // namespace giee
