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
      procedure ::get_BoolN=>sGetBoolD
      procedure:: get_BoolD=>sGetBoolD
      procedure:: get_IntsN=>sGetIntsN
      procedure:: get_IntsD=>sGetIntsD
      procedure:: get_FloatsN=>sGetFloatsN
      procedure:: get_FloatsD=>sGetFloatsD
      procedure::  err=>sError
end type

contains

function sGetIntN(struct,str)
   class(param_func) :: struct
   character(len=*) :: str
   integer:: sGetIntN
   integer :: ierr 
   ierr=getch(str,"f",sGetIntN)
   if(ierr==0) &
     call seperr(str//" param unspecified in parameters")
 end function
 
 function sGetIntD(struct,str,def)
   class(param_func) :: struct
   character(len=*) :: str
   integer :: sGetIntD,def
   integer :: ierr
   sGetFloatD=def
   ierr=getch(str,"f",sGetIntD)
 end function



function sGetFloatN(struct,str)
   class(param_func) :: struct
   character(len=*) :: str
   real:: sGetFloatN
   integer :: ierr 
   ierr=getch(str,"f",sGetFloatN)
   if(ierr==0) &
     call seperr(str//" param unspecified in parameters")
 end function
 
 function sGetFloatD(struct,str,def)
   class(param_func) :: struct
   character(len=*) :: str
   real :: sGetFloatD,def
   integer :: ierr
   sGetFloatD=def
   ierr=getch(str,"f",sGetFloatD)
 end function



function sGetStringN(struct,str)
   class(param_func) :: struct
   character(len=*) :: str
   character(len=1024) :: sGetStringN
   integer :: ierr 
   ierr=getch(str,"s",sGetStringN)
   if(ierr==0) &
     call seperr(str//" param unspecified in parameters")
 end function
 function sGetStringD(struct,str,def)
   class(param_func) :: struct
   character(len=*) :: str,def
   character(len=1024) :: sGetStringD
   integer :: ierr
   sGetStringD=def
   ierr=getch(str,"s",sGetStringD)
 end function


function sGetBoolN(struct,str)
   class(param_func) :: struct
   character(len=*) :: str
   logical :: sGetBoolN
   integer :: ierr 
   ierr=getch(str,"l",sGetBoolN)
   if(ierr==0) &
     call seperr(str//" param unspecified in parameters")
 end function
 function sGetBoolD(struct,str,def)
   class(param_func) :: struct
   character(len=*) :: str
   logical :: sGetBoolD,def
   integer :: ierr
   sGetBoolD=def
   ierr=getch(str,"l",sGetBoolD)
 end function


 function sGetIntsN(struct,str)
   class(param_func) :: struct
   character(len=*) :: str
   integer, dimension(:), pointer :: sGetIntsN
   integer :: ierr 
   integer :: tmp(10000)
   ierr=getch(str,"d",tmp)
   if(ierr==0) &
     call seperr(str//" param unspecified in parameters")
   allocate(sGetIntsN(ierr))
   sGetIntsN=tmp(1:ierr)
 end function
 function sGetIntsD(struct,str,def)
   class(param_func) :: struct
   character(len=*) :: str
   real, dimension(:), allocatable :: sGetIntsD
   real ::  def(:)
   integer :: ierr
   allocate(sGetIntsD(size(def)))
   sGetIntsD=def
   ierr=getch(str,"f",sGetIntsD)
 end function

 function sGetFloatsN(struct,str)
   class(param_func) :: struct
   character(len=*) :: str
   real, dimension(:), allocatable :: sGetFloatsN
   integer :: ierr 
   real :: tmp(10000)
   ierr=getch(str,"f",tmp)
   if(ierr==0) &
     call seperr(str//" param unspecified in parameters")
   allocate(sGetFloatsN(ierr))
   sGetFloatsN=tmp(1:ierr)
 end function
 function sGetFloatsD(struct,str,def)
   class(param_func) :: struct
   character(len=*) :: str
   real, dimension(:), allocatable :: sGetFloatsD
   real ::  def(:)
   integer :: ierr
   allocate(sGetFloatsD(size(def)))
   sGetFloatsD=def
   ierr=getch(str,"f",sGetFloatsD)
 end function
 
 subroutine sError(struct,str)
   class(param_func) :: struct
   character(len=*) :: str
   call seperr(str)
 end subroutine
   

 subroutine createSepParams()
   call initpar()
 end subroutine
end module  

