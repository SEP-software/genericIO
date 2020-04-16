#include "dictParams.h"
#include "floatHyper.h"
#include "genericFile.h"
#include "genericIO.h"
#include "ioModes.h"
#include "irregFile.h"
#include <pybind11/chrono.h>
#include <pybind11/complex.h>
#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
namespace py = pybind11;
namespace SEP {

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
      .value("dataComplexDouble", dataType::DATA_COMPLEXDOUBLE)
      .value("dataUndefined", dataType::DATA_UNKNOWN);

  py::class_<paramObj, std::shared_ptr<paramObj>>(clsGeneric,
                                                  "paramObj") //
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
      .def("getFloat",
           (float (paramObj::*)(const std::string &) const) &
               paramObj::getFloat,
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
      .def("addParams",
           (void (paramObj::*)(std::map<std::string, std::string> &)) &
               paramObj::addParams,
           "Add parameters")
      .def("addParams",
           (void (paramObj::*)(std::vector<std::string> &)) &
               paramObj::addParams,
           "Add parameters")
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
      .def("remove", (void (genericRegFile::*)()) & genericRegFile::remove,
           "Remove  all data  associated with the file")
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
      .def("getBinary",
           (std::string(genericRegFile ::*)() const) &
               genericRegFile::getBinary,
           "Return binary location")
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
      .def("writeComplexDoubleStream",
           (void (genericRegFile ::*)(const std::complex<double> *,
                                      const long long)) &
               genericRegFile::writeComplexDoubleStream,
           "Write a stream of complex doubles")
      .def("writeFloatStream",
           (void (genericRegFile ::*)(const float *, const long long)) &
               genericRegFile::writeFloatStream,
           "Write a stream of floats")
      .def("writeDoubleStream",
           (void (genericRegFile ::*)(const double *, const long long)) &
               genericRegFile::writeDoubleStream,
           "Write a stream of floats")

      .def("putDescriptionString",
           (void (genericRegFile::*)(const std::string &)) &
               genericRegFile::putDescriptionString,
           "Put the  description into the file")
      .def("getDescriptionString",
           (std::string(genericRegFile::*)()) &
               genericRegFile::getDescriptionString,
           "Get the  description from the file")

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
      .def("readDoubleWindow",
           (void (genericRegFile ::*)(const std::vector<int> &,
                                      const std::vector<int> &,
                                      const std::vector<int> &, double *)) &
               genericRegFile::readDoubleWindow,
           "Read a window of doubles")
      .def("writeFloatStream",
           (bool (genericRegFile ::*)(const std::shared_ptr<floatHyper>)) &
               genericRegFile::writeFloatStream,
           "Write a float stream into a sepVector")

      .def("writeDoubleStream",
           (bool (genericRegFile ::*)(const std::shared_ptr<doubleHyper>)) &
               genericRegFile::writeDoubleStream,
           "Write a double stream into a sepVector")
      .def("writeComplexStream",
           (bool (genericRegFile ::*)(const std::shared_ptr<complexHyper>)) &
               genericRegFile::writeComplexStream,
           "Write a complex stream into a sepVector")
      .def("writeComplexDoubleStream",
           (bool (genericRegFile ::*)(
               const std::shared_ptr<complexDoubleHyper>)) &
               genericRegFile::writeComplexDoubleStream,
           "Write a complex double stream into a sepVector")
      .def("writeByteStream",
           (bool (genericRegFile ::*)(const std::shared_ptr<byteHyper>)) &
               genericRegFile::writeByteStream,
           "Write a byte stream into a sepVector")
      .def("readFloatStream",
           (bool (genericRegFile ::*)(std::shared_ptr<floatHyper>)) &
               genericRegFile::readFloatStream,
           "Read  a float stream into a sepVector")
      .def("readDoubleStream",
           (bool (genericRegFile ::*)(std::shared_ptr<doubleHyper>)) &
               genericRegFile::readDoubleStream,
           "Read  a double stream into a sepVector")
      .def("readIntStream",
           (bool (genericRegFile ::*)(std::shared_ptr<intHyper>)) &
               genericRegFile::readIntStream,
           "Read  a int stream into a sepVector")
      .def("readComplexStream",
           (bool (genericRegFile ::*)(std::shared_ptr<complexHyper>)) &
               genericRegFile::readComplexStream,
           "Read  a complex stream into a sepVector")
      .def("readByteStream",
           (bool (genericRegFile ::*)(std::shared_ptr<byteHyper>)) &
               genericRegFile::readByteStream,
           "Read  a byte stream into a sepVector")
      .def("readFloatWindow",
           (bool (genericRegFile ::*)(
               const std::vector<int> &, const std::vector<int> &,
               const std::vector<int> &, std::shared_ptr<floatHyper>)) &
               genericRegFile::readFloatWindow,
           "Read  a window of floats  into a sepVector")
      .def("readDoubleWindow",
           (bool (genericRegFile ::*)(
               const std::vector<int> &, const std::vector<int> &,
               const std::vector<int> &, std::shared_ptr<doubleHyper>)) &
               genericRegFile::readDoubleWindow,
           "Read  a window of doubles  into a sepVector")
      .def("readByteWindow",
           (bool (genericRegFile ::*)(
               const std::vector<int> &, const std::vector<int> &,
               const std::vector<int> &, std::shared_ptr<byteHyper>)) &
               genericRegFile::readByteWindow,
           "Read  a window of bytes  into a sepVector")
      .def("writeByteWindow",
           (bool (genericRegFile ::*)(
               const std::vector<int> &, const std::vector<int> &,
               const std::vector<int> &, std::shared_ptr<byteHyper>)) &
               genericRegFile::writeByteWindow,
           "Write  a window of bytes  from a sepVector")
      .def("writeFloatWindow",
           (bool (genericRegFile ::*)(
               const std::vector<int> &, const std::vector<int> &,
               const std::vector<int> &, const std::shared_ptr<floatHyper>)) &
               genericRegFile::writeFloatWindow,
           "Write  a window of floats  into a sepVector")

      .def("writeComplexWindow",
           (bool (genericRegFile ::*)(
               const std::vector<int> &, const std::vector<int> &,
               const std::vector<int> &, const std::shared_ptr<complexHyper>)) &
               genericRegFile::writeComplexWindow,
           "Write  a window of complex float  into a sepVector")
      .def("writeComplexDoubleWindow",
           (bool (genericRegFile ::*)(
               const std::vector<int> &, const std::vector<int> &,
               const std::vector<int> &,
               const std::shared_ptr<complexDoubleHyper>)) &
               genericRegFile::writeComplexDoubleWindow,
           "Write  a window of complex double  into a sepVector")

      .def("readComplexWindow",
           (void (genericRegFile ::*)(
               const std::vector<int> &, const std::vector<int> &,
               const std::vector<int> &, std::complex<float> *)) &
               genericRegFile::readComplexWindow,
           "Read a window of complex")
      .def("readComplexWindow",
           (bool (genericRegFile ::*)(
               const std::vector<int> &, const std::vector<int> &,
               const std::vector<int> &, std::shared_ptr<complexHyper>)) &
               genericRegFile::readComplexWindow,
           "Read  a window of complex  into a sepVector")
      .def("readComplexDoubleWindow",
           (void (genericRegFile ::*)(
               const std::vector<int> &, const std::vector<int> &,
               const std::vector<int> &, std::complex<double> *)) &
               genericRegFile::readComplexDoubleWindow,
           "Read a window of complex doubles")
      .def("readComplexDoubleWindow",
           (bool (genericRegFile ::*)(
               const std::vector<int> &, const std::vector<int> &,
               const std::vector<int> &, std::shared_ptr<complexDoubleHyper>)) &
               genericRegFile::readComplexDoubleWindow,
           "Read  a window of complex doubles into a sepVector")
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
      .def("writeComplexWindow",
           (bool (genericRegFile ::*)(
               const std::vector<int> &, const std::vector<int> &,
               const std::vector<int> &, const std::shared_ptr<complexHyper>)) &
               genericRegFile::writeComplexWindow,
           "Write  a window of complex floats  into a sepVector")
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
           "Get the hypercube")
      .def_property("_hyper", &genericRegFile::getHyper,
                    &genericRegFile::setHyper,
                    py::return_value_policy::reference)
      .def("getDataType",
           (dataType(genericRegFile::*)()) & genericRegFile::getDataType)
      .def("setDataType", (void (genericRegFile::*)(const dataType)) &
                              genericRegFile::setDataType);

