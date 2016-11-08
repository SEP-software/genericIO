module c_param_mod
use param_func_mod
use generic_c_stubs
implicit none
! procedure(getIntD), deferred,pass :: get_intD
type,extends (paramObj)::cParam
  contains
        procedure:: init=>initC

      procedure::get_int=>sGetInt
      procedure ::get_Float=>sGetFloat
      procedure:: get_String=>sGetString
      procedure ::get_Bool=>sGetBool
      procedure:: get_Ints=>sGetInts
      procedure:: get_Floats=>sGetFloats
      procedure::  err=>sError
end type

contains


subroutine initC(struct)
  class(CParam) :: struct
end subroutine
subroutine sGetInt(struct,arg,val,def)
   class(CParam) :: struct
   character(len=*) ,intent(in):: arg
   integer,intent(inout):: val
   integer,optional :: def
   logical :: x
   
   x=present(def)
   if(present(def)) val=def;
   call getParamIntC(trim(arg)//C_NULL_CHAR,val,x);
  
 end subroutine
 
 subroutine sGetFloat(struct,arg,val,def)
   class(cParam) :: struct
   character(len=*),intent(in) :: arg
   real,intent(inout) :: val
   real, optional :: def
   if(present(def)) val=def;
   call getParamFloatC(trim(arg)//C_NULL_CHAR,val,present(def));
 end subroutine



subroutine sGetString(struct,arg,val,def)
   class(cParam) :: struct
   character(len=*),intent(in) :: arg
   character(len=*), intent(inout) :: val
   character(len=*), optional :: def

   if(present(def)) val=def;
   call getParamStringC(trim(arg)//C_NULL_CHAR,val,present(def));
 end subroutine
 
 subroutine sGetBool(struct,arg,val,def)
   class(cParam) :: struct
   character(len=*),intent(in) :: arg
   logical ,intent(inout):: val
   logical, optional :: def
   if(present(def)) val=def;
   call getParamBoolC(trim(arg)//C_NULL_CHAR,val,present(def));
 end subroutine


 subroutine sGetInts(struct,arg,val,def)
   class(cParam) :: struct
   character(len=*) ,intent(in):: arg
   integer, dimension(:),intent(inout):: val
   integer, optional :: def(:)
   if(present(def)) val=def;
   call getParamIntsC(trim(arg)//C_NULL_CHAR,val,present(def));

 end subroutine
 
 
 
 subroutine sGetFloats(struct,arg,val,def)
   class(cParam) :: struct
   character(len=*),intent(in) :: arg
   real ,intent(inout):: val(:)
   real,optional ::  def(:)
   if(present(def)) val=def;
   call getParamFloatsC(trim(arg)//C_NULL_CHAR,val,present(def));
 end subroutine
 
 subroutine sError(struct,arg)
   class(cParam) :: struct
   character(len=*),intent(in) :: arg
   call cerror(trim(arg)//C_NULL_CHAR)
 end subroutine
   
   
 subroutine initSEP(struct)
   class(cParam) :: struct
   call initPar()
 end subroutine
end module  

