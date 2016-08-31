module param_func_mod
  implicit none
  type,abstract  :: param_func
  
    contains
      procedure(getIntN), deferred :: get_intN
      procedure(getIntD), deferred :: get_intD
      procedure(getFloatN),deferred:: get_floatN
      procedure(getFloatD),deferred :: get_floatD
      procedure(getStringN),deferred :: get_StringN
      procedure(getStringD),deferred :: get_StringD
      procedure(getBoolN),deferred :: get_boolN
      procedure(getBoolD),deferred :: get_boolD
      procedure(getIntsN),deferred :: get_IntsN
      procedure(getIntsD),deferred :: get_IntsD
      procedure(getFloatsN),deferred :: get_floatsN
      procedure(getFloatsD),deferred :: get_floatsD
      procedure(error), deferred:: err
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
      integer :: getintN
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
      integer,pointer,dimension(:) :: getintsD
      integer :: def(:)
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
      real :: def(:)
      real,pointer,dimension(:) :: getfloatsD
      character(len=*) :: arg
    end function  
    
    subroutine error(struct,arg)
      import param_func
          class(param_func) :: struct
      character(len=*) :: arg
    end subroutine
  end  interface      
end module