  py::class_<genericIrregFile, std::shared_ptr<genericIrregFile>>(
      clsGeneric, "genericIrregFile")
      // .def(py::init<>(), "Initlialize a genericIrregFile (don't use this)")
      .def("putInt",
           (void (genericIrregFile::*)(const std::string &, const int) const) &
               genericIrregFile::putInt,
           "Write an integer parameters")
      .def("remove", (void (genericIrregFile::*)()) & genericIrregFile::remove,
           "Remove  all data associated with the file")
      .def(
          "putFloat",
          (void (genericIrregFile::*)(const std::string &, const float) const) &
              genericIrregFile::putFloat,
          "Write a float parameters")

      .def("putString",
           (void (genericIrregFile::*)(const std::string &, const std::string)
                const) &
               genericIrregFile::putFloat,
           "Write a string parameters")
      .def("putHeaderKeyList",
           (void (genericIrregFile::*)(const std::vector<std::string>) const) &
               genericIrregFile ::putHeaderKeyList,
           "Put the list of of headers")
      .def("getHeaderKeyList",
           (std::vector<std::string>(genericIrregFile::*)() const) &
               genericIrregFile ::getHeaderKeyList,
           "Get the list of of headers")
      .def("createOffsetMap",
           (std::pair<std::map<std::string, int>, std::map<std::string, int>>(
               genericIrregFile ::*)() const) &
               genericIrregFile::createOffsetMap,
           "Create a map of key offsets and sizes")
      .def("getHyperData",
           (std::shared_ptr<hypercube>(genericIrregFile::*)()) &
               genericIrregFile::getHyperData,
           "Get the hypercube of the data")
      .def("setHyperHeader",
           (void (genericIrregFile::*)(std::shared_ptr<hypercube>)) &
               genericIrregFile::setHyperHeader,
           "Set the hypercube of the header")
      .def("setHyperData",
           (void (genericIrregFile::*)(std::shared_ptr<hypercube>)) &
               genericIrregFile::setHyperData,
           "Set the hypercube of the data")
      .def("extractByte",
           (std::shared_ptr<byte1DReg>(genericIrregFile::*)(
               std::shared_ptr<byte2DReg>, const int) const) &
               genericIrregFile::extractByte,
           "Extract a byte key from a header chunk")
      .def("extractShort",
           (std::shared_ptr<short1DReg>(genericIrregFile::*)(
               std::shared_ptr<byte2DReg>, const int) const) &
               genericIrregFile::extractShort,
           "Extract a short key from a header chunk")
      .def("extractInt",
           (std::shared_ptr<int1DReg>(genericIrregFile::*)(
               std::shared_ptr<byte2DReg>, const int) const) &
               genericIrregFile::extractInt,
           "Extract a int key from a header chunk")
      .def("extractFloat",
           (std::shared_ptr<float1DReg>(genericIrregFile::*)(
               std::shared_ptr<byte2DReg>, const int) const) &
               genericIrregFile::extractFloat,
           "Extract a float key from a header chunk")
      .def("extractDouble",
           (std::shared_ptr<double1DReg>(genericIrregFile::*)(
               std::shared_ptr<byte2DReg>, const int) const) &
               genericIrregFile::extractDouble,
           "Extract a float key from a header chunk")
      .def("extractComplex",
           (std::shared_ptr<complex1DReg>(genericIrregFile::*)(
               std::shared_ptr<byte2DReg>, const int) const) &
               genericIrregFile::extractComplex,
           "Extract a float key from a header chunk")
      .def("extractComplexDouble",
           (std::shared_ptr<complexDouble1DReg>(genericIrregFile::*)(
               std::shared_ptr<byte2DReg>, const int) const) &
               genericIrregFile::extractComplexDouble,
           "Extract a float key from a header chunk")
      .def("insertValue",
           (void (genericIrregFile::*)(std::shared_ptr<byte2DReg>,
                                       std::shared_ptr<byte1DReg>, const int,
                                       const int, const int, const int) const) &
               genericIrregFile::insertValue,
           "Insert a key into a header chunk")

