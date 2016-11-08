module generic_c_stubs
use, intrinsic :: iso_c_binding
implicit none


interface
subroutine initializeIO(argc,ns1,ns2,argv) bind(c,name="initializeIO")
import
integer(c_int),intent(in) :: argc
integer(c_int),intent(in) :: ns1,ns2
character(c_char),dimension(*),intent(in) :: argv

end subroutine


subroutine openRegFile(tag,usg) bind(c,name="openRegFile")
 import

 character(c_char), dimension(*),intent(in) :: tag,usg
end subroutine
   
subroutine openIrregFile(tag,usg) bind(c,name="openIrregFile")
import

  character(c_char), dimension(*),intent(in) :: tag,usg
end subroutine
 
subroutine closeIO() bind(c,name="closeIO")
import

end subroutine

subroutine getParamIntC(par,val,def) bind(c,name="getParamInt")
import

  character(c_char), dimension(*),intent(in) :: par
  integer(c_int),intent(inout) :: val
  logical(c_bool) ,value :: def
end subroutine

subroutine getParamFloatC(par,val,def) bind(c,name="getParFloat")
import

  character(c_char), dimension(*),intent(in) :: par
  real(c_float) ,intent(inout):: val
  logical(c_bool),value,intent(in)  :: def
end subroutine

subroutine getParamBoolC(par,val,def) bind(c,name="getParamBool")
import

  character(c_char), dimension(*),intent(in) :: par
  logical(c_bool),intent(in) :: val
  logical(c_bool),value  :: def
end subroutine

subroutine getParamStringC(par,val,def) bind(c,name="getParamString")
import

  character(c_char), intent(in),dimension(*) :: par
  character(c_char) ,dimension(*),intent(inout):: val
  logical(c_bool) ,value,intent(in) :: def
end subroutine

subroutine getParamIntsC(par,val,def) bind(c,name="getParamInts")
import

  character(c_char), dimension(*),intent(in) :: par
  integer(c_int),intent(inout),dimension(*) :: val
  logical(c_bool) ,value,intent(in) :: def
end subroutine

subroutine getParamFloatsC(par,val,def) bind(c,name="getParFloats")
import

  character(c_char), dimension(*),intent(in) :: par
  real(c_float) ,intent(inout),dimension(*):: val
  logical(c_bool),value,intent(in)  :: def
end subroutine

subroutine tFileInt(myf,par,val,def) bind(c,name="getFileInt")
import
  character(c_char), dimension(*),intent(in) :: myf,par
  integer(c_int),intent(inout) :: val
  logical(c_bool) ,value,intent(in) :: def
end subroutine

subroutine getFileFloat(myf,par,val,def) bind(c,name="getFileFloat")

import
  character(c_char), dimension(*),intent(in) :: myf,par
  real(c_float) ,intent(inout):: val
  logical(c_bool),value,intent(in)  :: def
end subroutine

subroutine getFileBool(myf,par,val,def) bind(c,name="getFileBool")
import
  character(c_char), dimension(*),intent(in) :: myf,par
  logical(c_bool),intent(in) :: val
  logical(c_bool),value  :: def
end subroutine

subroutine getFileString(myf,par,val,def) bind(c,name="getFileString")
import
  character(c_char), intent(in),dimension(*) :: myf,par
  character(c_char) ,dimension(*),intent(inout):: val
  logical(c_bool) ,value,intent(in) :: def
end subroutine

subroutine getFileInts(myf,par,nsz,val,def) bind(c,name="getFileInts")
import
  character(c_char), dimension(*),intent(in) :: myf,par
  integer(c_int),intent(inout),dimension(*) :: val
  integer,intent(in) :: nsz
  logical(c_bool) ,value,intent(in) :: def
end subroutine

subroutine getFileFloats(myf,par,nsz,val,def) bind(c,name="getFileFloats")
import
  character(c_char), dimension(*),intent(in) :: myf,par
  integer,intent(in) :: nsz
  real(c_float) ,intent(inout),dimension(*):: val
  logical(c_bool),value,intent(in)  :: def
end subroutine

subroutine putFileInt(myf,par,val) bind(c,name="putFileInt")
import
  character(c_char), dimension(*),intent(in) :: myf,par
  integer(c_int),intent(in) :: val
end subroutine

subroutine putFileFloat(myf,par,val) bind(c,name="putFileFloat")
import
  character(c_char), dimension(*),intent(in) :: myf,par
  real(c_float) ,intent(in):: val
end subroutine

subroutine putFileBool(myf,par,val) bind(c,name="putFileBool")
import
  character(c_char), dimension(*),intent(in) :: myf,par
  logical(c_bool),intent(in) :: val
end subroutine

subroutine putFileString(myf,par,val) bind(c,name="putFileString")
import
  character(c_char), intent(in),dimension(*) :: myf,par
  character(c_char) ,dimension(*),intent(in):: val
