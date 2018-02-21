#include <pybind11/chrono.h>
#include <pybind11/complex.h>
#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "genericFile.h"
#include "genericIO.h"
#include "ioModes.h"
#ifdef USE_SEPVECTOR
#include "floatHyper.h"
#endif

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
      .value("dataFloat", dataType::dataFloat)
      .value("dataByte", dataType ::dataByte)
      .value("dataShort", dataType ::dataShort)
      .value("dataInt", dataType::dataInt)
      .value("dataComplex", dataType::dataComplex)
      .value("dataUndefined", dataType::dataUndefined);

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

  py::class_<genericRegFile, paramObj, std::shared_ptr<genericRegFile>>(
      clsGeneric, "genericRegFile")
      .def(py::init<>(), "Initlialize a genericRegFile (don't use this)")
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

      .def("readUCharStream",
           (void (genericRegFile ::*)(unsigned char *, const long long)) &
               genericRegFile::readUCharStream,
           "Read a stream of unisigned chars")

      .def("readFloatStream",
           (void (genericRegFile ::*)(float *, const long long)) &
               genericRegFile::readFloatStream,
           "Read a stream of floats")

      .def("readComplexStream",
           (void (genericRegFile ::*)(std::complex<float>, const long long)) &
               genericRegFile::readComplexStream,
           "Read a stream of complex numbers")

      .def("writeFloatStream",
           (void (genericRegFile ::*)(const float *, const long long)) &
               genericRegFile::writeFloatStream,
           "Write a stream of floats")
      .def("close", (void (genericRegFile ::*)()) & genericRegFile::close,
           "Close file")
      .def("readUCharWindow",
           (void (genericRegFile ::*)(
               const std::vector<int> &, const std::vector<int> &,
               const std::vector<int>, unsigned char *)) &
               genericRegFile::readUCharWindow,
           "Read a window of unsigned chars")
      .def("readFloatWindow",
           (void (genericRegFile ::*)(const std::vector<int> &,
                                      const std::vector<int> &,
                                      const std::vector<int> &, float *)) &
               genericRegFile::readFloatWindow,
           "Read a window of floats")
#ifdef USE_SEPVECTOR

      .def(
          "writeFloatStream",
          (bool (genericRegFile ::*)(const std::shared_ptr<giee::floatHyper>)) &
              genericRegFile::writeFloatStream,
          "Write a float stream into a sepVector")
      .def("readFloatStream",
           (bool (genericRegFile ::*)(std::shared_ptr<giee::floatHyper>)) &
               genericRegFile::readFloatStream,
           "Read  a float stream into a sepVector")
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
#endif
      .def("readComplexWindow",
           (void (genericRegFile ::*)(
               const std::vector<int> &, const std::vector<int> &,
               const std::vector<int>, std::complex<float> *)) &
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
               const std::vector<int>, std::complex<float> *)) &
               genericRegFile::writeComplexWindow,
           "Write a window of complex")

      .def("readDescription",
           (void (genericRegFile::*)()) & genericRegFile::readDescription)
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

      .def("getRegFile", (std::shared_ptr<SEP::genericRegFile>(genericIO::*)(
                             const std::string &, const SEP::usage_code)) &
                             genericIO::getRegFile)
      .def("getRegFile", (std::shared_ptr<SEP::genericRegFile>(genericIO::*)(
                             const std::string &, const std::string)) &
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
      .def("getDefaultIO",
           (std::shared_ptr<genericIO>(ioModes::*)()) & ioModes::getDefaultIO)
      .def("getIO", (std::shared_ptr<genericIO>(ioModes::*)(std::string)) &
                        ioModes::getIO);
}
}  // namespace giee