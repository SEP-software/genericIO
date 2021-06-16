#include "sep_reg_file.h"
extern "C"
{
#include "sep3d.h"
#include "seplib.h"
}
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include "SEPException.h"
using namespace SEP;
sepRegFile::sepRegFile(const std::string &tag, const usage_code usage,
                       const int ndim)
{
  _tag = tag;
  _usage = usage;
  switch (usage)
  {
  case usageIn:

    if (_tag != "in")
      if (NULL == auxin(_tag.c_str()))
        error(std::string("can not open file ") + tag);

    readDescription(ndim);
    _binary = getString("in");

    break;
  case usageOut:
    if (tag != "out")
      if (0 == auxout(_tag.c_str()))
        error(std::string("can not open file ") + tag);
    break;
  case usageInOut:
    if (0 == auxinout(_tag.c_str()))
      _binary = getString("in");

    error(std::string("can not open file ") + tag);
    break;
  case usageScr:
    if (0 == auxscr(_tag.c_str()))
      _binary = getString("in");

    error(std::string("can not open file ") + tag);
    break;
  default:
    error("can't handle type");
  }
}

void sepRegFile::remove()
{
  char temp[20000];
  auxpar("in", "s", temp, _tag.c_str());
  std::stringstream test(temp);
  std::string segment;

  while (std::getline(test, segment, ';'))
    std::remove(segment.c_str()); // delete file

  strcpy(temp, _tag.c_str());
  getch(_tag.c_str(), "s", temp);

  segment = temp;
  std::remove(segment.c_str()); // delete file
}

void sepRegFile::readFloatStream(float *array, const long long npts)
{
  long long nptsT = npts * 4;
  long long ierr = sreed_big(_tag.c_str(), (void *)array, nptsT);
  if (ierr != nptsT)
    error(std::string("Trouble reading from ") + _tag + std::string(" after ") +
          std::to_string(ierr) + std::string(" bytes"));
}
void sepRegFile::readIntStream(int *array, const long long npts)
{
  long long nptsT = npts * 4;
  long long ierr = sreed_big(_tag.c_str(), (void *)array, nptsT);
  if (ierr != nptsT)
    error(std::string("Trouble reading from ") + _tag + std::string(" after ") +
          std::to_string(ierr) + std::string(" bytes"));
}
void sepRegFile::readDoubleStream(double

                                      *array,
                                  const long long npts)
{
  long long nptsT = npts * 8;
  long long ierr = sreed_big(_tag.c_str(), (void *)array, nptsT);
  if (ierr != nptsT)
    error(std::string("Trouble reading from ") + _tag + std::string(" after ") +
          std::to_string(ierr) + std::string(" bytes"));
}
void sepRegFile::readComplexStream(std::complex<float> *array,
                                   const long long npts)
{
  long long nptsT = npts * 8;
  long long ierr = sreed_big(_tag.c_str(), (void *)array, nptsT);
  if (ierr != nptsT)
    error(std::string("Trouble reading from ") + _tag + std::string(" after ") +
          std::to_string(ierr) + std::string(" bytes"));
}
void sepRegFile::readComplexDoubleStream(std::complex<double> *array,
                                         const long long npts)
{
  long long nptsT = npts * 16;
  long long ierr = sreed_big(_tag.c_str(), (void *)array, nptsT);
  if (ierr != nptsT)
    error(std::string("Trouble reading from ") + _tag + std::string(" after ") +
          std::to_string(ierr) + std::string(" bytes"));
}

void sepRegFile::readByteStream(unsigned char *array, const long long npts)
{
  long long nptsT = npts * 1;
  long long ierr = sreed_big(_tag.c_str(), (void *)array, nptsT);
  if (ierr != nptsT)
    error(std::string("Trouble reading from ") + _tag + std::string(" after ") +
          std::to_string(ierr) + std::string(" bytes"));
}