      .def("insertValue",
           (void (genericIrregFile::*)(std::shared_ptr<byte2DReg>,
                                       std::shared_ptr<short1DReg>, const int,
                                       const int, const int, const int) const) &
               genericIrregFile::insertValue,
           "Insert a key into a header chunk")
      .def("insertValue",
           (void (genericIrregFile::*)(std::shared_ptr<byte2DReg>,
                                       std::shared_ptr<float1DReg>, const int,
                                       const int, const int, const int) const) &
               genericIrregFile::insertValue,
           "Insert a key into a header chunk")
      .def("insertValue",
           (void (genericIrregFile::*)(std::shared_ptr<byte2DReg>,
                                       std::shared_ptr<int1DReg>, const int,
                                       const int, const int, const int) const) &
               genericIrregFile::insertValue,
           "Insert a key into a header chunk")
      .def("insertValue",
           (void (genericIrregFile::*)(std::shared_ptr<byte2DReg>,
                                       std::shared_ptr<double1DReg>, const int,
                                       const int, const int, const int) const) &
               genericIrregFile::insertValue,
           "Insert a key into a header chunk")
      .def("insertValue",
           (void (genericIrregFile::*)(std::shared_ptr<byte2DReg>,
                                       std::shared_ptr<complex1DReg>, const int,
                                       const int, const int, const int) const) &
               genericIrregFile::insertValue,
           "Insert a key into a header chunk")
      .def("insertValue",
           (void (genericIrregFile::*)(
               std::shared_ptr<byte2DReg>, std::shared_ptr<complexDouble1DReg>,
               const int, const int, const int, const int) const) &
               genericIrregFile::insertValue,
           "Insert a key into a header chunk")
      .def("getHeaderKeyTypes",
           (std::map<std::string, std::string>(genericIrregFile::*)() const) &
               genericIrregFile ::getHeaderKeyTypes,
           "Get the header key types ")
      .def("putHeaderKeyTypes",
           (void (genericIrregFile::*)(std::map<std::string, std::string>)
                const) &
               genericIrregFile ::putHeaderKeyTypes,
           "Put the list of of headers")
      .def("putDataDescriptionString",
           (void (genericIrregFile::*)(const std::string &)) &
               genericIrregFile::putDataDescriptionString,
           "Put the data description into the file")
      .def("putDescriptionString",
           (void (genericIrregFile::*)(const std::string &)) &
               genericIrregFile::putDescriptionString,
           "Put the  description into the file")
      .def("getDescriptionString",
           (std::string(genericIrregFile::*)()) &
               genericIrregFile::getDescriptionString,
           "Get the  description from the file")
      .def("getDataDescriptionString",
           (std::string(genericIrregFile::*)()) &
               genericIrregFile::getDataDescriptionString,
           "Get the data  description from the file")
      .def("putBool",
           (void (genericIrregFile::*)(const std::string &, const bool) const) &
               genericIrregFile::putBool,
           "Write a boolean parameters")

