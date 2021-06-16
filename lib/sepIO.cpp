
#include "sepIO.h"
#include <cstring>
#include <fstream> // std::ifstream
using namespace SEP;
sepIO::sepIO(const int argc, char **argv)
{
  std::shared_ptr<sepParam> x(new sepParam(argc, argv));
  _param = x;
  setValid(true);
  _type = "SEP";
}

std::shared_ptr<genericReg>
sepIO::getRegTag(const std::string &tag, const std::string &name,
                     const SEP::usage_code usage, const int ndimMax)
{
  std::shared_ptr<sepRegFile> x(new sepRegFile(name, usage));

  addRegFile(tag, x);

  return x;
}
std::shared_ptr<genericIrreg>
sepIO::getIrregTag(const std::string &tag, const std::string &name,
                       const SEP::usage_code usage, const int ndimMax)
{
  std::shared_ptr<sep3dFile> x(new sep3dFile(name, usage, ndimMax));
  addIrregFile(name, x);
  return x;
}

SEP::file_type sepIO::getType(const std::string &name)
{

  std::ifstream inps;
  inps.open(name, std::ifstream::in);
  if (!inps)
    return SEP::invalid;
  if (NULL == auxin(name.c_str()))
    return SEP::invalid;
  int n;
  char tmp[1024];
  if (0 == auxpar("n1", "d", &n, name.c_str()) ||
      0 == auxpar("in", "s", tmp, name.c_str()))
    return SEP::invalidFile;

  if (0 == auxpar("hff", "s", tmp, name.c_str()))
    return SEP::regularFile;
  if (strcmp("-1", tmp) == 0)
    return SEP::regular;

  return SEP::irregular;
}