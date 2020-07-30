#include "irregFile.h"
#include "string.h"
using namespace SEP;

void genericIrregFile::setHyper(const std::shared_ptr<SEP::hypercube> &hyp)
{
  _hyper = hyp->clone();
}
std::string genericIrregFile::getDataTypeString()
{
  dataType x = getDataType();

  switch (x)
  {
  case DATA_FLOAT:
    return std::string("DATA_FLOAT");
    break;
  case DATA_BYTE:
    return std::string("DATA_BYTE");
    break;
  // case dataShort:
  // return std::string("DATA_SHORT");
  // break;
  case DATA_INT:
    return std::string("DATA_INT");
    break;
  case DATA_DOUBLE:
    return std::string("DATA_DOUBLE");
    break;
  case DATA_COMPLEX:
    return std::string("DATA_COMPLEX");
    break;
  case DATA_COMPLEXDOUBLE:
    return std::string("DATA_COMPLEXDOUBLE");
    break;
  default:
    return std::string("dataUndefined");
  }
}
int genericIrregFile::getDataEsize()
{
  dataType x = getDataType();

  switch (x)
  {
  case DATA_FLOAT:
    return 4;
    break;
  case DATA_BYTE:
    return 1;
    break;
  case DATA_DOUBLE:
    return 8;
    break;
  case DATA_INT:
    return 4;
    break;
  case DATA_COMPLEX:
    return 8;
    break;
  case DATA_COMPLEXDOUBLE:
    return 16;
    break;
  default:
    return -1;
  }
}

std::string genericIrregFile::getDescriptionString()
{

  Json::Value x = getDescription();
  Json::FastWriter fast;
  return fast.write(x);
}

std::string genericIrregFile::getDataDescriptionString()
{
  Json::Value x = getDataDescription();
  Json::FastWriter fast;
  return fast.write(x);
}
std::pair<std::map<std::string, int>, std::map<std::string, int>>
genericIrregFile::createOffsetMap() const
{

  std::vector<std::string> keyList = getHeaderKeyList();
  std::map<std::string, std::string> keyType = getHeaderKeyTypes();
  std::map<std::string, int> offset, sz;
  int last = 0;
  for (auto i = 0; i < keyList.size(); i++)
  {
    std::string key = keyList[i];
    offset[key] = last;
    if (keyType[key] == std::string("dataByte"))
      sz[key] = 1;
    else if (keyType[key] == std::string("dataShort"))
      sz[key] = 2;
    else if (keyType[key] == std::string("dataInt"))
      sz[key] = 4;
    else if (keyType[key] == std::string("dataFloat"))
      sz[key] = 4;
    else if (keyType[key] == std::string("dataComplex"))
      sz[key] = 8;
    else if (keyType[key] == std::string("dataDouble"))
      sz[key] = 8;
    else if (keyType[key] == std::string("dataComplexDouble"))
      sz[key] = 16;
    else
      throw SEPException(std::string("Unknown keytype:") + keyType[key]);
    last += sz[key];
  }
  return make_pair(offset, sz);
}