      .def("putInts",
           (void (genericIrregFile::*)(const std::string &,
                                       const std::vector<int> &) const) &
               genericIrregFile::putInts,
           "Write  a vector or integer parameters")

      .def("putFloats",
           (void (genericIrregFile::*)(const std::string &,
                                       const std::vector<float> &) const) &
               genericIrregFile::putFloats,
           "Write  a vector or float parameters")
      .def("getInt",
           (int (genericIrregFile::*)(const std::string &) const) &
               genericIrregFile::getInt,
           "Get a required integer parameters")
      .def("getInt",
           (int (genericIrregFile::*)(const std::string &, const int) const) &
               genericIrregFile::getInt,
           "Get an integer parameter, if not specified use the default")
      .def("getFloat",
           (float (genericIrregFile::*)(const std::string &) const) &
               genericIrregFile::getFloat,
           "Get a required float parameters")
      .def("getFloat",
           (float (genericIrregFile::*)(const std::string &, const float)
                const) &
               genericIrregFile::getFloat,
           "Get a float parameter, if not specified use the default")
      .def("getString",
           (std::string(genericIrregFile::*)(const std::string &) const) &
               genericIrregFile::getString,
           "Get a required string parameters")
      .def("getString",
           (std::string(genericIrregFile::*)(const std::string &,
                                             const std::string &) const) &
               genericIrregFile::getString,
           "Get a string parameter, if not specified use the default")
      .def("getBool",
           (bool (genericIrregFile::*)(const std::string &) const) &
               genericIrregFile::getBool,
           "Get a required bool parameter")
      .def("getBool",
           (bool (genericIrregFile::*)(const std::string &, const bool) const) &
               genericIrregFile::getBool,
           "Get a boolean parameter, if not specified use the default")
      .def("getInts",
           (std::vector<int>(genericIrregFile::*)(const std::string &,
                                                  const int) const) &
               genericIrregFile::getInts,
           "Get a required  list of integeres parameter")
      .def("getInts",
           (std::vector<int>(genericIrregFile::*)(
               const std::string &, const std::vector<int> &) const) &
               genericIrregFile::getInts,
           "Get a series of intergers, if not specified use the default")
      .def("getFloats",
           (std::vector<float>(genericIrregFile::*)(const std::string &,
                                                    const int) const) &
               genericIrregFile::getFloats,
           "Get a required  list of floats parameter")

