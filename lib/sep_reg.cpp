#include "sep_reg.h"
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

int sepReg::getInt(const std::string &arg) const
{
  int x;
  if (0 == auxpar(arg.c_str(), "d", &x, _tag.c_str()))
    error(std::string("trouble grabbing parameter ") + arg +
          std::string(" from parameters"));
  return x;
}
int sepReg::getInt(const std::string &arg, const int def) const
{
  int x = def;
  int i = auxpar(arg.c_str(), "d", &x, _tag.c_str());
  return x;
}

float sepReg::getFloat(const std::string &arg, const float def) const
{
  float x = def;
  int i = auxpar(arg.c_str(), "f", &x, _tag.c_str());
  return x;
}
float sepReg::getFloat(const std::string &arg) const
{
  float x;
  if (0 == auxpar(arg.c_str(), "f", &x, _tag.c_str()))
    error(std::string("trouble grabbing parameter ") + arg +
          std::string(" from parameters"));
  return x;
}

std::string sepReg::getString(const std::string &arg) const
{
  char buf[10000];
  if (0 == auxpar(arg.c_str(), "s", buf, _tag.c_str()))
    error(std::string("trouble grabbing parameter ") + arg +
          std::string(" from parameters"));
  return std::string(buf);
}
std::string sepReg::getString(const std::string &arg,
                                  const std::string &def) const
{
  char buf[10000];
  std::copy(def.begin(), def.end(), buf);
  int i = auxpar(arg.c_str(), "s", buf, _tag.c_str());
  return std::string(buf);
}

bool sepReg::getBool(const std::string &arg, const bool def) const
{
  bool x = def;
  int i = auxpar(arg.c_str(), "l", &x, _tag.c_str());
  return x;
}
bool sepReg::getBool(const std::string &arg) const
{
  bool x;
  if (0 == auxpar(arg.c_str(), "l", &x, _tag.c_str()))
  {
    error(std::string("trouble grabbing parameter ") + arg +
          std::string(" from parameters"));
  }
  return x;
}

std::vector<int> sepReg::getInts(const std::string &arg, int num) const
{
  int tmp[10000];
  int ierr = auxpar(arg.c_str(), "d", tmp, _tag.c_str());
  if (ierr == 0)
    error(std::string("trouble grabbing parameter ") + arg +
          std::string(" from parameters"));
  std::vector<int> x;
  for (int i = 0; i < ierr; i++)
    x.push_back(tmp[i]);
  return x;
}
std::vector<int> sepReg::getInts(const std::string &arg,
                                     const std::vector<int> &defs) const
{
  int tmp[10000];
  for (int i = 0; i < defs.size(); i++)
  {
    tmp[i] = defs[i];
  }
  int ierr = auxpar(arg.c_str(), "d", tmp, _tag.c_str());
  if (ierr == 0)
    error(std::string("trouble grabbing parameter ") + arg +
          std::string(" from parameters"));
  std::vector<int> x;
  if (ierr > 0)
  {
    for (int i = 0; i < ierr; i++)
      x.push_back(tmp[i]);
  }
  else
  {
    for (int i = 0; i < defs.size(); i++)
      x.push_back(defs[i]);
  }
  return x;
}

std::vector<float> sepReg::getFloats(const std::string &arg,
                                         int num) const
{
  float tmp[10000];
  int ierr = auxpar(arg.c_str(), "f", tmp, _tag.c_str());
  if (ierr == 0)
    error(std::string("trouble grabbing parameter ") + arg +
          std::string(" from parameters"));
  std::vector<float> x;
  for (int i = 0; i < ierr; i++)
    x.push_back(tmp[i]);
  return x;
}
std::vector<float> sepReg::getFloats(const std::string &arg,
                                         const std::vector<float> &defs) const
{
  float tmp[10000];
  for (int i = 0; i < defs.size(); i++)
  {
    tmp[i] = defs[i];
  }
  int ierr = auxpar(arg.c_str(), "f", tmp, _tag.c_str());
  if (ierr == 0)
    error(std::string("trouble grabbing parameter ") + arg +
          std::string(" from parameters"));
  std::vector<float> x;
  if (ierr > 0)
  {
    for (int i = 0; i < ierr; i++)
      x.push_back(tmp[i]);
  }
  else
  {
    for (int i = 0; i < defs.size(); i++)
      x.push_back(defs[i]);
  }
  return x;
}

void sepReg::error(const std::string &err) const
{
  std::cerr << "why exited " << std::endl;
  throw SEPException(err);
}

void sepReg::putInt(const std::string &par, const int val)
{
  auxputch(par.c_str(), "d", &val, _tag.c_str());
}
void sepReg::putFloat(const std::string &par, const float val)
{
  auxputch(par.c_str(), "f", &val, _tag.c_str());
}
void sepReg::putString(const std::string &par, const std::string &val)
{
  char x[9999];
  std::copy(val.begin(), val.end(), x);
  x[val.length()] = '\0';
  auxputch(par.c_str(), "s", val.c_str(), _tag.c_str());
}

