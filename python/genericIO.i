%module genericIO_int
%{ 
    #define SWIG_FILE_WITH_INIT
    #include "genericIO.h"
using namespace SEP;
%}
%include "genericIO.h"