      .def("getFloats",
           (std::vector<float>(genericIrregFile::*)(
               const std::string &, const std::vector<float> &) const) &
               genericIrregFile::getFloats,
           "Get a series of floats, if not specified use the default")

      .def("close", (void (genericIrregFile ::*)()) & genericIrregFile::close,
           "Close file")

      .def("readDescription", (void (genericIrregFile::*)(const int)) &
                                  genericIrregFile::readDescription)
      .def("writeDescription",
           (void (genericIrregFile::*)()) & genericIrregFile::writeDescription)

      .def("setHyper",
           (void (genericIrregFile::*)(std::shared_ptr<SEP::hypercube>)) &
               genericIrregFile::setHyper)

      .def("getHyper",
           (std::shared_ptr<hypercube>(genericIrregFile::*)()) &
               genericIrregFile::getHyper,
           "Get the hypercube")
      .def_property("_hyper", &genericIrregFile::getHyper,
                    &genericIrregFile::setHyper,
                    py::return_value_policy::reference)
      .def("getDataType",
           (dataType(genericIrregFile::*)()) & genericIrregFile::getDataType)
      .def("setDataType", (void (genericIrregFile::*)(const dataType)) &
                              genericIrregFile::setDataType)
      .def("setHaveGrid", (void (genericIrregFile::*)(const bool)) &
                              genericIrregFile::setHaveGrid)
      .def("setInOrder, (void (genericIrregFile::*)(const bool)) &
           genericIrregFile::setInOrder)
      .def("readHeaderWindow",
           (std::tuple<std::shared_ptr<byte2DReg>, std::shared_ptr<int1DReg>,
                       std::shared_ptr<byte1DReg>>(genericIrregFile ::*)(
               const std::vector<int> &nwind, const std::vector<int> &fwind,
               const std::vector<int> &jwind)) &
               genericIrregFile::readHeaderWindow,
           "Read a window of headers")

