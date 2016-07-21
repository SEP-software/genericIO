module param_func_mod
  implicit none
  type,abstract  :: param_func
    contains
      procedure(getIntN), deferred,pass :: get_intN
      procedure(getIntD), deferred,pass :: get_intD
      procedure(getFloatN),deferred,pass :: get_floatN
      procedure(getFloatD),deferred,pass :: get_floatD
      procedure(getStringN),deferred,pass :: get_StringN
      procedure(getStringD),deferred,pass :: get_StringD
      procedure(getBoolN),deferred,pass :: get_boolN
      procedure(getBoolD),deferred,pass :: get_boolD
      procedure(getIntsN),deferred,pass :: get_IntsN
      procedure(getIntsD),deferred,pass :: get_IntsD
      procedure(getFloatsN),deferred,pass :: get_floatsN
      procedure(getFloatsD),deferred,pass :: get_floatsD
      procedure(error), deferred,pass:: err
      generic:: getInt=>get_intN,get_intD
      generic:: getReal=>get_floatN,get_floatD
      generic:: getLogical=>get_boolN,get_boolD
      generic:: getString=>get_stringN,get_stringD
      generic:: getReals=>get_floatsN,get_floatsD
      generic:: getInts=>get_intN,get_intD
  end type
  abstract interface 
    function getintN(struct,arg)
      import param_func
      class(param_func) :: struct
      integer :: get_intN
      character(len=*) :: arg
    end function
    function getintD(struct,arg,def)
      import param_func
          class(param_func) :: struct
      integer :: getintD,def
      character(len=*) :: arg
    end function
    function getfloatN(struct,arg)
      import param_func
          class(param_func) :: struct
      real :: getfloatN
      character(len=*) :: arg
    end function
        function getstringD(struct,arg,def)
      import param_func
          class(param_func) :: struct
      character(len=1024) :: getStringD
      character(len=*) :: arg,def
    end function
    function getStringN(struct,arg)
      import param_func
          class(param_func) :: struct
      character(len=1024) :: getstringN
      character(len=*) :: arg
    end function
    function getfloatD(struct,arg,def)
      import param_func
          class(param_func) :: struct
      real :: getfloatD,def
      character(len=*) :: arg
    end function    
    function getboolN(struct,arg)
      import param_func
          class(param_func) :: struct
      logical :: getboolN
      character(len=*) :: arg
    end function
    function getboolD(struct,arg,def)
      import param_func
          class(param_func) :: struct
      logical :: getboolD,def
      character(len=*) :: arg
    end function 
     function getintsN(struct,arg)
       import param_func
           class(param_func) :: struct
      integer,pointer,dimension(:) :: getintsN
      character(len=*) :: arg
    end function
    function getintsD(struct,arg,def)
      import param_func
          class(param_func) :: struct
      integer,pointer,dimension(:) :: getintsD,def
      character(len=*) :: arg
    end function   
    function getfloatsN(struct,arg)
      import param_func
          class(param_func) :: struct
      real,pointer,dimension(:) :: getfloatsN
      character(len=*) :: arg
    end function
    function getfloatsD(struct,arg,def)
      import param_func
          class(param_func) :: struct
      real,pointer,dimension(:) :: getfloatsD,def
      character(len=*) :: arg
    end function  
    subroutine error(struct,arg)
      import param_func
          class(param_func) :: struct
      character(len=*) :: arg
    end subroutine
  end  interface      
end module