end subroutine

subroutine putFileInts(myf,par,num,val) bind(c,name="putFileInts")
import
  character(c_char), dimension(*),intent(in) :: myf,par
  integer(c_int),intent(in),dimension(*) :: val
  integer,intent(in) :: num
end subroutine

subroutine putFileFloats(myf,par,num,val) bind(c,name="putFileFloats")
import
  character(c_char), dimension(*),intent(in) :: myf,par
  real(c_float) ,intent(in),dimension(*):: val
  integer,intent(in) :: num
end subroutine

subroutine readFloatStream(myf,nsz,val) bind(c,name="readFloatStream")
import
  character(c_char), dimension(*),intent(in) :: myf
  real(c_float) ,intent(out),dimension(*):: val
 integer(c_long_long) , intent(in) :: nsz
end subroutine

subroutine writeFloatStream(myf,nsz,val) bind(c,name="writeFloatStream")
import
  character(c_char), dimension(*),intent(in) :: myf
  real(c_float) ,intent(in),dimension(*):: val
 integer(c_long_long) , intent(in) :: nsz
end subroutine

subroutine writeFloatWindow(myf,nw,fw,jw,val) bind(c,name="writeFloatWindow")
import
  character(c_char), dimension(*),intent(in) :: myf
  real(c_float) ,intent(in),dimension(*):: val
  integer(c_int),intent(in),dimension(*) :: nw,fw,jw
end subroutine

subroutine readFloatWindow(myf,nw,fw,jw,val) bind(c,name="readFloatWindow")
import
  character(c_char), dimension(*),intent(in) :: myf
  real(c_float) ,intent(out),dimension(*):: val
  integer(c_int),intent(in),dimension(*) :: nw,fw,jw
end subroutine



subroutine readComplexStream(myf,nsz,val) bind(c,name="readComplexStream")
import
  character(c_char), dimension(*),intent(in) :: myf
  complex(C_FLOAT_COMPLEX) ,intent(out),dimension(*):: val
 integer(c_long_long) , intent(in) :: nsz
end subroutine

subroutine writeComplexStream(myf,nsz,val) bind(c,name="writeComplexStream")
import
  character(c_char), dimension(*),intent(in) :: myf
  complex(C_FLOAT_COMPLEX) ,intent(in),dimension(*):: val
 integer(c_long_long) , intent(in) :: nsz
end subroutine

subroutine writeComplexWindow(myf,nw,fw,jw,val) bind(c,name="writeComplexWindow")
import
  character(c_char), dimension(*),intent(in) :: myf
  complex(C_FLOAT_COMPLEX) ,intent(in),dimension(*):: val
  integer(c_int),intent(in),dimension(*) :: nw,fw,jw
end subroutine

subroutine readComplexWindow(myf,nw,fw,jw,val) bind(c,name="readComplexWindow")
import
  character(c_char), dimension(*),intent(in) :: myf
  complex(C_FLOAT_COMPLEX) ,intent(out),dimension(*):: val
  integer(c_int),intent(in),dimension(*) :: nw,fw,jw
end subroutine





subroutine readDescriptionC(name) bind(c,name="readDescription")
import
 character(c_char), dimension(*),intent(in) :: name
end subroutine


subroutine writeDescriptionC(name) bind(c,name="writeDescription")
import
 character(c_char), dimension(*),intent(in) :: name
end subroutine

subroutine getDataType(name,typ) bind(c,name="getDataType")
import
 character(c_char), dimension(*),intent(in) :: name
  character(c_char), dimension(*),intent(out) :: typ

end subroutine

subroutine setDataType(name,typ) bind(c,name="setDataType")
import
 character(c_char), dimension(*),intent(in) :: name,typ
end subroutine
subroutine cerror(er) bind(c,name="cerror")
import
 character(c_char), dimension(*),intent(in) :: er
end subroutine


subroutine getHyper(tag,ndimin,ndimout,n,o,d,ns1,ns2,label) bind(c,name="getHyper")
import
integer(c_int),intent(in),value :: ns1,ns2
character(c_char),intent(in) :: tag
character(c_char),dimension(*),intent(out) :: label
real(c_float),dimension(*),intent(out) :: o,d
integer(c_int),dimension(*), intent(out) :: n
integer(c_int),intent(out)  ::ndimout
integer(c_int),value,intent(in) :: ndimin
end subroutine



subroutine setHyper(tag,ndimout,n,o,d,ns1,ns2,label) bind(c,name="setHyper")
import
character(c_char),dimension(*),intent(in) :: label,tag
real(c_float),dimension(*),intent(in) :: o,d
integer(c_int),dimension(*), intent(in) :: n
integer(c_int), intent(in),value :: ns1,ns2
integer(c_int),value,intent(in)  ::ndimout
end subroutine
end interface





end module
