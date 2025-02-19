#include "sep3dFile.h"
#include <string.h>
extern "C"
{
#include "sep3d.h"
#include "seplib.h"
}
using namespace SEP;
#include <algorithm>
#include "SEPException.h"

sep3dFile::sep3dFile(const std::string &tag, const usage_code usage,
                     const int ndim)
{
  _tag = tag;
  _usage = usage;
  _inOrder = true;

  char *val = getenv("ntrBuffer");
  if (val != NULL)
    _ntrBuffer = atoi(val);

  switch (usage)
  {
  case usageIn:
    /*By default data is in order*/
    /*Set the SEP data type*/
    if (_tag != "in")
      if (NULL == auxin(_tag.c_str()))
        error(std::string("can not open file ") + tag);

    readDescription(ndim);

    break;
  case usageOut:
    if (tag != "out")
      if (0 == auxout(_tag.c_str()))
        error(std::string("can not open file ") + tag);
    break;
  case usageInOut:
    if (0 == auxinout(_tag.c_str()))

      error(std::string("can not open file ") + tag);
    break;
  case usageScr:
    if (0 == auxscr(_tag.c_str()))

      error(std::string("can not open file ") + tag);
    break;
  default:
    error("can't handle type");
  }
}

void sep3dFile::remove()
{
  char temp[20000];
  auxpar("in", "s", temp, _tag.c_str()); // Get Data binary files
  std::stringstream test(temp);
  std::string segment;
  char *tag_header[1];

  // Loop through binary files
  while (std::getline(test, segment, ';'))
    std::remove(segment.c_str()); // delete binary file

  // Remove history file
  strcpy(temp, _tag.c_str());
  getch(_tag.c_str(), "s", temp);
  segment = temp;
  std::remove(segment.c_str()); // delete file

  // Get Header Format File
  sep_get_header_format_tag(_tag.c_str(), tag_header);
  std::string hff = tag_header[0];
  auxpar("in", "s", temp, hff.c_str());

  // Get all the binary files associated with the headers and remove them
  std::stringstream test2(temp);
  while (std::getline(test2, segment, ';'))
    std::remove(segment.c_str()); // delete file
  segment = hff;
  std::remove(segment.c_str()); // delete file
  free(tag_header[0]);

  char *tag_grid[1];
  // Get the grid format file
  if (0 == sep_get_grid_format_tag(_tag.c_str(), tag_grid))
  {
    std::string gff = tag_grid[0];
    auxpar("in", "s", temp, gff.c_str());

    // Remove all the files associated with
    std::stringstream test3(temp);
    while (std::getline(test3, segment, ';'))
      std::remove(segment.c_str()); // delete file

    // Remove grid format file
    segment = gff;
    std::remove(segment.c_str()); // delete file
    free(tag_grid[0]);
  }
}
int sep3dFile::getInt(const std::string &arg) const
{
  int x;
  if (0 == auxpar(arg.c_str(), "d", &x, _tag.c_str()))
    error(std::string("trouble grabbing parameter ") + arg +
          std::string(" from parameters"));
  return x;
}
int sep3dFile::getInt(const std::string &arg, const int def) const
{
  int x = def;
  int i = auxpar(arg.c_str(), "d", &x, _tag.c_str());
  return x;
}

float sep3dFile::getFloat(const std::string &arg, const float def) const
{
  float x = def;
  int i = auxpar(arg.c_str(), "f", &x, _tag.c_str());
  return x;
}
float sep3dFile::getFloat(const std::string &arg) const
{
  float x;
  if (0 == auxpar(arg.c_str(), "f", &x, _tag.c_str()))
    error(std::string("trouble grabbing parameter ") + arg +
          std::string(" from parameters"));
  return x;
}

std::string sep3dFile::getString(const std::string &arg) const
{
  char buf[10000];
  if (0 == auxpar(arg.c_str(), "s", buf, _tag.c_str()))
    error(std::string("trouble grabbing parameter ") + arg +
          std::string(" from parameters"));
  return std::string(buf);
}
std::string sep3dFile::getString(const std::string &arg,
                                 const std::string &def) const
{
  char buf[10000];
  std::copy(def.begin(), def.end(), buf);
  int i = auxpar(arg.c_str(), "s", buf, _tag.c_str());
  return std::string(buf);
}

bool sep3dFile::getBool(const std::string &arg, const bool def) const
{
  bool x = def;
  int i = auxpar(arg.c_str(), "l", &x, _tag.c_str());
  return x;
}
bool sep3dFile::getBool(const std::string &arg) const
{
  bool x;
  if (0 == auxpar(arg.c_str(), "l", &x, _tag.c_str()))
  {
    error(std::string("trouble grabbing parameter ") + arg +
          std::string(" from parameters"));
  }
  return x;
}