void sepRegFile::writeFloatStream(const float *array, const long long npts)
{
  long long nptsT = npts * 4;
  long long ierr = srite_big(_tag.c_str(), (void *)array, nptsT);
  if (ierr != nptsT)
    error(std::string("Trouble write from ") + _tag + std::string(" after ") +
          std::to_string(ierr) + std::string(" bytes"));
}
void sepRegFile::writeByteStream(const unsigned char *array,
                                 const long long npts)
{
  long long nptsT = npts * 1;
  long long ierr = srite_big(_tag.c_str(), (void *)array, nptsT);
  if (ierr != nptsT)
    error(std::string("Trouble write from ") + _tag + std::string(" after ") +
          std::to_string(ierr) + std::string(" bytes"));
}
void sepRegFile::writeIntStream(const int *array, const long long npts)
{
  long long nptsT = npts * 4;
  long long ierr = srite_big(_tag.c_str(), (void *)array, nptsT);
  if (ierr != nptsT)
    error(std::string("Trouble write from ") + _tag + std::string(" after ") +
          std::to_string(ierr) + std::string(" bytes"));
}
void sepRegFile::writeDoubleStream(const double *array, const long long npts)
{
  long long nptsT = npts * 8;
  set_format(_tag.c_str(), "native_double");
  long long ierr = srite_big(_tag.c_str(), (void *)array, nptsT);
  if (ierr != nptsT)
    error(std::string("Trouble write from ") + _tag + std::string(" after ") +
          std::to_string(ierr) + std::string(" bytes"));
}

void sepRegFile::readFloatWindow(const std::vector<int> &nw,
                                 const std::vector<int> &fw,
                                 const std::vector<int> &jw, float *array)
{
  std::shared_ptr<hypercube> hyper = getHyper();
  std::vector<int> ng = hyper->getNs();

  setDataType(DATA_FLOAT);

  if (ng.size() > nw.size())
  {
    for (int i = nw.size(); i < ng.size(); i++)
    {
      if (ng[i] > 1)
        error("number of dimension does not equal data size");
    }
  }
  if (nw.size() < ng.size() || fw.size() < ng.size() || jw.size() < jw.size())
  {
    error("number of dimensions does not equal data size");
  }

  int ndim = ng.size();
  if (0 != sreed_window(_tag.c_str(), &ndim, ng.data(), nw.data(), fw.data(),
                        jw.data(), 4, array))
    error(std::string("trouble reading data from tag ") + _tag);
}

void sepRegFile::readDoubleWindow(const std::vector<int> &nw,
                                  const std::vector<int> &fw,
                                  const std::vector<int> &jw, double *array)
{
  std::shared_ptr<hypercube> hyper = getHyper();
  std::vector<int> ng = hyper->getNs();

  setDataType(DATA_DOUBLE);

  if (ng.size() > nw.size())
  {
    for (int i = nw.size(); i < ng.size(); i++)
    {
      if (ng[i] > 1)
        error("number of dimension does not equal data size");
    }
  }
  if (nw.size() < ng.size() || fw.size() < ng.size() || jw.size() < jw.size())
  {
    error("number of dimensions does not equal data size");
  }

  int ndim = ng.size();
  if (0 != sreed_window(_tag.c_str(), &ndim, ng.data(), nw.data(), fw.data(),
                        jw.data(), 8, array))
    error(std::string("trouble reading data from tag ") + _tag);
}
void sepRegFile::readIntWindow(const std::vector<int> &nw,
                               const std::vector<int> &fw,
                               const std::vector<int> &jw, int *array)
{
  std::shared_ptr<hypercube> hyper = getHyper();
  std::vector<int> ng = hyper->getNs();

  setDataType(DATA_INT);

  if (ng.size() > nw.size())
  {
    for (int i = nw.size(); i < ng.size(); i++)
    {
      if (ng[i] > 1)
        error("number of dimension does not equal data size");
    }
  }
  if (nw.size() < ng.size() || fw.size() < ng.size() || jw.size() < jw.size())
  {
    error("number of dimensions does not equal data size");
  }

  int ndim = ng.size();
  if (0 != sreed_window(_tag.c_str(), &ndim, ng.data(), nw.data(), fw.data(),
                        jw.data(), 4, array))
    error(std::string("trouble reading data from tag ") + _tag);
}

void sepRegFile::readComplexWindow(const std::vector<int> &nw,
                                   const std::vector<int> &fw,
                                   const std::vector<int> &jw,
                                   std::complex<float> *array)
{
  std::shared_ptr<hypercube> hyper = getHyper();
  setDataType(DATA_COMPLEX);

  std::vector<int> ng = hyper->getNs();
  if (ng.size() > nw.size())
  {
    for (int i = nw.size(); i < ng.size(); i++)
    {
      if (ng[i] > 1)
        error("number of dimension does not equal data size");
    }
  }
  if (nw.size() < ng.size() || fw.size() < ng.size() || jw.size() < jw.size())
  {
    error("number of dimensions does not equal data size");
  }

  int ndim = ng.size();
  if (0 != sreed_window(_tag.c_str(), &ndim, ng.data(), nw.data(), fw.data(),
                        jw.data(), 8, array))
    error(std::string("trouble reading data from tag ") + _tag);
}