      .def("readByteTraceWindow",
           (std::tuple<std::shared_ptr<byte2DReg>, std::shared_ptr<float2DReg>,
                       std::shared_ptr<byte1DReg>>(genericIrregFile ::*)(
               const std::vector<int> &nwind, const std::vector<int> &fwind,
               const std::vector<int> &jwind)) &
               genericIrregFile::readByteTraceWindow,
           "Read a byte of floats")

      .def("readFloatTraceWindow",
           (std::tuple<std::shared_ptr<byte2DReg>, std::shared_ptr<float2DReg>,
                       std::shared_ptr<byte1DReg>>(genericIrregFile ::*)(
               const std::vector<int> &nwind, const std::vector<int> &fwind,
               const std::vector<int> &jwind)) &
               genericIrregFile::readFloatTraceWindow,
           "Read a window of floats")
      .def("readDoubleTraceWindow",
           (std::tuple<std::shared_ptr<byte2DReg>, std::shared_ptr<double2DReg>,
                       std::shared_ptr<byte1DReg>>(genericIrregFile ::*)(
               const std::vector<int> &nwind, const std::vector<int> &fwind,
               const std::vector<int> &jwind)) &
               genericIrregFile::readDoubleTraceWindow,
           "Read a window of double")

      .def("readIntTraceWindow",
           (std::tuple<std::shared_ptr<byte2DReg>, std::shared_ptr<int2DReg>,
                       std::shared_ptr<byte1DReg>>(genericIrregFile ::*)(
               const std::vector<int> &nwind, const std::vector<int> &fwind,
               const std::vector<int> &jwind)) &
               genericIrregFile::readIntTraceWindow,
           "Read a window of int")
      .def(
          "readComplexTraceWindow",
          (std::tuple<std::shared_ptr<byte2DReg>, std::shared_ptr<complex2DReg>,
                      std::shared_ptr<byte1DReg>>(genericIrregFile ::*)(
              const std::vector<int> &nwind, const std::vector<int> &fwind,
              const std::vector<int> &jwind)) &
              genericIrregFile::readComplexTraceWindow,
          "Read a window of complex")
      .def("readComplexDoubleTraceWindow",
           (std::tuple<std::shared_ptr<byte2DReg>,
                       std::shared_ptr<complexDouble2DReg>,
                       std::shared_ptr<byte1DReg>>(genericIrregFile ::*)(
               const std::vector<int> &nwind, const std::vector<int> &fwind,
               const std::vector<int> &jwind)) &
               genericIrregFile::readComplexDoubleTraceWindow,
           "Read a window of int")

      .def("writeHeaderWindow",
           (void (genericIrregFile ::*)(const std::vector<int> &nwind,
                                        const std::vector<int> &fwind,
                                        const std::vector<int> &jwind,
                                        const std::shared_ptr<int1DReg> &drn,
                                        const std::shared_ptr<byte2DReg> &)) &
               genericIrregFile::writeHeaderWindow,
           "Write a window of headers")

      .def(
          "writeComplexDoubleTraceWindow",
          (void (genericIrregFile ::*)(
              const std::vector<int> &nwind, const std::vector<int> &fwind,
              const std::vector<int> &jwind, const std::shared_ptr<byte2DReg> &,
              const std::shared_ptr<complexDouble2DReg> &,
              const std::shared_ptr<byte1DReg> &)) &
              genericIrregFile::writeComplexDoubleTraceWindow,
          "Write a window of complex doubles")

      .def("writeComplexTraceWindow",
           (void (genericIrregFile ::*)(const std::vector<int> &nwind,
                                        const std::vector<int> &fwind,
                                        const std::vector<int> &jwind,
                                        const std::shared_ptr<byte2DReg> &,
                                        const std::shared_ptr<complex2DReg> &,
                                        const std::shared_ptr<byte1DReg> &)) &
               genericIrregFile::writeComplexTraceWindow,
           "Write a window of complex floats")