std::vector<int> sep3dFile::getInts(const std::string &arg, int num) const
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
std::vector<int> sep3dFile::getInts(const std::string &arg,
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
// A Function to a vector of length [n][2] based on the second
bool sortFunc(std::vector<int> i, std::vector<int> j) { return (i[1] < j[1]); }

std::vector<float> sep3dFile::getFloats(const std::string &arg, int num) const
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
std::vector<float> sep3dFile::getFloats(const std::string &arg,
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

void sep3dFile::close()
{
  // Close the tag
  if (_tag == std::string("in"))
  {
    sep_3d_close();
  }
  else
    sep3dClose(_tag.c_str());
}
// Hopefully never called instead SEPException
void sep3dFile::error(const std::string &err) const
{
  throw SEPException(err);
}

void sep3dFile::putInt(const std::string &par, const int val)
{
  auxputch(par.c_str(), "d", &val, _tag.c_str());
}
void sep3dFile::putFloat(const std::string &par, const float val)
{
  auxputch(par.c_str(), "f", &val, _tag.c_str());
}
void sep3dFile::putString(const std::string &par, const std::string &val)
{
  char x[9999];
  std::copy(val.begin(), val.end(), x);
  x[val.length()] = '\0';
  auxputch(par.c_str(), "s", val.c_str(), _tag.c_str());
}

void sep3dFile::putBool(const std::string &par, const bool val)
{
  int x = 0;
  if (val)
    x = 1;
  auxputch(par.c_str(), "l", &x, _tag.c_str());
}
void sep3dFile::putInts(const std::string &par, const std::vector<int> &val)
{
  int *tmp = new int[val.size()];
  for (int i = 0; i < val.size(); i++)
    tmp[i] = val[i];
  auxputch(par.c_str(), "d", tmp, _tag.c_str());
  delete[] tmp;
}
void sep3dFile::putFloats(const std::string &par,
                          const std::vector<float> &val)
{
  float *tmp = new float[val.size()];
  for (int i = 0; i < val.size(); i++)
    tmp[i] = val[i];
  auxputch(par.c_str(), "f", tmp, _tag.c_str());
  delete[] tmp;
}

void sep3dFile::readDescription(const int ndimMax)
{
  int ndim;

  // Red the data description
  sep_get_number_data_axes(_tag.c_str(), &ndim);
  std::vector<axis> axes, axesT;
  for (int i = 1; i <= ndim; i++)
  {
    int n;
    float o, d;
    char label[1024];
    sep_get_data_axis_par(_tag.c_str(), &i, &n, &o, &d, label);
    axes.push_back(axis(n, o, d, std::string(label)));
  }
  axesT.push_back(axes[0]);
  // Store the data hypercube
  _hyperData.reset(new hypercube(axes));

  // Build a hypercube for the headers
  if (0 != sep_get_number_header_axes(_tag.c_str(), &ndim))
    throw SEPException("Trying to read a regular file as irregular");
  int nkeys;
  char temp_ch[2048];
  if (0 != sep_get_number_keys(_tag.c_str(), &nkeys))
    throw SEPException("Trouble getting number keys");
  std::vector<axis> axesH;
  axesH.push_back(axis(nkeys));

  for (int i = 2; i <= ndim; i++)
  {
    int n;
    float o, d;
    char label[1024];
    sep_get_header_axis_par(_tag.c_str(), &i, &n, &o, &d, label);
    axesH.push_back(axis(n, o, d, std::string(label)));
  }
  _hyperHeader.reset(new hypercube(axesH));

  // Build a hypercube for the grid if it exists
  if (0 == sep_get_number_grid_axes(_tag.c_str(), &ndim))
  {

    std::vector<axis> axesG;
    axesG.push_back(axis(1));
    for (int i = 2; i <= ndim; i++)
    {
      int n;
      float o, d;
      char label[1024];
      sep_get_grid_axis_par(_tag.c_str(), &i, &n, &o, &d, label);
      axesG.push_back(axis(n, o, d, std::string(label)));
    }
    axesG[0] = axesT[0];
    for (int i = 1; i < axesG.size(); i++)
      axesT.push_back(axesG[i]);
    _hyper.reset(new hypercube(axesT));
    _haveGrid = true;
  }
  else
  {

    // The grid doesn't exist use the header hypercube for the dataset
    for (int i = 1; i < axesH.size(); i++)
      axesT.push_back(axesH[i]);
    _hyper.reset(new hypercube(axesT));
    _haveGrid = false;
  }

  // Set the data type
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

  // Read in the keys
  _keys.resize(0);
  for (int ikey = 0; ikey < nkeys; ikey++)
  {
    int ii = ikey + 1;
    if (0 != sep_get_key_name(_tag.c_str(), &ii, temp_ch))
      throw SEPException(std::string("trouble grabbing name for key ") +
                         std::to_string(ikey));
    if (strcmp(temp_ch, "data_record_number") == 0)
    {
      _drn = ikey;
    }
    else
    {

      _keys.push_back(temp_ch);
      if (0 != sep_get_key_type(_tag.c_str(), &ii, temp_ch))
        throw SEPException(std::string("trouble grabbing "
                                       "type for key ") +
                           std::to_string(ikey));

      if (0 == strcmp(temp_ch, "scalar_float"))
        _keyType[_keys[_keys.size() - 1]] = "dataFloat";
      else if (0 == strcmp(temp_ch, "scalar_int"))
        _keyType[_keys[_keys.size() - 1]] = "dataInt";
      else
        throw SEPException(std::string("Can not handle data type ") +
                           std::string(temp_ch));
    }
  }
}
void sep3dFile::writeDescription()
{

  // Write the hypedcube associated with the data
  std::vector<axis> axes = _hyperData->getAxes();
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

  // Set the data type
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

  // Get the hypercube for the headers
  axes = _hyperHeader->getAxes();

  // Write the number of keys. One more if we have a DRN
  int nkeys = _keys.size();
  if (!_inOrder)
  {
    nkeys += 1;
  }
  sep_put_number_keys(_tag.c_str(), &nkeys);

  // Write the keys
  for (int i = 0; i < _keys.size(); i++)
  {
    int j = i + 1;
    if (_keyType[_keys[i]] == "dataInt")
    {
      if (0 != sep_put_key(_tag.c_str(), _keys[i].c_str(), "scalar_int",
                           "xdr_int", &j))
        throw SEPException("Trouble putting key");
    }
    else if (_keyType[_keys[i]] == "dataFloat")
    {
      if (0 != sep_put_key(_tag.c_str(), _keys[i].c_str(), "scalar_float",
                           "xdr_float", &j))
        throw SEPException("Trouble putting key");
    }
    else
    {
      throw SEPException(std::string("Currently unsupported type ") +
                         _keyType[_keys[i]]);
    }
  }

  // Put DRN key
  if (!_inOrder)
  {
    if (0 != sep_put_key(_tag.c_str(), "data_recrd_number", "scalar_int",
                         "xdr_int", &nkeys))
      throw SEPException("Trouble putting key");
  }
  // Put header format file axes
  for (int i = 2; i <= axes.size(); i++)
  {
    int n = axes[i - 1].n;
    float o = axes[i - 1].o;
    float d = axes[i - 1].d;
    char label[1024];
    std::copy(axes[i - 1].label.begin(), axes[i - 1].label.end(), label);
    label[axes[i - 1].label.length()] = '\0';
    sep_put_header_axis_par(_tag.c_str(), &i, &n, &o, &d, label);
  }

  if (_haveGrid)
  {
    // We always write out the grid
    axes = getHyper()->returnAxes(getHyper()->getNdim());
    for (int i = 2; i <= axes.size(); i++)
    {
      int n = axes[i - 1].n;
      float o = axes[i - 1].o;
      float d = axes[i - 1].d;
      char label[1024];
      std::copy(axes[i - 1].label.begin(), axes[i - 1].label.end(), label);
      label[axes[i - 1].label.length()] = '\0';
      sep_put_grid_axis_par(_tag.c_str(), &i, &n, &o, &d, label);
    }
  }
}
// Hopefully never called
void sep3dFile::message(const std::string &arg) const
{
  sepwarn(0, arg.c_str());
}

// Get description
Json::Value sep3dFile::getDescription()
{
  char *tmp_ch;
  int nsz = 100000;
  int nout = nsz * 2;
  tmp_ch = new char[100000];
  grab_history(_tag.c_str(), tmp_ch, nsz, &nout);
  nsz = nout + 1;
  delete[] tmp_ch;
  tmp_ch = new char[nsz];
  grab_history(_tag.c_str(), tmp_ch, nsz, &nout);
  std::string d = tmp_ch;
  char delim = '\n'; // Ddefine the delimiter to split by
  std::string tmp;
  std::stringstream stream;
  stream.str(d);
  Json::Value j;
  while (std::getline(stream, tmp, delim))
  {
    j["History"].append(tmp);
  }

  // std::cerr << "what is going on" << d << std::endl;
  delete[] tmp_ch;
  // Json::Value j;
  // j["SEPFILE"] = d;
  return j;
}

// Get description
Json::Value sep3dFile::getDataDescription()
{
  Json::Value x;
  x["ndim"] = _hyperData->getNdim();
  for (int idim = 0; idim < _hyperData->getNdim(); idim++)
  {
    SEP::axis a = _hyperData->getAxis(idim + 1);
    x[std::string("n") + std::to_string(idim + 1)] = a.n;
    x[std::string("o") + std::to_string(idim + 1)] = a.n;
    x[std::string("d") + std::to_string(idim + 1)] = a.d;
    x[std::string("label") + std::to_string(idim + 1)] = a.label;
  }
  char temp_ch[20400];
  if (1 != auxpar("in", "s", temp_ch, _tag.c_str()))
    throw SEPException("trouble grabbing in ");
  x["in"] = std::string(temp_ch);
  if (1 != auxpar("data_format", "s", temp_ch, _tag.c_str()))
    strcpy(temp_ch, "xdr_float");
  x["data_format"] = std::string(temp_ch);
  int esize = 4;
  auxpar("esize", "d", &esize, _tag.c_str());
  x["esize"] = esize;
  return x;
}

// Put description
void sep3dFile::putDataDescription(const Json::Value &desc)
{

  std::vector<axis> axes;
  for (int i = 0; i < desc["ndim"].asInt(); i++)
  {
    int n = desc[std::string("n") + std::to_string(i + 1)].asInt();
    axes.push_back(
        axis(n, desc[std::string("o") + std::to_string(i + 1)].asFloat(),
             desc[std::string("d") + std::to_string(i + 1)].asFloat(),
             desc[std::string("label") + std::to_string(i + 1)].asString()));
  }
  _hyperData.reset(new SEP::hypercube(axes));
  auxputch("data_format", "s", desc["data_format"].asString().c_str(),
           _tag.c_str());
  int esz = desc["esize"].asInt();
  auxputch("esize", "d", &esz, _tag.c_str());
  auxputch("data_format", "s", desc["data_format"].asString().c_str(),
           _tag.c_str());
  auxputch("in", "s", desc["in"].asString().c_str(), _tag.c_str());
}

// Put description
void sep3dFile::putDescription(const std::string &title,
                               const Json::Value &desc)
{
  std::stringstream stream;
  stream << desc;
  std::string m = std::string("BEG OF OLD\t") + title + std::string("\n-------------------------\n");
  auxputhead(_tag.c_str(), m.c_str());

  std::string tmp = std::string("FROM ") + title + "\n";
  Json::Value lines = desc["History"];
  for (Json::ValueIterator itr = lines.begin(); itr != lines.end(); itr++)
  {
    std::string tmp = (*itr).asString();
    auxputhead(_tag.c_str(), tmp.c_str());
  }
  m = "END OF OLD\n-------------------------\n";
  auxputhead(_tag.c_str(), m.c_str());
}

std::vector<std::string> sep3dFile::getHeaderKeyList() const
{
  std::vector<std::string> lst;
  for (int i = 0; i < _keys.size(); i++)
  {
    lst.push_back(_keys[i]);
  }
  return lst;
}

std::map<std::string, std::string> sep3dFile::getHeaderKeyTypes() const
{
  std::map<std::string, std::string> lst;
  for (auto k = _keyType.begin(); k != _keyType.end(); k++)
  {
    lst[k->first] = k->second;
  }
  return lst;
}

void sep3dFile::putHeaderKeyList(const std::vector<std::string> &keylist)
{
  _keys.clear();
  for (int i = 0; i < keylist.size(); i++)
  {
    _keys.push_back(keylist[i]);
  }
}
void sep3dFile::putHeaderKeyTypes(
    const std::map<std::string, std::string> &typs)
{
  _keyType.clear();
  for (auto k = typs.begin(); k != typs.end(); k++)
  {
    _keyType[k->first] = k->second;
  }
}

std::tuple<std::shared_ptr<byte2DReg>, std::shared_ptr<int1DReg>,
           std::shared_ptr<byte1DReg>>
sep3dFile::readHeaderWindow(const std::vector<int> &nwind,
                            const std::vector<int> &fwind,
                            const std::vector<int> &jwind)
{
  auto both = readHeaderLocs(nwind, fwind, jwind);

  std::vector<std::vector<int>> headerLocs = std::get<0>(both);
  int nkeyIn = _keys.size();
  if (_drn > -1)
    nkeyIn += 1;
  std::shared_ptr<byte2DReg> headBuf(new byte2DReg(4 * nkeyIn, _ntrBuffer));

  std::shared_ptr<byte2DReg> headers(
      new byte2DReg(4 * _keys.size(), headerLocs.size()));
  std::shared_ptr<int1DReg> drns(new int1DReg(headerLocs.size()));
  int idone = 0;
  int imore = 0;
  while (idone + imore < headerLocs.size())
  {
    int ifirst = headerLocs[idone][1];
    bool found = false;
    imore = 1;
    while (!found && idone + imore < headerLocs.size())
    {
      if (headerLocs[idone][1] != idone + ifirst)
      {
        found = true;
        int ii = idone + 1;
        if (0 !=
            sep_get_val_headers(_tag.c_str(), &ii, &imore, headBuf->getVals()))
          throw SEPException(std::string("Trouble reading headers"));
        extractDRN(headers, idone, imore, drns, headBuf, headerLocs);
        idone += imore;
      }
      else
        imore += 1;
    }
  }
  if (idone != headerLocs.size())
  {
    int ii = idone + 1;
    int imore = headerLocs.size() - idone;
    if (0 != sep_get_val_headers(_tag.c_str(), &ii, &imore, headBuf->getVals()))
      throw SEPException(std::string("Trouble reading headers"));
    extractDRN(headers, idone, headerLocs.size() - idone, drns, headBuf,
               headerLocs);
  }
  return std::make_tuple(headers, drns, std::get<1>(both));
}

void sep3dFile::extractDRN(std::shared_ptr<byte2DReg> outV, const int ifirst,
                           const int ntransfer, std::shared_ptr<int1DReg> drns,
                           std::shared_ptr<byte2DReg> &temp,
                           std::vector<std::vector<int>> &headerLocs)
{
  int end = 0, beg = 4 * _keys.size();
  int n1out = beg, n1in = beg;

  if (_drn >= 0)
  {
    beg = 4 * _drn;
    end = 4 * (_keys.size() + 1 - _drn);
    n1in += 4;
  }

  unsigned char *in = temp->getVals();
  unsigned char *out = outV->getVals();
  int *rns = drns->getVals();
  for (int i = 0; i < ntransfer; i++)
  {

    memcpy(out + n1out * (ifirst + i), in + n1in * i, beg);
    if (_drn >= 0)
    {
      memcpy(rns + ifirst + i, in + n1in * i + beg, 4);
      rns[ifirst + i] -= 1;
    }
    else
      memcpy(rns + ifirst + i, &headerLocs[ifirst + i][1], 4);
    if (end > 0)
      memcpy(out + n1out * (ifirst + i) + beg, in + n1in * i + beg + 4, end);
  }
}

std::tuple<std::vector<std::vector<int>>, std::shared_ptr<byte1DReg>>
sep3dFile::readHeaderLocs(const std::vector<int> &nwind,
                          const std::vector<int> &fwind,
                          const std::vector<int> &jwind)
{

  if (_haveGrid)
  {
    std::vector<int> ng, nw = nwind, fw = fwind, jw = jwind;

    nw[0] = 1;
    fw[0] = 0;
    jw[0] = 1;
    long long n123 = 1;
    ng = getHyper()->getNs();
    checkWindow(nw, fw, jw, _hyper);
    for (int i = 0; i < nw.size(); i++)
    {
      n123 *= (long long)nw[i];
    }
    std::vector<int> grid(n123);
    int ndim = ng.size();
    if (0 != sep_get_grid_window(_tag.c_str(), &ndim, &ng[1], &nw[1], &fw[1],
                                 &jw[1], &grid[0]))
      throw SEPException("Trouble reading grid");
    std::shared_ptr<byte1DReg> gr(new byte1DReg(n123));
    int ireal = 0;
    for (auto i = 0; i < n123; i++)
      if (grid[i] >= 0)
        ireal++;
    std::vector<std::vector<int>> headPos(ireal, std::vector<int>(2));
    ireal = 0;
    for (auto i = 0; i < n123; i++)
    {
      if (grid[i] >= 0)
      {
        headPos[ireal][0] = ireal;
        headPos[ireal][1] = grid[i] - 1;
        ireal++;
        (*gr->_mat)[i] = 1;
      }
      else
        (*gr->_mat)[i] = 0;
    }
    std::sort(headPos.begin(), headPos.end(), sortFunc);
    return std::make_tuple(headPos, gr);
  }
  else
  {
    std::vector<int> bs(1, 1);
    std::vector<int> ns = _hyperHeader->getNs();
    int n123 = 1;
    for (auto i = 1; i < ns.size(); i++)
    {

      bs.push_back(bs[i - 1] * ns[i]);
      n123 = ns[i] * n123;
    }
    if (ns.size() != 2)
      throw SEPException("Expecting 2-D headers for now");
    std::vector<std::vector<int>> headPos(nwind[1], std::vector<int>(2));

    for (auto i = 0; i < nwind[1]; i++)
    {
      headPos[i][0] = i;
      headPos[i][1] = fwind[1] + jwind[1] * i;
    }
    return std::make_tuple(headPos, nullptr);
  }
}
void sep3dFile::readArrangeTraces(std::vector<std::vector<int>> &itrs,
                                  const int n1, void *temp, void *data)
{

  int idone = 0;
  int iread = 0;
  while (idone + iread < itrs.size())
  {
    bool found = false;
    iread = 1;
    while (!found && idone + iread < itrs.size())
    {
      if (itrs[idone + iread][1] != itrs[idone][1] + iread || iread > 9999)
      {
        found = true;
        sseek_block(_tag.c_str(), itrs[idone][1], n1, 0);
        if (iread * n1 != sreed(_tag.c_str(), temp, iread * n1))
          throw SEPException("trouble reading data");
        for (int i = 0; i < iread; i++)
        {
          memcpy((char *)data + itrs[idone + i][0] * n1, (char *)temp + i * n1,
                 n1);
        }
        idone += iread;
        iread = 0;
      }
      else
        iread += 1;
    }
  }
  sseek_block(_tag.c_str(), itrs[idone][1], n1, 0);

  int ierr = sreed(_tag.c_str(), temp, iread * n1);
  if (ierr != iread * n1)
    throw SEPException(std::string("tr2ouble reading data requested=") +
                       std::to_string(iread * n1) + std::string(" read=") +
                       std::to_string(ierr));
  for (int i = 0; i < iread; i++)
  {
    memcpy((char *)data + itrs[idone + i][0] * n1, (char *)temp + i * n1, n1);
  }
}
std::tuple<std::shared_ptr<byte2DReg>, std::shared_ptr<float2DReg>,
           std::shared_ptr<byte1DReg>>
sep3dFile::readFloatTraceWindow(const std::vector<int> &nwind,
                                const std::vector<int> &fwind,
                                const std::vector<int> &jwind)
{

  if (getDataType() != DATA_FLOAT)
    throw SEPException("Attempt to read float from a non-float file");
  auto head_drn = readHeaderWindow(nwind, fwind, jwind);
  auto drn = std::get<1>(head_drn);
  int ntr = drn->getHyper()->getN123();
  std::shared_ptr<float2DReg> data(
      new float2DReg(_hyperData->getAxis(1).n, ntr));

  std::vector<std::vector<int>> headPos(ntr, std::vector<int>(2));
  for (int i = 0; i < ntr; i++)
  {
    headPos[i][0] = i;
    headPos[i][1] = (*drn->_mat)[i];

    (*drn->_mat)[i] -= 1;
  }

  int n1 = _hyperData->getAxis(1).n;
  std::sort(headPos.begin(), headPos.end(), sortFunc);

  std::shared_ptr<float2DReg> temp(new float2DReg(n1, _ntrBuffer));

  readArrangeTraces(headPos, n1 * 4, (void *)temp->getVals(),
                    (void *)data->getVals());

  return std::make_tuple(std::get<0>(head_drn), data, std::get<2>(head_drn));
}

std::tuple<std::shared_ptr<byte2DReg>, std::shared_ptr<int2DReg>,
           std::shared_ptr<byte1DReg>>
sep3dFile::readIntTraceWindow(const std::vector<int> &nwind,
                              const std::vector<int> &fwind,
                              const std::vector<int> &jwind)
{
  if (getDataType() != DATA_INT)
    throw SEPException("Attempt to read int from a non-float file");
  auto head_drn = readHeaderWindow(nwind, fwind, jwind);
  std::shared_ptr<int1DReg> drn = std::get<1>(head_drn);

  int ntr = drn->getHyper()->getN123();
  std::shared_ptr<int2DReg> data(new int2DReg(_hyperData->getAxis(1).n, ntr));
  int n1 = _hyperData->getAxis(1).n;

  std::vector<std::vector<int>> headPos(ntr, std::vector<int>(2));
  for (int i = 0; i < ntr; i++)
  {
    headPos[i][0] = i;
    headPos[i][1] = (*drn->_mat)[i];
  }
  std::sort(headPos.begin(), headPos.end(), sortFunc);
  std::shared_ptr<int2DReg> temp(new int2DReg(n1, _ntrBuffer));
  readArrangeTraces(headPos, n1 * 4, (void *)temp->getVals(),
                    (void *)data->getVals());
  return std::make_tuple(std::get<0>(head_drn), data, std::get<2>(head_drn));
}

std::tuple<std::shared_ptr<byte2DReg>, std::shared_ptr<double2DReg>,
           std::shared_ptr<byte1DReg>>
sep3dFile::readDoubleTraceWindow(const std::vector<int> &nwind,
                                 const std::vector<int> &fwind,
                                 const std::vector<int> &jwind)
{
  if (getDataType() != DATA_DOUBLE)
    throw SEPException("Attempt to read int from a non-float file");
  auto head_drn = readHeaderWindow(nwind, fwind, jwind);
  std::shared_ptr<int1DReg> drn = std::get<1>(head_drn);

  int ntr = drn->getHyper()->getN123();
  std::shared_ptr<double2DReg> data(
      new double2DReg(_hyperData->getAxis(1).n, ntr));
  int n1 = _hyperData->getAxis(1).n;

  std::vector<std::vector<int>> headPos(ntr, std::vector<int>(2));
  for (int i = 0; i < ntr; i++)
  {
    headPos[i][0] = i;
    headPos[i][1] = (*drn->_mat)[i];
  }
  std::sort(headPos.begin(), headPos.end(), sortFunc);
  std::shared_ptr<double2DReg> temp(new double2DReg(n1, _ntrBuffer));
  readArrangeTraces(headPos, n1 * 8, (void *)temp->getVals(),
                    (void *)data->getVals());
  return std::make_tuple(std::get<0>(head_drn), data, std::get<2>(head_drn));
}
std::tuple<std::shared_ptr<byte2DReg>, std::shared_ptr<byte2DReg>,
           std::shared_ptr<byte1DReg>>
sep3dFile::readByteTraceWindow(const std::vector<int> &nwind,
                               const std::vector<int> &fwind,
                               const std::vector<int> &jwind)
{

  if (getDataType() != DATA_DOUBLE)
    throw SEPException("Attempt to read int from a non-float file");
  auto head_drn = readHeaderWindow(nwind, fwind, jwind);
  std::shared_ptr<int1DReg> drn = std::get<1>(head_drn);

  int ntr = drn->getHyper()->getN123();
  std::shared_ptr<byte2DReg> data(new byte2DReg(_hyperData->getAxis(1).n, ntr));

  std::vector<std::vector<int>> headPos(ntr, std::vector<int>(2));
  for (int i = 0; i < ntr; i++)
  {
    headPos[i][0] = i;
    headPos[i][1] = (*drn->_mat)[i];
  }
  int n1 = _hyperData->getAxis(1).n;

  std::sort(headPos.begin(), headPos.end(), sortFunc);
  std::shared_ptr<byte2DReg> temp(new byte2DReg(n1, _ntrBuffer));
  readArrangeTraces(headPos, n1 * 1, (void *)temp->getVals(),
                    (void *)data->getVals());
  return std::make_tuple(std::get<0>(head_drn), data, std::get<2>(head_drn));
}

std::tuple<std::shared_ptr<byte2DReg>, std::shared_ptr<complex2DReg>,
           std::shared_ptr<byte1DReg>>
sep3dFile::readComplexTraceWindow(const std::vector<int> &nwind,
                                  const std::vector<int> &fwind,
                                  const std::vector<int> &jwind)
{
  if (getDataType() != DATA_COMPLEX)
    throw SEPException("Attempt to read int from a non-float file");
  auto head_drn = readHeaderWindow(nwind, fwind, jwind);
  std::shared_ptr<int1DReg> drn = std::get<1>(head_drn);

  int ntr = drn->getHyper()->getN123();
  std::shared_ptr<complex2DReg> data(
      new complex2DReg(_hyperData->getAxis(1).n, ntr));

  std::vector<std::vector<int>> headPos(ntr, std::vector<int>(2));
  for (int i = 0; i < ntr; i++)
  {
    headPos[i][0] = i;
    headPos[i][1] = (*drn->_mat)[i];
  }
  int n1 = _hyperData->getAxis(1).n;

  std::sort(headPos.begin(), headPos.end(), sortFunc);
  std::shared_ptr<complex2DReg> temp(new complex2DReg(n1, _ntrBuffer));
  readArrangeTraces(headPos, n1 * 8, (void *)temp->getVals(),
                    (void *)data->getVals());
  return std::make_tuple(std::get<0>(head_drn), data, std::get<2>(head_drn));
}
std::tuple<std::shared_ptr<byte2DReg>, std::shared_ptr<complexDouble2DReg>,
           std::shared_ptr<byte1DReg>>
sep3dFile::readComplexDoubleTraceWindow(const std::vector<int> &nwind,
                                        const std::vector<int> &fwind,
                                        const std::vector<int> &jwind)
{
  if (getDataType() != DATA_COMPLEXDOUBLE)
    throw SEPException("Attempt to read int from a non-float file");
  auto head_drn = readHeaderWindow(nwind, fwind, jwind);
  std::shared_ptr<int1DReg> drn = std::get<1>(head_drn);

  int ntr = drn->getHyper()->getN123();
  std::shared_ptr<complexDouble2DReg> data(
      new complexDouble2DReg(_hyperData->getAxis(1).n, ntr));
  int n1 = _hyperData->getAxis(1).n;

  std::vector<std::vector<int>> headPos(ntr, std::vector<int>(2));
  for (int i = 0; i < ntr; i++)
  {
    headPos[i][0] = i;
    headPos[i][1] = (*drn->_mat)[i];
  }
  std::sort(headPos.begin(), headPos.end(), sortFunc);
  std::shared_ptr<complexDouble2DReg> temp(
      new complexDouble2DReg(n1, _ntrBuffer));
  readArrangeTraces(headPos, n1 * 16, (void *)temp->getVals(),
                    (void *)data->getVals());
  return std::make_tuple(std::get<0>(head_drn), data, std::get<2>(head_drn));
}
void sep3dFile::addtDRN(std::shared_ptr<byte2DReg> inV, const int ifirst,
                        const int ntransfer, std::shared_ptr<int1DReg> drns,
                        std::shared_ptr<byte2DReg> &outV)
{
  int n1in = inV->getHyper()->getAxis(1).n * 4;
  int n1out = outV->getHyper()->getAxis(1).n * 4;

  unsigned char *in = inV->getVals();
  unsigned char *out = outV->getVals();

  int *rns = drns->getVals();
  for (int i = 0; i < ntransfer; i++)
  {
    memcpy(out + n1out * i, in + n1in * i, n1in);
    memcpy(out + n1out * i + n1in, rns + i, 4);
  }
}
void sep3dFile::writeGrid(const std::vector<int> &nwind,
                          const std::vector<int> &fwind,
                          const std::vector<int> &jwind,
                          const std::shared_ptr<byte2DReg> &headers,
                          const std::shared_ptr<byte1DReg> &byte

)
{
  long long first = 0, last = 0;
  long long sz = 1;
  checkWindow(nwind, fwind, jwind, _hyper);

  if (!_haveGrid)
    throw SEPException("Can not write dataset that doesn't have a grid");
  std::vector<int> ns = _hyper->getNs();
  for (auto i = 0; i < nwind.size(); i++)
  {
    first += fwind[i] * sz;
    last += (fwind[i] + jwind[i] * nwind[i]) * sz;
    sz = sz * (long long)nwind[i];
  }
  if (_writeLastG + 1 != first)
    throw SEPException("Non-consecutive read of grid");
  int n2h = 0;
  for (auto i = 0; i < byte->getHyper()->getN123(); i++)
  {
    if ((*byte->_mat)[i] > 0)
      n2h += 1;
  }
  if (n2h != headers->getHyper()->getAxis(2).n)
    throw SEPException(
        "Number of headers does not match number of non-zero grid elements");
  int ih = 0;
  std::shared_ptr<int1DReg> grid(new int1DReg(byte->getHyper()->getN123()));
  for (auto i = 0; i < byte->getHyper()->getN123(); i++)
  {
    if ((*byte->_mat)[i] != 0)
    {
      ih++;
      (*grid->_mat)[i] = _writeLastH + ih;
    }
    else
      (*grid->_mat)[i] = -1;
  }
  std::vector<int> ng = _hyper->getNs();
  int ndim = ng.size();

  if (0 != sep_put_grid_window(_tag.c_str(), &ndim, &ng[1], &nwind[1],
                               &fwind[1], &jwind[1], grid->getVals()))
  {
    throw SEPException("Trouble writing grid");
  }
  _writeLastG = last;
}
void sep3dFile::writeHeaderWindow(const std::vector<int> &nwind,
                                  const std::vector<int> &fwind,
                                  const std::vector<int> &jwind,
                                  const std::shared_ptr<int1DReg> &drn,
                                  const std::shared_ptr<byte2DReg> &headers,
                                  const std::shared_ptr<byte1DReg> &grid)
{

  if (_haveGrid)
  {
    writeGrid(nwind, fwind, jwind, headers, grid);
  }
  std::vector<int> ns = headers->getHyper()->getNs();
  if (_inOrder)
  {
    int ifirst = _writeLastH + 1;
    int nblock = ns[1];

    if (0 !=
        sep_put_val_headers(_tag.c_str(), &ifirst, &nblock, headers->getVals()))
      throw SEPException("Trouble writing headers");
  }

  else
  {
    std::shared_ptr<byte2DReg> temp(
        new byte2DReg(ns[0] + 4, std::min(_ntrBuffer, ns[1])));
    char *outb = (char *)temp->getVals();
    char *inb = (char *)headers->getVals();
    std::vector<int> drnV(ns[1]);
    if (ns[1] != drn->getHyper()->getN123())
      throw SEPException(
          std::string("Number of drns does not match number of headers tag=") +
          _tag);
    for (auto i = 0; i < ns[1]; i++)
    {
      drnV[i] = (*drn->_mat)[i] + 1;
    }
    int n1In = headers->getHyper()->getAxis(1).n;
    int n1Out = n1In + 4;
    int idone = 0;

    while (idone < ns[1])
    {
      int nblock = std::min(ns[1] - idone, _ntrBuffer);

      int ifirst = _writeLastH + idone + 1;
      for (int i2 = 0; i2 < nblock; i2++)
      {
        memcpy(outb + n1Out * i2, inb + n1In * i2, n1In);

        memcpy(outb + n1Out * i2 + n1In, &drnV[i2], 4);
      }

      if (0 !=
          sep_put_val_headers(_tag.c_str(), &ifirst, &nblock, temp->getVals()))
        throw SEPException("Trouble writing "
                           "headers");
      idone += nblock;
    }
    _writeLastH += ns[1];
  }
}
void sep3dFile::writeComplexDoubleTraceWindow(
    const std::vector<int> &nwind, const std::vector<int> &fwind,
    const std::vector<int> &jwind, std::shared_ptr<byte2DReg> &headers,
    std::shared_ptr<complexDouble2DReg> &data,
    const std::shared_ptr<byte1DReg> &grid)
{

  if (getDataType() != DATA_COMPLEXDOUBLE)
    throw SEPException("Expecting datatype complex double");
  if (_haveGrid)
    writeGrid(nwind, fwind, jwind, headers, grid);
  std::vector<int> ns = headers->getHyper()->getNs();

  int ifirst = _writeLastH + 1;
  int nblock = ns[1];

  if (0 !=
      sep_put_val_headers(_tag.c_str(), &ifirst, &nblock, headers->getVals()))
    throw SEPException("Trouble writing headers");
  if (16 * ns[1] * data->getHyper()->getAxis(1).n !=
      srite(_tag.c_str(), data->getVals(),
            16 * ns[1] * data->getHyper()->getAxis(1).n))
    throw SEPException("Trouble writing data");
}

void sep3dFile::writeComplexTraceWindow(
    const std::vector<int> &nwind, const std::vector<int> &fwind,
    const std::vector<int> &jwind, const std::shared_ptr<byte2DReg> &headers,
    const std::shared_ptr<complex2DReg> &data,
    const std::shared_ptr<byte1DReg> &grid)
{
  if (getDataType() != DATA_COMPLEXDOUBLE)
    throw SEPException("Expecting datatype complex ");
  if (_haveGrid)

    writeGrid(nwind, fwind, jwind, headers, grid);
  std::vector<int> ns = headers->getHyper()->getNs();

  int ifirst = _writeLastH + 1;
  int nblock = ns[1];

  if (0 !=
      sep_put_val_headers(_tag.c_str(), &ifirst, &nblock, headers->getVals()))
    throw SEPException("Trouble writing headers");
  if (8 * ns[1] * data->getHyper()->getAxis(1).n !=
      srite(_tag.c_str(), data->getVals(),
            8 * ns[1] * data->getHyper()->getAxis(1).n))
    throw SEPException("Trouble writing data");
}
void sep3dFile::writeDoubleTraceWindow(
    const std::vector<int> &nwind, const std::vector<int> &fwind,
    const std::vector<int> &jwind, const std::shared_ptr<byte2DReg> &headers,
    const std::shared_ptr<double2DReg> &data,
    const std::shared_ptr<byte1DReg> &grid)
{
  if (getDataType() != DATA_DOUBLE)
    throw SEPException("Expecting datatype double");
  if (_haveGrid)

    writeGrid(nwind, fwind, jwind, headers, grid);
  std::vector<int> ns = headers->getHyper()->getNs();

  int ifirst = _writeLastH + 1;
  int nblock = ns[1];

  if (0 !=
      sep_put_val_headers(_tag.c_str(), &ifirst, &nblock, headers->getVals()))
    throw SEPException("Trouble writing headers");
  if (8 * ns[1] * data->getHyper()->getAxis(1).n !=
      srite(_tag.c_str(), data->getVals(),
            8 * ns[1] * data->getHyper()->getAxis(1).n))
    throw SEPException("Trouble writing data");
}
void sep3dFile::writeIntTraceWindow(const std::vector<int> &nwind,
                                    const std::vector<int> &fwind,
                                    const std::vector<int> &jwind,
                                    const std::shared_ptr<byte2DReg> &headers,
                                    const std::shared_ptr<int2DReg> &data,
                                    const std::shared_ptr<byte1DReg> &grid)
{
  if (getDataType() != DATA_INT)
    throw SEPException("Expecting datatype int");
  if (_haveGrid)
    writeGrid(nwind, fwind, jwind, headers, grid);
  std::vector<int> ns = headers->getHyper()->getNs();

  int ifirst = _writeLastH + 1;
  int nblock = ns[1];

  if (0 !=
      sep_put_val_headers(_tag.c_str(), &ifirst, &nblock, headers->getVals()))
    throw SEPException("Trouble writing headers");

  if (4 * ns[1] * data->getHyper()->getAxis(1).n !=
      srite(_tag.c_str(), data->getVals(),
            4 * ns[1] * data->getHyper()->getAxis(1).n))
    throw SEPException("Trouble writing data");
}
void sep3dFile::writeFloatTraceWindow(const std::vector<int> &nwind,
                                      const std::vector<int> &fwind,
                                      const std::vector<int> &jwind,
                                      const std::shared_ptr<byte2DReg> &headers,
                                      const std::shared_ptr<float2DReg> &data,
                                      const std::shared_ptr<byte1DReg> &grid)
{
  if (getDataType() != DATA_FLOAT)
    throw SEPException("Expecting datatype complex double");

  if (_haveGrid)
  {

    writeGrid(nwind, fwind, jwind, headers, grid);
  }

  std::vector<int> ns = headers->getHyper()->getNs();

  int ifirst = _writeLastH + 1;
  int nblock = ns[1];

  if (0 !=
      sep_put_val_headers(_tag.c_str(), &ifirst, &nblock, headers->getVals()))
    throw SEPException("Trouble writing headers");
  if (4 * ns[1] * data->getHyper()->getAxis(1).n !=
      srite(_tag.c_str(), data->getVals(),
            4 * ns[1] * data->getHyper()->getAxis(1).n))
    throw SEPException("Trouble writing data");
}

void sep3dFile::writeByteTraceWindow(const std::vector<int> &nwind,
                                     const std::vector<int> &fwind,
                                     const std::vector<int> &jwind,
                                     const std::shared_ptr<byte2DReg> &headers,
                                     const std::shared_ptr<byte2DReg> &data,
                                     const std::shared_ptr<byte1DReg> &grid)
{
  if (getDataType() != DATA_BYTE)
    throw SEPException("Expecting datatype byte");
  if (_haveGrid)
    writeGrid(nwind, fwind, jwind, headers, grid);
  std::vector<int> ns = headers->getHyper()->getNs();

  int ifirst = _writeLastH + 1;
  int nblock = ns[1];

  if (0 !=
      sep_put_val_headers(_tag.c_str(), &ifirst, &nblock, headers->getVals()))
    throw SEPException("Trouble writing headers");
  if (1 * ns[1] * data->getHyper()->getAxis(1).n !=
      srite(_tag.c_str(), data->getVals(),
            1 * ns[1] * data->getHyper()->getAxis(1).n))
    throw SEPException("Trouble writing data");
}
/*!

Set that the data is out of order


*/
void sep3dFile::setOutOfOrder() { _inOrder = false; }