std::shared_ptr<byte1DReg>
genericIrregFile::extractByte(std::shared_ptr<byte2DReg> buf,
                              const int off) const
{
  char *inb = (char *)buf->getVals();
  int n2 = buf->getHyper()->getAxis(2).n;
  int n1 = buf->getHyper()->getAxis(1).n;
  std::shared_ptr<byte1DReg> out(new byte1DReg(n2));
  char *outb = (char *)out->getVals();

  for (int i = 0; i < n2; i++)
  {
    memcpy(outb + 1 * i, inb + n1 * i + off, 1);
  }
  return out;
}
std::shared_ptr<short1DReg>
genericIrregFile::extractShort(std::shared_ptr<byte2DReg> buf,
                               const int off) const
{
  char *inb = (char *)buf->getVals();
  int n2 = buf->getHyper()->getAxis(2).n;
  int n1 = buf->getHyper()->getAxis(1).n;
  std::shared_ptr<short1DReg> out(new short1DReg(n2));
  char *outb = (char *)out->getVals();

  for (int i = 0; i < n2; i++)
  {
    memcpy(outb + 2 * i, inb + n1 * i + off, 2);
  }
  return out;
}
std::shared_ptr<int1DReg>
genericIrregFile::extractInt(std::shared_ptr<byte2DReg> buf,
                             const int off) const
{
  char *inb = (char *)buf->getVals();
  int n2 = buf->getHyper()->getAxis(2).n;
  int n1 = buf->getHyper()->getAxis(1).n;
  std::shared_ptr<int1DReg> out(new int1DReg(n2));
  char *outb = (char *)out->getVals();

  for (int i = 0; i < n2; i++)
  {
    memcpy(outb + 4 * i, inb + n1 * i + off, 4);
  }
  return out;
}
std::shared_ptr<float1DReg>
genericIrregFile::extractFloat(std::shared_ptr<byte2DReg> buf,
                               const int off) const
{
  char *inb = (char *)buf->getVals();
  int n2 = buf->getHyper()->getAxis(2).n;
  int n1 = buf->getHyper()->getAxis(1).n;
  std::shared_ptr<float1DReg> out(new float1DReg(n2));
  char *outb = (char *)out->getVals();

  for (int i = 0; i < n2; i++)
  {
    memcpy(outb + 4 * i, inb + n1 * i + off, 4);
  }
  return out;
}
std::shared_ptr<complex1DReg>
genericIrregFile::extractComplex(std::shared_ptr<byte2DReg> buf,
                                 const int off) const
{
  char *inb = (char *)buf->getVals();
  int n2 = buf->getHyper()->getAxis(2).n;
  int n1 = buf->getHyper()->getAxis(1).n;
  std::shared_ptr<complex1DReg> out(new complex1DReg(n2));
  char *outb = (char *)out->getVals();

  for (int i = 0; i < n2; i++)
  {
    memcpy(outb + 8 * i, inb + n1 * i + off, 8);
  }
  return out;
}
std::shared_ptr<double1DReg>
genericIrregFile::extractDouble(std::shared_ptr<byte2DReg> buf,
                                const int off) const
{
  char *inb = (char *)buf->getVals();
  int n2 = buf->getHyper()->getAxis(2).n;
  int n1 = buf->getHyper()->getAxis(1).n;
  std::shared_ptr<double1DReg> out(new double1DReg(n2));
  char *outb = (char *)out->getVals();

  for (int i = 0; i < n2; i++)
  {
    memcpy(outb + 8 * i, inb + n1 * i + off, 8);
  }
  return out;
}
std::shared_ptr<complexDouble1DReg>
genericIrregFile::extractComplexDouble(std::shared_ptr<byte2DReg> buf,
                                       const int off) const
{
  char *inb = (char *)buf->getVals();
  int n2 = buf->getHyper()->getAxis(2).n;
  int n1 = buf->getHyper()->getAxis(1).n;
  std::shared_ptr<complexDouble1DReg> out(new complexDouble1DReg(n2));
  char *outb = (char *)out->getVals();

  for (int i = 0; i < n2; i++)
  {
    memcpy(outb + 16 * i, inb + n1 * i + off, 16);
  }
  return out;
}
void genericIrregFile::insertValue(void *outv, void *inv, const int off,
                                   const int sz, const int n1,
                                   const int n2) const
{
  char *outb = (char *)outv;
  char *inb = (char *)inv;
  int *x = (int *)inv;
  fprintf(stderr, "in inser value off=%d sz=%d n1=%d \n", off, sz, n1);
  for (int i = 0; i < n2; i++)
  {
    fprintf(stderr, "seeing %d %d\n", i, x[i]);
    memcpy(outb + n1 * i + off, inb + i * sz, sz);
  }
}
void genericIrregFile::putDescriptionString(const std::string &title,
                                            const std::string &descrp)
{
  Json::Value x;

  Json::Reader reader;
  if (!reader.parse(descrp.c_str(), x))
    throw SEPException("trouble parsing string");

  putDescription(title, x);
}

void genericIrregFile::putDataDescriptionString(const std::string &descrp)
{
  Json::Value x;
  Json::Reader reader;
  if (!reader.parse(descrp.c_str(), x))
    throw SEPException("trouble parsing string");
  putDataDescription(x);
}
void genericIrregFile::checkWindow(const std::vector<int> &nwind,
                                   const std::vector<int> &fwind,
                                   const std::vector<int> &jwind,
                                   std::shared_ptr<SEP::hypercube> hyper)
{
  std::vector<int> ns = hyper->getNs();
  for (int i = 1; i < ns.size(); i++)
  {
    if (fwind[i] < 0)
      throw SEPException("Illegal fwind < 0");
    if (jwind[i] < 1)
      throw SEPException("Illegal jwind <1");
    if (fwind[i] + jwind[i] * (nwind[i] - 1) + 1 > ns[i])
      throw SEPException(std::string("Illegal window parameter axis ") +
                         std::to_string(i + 1) + std::string(" nw=") +
                         std::to_string(nwind[i]) + std::string(" fw=") +
                         std::to_string(fwind[i]) + std::string(" jw=") +
                         std::to_string(jwind[i]) + std::string(" n=") +
                         std::to_string(ns[i]));
  }
}

void genericIrregFile::setHaveGrid(const bool gr)
{
  if (_writeLastH != 0)
  {
    if (_haveGrid != gr)
      throw SEPException(
          "Can not change wheter or not you have a grid after first write");
  }
  _haveGrid = gr;
}
