module sep_param_mod
use param_func_mod
use sep
implicit none
! procedure(getIntD), deferred,pass :: get_intD
type,extends (param_func)::sepParam
  contains
      procedure::get_intN=>sGetIntN
      procedure ::get_IntD=>sGetIntD
      procedure ::get_FloatN=>sGetFloatN
      procedure:: get_FloatD=>sGetFloatD
      procedure:: get_StringN=>sGetStringN
      procedure:: get_StringD=>sGetStringD
      procedure ::get_BoolN=>sGetBoolN
      procedure:: get_BoolD=>sGetBoolD
      procedure:: get_IntsN=>sGetIntsN
      procedure:: get_IntsD=>sGetIntsD
      procedure:: get_FloatsN=>sGetFloatsN
      procedure:: get_FloatsD=>sGetFloatsD
      procedure::  err=>sError
end type

contains

function sGetIntN(struct,arg)
   class(sepParam) :: struct
   character(len=*) :: arg
   integer:: sGetIntN
   integer :: ierr 
   ierr=getch(arg,"f",sGetIntN)
   if(ierr==0) &
     call seperr(arg//" param unspecified in parameters")
 end function
 
 function sGetIntD(struct,arg,def)
   class(sepParam) :: struct
   character(len=*) :: arg
   integer :: sGetIntD,def
   integer :: ierr
   sGetIntD=def
   ierr=getch(arg,"f",sGetIntD)
 end function



function sGetFloatN(struct,arg)
   class(sepParam) :: struct
   character(len=*) :: arg
   real:: sGetFloatN
   integer :: ierr 
   ierr=getch(arg,"f",sGetFloatN)
   if(ierr==0) &
     call seperr(arg//" param unspecified in parameters")
 end function
 
 function sGetFloatD(struct,arg,def)
   class(sepParam) :: struct
   character(len=*) :: arg
   real :: sGetFloatD,def
   integer :: ierr
   sGetFloatD=def
   ierr=getch(arg,"f",sGetFloatD)
 end function



function sGetStringN(struct,arg)
   class(sepParam) :: struct
   character(len=*) :: arg
   character(len=1024) :: sGetStringN
   integer :: ierr 
   ierr=getch(arg,"s",sGetStringN)
   if(ierr==0) &
     call seperr(arg//" param unspecified in parameters")
 end function
 
 function sGetStringD(struct,arg,def)
   class(sepParam) :: struct
   character(len=*) :: arg,def
   character(len=1024) :: sGetStringD
   integer :: ierr
   sGetStringD=def
   ierr=getch(arg,"s",sGetStringD)
 end function


function sGetBoolN(struct,arg)
   class(sepParam) :: struct
   character(len=*) :: arg
   logical :: sGetBoolN
   integer :: ierr 
   ierr=getch(arg,"l",sGetBoolN)
   if(ierr==0) &
     call seperr(arg//" param unspecified in parameters")
 end function
 function sGetBoolD(struct,arg,def)
   class(sepParam) :: struct
   character(len=*) :: arg
   logical :: sGetBoolD,def
   integer :: ierr
   sGetBoolD=def
   ierr=getch(arg,"l",sGetBoolD)
 end function


 function sGetIntsN(struct,arg)
   class(sepParam) :: struct
   character(len=*) :: arg
   integer, dimension(:), pointer :: sGetIntsN
   integer :: ierr 
   integer :: tmp(10000)
   ierr=getch(arg,"d",tmp)
   if(ierr==0) &
     call seperr(arg//" param unspecified in parameters")
   allocate(sGetIntsN(ierr))
   sGetIntsN=tmp(1:ierr)
 end function
 
 function sGetIntsD(struct,arg,def)
   class(sepParam) :: struct
   character(len=*) :: arg
   integer, dimension(:), pointer :: sGetIntsD
   integer ::  def(:)
   integer :: ierr
   allocate(sGetIntsD(size(def)))
   sGetIntsD=def
   ierr=getch(arg,"f",sGetIntsD)
 end function

 function sGetFloatsN(struct,arg)
   class(sepParam) :: struct
   character(len=*) :: arg
   real, dimension(:), pointer :: sGetFloatsN
   integer :: ierr 
   real :: tmp(10000)
   ierr=getch(arg,"f",tmp)
   if(ierr==0) &
     call seperr(arg//" param unspecified in parameters")
   allocate(sGetFloatsN(ierr))
   sGetFloatsN=tmp(1:ierr)
 end function
 
 function sGetFloatsD(struct,arg,def)
   class(sepParam) :: struct
   character(len=*) :: arg
   real, dimension(:), pointer :: sGetFloatsD
   real ::  def(:)
   integer :: ierr
   allocate(sGetFloatsD(size(def)))
   sGetFloatsD=def
   ierr=getch(arg,"f",sGetFloatsD)
 end function
 
 subroutine sError(struct,arg)
   class(sepParam) :: struct
   character(len=*) :: arg
   call seperr(arg)
 end subroutine
   

 type(sepParam) function createSepParams() result(x)
   call initpar()
   x=sepParam();
 end function
end module  