void sepRegFile::readComplexDoubleWindow(const std::vector<int> &nw,
                                         const std::vector<int> &fw,
                                         const std::vector<int> &jw,
                                         std::complex<double> *array)
{
  std::shared_ptr<hypercube> hyper = getHyper();
  setDataType(DATA_COMPLEXDOUBLE);

  std::vector<int> ng = hyper->getNs();
  if (ng.size() > nw.size())
  {
    for (int i = nw.size(); i < ng.size(); i++)
    {
      if (ng[i] > 1)
        error("number of dimension does not equal data size");
    }
  }
  if (nw.size() < ng.size() || fw.size() < ng.size() || jw.size() < jw.size())
  {
    error("number of dimensions does not equal data size");
  }

  int ndim = ng.size();

  if (0 != sreed_window(_tag.c_str(), &ndim, ng.data(), nw.data(), fw.data(),
                        jw.data(), 16, array))
    error(std::string("trouble reading data from tag ") + _tag);
}

void sepRegFile::writeComplexStream(const std::complex<float> *array,
                                    const long long npts)
{
  long long nptsT = npts * 8;
  long long ierr = srite_big(_tag.c_str(), (void *)array, nptsT);
  if (ierr != nptsT)
    error(std::string("Trouble write from ") + _tag + std::string(" after ") +
          std::to_string(ierr) + std::string(" bytes"));
}

void sepRegFile::writeComplexDoubleStream(const std::complex<double> *array,
                                          const long long npts)
{
  set_format(_tag.c_str(), "native_double");
  long long nptsT = npts * 16;
  long long ierr = srite_big(_tag.c_str(), (void *)array, nptsT);
  if (ierr != nptsT)
    error(std::string("Trouble write from ") + _tag + std::string(" after ") +
          std::to_string(ierr) + std::string(" bytes"));
}

void sepRegFile::writeComplexWindow(const std::vector<int> &nw,
                                    const std::vector<int> &fw,
                                    const std::vector<int> &jw,
                                    const std::complex<float> *array)
{
  setDataType(DATA_COMPLEX);

  std::shared_ptr<hypercube> hyper = getHyper();
  std::vector<int> ng = hyper->getNs();
  if (ng.size() > nw.size())
  {
    for (int i = nw.size(); i < ng.size(); i++)
    {
      if (ng[i] > 1)
        error("number of dimension does not equal data size");
    }
  }

  if (nw.size() < ng.size() || fw.size() < ng.size() || jw.size() < jw.size())
  {
    error("number of dimensions does not equal data size");
  }

  int ndim = ng.size();
  if (0 != srite_window(_tag.c_str(), &ndim, ng.data(), nw.data(), fw.data(),
                        jw.data(), 8, array))
    error(std::string("trouble writing data to tag ") + _tag);
}
void sepRegFile::writeComplexDoubleWindow(const std::vector<int> &nw,
                                          const std::vector<int> &fw,
                                          const std::vector<int> &jw,
                                          const std::complex<double> *array)
{
  setDataType(DATA_COMPLEXDOUBLE);

  std::shared_ptr<hypercube> hyper = getHyper();
  std::vector<int> ng = hyper->getNs();
  if (ng.size() > nw.size())
  {
    for (int i = nw.size(); i < ng.size(); i++)
    {
      if (ng[i] > 1)
        error("number of dimension does not equal data size");
    }
  }
  if (nw.size() < ng.size() || fw.size() < ng.size() || jw.size() < jw.size())
  {
    error("number of dimensions does not equal data size");
  }
  int ndim = ng.size();
  if (0 != srite_window(_tag.c_str(), &ndim, ng.data(), nw.data(), fw.data(),
                        jw.data(), 16, array))
    error(std::string("trouble writing data to tag ") + _tag);
}
void sepRegFile::readByteWindow(const std::vector<int> &nw,
                                const std::vector<int> &fw,
                                const std::vector<int> &jw,
                                unsigned char *array)
{
  std::shared_ptr<hypercube> hyper = getHyper();
  std::vector<int> ng = hyper->getNs();
  if (ng.size() > nw.size())
  {
    for (int i = nw.size(); i < ng.size(); i++)
    {
      if (ng[i] > 1)
        error("number of dimension does not equal data size");
    }
  }
  if (nw.size() < ng.size() || fw.size() < ng.size() || jw.size() < jw.size())
  {
    error("number of dimensions does not equal data size");
  }
  int ndim = ng.size();
  if (0 != sreed_window(_tag.c_str(), &ndim, ng.data(), nw.data(), fw.data(),
                        jw.data(), 1, array))
    error(std::string("trouble reading data from tag ") + _tag);
}
void sepRegFile::writeFloatWindow(const std::vector<int> &nw,
                                  const std::vector<int> &fw,
                                  const std::vector<int> &jw,
                                  const float *array)
{
  setDataType(DATA_FLOAT);
  std::shared_ptr<hypercube> hyper = getHyper();
  std::vector<int> ng = hyper->getNs();
  if (ng.size() > nw.size())
  {
    for (int i = nw.size(); i < ng.size(); i++)
    {
      if (ng[i] > 1)
        error("number of dimension does not equal data size");
    }
  }

  if (nw.size() < ng.size() || fw.size() < ng.size() || jw.size() < jw.size())
  {
    error("number of dimensions does not equal data size");
  }

  int ndim = ng.size();
  if (0 != srite_window(_tag.c_str(), &ndim, ng.data(), nw.data(), fw.data(),
                        jw.data(), 4, array))
    error(std::string("trouble writing data to tag ") + _tag);
}
void sepRegFile::writeByteWindow(const std::vector<int> &nw,
                                 const std::vector<int> &fw,
                                 const std::vector<int> &jw,
                                 const unsigned char *array)
{
  setDataType(DATA_FLOAT);

  std::shared_ptr<hypercube> hyper = getHyper();
  std::vector<int> ng = hyper->getNs();
  if (ng.size() > nw.size())
  {
    for (int i = nw.size(); i < ng.size(); i++)
    {
      if (ng[i] > 1)
        error("number of dimension does not equal data size");
    }
  }
  if (nw.size() < ng.size() || fw.size() < ng.size() || jw.size() < jw.size())
  {
    error("number of dimensions does not equal data size");
  }
  int ndim = ng.size();
  if (0 != srite_window(_tag.c_str(), &ndim, ng.data(), nw.data(), fw.data(),
                        jw.data(), 1, array))
    error(std::string("trouble writing data to tag ") + _tag);
}

