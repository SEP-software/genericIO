#ifndef GENERIC_C_IO_H
#define GENERIC_C_IO_H 1
#include"genericIO.h"


extern "C" void initializeIO(int argc, const int ns1, const int ns2, char *aa);
extern "C" void openRegFile(const char *name, const char *usg);
extern "C" void openIrregFile(const char *name, const char *usg);
extern "C" void closeIO();
extern "C" void getParamIntconst (char *name, int *val,const  bool def);
extern "C" void getParamFloat(const char *name, float *val, const bool def);
extern "C" void getParamString(const char *name, char *val,const  bool def);
extern "C" void getParamBool(const char *name, bool *val,const  bool def);
extern "C" void getParamInts(const char *name, const int num, int *val, const bool def);
extern "C" void getParamFloats(const char *name,const int num, float *val,const  bool defs);

extern "C" void getFileInt(const char *tag, const char *name, int *val,const  bool def);
extern "C" void getFileFloat(const char *tag,const  char *name, float *val,const  bool def);
extern "C" void getFileString(const char *tag, const char *name, char *val, const bool def);
extern "C" void getFileBool(const char *tag, const char *name, bool *val,const  bool def);
extern "C" void getFileInts(const char *tag, const char *name,const int num, int *val,const  bool def);
extern "C" void getFileFloats(const char *file,const char *name, const int num,float *val,const  bool defs);

extern "C" void putFileInt(const char *tag,const  char *name,const  int val);
extern "C" void putFileFloat(const char *tag,const  char *name,const  float val);
extern "C" void putFileString(const char *tag, const char *name,const  char *val);
extern "C" void putFileBool(const char *tag, const char *name,const  bool val);
extern "C" void putFileInts(const char *tag, const char *name,const  int num,const int *val);
extern "C" void puFileFloats(const char *file,const char *name, const int num,const float *val);

extern "C" void readFloatStream(const char *tag, const long long npts, float *array);
extern "C" void writeFloatStream(const char *tag, const long long npts,const  float *array);
extern "C" void readFloatWindow(const char *tag, const int ndim,const  int *nw,const  int *fw,const  int *jw, float *ar);
extern "C" void writeFloatWindow(const char *tag, const int ndim,const  int *nw, const int *fw,const  int *jw,const  float *ar);


extern "C" void readComplexStream(const char *tag, const long long npts, float _Complex *array);
extern "C" void writeComplexStream(const char *tag, const long long npts,const  float  _Complex *array);
extern "C" void readComplexWindow(const char *tag, const int ndim,const  int *nw,const  int *fw,const  int *jw, float  _Complex *ar);
extern "C" void writeComplexWindow(const char *tag, const int ndim,const  int *nw, const int *fw,const  int *jw,const  float  _Complex *ar);


extern "C" void readDescription(const char *tag);
extern "C" void writeDescription(const char *tag);
extern "C" void getDataType(const char *tag, char *typ);
extern "C" void setDataType(const char *tag,const  char *typ);

extern "C" void getHyper(const char *tag,const int ndimin, int *ndimout, int *n, float *o, float *d, const int ns1, const int ns2, char **label);
extern "C" void setHyper(const char *tag,const int ndim, const int *n, const float *o, const float *d,const int ns1,const  int ns2, const  char **label);
extern "C" void cError( const char *err);
extern "C" std::vector<std::string> fromChar1D(const int n1,const  int n2, const char *val);
extern "C" void toChar1D(const std::vector<std::string>  in, const int n1, const int n2, char *val);

#endif 