      .def("writeDoubleTraceWindow",
           (void (genericIrregFile ::*)(
               const std::vector<int> &nwind, const std::vector<int> &fwind,
               const std::vector<int> &jwind, const std::shared_ptr<byte2DReg>,
               const std::shared_ptr<double2DReg> &,
               const std::shared_ptr<byte1DReg> &)) &
               genericIrregFile::writeDoubleTraceWindow,
           "Write a window of doubles")

      .def("writeIntTraceWindow",
           (void (genericIrregFile ::*)(
               const std::vector<int> &nwind, const std::vector<int> &fwind,
               const std::vector<int> &jwind, const std::shared_ptr<byte2DReg>,
               const std::shared_ptr<int2DReg> &,
               const std::shared_ptr<byte1DReg> &)) &
               genericIrregFile::writeIntTraceWindow,
           "Write a window of ints")

      .def("writeFloatTraceWindow",
           (void (genericIrregFile ::*)(const std::vector<int> &nwind,
                                        const std::vector<int> &fwind,
                                        const std::vector<int> &jwind,
                                        const std::shared_ptr<byte2DReg> &head,
                                        const std::shared_ptr<float2DReg> &,
                                        const std::shared_ptr<byte1DReg>)) &
               genericIrregFile::writeFloatTraceWindow,
           "Write a window of floats")

      .def("writeByteTraceWindow",
           (void (genericIrregFile ::*)(const std::vector<int> &nwind,
                                        const std::vector<int> &fwind,
                                        const std::vector<int> &jwind,
                                        const std::shared_ptr<byte2DReg> &,
                                        const std::shared_ptr<byte2DReg> &,
                                        const std::shared_ptr<byte1DReg>)) &
               genericIrregFile::writeByteTraceWindow,
           "Write a window of bytes")

      ;

  py::class_<genericIO, std::shared_ptr<genericIO>>(clsGeneric, "genericIO")

      .def("getRegFile",
           (std::shared_ptr<SEP::genericRegFile>(genericIO::*)(
               const std::string &, const SEP::usage_code, const int)) &
               genericIO::getRegFile)
      .def("getRegFile",
           (std::shared_ptr<SEP::genericRegFile>(genericIO::*)(
               const std::string &, const std::string, const int)) &
               genericIO::getRegFile)

      .def("getIrregFile",
           (std::shared_ptr<SEP::genericIrregFile>(genericIO::*)(
               const std::string &, const SEP::usage_code, const int)) &
               genericIO::getIrregFile)

      .def("fileDebug", (void (genericIO::*)(const std::string, const float *,
                                             const int, const int)) &
                            genericIO::fileDebug)
      .def("fileDebug", (void (genericIO::*)(const std::string, const float *,
                                             const int, const int, const int)) &
                            genericIO::fileDebug)
      .def("getType", (std::string(genericIO::*)() const) & genericIO::getType,
           "Get IO type")
      .def("getParamObj", (std::shared_ptr<paramObj>(genericIO::*)()) &
                              genericIO::getParamObj);
  py::class_<ioModes>(clsGeneric, "ioModes")
      .def(py::init<std::vector<std::string>>(), "Initlialize a new IO")
      .def("getInputIO",
           (std::shared_ptr<genericIO>(ioModes::*)()) & ioModes::getInputIO)
      .def("getIOs", (std::vector<std::string>(ioModes::*)()) & ioModes::getIOs)
      .def("getOutputIO",
           (std::shared_ptr<genericIO>(ioModes::*)()) & ioModes::getOutputIO)
      .def("getParamObj",
           (std::shared_ptr<paramObj>(ioModes::*)()) & ioModes::getParamObj)
      .def("changeParamObj", (void (ioModes::*)(std::shared_ptr<paramObj>)) &
                                 ioModes::changeParamObj)
      .def("getDefaultIO",
           (std::shared_ptr<genericIO>(ioModes::*)()) & ioModes::getDefaultIO)
      .def("getDefaultType",
           (std::string(ioModes::*)()) & ioModes::getDefaultType)
      .def("getIO", (std::shared_ptr<genericIO>(ioModes::*)(std::string)) &
                        ioModes::getIO);
}
} // namespace SEP