void sepRegFile::writeDoubleWindow(const std::vector<int> &nw,
                                   const std::vector<int> &fw,
                                   const std::vector<int> &jw,
                                   const double *array)
{
  set_format(_tag.c_str(), "native_double");
  setDataType(DATA_DOUBLE);

  std::shared_ptr<hypercube> hyper = getHyper();
  std::vector<int> ng = hyper->getNs();
  if (ng.size() > nw.size())
  {
    for (int i = nw.size(); i < ng.size(); i++)
    {
      if (ng[i] > 1)
        error("number of dimension does not equal data size");
    }
  }
  if (nw.size() < ng.size() || fw.size() < ng.size() || jw.size() < jw.size())
  {
    error("number of dimensions does not equal data size");
  }
  int ndim = ng.size();
  if (0 != srite_window(_tag.c_str(), &ndim, ng.data(), nw.data(), fw.data(),
                        jw.data(), 8, array))
    error(std::string("trouble writing data to tag ") + _tag);
}
void sepRegFile::writeIntWindow(const std::vector<int> &nw,
                                const std::vector<int> &fw,
                                const std::vector<int> &jw, const int *array)
{
  setDataType(DATA_INT);

  std::shared_ptr<hypercube> hyper = getHyper();
  std::vector<int> ng = hyper->getNs();
  if (ng.size() > nw.size())
  {
    for (int i = nw.size(); i < ng.size(); i++)
    {
      if (ng[i] > 1)
        error("number of dimension does not equal data size");
    }
  }
  if (nw.size() < ng.size() || fw.size() < ng.size() || jw.size() < jw.size())
  {
    error("number of dimensions does not equal data size");
  }
  int ndim = ng.size();
  if (0 != srite_window(_tag.c_str(), &ndim, ng.data(), nw.data(), fw.data(),
                        jw.data(), 4, array))
    error(std::string("trouble writing data to tag ") + _tag);
}


void sepRegFile::seekTo(const long long iv, const int whence)
{
  sseek(_tag.c_str(), iv, whence);
}

void sepRegFile::close()
{
  if (_tag == std::string("in"))
  {
    hclose();
  }
  else
    auxclose(_tag.c_str());
}
