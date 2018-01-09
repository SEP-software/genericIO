%module ioModes_int
%{ 
    #define SWIG_FILE_WITH_INIT
    #include "ioModes.h"
using namespace SEP;
%}
%include "std_vector.i"
%include "std_string.i"

namespace std{
	   %template(StringVector) vector<string>;

}

%include "ioModes.h"