void sepReg::putBool(const std::string &par, const bool val)
{
  int x = 0;
  if (val)
    x = 1;
  auxputch(par.c_str(), "l", &x, _tag.c_str());
}
void sepReg::putInts(const std::string &par, const std::vector<int> &val)
{
  int *tmp = new int[val.size()];
  for (int i = 0; i < val.size(); i++)
    tmp[i] = val[i];
  auxputch(par.c_str(), "d", tmp, _tag.c_str());
  delete[] tmp;
}
void sepReg::putFloats(const std::string &par,
                           const std::vector<float> &val)
{
  float *tmp = new float[val.size()];
  for (int i = 0; i < val.size(); i++)
    tmp[i] = val[i];
  auxputch(par.c_str(), "f", tmp, _tag.c_str());
  delete[] tmp;
}


void sepReg::readDescription(const int ndimMax)
{
  int ndim;
  sep_get_number_data_axes(_tag.c_str(), &ndim);
  if (ndimMax != -1 && ndimMax > ndim)
    ndim = ndimMax;
  std::vector<axis> axes;
  for (int i = 1; i <= ndim; i++)
  {
    int n;
    float o, d;
    char label[1024];
    sep_get_data_axis_par(_tag.c_str(), &i, &n, &o, &d, label);
    axes.push_back(axis(n, o, d, std::string(label)));
  }
  std::shared_ptr<hypercube> hyper(new hypercube(axes));
  setHyper(hyper);
  int esize = getInt("esize", 4);
  if (esize == 1)
    setDataType(DATA_BYTE);
  else if (esize == 4)
  {
    std::string format =
        getString(std::string("data_format"), std::string("xdr_float"));
    if (format == std::string("xdr_float") ||
        format == std::string("native_float"))
      setDataType(DATA_FLOAT);
    else if (format == std::string("xdr_int") ||
             format == std::string("native_int"))
      setDataType(DATA_INT);
    else
      error(std::string("Unknown data type " + format));
  }
  else if (esize == 8)
  {
    std::string format =
        getString(std::string("data_format"), std::string("xdr_float"));
    if (format == std::string("xdr_float") || format == "native_float")
      setDataType(DATA_COMPLEX);
    else if (format == std::string("native_double"))
      setDataType(DATA_DOUBLE);
    else // For now default to complex
      setDataType(DATA_COMPLEX);
  }
  else if (esize == 16)
  {
    std::string format = std::string("native_double");
    setDataType(DATA_COMPLEXDOUBLE);
  }
  else
    error(std::string("Only know about esize=8, 4 or 1"));
}
void sepReg::writeDescription()
{
  std::shared_ptr<hypercube> hyper = getHyper();
  std::vector<axis> axes = hyper->returnAxes(hyper->getNdim());

  for (int i = 1; i <= axes.size(); i++)
  {
    int n = axes[i - 1].n;
    float o = axes[i - 1].o;
    float d = axes[i - 1].d;
    char label[1024];
    std::copy(axes[i - 1].label.begin(), axes[i - 1].label.end(), label);
    label[axes[i - 1].label.length()] = '\0';
    sep_put_data_axis_par(_tag.c_str(), &i, &n, &o, &d, label);
  }
  for (int i = axes.size() + 1; i <= 8; i++)
  {
    int n = 1;
    float o = 0., d = 1.;
    sep_put_data_axis_par(_tag.c_str(), &i, &n, &o, &d, "none");
  }
  int esize = 4;

  switch (getDataType())
  {
  case DATA_INT:
    set_format(_tag.c_str(), "xdr_int");
    break;
  case DATA_DOUBLE:
    set_format(_tag.c_str(), "native_float");
    esize = 8;
    break;
  case DATA_COMPLEX:
    set_format(_tag.c_str(), "xdr_int");
    esize = 8;
    break;
  case DATA_COMPLEXDOUBLE:
    set_format(_tag.c_str(), "native_double");
    esize = 16;
    break;
  case DATA_BYTE:
    set_format(_tag.c_str(), "xdr_byte");
    esize = 1;
    break;
  default:
    set_format(_tag.c_str(), "xdr_float");
    break;
  }

  auxputch("esize", "d", &esize, _tag.c_str());
}
void sepReg::message(const std::string &arg) const
{
  sepwarn(0, arg.c_str());
}



void sepReg::putDescription(const std::string &title,
                                const Json::Value &desc)
{
  std::stringstream stream;
  stream << desc;
  std::string tmp = std::string("FROM ") + title;
  char delim = '\n'; // Ddefine the delimiter to split by
  auxputhead(_tag.c_str(), tmp.c_str());
  while (std::getline(stream, tmp, delim))
  {
    auxputhead(_tag.c_str(), tmp.c_str());
  }
}
