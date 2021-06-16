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
namespace SEP
{

     /*

      */

     PYBIND11_MODULE(pyGenericIO, clsGeneric)
     {
          py::enum_<usage_code>(clsGeneric, "usage_code")
              .value("usageIn", usage_code::usageIn)
              .value("usageOut", usage_code::usageOut)
              .value("usageInOut", usage_code::usageInOut)
              .value("usageScr", usage_code::usageScr);

          py::enum_<file_type>(clsGeneric, "file_type")
              .value("invalidFile", file_type::invalid)
              .value("regularFile", file_type::regular)
              .value("irregularFile", file_type::irregular);

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

          py::class_<genericReg, paramObj, std::shared_ptr<genericReg>>(
              clsGeneric, "genericReg")
              // .def(py::init<>(), "Initlialize a genericReg (don't use this)")
              .def("putInt",
                   (void (genericReg::*)(const std::string &, const int) const) &
                       genericReg::putInt,
                   "Write an integer parameters")
              .def("remove", (void (genericReg::*)()) & genericReg::remove,
                   "Remove  all data  associated with the file")
              .def("putFloat",
                   (void (genericReg::*)(const std::string &, const float) const) &
                       genericReg::putFloat,
                   "Write a float parameters")

              .def("putString",
                   (void (genericReg::*)(const std::string &, const std::string)
                        const) &
                       genericReg::putFloat,
                   "Write a string parameters")

              .def("putBool",
                   (void (genericReg::*)(const std::string &, const bool) const) &
                       genericReg::putBool,
                   "Write a boolean parameters")

              .def("putInts",
                   (void (genericReg::*)(const std::string &,
                                             const std::vector<int> &) const) &
                       genericReg::putInts,
                   "Write  a vector or integer parameters")

              .def("putFloats",
                   (void (genericReg::*)(const std::string &,
                                             const std::vector<float> &) const) &
                       genericReg::putFloats,
                   "Write  a vector or float parameters")

              .def("readByteStream",
                   (void (genericReg ::*)(unsigned char *, const long long)) &
                       genericReg::readByteStream,
                   "Read a stream of unisigned chars")

              .def("readFloatStream",
                   (void (genericReg ::*)(float *, const long long)) &
                       genericReg::readFloatStream,
                   "Read a stream of floats")
              .def("readDoubleStream",
                   (void (genericReg ::*)(double *, const long long)) &
                       genericReg::readDoubleStream,
                   "Read a stream of doubles")
              .def("readIntStream",
                   (void (genericReg ::*)(int *, const long long)) &
                       genericReg::readIntStream,
                   "Read a stream of ints")
              .def("getBinary",
                   (std::string(genericReg ::*)() const) &
                       genericReg::getBinary,
                   "Return binary location")
              .def("readComplexStream",
                   (void (genericReg ::*)(std::complex<float> *, const long long)) &
                       genericReg::readComplexStream,
                   "Read a stream of complex numbers")
              .def("writeByteStream",
                   (void (genericReg ::*)(const unsigned char *, const long long)) &
                       genericReg::writeByteStream,
                   "Write a stream of complex")
              .def("writeComplexStream",
                   (void (genericReg ::*)(const std::complex<float> *,
                                              const long long)) &
                       genericReg::writeComplexStream,
                   "Write a stream of complex")
              .def("writeComplexDoubleStream",
                   (void (genericReg ::*)(const std::complex<double> *,
                                              const long long)) &
                       genericReg::writeComplexDoubleStream,
                   "Write a stream of complex doubles")
              .def("writeFloatStream",
                   (void (genericReg ::*)(const float *, const long long)) &
                       genericReg::writeFloatStream,
                   "Write a stream of floats")
              .def("writeDoubleStream",
                   (void (genericReg ::*)(const double *, const long long)) &
                       genericReg::writeDoubleStream,
                   "Write a stream of floats")

              .def("putDescriptionString",
                   (void (genericReg::*)(const std::string &, const std::string &)) &
                       genericReg::putDescriptionString,
                   "Put the  description into the file")
              .def("getDescriptionString",
                   (std::string(genericReg::*)()) &
                       genericReg::getDescriptionString,
                   "Get the  description from the file")

              .def("close", (void (genericReg ::*)()) & genericReg::close,
                   "Close file")
              .def("readByteWindow",
                   (void (genericReg ::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &, unsigned char *)) &
                       genericReg::readByteWindow,
                   "Read a window of unsigned chars")
              .def("readFloatWindow",
                   (void (genericReg ::*)(const std::vector<int> &,
                                              const std::vector<int> &,
                                              const std::vector<int> &, float *)) &
                       genericReg::readFloatWindow,
                   "Read a window of floats")
              .def("readIntWindow",
                   (void (genericReg ::*)(const std::vector<int> &,
                                              const std::vector<int> &,
                                              const std::vector<int> &, int *)) &
                       genericReg::readIntWindow,
                   "Read a window of ints")
              .def("readDoubleWindow",
                   (void (genericReg ::*)(const std::vector<int> &,
                                              const std::vector<int> &,
                                              const std::vector<int> &, double *)) &
                       genericReg::readDoubleWindow,
                   "Read a window of doubles")
              .def("writeFloatStream",
                   (bool (genericReg ::*)(const std::shared_ptr<floatHyper>)) &
                       genericReg::writeFloatStream,
                   "Write a float stream into a sepVector")

              .def("writeDoubleStream",
                   (bool (genericReg ::*)(const std::shared_ptr<doubleHyper>)) &
                       genericReg::writeDoubleStream,
                   "Write a double stream into a sepVector")
              .def("writeComplexStream",
                   (bool (genericReg ::*)(const std::shared_ptr<complexHyper>)) &
                       genericReg::writeComplexStream,
                   "Write a complex stream into a sepVector")
              .def("writeComplexDoubleStream",
                   (bool (genericReg ::*)(
                       const std::shared_ptr<complexDoubleHyper>)) &
                       genericReg::writeComplexDoubleStream,
                   "Write a complex double stream into a sepVector")
              .def("writeByteStream",
                   (bool (genericReg ::*)(const std::shared_ptr<byteHyper>)) &
                       genericReg::writeByteStream,
                   "Write a byte stream into a sepVector")
              .def("readFloatStream",
                   (bool (genericReg ::*)(std::shared_ptr<floatHyper>)) &
                       genericReg::readFloatStream,
                   "Read  a float stream into a sepVector")
              .def("readDoubleStream",
                   (bool (genericReg ::*)(std::shared_ptr<doubleHyper>)) &
                       genericReg::readDoubleStream,
                   "Read  a double stream into a sepVector")
              .def("readIntStream",
                   (bool (genericReg ::*)(std::shared_ptr<intHyper>)) &
                       genericReg::readIntStream,
                   "Read  a int stream into a sepVector")
              .def("readComplexStream",
                   (bool (genericReg ::*)(std::shared_ptr<complexHyper>)) &
                       genericReg::readComplexStream,
                   "Read  a complex stream into a sepVector")
              .def("readByteStream",
                   (bool (genericReg ::*)(std::shared_ptr<byteHyper>)) &
                       genericReg::readByteStream,
                   "Read  a byte stream into a sepVector")
              .def("readFloatWindow",
                   (bool (genericReg ::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &, std::shared_ptr<floatHyper>)) &
                       genericReg::readFloatWindow,
                   "Read  a window of floats  into a sepVector")
              .def("readIntWindow",
                   (bool (genericReg ::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &, std::shared_ptr<intHyper>)) &
                       genericReg::readIntWindow,
                   "Read  a window of ints  into a sepVector")
              .def("readDoubleWindow",
                   (bool (genericReg ::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &, std::shared_ptr<doubleHyper>)) &
                       genericReg::readDoubleWindow,
                   "Read  a window of doubles  into a sepVector")
              .def("readByteWindow",
                   (bool (genericReg ::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &, std::shared_ptr<byteHyper>)) &
                       genericReg::readByteWindow,
                   "Read  a window of bytes  into a sepVector")
              .def("writeByteWindow",
                   (bool (genericReg ::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &, std::shared_ptr<byteHyper>)) &
                       genericReg::writeByteWindow,
                   "Write  a window of bytes  from a sepVector")
              .def("writeFloatWindow",
                   (bool (genericReg ::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &, const std::shared_ptr<floatHyper>)) &
                       genericReg::writeFloatWindow,
                   "Write  a window of floats  into a sepVector")
              .def("writeIntWindow",
                   (bool (genericReg ::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &, const std::shared_ptr<intHyper>)) &
                       genericReg::writeIntWindow,
                   "Write  a window of int  into a sepVector")

              .def("writeComplexWindow",
                   (bool (genericReg ::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &, const std::shared_ptr<complexHyper>)) &
                       genericReg::writeComplexWindow,
                   "Write  a window of complex float  into a sepVector")
              .def("writeComplexDoubleWindow",
                   (bool (genericReg ::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &,
                       const std::shared_ptr<complexDoubleHyper>)) &
                       genericReg::writeComplexDoubleWindow,
                   "Write  a window of complex double  into a sepVector")

              .def("readComplexWindow",
                   (void (genericReg ::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &, std::complex<float> *)) &
                       genericReg::readComplexWindow,
                   "Read a window of complex")
              .def("readComplexWindow",
                   (bool (genericReg ::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &, std::shared_ptr<complexHyper>)) &
                       genericReg::readComplexWindow,
                   "Read  a window of complex  into a sepVector")
              .def("readComplexDoubleWindow",
                   (void (genericReg ::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &, std::complex<double> *)) &
                       genericReg::readComplexDoubleWindow,
                   "Read a window of complex doubles")
              .def("readComplexDoubleWindow",
                   (bool (genericReg ::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &, std::shared_ptr<complexDoubleHyper>)) &
                       genericReg::readComplexDoubleWindow,
                   "Read  a window of complex doubles into a sepVector")
              .def("writeFloatWindow",
                   (void (genericReg ::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &, const float *)) &
                       genericReg::writeFloatWindow,
                   "Write a window of floats")

              .def("writeComplexWindow",
                   (void (genericReg ::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &, const std::complex<float> *)) &
                       genericReg::writeComplexWindow,
                   "Write a window of complex")
              .def("writeComplexWindow",
                   (bool (genericReg ::*)(
                       const std::vector<int> &, const std::vector<int> &,
                       const std::vector<int> &, const std::shared_ptr<complexHyper>)) &
                       genericReg::writeComplexWindow,
                   "Write  a window of complex floats  into a sepVector")
              .def("readDescription", (void (genericReg::*)(const int)) &
                                          genericReg::readDescription)
              .def("writeDescription",
                   (void (genericReg::*)()) & genericReg::writeDescription)

              .def("setHyper",
                   (void (genericReg::*)(std::shared_ptr<SEP::hypercube>)) &
                       genericReg::setHyper)
              .def("getHyper",
                   (std::shared_ptr<hypercube>(genericReg::*)()) &
                       genericReg::getHyper,
                   "Get the hypercube")
              .def_property("_hyper", &genericReg::getHyper,
                            &genericReg::setHyper,
                            py::return_value_policy::reference)
              .def("getDataType",
                   (dataType(genericReg::*)()) & genericReg::getDataType)
              .def("setDataType", (void (genericReg::*)(const dataType)) &
                                      genericReg::setDataType);

          py::class_<genericIrreg, std::shared_ptr<genericIrreg>>(
              clsGeneric, "genericIrreg")
              // .def(py::init<>(), "Initlialize a genericIrreg (don't use this)")
              .def("putInt",
                   (void (genericIrreg::*)(const std::string &, const int) const) &
                       genericIrreg::putInt,
                   "Write an integer parameters")
              .def("remove", (void (genericIrreg::*)()) & genericIrreg::remove,
                   "Remove  all data associated with the file")
              .def(
                  "putFloat",
                  (void (genericIrreg::*)(const std::string &, const float) const) &
                      genericIrreg::putFloat,
                  "Write a float parameters")

              .def("putString",
                   (void (genericIrreg::*)(const std::string &, const std::string)
                        const) &
                       genericIrreg::putFloat,
                   "Write a string parameters")
              .def("putHeaderKeyList",
                   (void (genericIrreg::*)(const std::vector<std::string>) const) &
                       genericIrreg ::putHeaderKeyList,
                   "Put the list of of headers")
              .def("getHeaderKeyList",
                   (std::vector<std::string>(genericIrreg::*)() const) &
                       genericIrreg ::getHeaderKeyList,
                   "Get the list of of headers")
              .def("createOffsetMap",
                   (std::pair<std::map<std::string, int>, std::map<std::string, int>>(
                       genericIrreg ::*)() const) &
                       genericIrreg::createOffsetMap,
                   "Create a map of key offsets and sizes")
              .def("getHyperData",
                   (std::shared_ptr<hypercube>(genericIrreg::*)()) &
                       genericIrreg::getHyperData,
                   "Get the hypercube of the data")
              .def("getHyperHeader",
                   (std::shared_ptr<hypercube>(genericIrreg::*)()) &
                       genericIrreg::getHyperHeader,
                   "Get the hypercube of the header")
              .def("setHyperHeader",
                   (void (genericIrreg::*)(std::shared_ptr<hypercube>)) &
                       genericIrreg::setHyperHeader,
                   "Set the hypercube of the header")
              .def("setHyperData",
                   (void (genericIrreg::*)(std::shared_ptr<hypercube>)) &
                       genericIrreg::setHyperData,
                   "Set the hypercube of the data")
              .def("extractByte",
                   (std::shared_ptr<byte1DReg>(genericIrreg::*)(
                       std::shared_ptr<byte2DReg>, const int) const) &
                       genericIrreg::extractByte,
                   "Extract a byte key from a header chunk")
              .def("extractShort",
                   (std::shared_ptr<short1DReg>(genericIrreg::*)(
                       std::shared_ptr<byte2DReg>, const int) const) &
                       genericIrreg::extractShort,
                   "Extract a short key from a header chunk")
              .def("extractInt",
                   (std::shared_ptr<int1DReg>(genericIrreg::*)(
                       std::shared_ptr<byte2DReg>, const int) const) &
                       genericIrreg::extractInt,
                   "Extract a int key from a header chunk")
              .def("extractFloat",
                   (std::shared_ptr<float1DReg>(genericIrreg::*)(
                       std::shared_ptr<byte2DReg>, const int) const) &
                       genericIrreg::extractFloat,
                   "Extract a float key from a header chunk")
              .def("extractDouble",
                   (std::shared_ptr<double1DReg>(genericIrreg::*)(
                       std::shared_ptr<byte2DReg>, const int) const) &
                       genericIrreg::extractDouble,
                   "Extract a float key from a header chunk")
              .def("extractComplex",
                   (std::shared_ptr<complex1DReg>(genericIrreg::*)(
                       std::shared_ptr<byte2DReg>, const int) const) &
                       genericIrreg::extractComplex,
                   "Extract a float key from a header chunk")
              .def("extractComplexDouble",
                   (std::shared_ptr<complexDouble1DReg>(genericIrreg::*)(
                       std::shared_ptr<byte2DReg>, const int) const) &
                       genericIrreg::extractComplexDouble,
                   "Extract a float key from a header chunk")
              .def("insertValue",
                   (void (genericIrreg::*)(std::shared_ptr<byte2DReg>,
                                               std::shared_ptr<byte1DReg>, const int,
                                               const int, const int, const int) const) &
                       genericIrreg::insertValue,
                   "Insert a key into a header chunk")

              .def("insertValue",
                   (void (genericIrreg::*)(std::shared_ptr<byte2DReg>,
                                               std::shared_ptr<short1DReg>, const int,
                                               const int, const int, const int) const) &
                       genericIrreg::insertValue,
                   "Insert a key into a header chunk")
              .def("insertValue",
                   (void (genericIrreg::*)(std::shared_ptr<byte2DReg>,
                                               std::shared_ptr<float1DReg>, const int,
                                               const int, const int, const int) const) &
                       genericIrreg::insertValue,
                   "Insert a key into a header chunk")
              .def("insertValue",
                   (void (genericIrreg::*)(std::shared_ptr<byte2DReg>,
                                               std::shared_ptr<int1DReg>, const int,
                                               const int, const int, const int) const) &
                       genericIrreg::insertValue,
                   "Insert a key into a header chunk")
              .def("insertValue",
                   (void (genericIrreg::*)(std::shared_ptr<byte2DReg>,
                                               std::shared_ptr<double1DReg>, const int,
                                               const int, const int, const int) const) &
                       genericIrreg::insertValue,
                   "Insert a key into a header chunk")
              .def("insertValue",
                   (void (genericIrreg::*)(std::shared_ptr<byte2DReg>,
                                               std::shared_ptr<complex1DReg>, const int,
                                               const int, const int, const int) const) &
                       genericIrreg::insertValue,
                   "Insert a key into a header chunk")
              .def("insertValue",
                   (void (genericIrreg::*)(
                       std::shared_ptr<byte2DReg>, std::shared_ptr<complexDouble1DReg>,
                       const int, const int, const int, const int) const) &
                       genericIrreg::insertValue,
                   "Insert a key into a header chunk")
              .def("getHeaderKeyTypes",
                   (std::map<std::string, std::string>(genericIrreg::*)() const) &
                       genericIrreg ::getHeaderKeyTypes,
                   "Get the header key types ")
              .def("putHeaderKeyTypes",
                   (void (genericIrreg::*)(std::map<std::string, std::string>)
                        const) &
                       genericIrreg ::putHeaderKeyTypes,
                   "Put the list of of headers")
              .def("putDataDescriptionString",
                   (void (genericIrreg::*)(const std::string &)) &
                       genericIrreg::putDataDescriptionString,
                   "Put the data description into the file")
              .def("putDescriptionString",
                   (void (genericIrreg::*)(const std::string &, const std::string &)) &
                       genericIrreg::putDescriptionString,
                   "Put the  description into the file")
              .def("getDescriptionString",
                   (std::string(genericIrreg::*)()) &
                       genericIrreg::getDescriptionString,
                   "Get the  description from the file")
              .def("getDataDescriptionString",
                   (std::string(genericIrreg::*)()) &
                       genericIrreg::getDataDescriptionString,
                   "Get the data  description from the file")
              .def("putBool",
                   (void (genericIrreg::*)(const std::string &, const bool) const) &
                       genericIrreg::putBool,
                   "Write a boolean parameters")

              .def("putInts",
                   (void (genericIrreg::*)(const std::string &,
                                               const std::vector<int> &) const) &
                       genericIrreg::putInts,
                   "Write  a vector or integer parameters")

              .def("putFloats",
                   (void (genericIrreg::*)(const std::string &,
                                               const std::vector<float> &) const) &
                       genericIrreg::putFloats,
                   "Write  a vector or float parameters")
              .def("getInt",
                   (int (genericIrreg::*)(const std::string &) const) &
                       genericIrreg::getInt,
                   "Get a required integer parameters")
              .def("getInt",
                   (int (genericIrreg::*)(const std::string &, const int) const) &
                       genericIrreg::getInt,
                   "Get an integer parameter, if not specified use the default")
              .def("getFloat",
                   (float (genericIrreg::*)(const std::string &) const) &
                       genericIrreg::getFloat,
                   "Get a required float parameters")
              .def("getFloat",
                   (float (genericIrreg::*)(const std::string &, const float)
                        const) &
                       genericIrreg::getFloat,
                   "Get a float parameter, if not specified use the default")
              .def("getString",
                   (std::string(genericIrreg::*)(const std::string &) const) &
                       genericIrreg::getString,
                   "Get a required string parameters")
              .def("getString",
                   (std::string(genericIrreg::*)(const std::string &,
                                                     const std::string &) const) &
                       genericIrreg::getString,
                   "Get a string parameter, if not specified use the default")
              .def("getBool",
                   (bool (genericIrreg::*)(const std::string &) const) &
                       genericIrreg::getBool,
                   "Get a required bool parameter")
              .def("getBool",
                   (bool (genericIrreg::*)(const std::string &, const bool) const) &
                       genericIrreg::getBool,
                   "Get a boolean parameter, if not specified use the default")
              .def("getInts",
                   (std::vector<int>(genericIrreg::*)(const std::string &,
                                                          const int) const) &
                       genericIrreg::getInts,
                   "Get a required  list of integeres parameter")
              .def("getInts",
                   (std::vector<int>(genericIrreg::*)(
                       const std::string &, const std::vector<int> &) const) &
                       genericIrreg::getInts,
                   "Get a series of intergers, if not specified use the default")
              .def("getFloats",
                   (std::vector<float>(genericIrreg::*)(const std::string &,
                                                            const int) const) &
                       genericIrreg::getFloats,
                   "Get a required  list of floats parameter")

              .def("getFloats",
                   (std::vector<float>(genericIrreg::*)(
                       const std::string &, const std::vector<float> &) const) &
                       genericIrreg::getFloats,
                   "Get a series of floats, if not specified use the default")

              .def("close", (void (genericIrreg ::*)()) & genericIrreg::close,
                   "Close file")

              .def("readDescription", (void (genericIrreg::*)(const int)) &
                                          genericIrreg::readDescription)
              .def("writeDescription",
                   (void (genericIrreg::*)()) & genericIrreg::writeDescription)

              .def("setHyper",
                   (void (genericIrreg::*)(std::shared_ptr<SEP::hypercube>)) &
                       genericIrreg::setHyper)

              .def("getHyper",
                   (std::shared_ptr<hypercube>(genericIrreg::*)()) &
                       genericIrreg::getHyper,
                   "Get the hypercube")
              .def_property("_hyper", &genericIrreg::getHyper,
                            &genericIrreg::setHyper,
                            py::return_value_policy::reference)
              .def("getDataType",
                   (dataType(genericIrreg::*)()) & genericIrreg::getDataType)
              .def("setDataType",
                   (void (genericIrreg::*)(const dataType)) &
                       genericIrreg::setDataType,
                   "Set data type for traces")
              .def("setHaveGrid",
                   (void (genericIrreg::*)(const bool)) &
                       genericIrreg::setHaveGrid,
                   "Set whether the dataset has a grid")
              .def("setInOrder",
                   (void (genericIrreg::*)(const bool)) &
                       genericIrreg::setInOrder,
                   "Set whether the data and header order match")
              .def("getInOrder",
                   (bool (genericIrreg::*)() const) & genericIrreg::getInOrder,
                   "Get whether or traces are in order with headers ")
              .def("getHaveGrid",
                   (bool (genericIrreg::*)() const) & genericIrreg::getHaveGrid,
                   "Get whether or not we have a grid ")
              .def("readHeaderWindow",
                   (std::tuple<std::shared_ptr<byte2DReg>, std::shared_ptr<int1DReg>,
                               std::shared_ptr<byte1DReg>>(genericIrreg ::*)(
                       const std::vector<int> &nwind, const std::vector<int> &fwind,
                       const std::vector<int> &jwind)) &
                       genericIrreg::readHeaderWindow,
                   "Read a window of headers")

              .def("readByteTraceWindow",
                   (std::tuple<std::shared_ptr<byte2DReg>, std::shared_ptr<float2DReg>,
                               std::shared_ptr<byte1DReg>>(genericIrreg ::*)(
                       const std::vector<int> &nwind, const std::vector<int> &fwind,
                       const std::vector<int> &jwind)) &
                       genericIrreg::readByteTraceWindow,
                   "Read a byte of floats")

              .def("readFloatTraceWindow",
                   (std::tuple<std::shared_ptr<byte2DReg>, std::shared_ptr<float2DReg>,
                               std::shared_ptr<byte1DReg>>(genericIrreg ::*)(
                       const std::vector<int> &nwind, const std::vector<int> &fwind,
                       const std::vector<int> &jwind)) &
                       genericIrreg::readFloatTraceWindow,
                   "Read a window of floats")
              .def("readDoubleTraceWindow",
                   (std::tuple<std::shared_ptr<byte2DReg>, std::shared_ptr<double2DReg>,
                               std::shared_ptr<byte1DReg>>(genericIrreg ::*)(
                       const std::vector<int> &nwind, const std::vector<int> &fwind,
                       const std::vector<int> &jwind)) &
                       genericIrreg::readDoubleTraceWindow,
                   "Read a window of double")

              .def("readIntTraceWindow",
                   (std::tuple<std::shared_ptr<byte2DReg>, std::shared_ptr<int2DReg>,
                               std::shared_ptr<byte1DReg>>(genericIrreg ::*)(
                       const std::vector<int> &nwind, const std::vector<int> &fwind,
                       const std::vector<int> &jwind)) &
                       genericIrreg::readIntTraceWindow,
                   "Read a window of int")
              .def(
                  "readComplexTraceWindow",
                  (std::tuple<std::shared_ptr<byte2DReg>, std::shared_ptr<complex2DReg>,
                              std::shared_ptr<byte1DReg>>(genericIrreg ::*)(
                      const std::vector<int> &nwind, const std::vector<int> &fwind,
                      const std::vector<int> &jwind)) &
                      genericIrreg::readComplexTraceWindow,
                  "Read a window of complex")
              .def("readComplexDoubleTraceWindow",
                   (std::tuple<std::shared_ptr<byte2DReg>,
                               std::shared_ptr<complexDouble2DReg>,
                               std::shared_ptr<byte1DReg>>(genericIrreg ::*)(
                       const std::vector<int> &nwind, const std::vector<int> &fwind,
                       const std::vector<int> &jwind)) &
                       genericIrreg::readComplexDoubleTraceWindow,
                   "Read a window of int")

              .def("writeHeaderWindow",
                   (void (genericIrreg ::*)(
                       const std::vector<int> &nwind, const std::vector<int> &fwind,
                       const std::vector<int> &jwind, const std::shared_ptr<int1DReg> &,
                       const std::shared_ptr<byte2DReg> &,
                       const std::shared_ptr<byte1DReg> &

                       )) &
                       genericIrreg::writeHeaderWindow,
                   "Write a window of headers")

              .def(
                  "writeComplexDoubleTraceWindow",
                  (void (genericIrreg ::*)(
                      const std::vector<int> &nwind, const std::vector<int> &fwind,
                      const std::vector<int> &jwind, const std::shared_ptr<byte2DReg> &,
                      const std::shared_ptr<complexDouble2DReg> &,
                      const std::shared_ptr<byte1DReg> &)) &
                      genericIrreg::writeComplexDoubleTraceWindow,
                  "Write a window of complex doubles")

              .def("writeComplexTraceWindow",
                   (void (genericIrreg ::*)(const std::vector<int> &nwind,
                                                const std::vector<int> &fwind,
                                                const std::vector<int> &jwind,
                                                const std::shared_ptr<byte2DReg> &,
                                                const std::shared_ptr<complex2DReg> &,
                                                const std::shared_ptr<byte1DReg> &)) &
                       genericIrreg::writeComplexTraceWindow,
                   "Write a window of complex floats")

              .def("writeDoubleTraceWindow",
                   (void (genericIrreg ::*)(
                       const std::vector<int> &nwind, const std::vector<int> &fwind,
                       const std::vector<int> &jwind, const std::shared_ptr<byte2DReg>,
                       const std::shared_ptr<double2DReg> &,
                       const std::shared_ptr<byte1DReg> &)) &
                       genericIrreg::writeDoubleTraceWindow,
                   "Write a window of doubles")

              .def("writeIntTraceWindow",
                   (void (genericIrreg ::*)(
                       const std::vector<int> &nwind, const std::vector<int> &fwind,
                       const std::vector<int> &jwind, const std::shared_ptr<byte2DReg>,
                       const std::shared_ptr<int2DReg> &,
                       const std::shared_ptr<byte1DReg> &)) &
                       genericIrreg::writeIntTraceWindow,
                   "Write a window of ints")

              .def("writeFloatTraceWindow",
                   (void (genericIrreg ::*)(const std::vector<int> &nwind,
                                                const std::vector<int> &fwind,
                                                const std::vector<int> &jwind,
                                                const std::shared_ptr<byte2DReg> &head,
                                                const std::shared_ptr<float2DReg> &,
                                                const std::shared_ptr<byte1DReg>)) &
                       genericIrreg::writeFloatTraceWindow,
                   "Write a window of floats")

              .def("writeByteTraceWindow",
                   (void (genericIrreg ::*)(const std::vector<int> &nwind,
                                                const std::vector<int> &fwind,
                                                const std::vector<int> &jwind,
                                                const std::shared_ptr<byte2DReg> &,
                                                const std::shared_ptr<byte2DReg> &,
                                                const std::shared_ptr<byte1DReg>)) &
                       genericIrreg::writeByteTraceWindow,
                   "Write a window of bytes")

              ;

          py::class_<genericIO, std::shared_ptr<genericIO>>(clsGeneric, "genericIO")

              .def("getReg",
                   (std::shared_ptr<SEP::genericReg>(genericIO::*)(
                       const std::string &, const SEP::usage_code, const int)) &
                       genericIO::getReg)
              .def("getReg",
                   (std::shared_ptr<SEP::genericReg>(genericIO::*)(
                       const std::string &, const std::string, const int)) &
                       genericIO::getReg)
              .def("getType",
                   (SEP::file_type(genericIO::*)(
                       const std::string &)) &
                       genericIO::getType)
              .def("getIrreg",
                   (std::shared_ptr<SEP::genericIrreg>(genericIO::*)(
                       const std::string &, const SEP::usage_code, const int)) &
                       genericIO::getIrreg)
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
