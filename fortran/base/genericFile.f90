module generic_file_mod
  use hypercube_mod
  use param_func_mod
  implicit none
  type,extends(param_func),abstract :: generic_reg_file
    private
      type(hypercube),pointer :: hyper=>null()
      character(len=1024) :: fle
  contains
    procedure(readDescription),deferred :: readDescription
    procedure(writeDescription),deferred :: writeDescription
    procedure(setFile),deferred :: setFile
    procedure(putReal),deferred :: putReal
    procedure(putInt),deferred :: putInt
    procedure(putString),deferred :: putString
    procedure(putLogical),deferred :: putLogical
    procedure(putReals),deferred :: putReals
    procedure(putInts),deferred :: putInts
    procedure(readF1),deferred :: readF1
    procedure(readF2),deferred :: readF2
    procedure(readF3),deferred :: readF3
    procedure(readF4),deferred :: readF4
    procedure(readF5),deferred :: readF5
    procedure(writeF1),deferred :: writeF1
    procedure(writeF2),deferred :: writeF2
    procedure(writeF3),deferred :: writeF3
    procedure(writeF4),deferred :: writeF4
    procedure(writeF5),deferred :: writeF5
    procedure(rfwind1),deferred :: rfwind1
    procedure(rfwind2),deferred :: rfwind2
    procedure(rfwind3),deferred :: rfwind3
    procedure(rfwind4),deferred :: rfwind4
    procedure(rfwind5),deferred :: rfwind5
    procedure(wfwind1),deferred :: wfwind1
    procedure(wfwind2),deferred :: wfwind2
    procedure(wfwind3),deferred :: wfwind3
    procedure(wfwind4),deferred :: wfwind4
    procedure(wfwind5),deferred :: wfwind5
    procedure(setHyper),deferred :: setHyper
    procedure(getHyper),deferred :: getHyper
    generic :: readRealStream=>readF1,readF2,readF3,readF4,readF5
    generic :: writeRealStream=>writeF1,writeF2,writeF3,writeF4,writeF5
    generic:: readRealWindow=>RFwind1,RFwind2,rFwind3,rfwind4,rfwind5
    generic:: writeRealWindow=>WFwind1,wFwind2,wFwind3,wFwind4,wfwind5
  end type


! procedure(getBoolD),deferred,pass :: get_boolD
 !     procedure(getIntsN),deferred,pass :: get_IntsN
  !    procedure(getIntsD),deferred,pass :: get_IntsD
   !   procedure(getFloatsN),deferred,pass :: get_floatsN
    !  procedure(getFloatsD),deferred,pass :: get_floatsD
   !   procedure(error), deferred,pass:: err
   !   generic:: getInt=>get_intN,get_intD
   !   generic:: getReal=>get_floatN,get_floatD
   !   generic:: getLogical=>get_boolN,get_boolD  

  abstract interface
    subroutine readDescription(struct)
      import generic_reg_file
      class(generic_reg_file) :: struct
    end subroutine
     subroutine writeDescription(struct)
      import generic_reg_file
      class(generic_reg_file) :: struct
    end subroutine 
    subroutine rfwind1(struct,vals,sz)
      import generic_reg_file
      class(generic_reg_file) :: struct
      real, dimension(:) :: vals
      integer :: sz
    end subroutine
    subroutine rfwind2(struct,vals,sz)
      import generic_reg_file
      class(generic_reg_file) :: struct
      real, dimension(:,:) :: vals
      integer :: sz
    end subroutine
    subroutine rfwind3(struct,vals,sz)
      import generic_reg_file
      class(generic_reg_file) :: struct
      real, dimension(:,:,:) :: vals
      integer :: sz
    end subroutine
    subroutine rfwind4(struct,vals,sz)
      import generic_reg_file
      class(generic_reg_file) :: struct
      real, dimension(:,:,:,:) :: vals
      integer :: sz
    end subroutine
    subroutine rfwind5(struct,vals,sz)
      import generic_reg_file
      class(generic_reg_file) :: struct
      real, dimension(:,:,:,:,:) :: vals
      integer :: sz
    end subroutine
    subroutine wfwind1(struct,vals,sz)
      import generic_reg_file
      class(generic_reg_file) :: struct
      real, dimension(:) :: vals
      integer :: sz
    end subroutine
    subroutine wfwind2(struct,vals,sz)
      import generic_reg_file
      class(generic_reg_file) :: struct
      real, dimension(:,:) :: vals
      integer :: sz
    end subroutine
    subroutine wfwind3(struct,vals,sz)
      import generic_reg_file
      class(generic_reg_file) :: struct
      real, dimension(:,:,:) :: vals
      integer :: sz
    end subroutine
    subroutine wfwind4(struct,vals,sz)
      import generic_reg_file
      class(generic_reg_file) :: struct
      real, dimension(:,:,:,:) :: vals
      integer :: sz
    end subroutine
    subroutine wfwind5(struct,vals,sz)
      import generic_reg_file
      class(generic_reg_file) :: struct
      real, dimension(:,:,:,:,:) :: vals
      integer :: sz
    end subroutine
  
  
  
    subroutine readF1(struct,vals,sz)
      import generic_reg_file
      class(generic_reg_file) :: struct
      real, dimension(:) :: vals
      integer :: sz
    end subroutine
    subroutine readF2(struct,vals,sz)
      import generic_reg_file
      class(generic_reg_file) :: struct
      real, dimension(:,:) :: vals
      integer :: sz
    end subroutine
    subroutine readF3(struct,vals,sz)
      import generic_reg_file
      class(generic_reg_file) :: struct
      real, dimension(:,:,:) :: vals
      integer :: sz
    end subroutine
    subroutine readF4(struct,vals,sz)
      import generic_reg_file
      class(generic_reg_file) :: struct
      real, dimension(:,:,:,:) :: vals
      integer :: sz
    end subroutine
    subroutine readF5(struct,vals,sz)
      import generic_reg_file
      class(generic_reg_file) :: struct
      real, dimension(:,:,:,:,:) :: vals
      integer :: sz
    end subroutine
    subroutine writeF1(struct,vals,sz)
      import generic_reg_file
      class(generic_reg_file) :: struct
      real, dimension(:) :: vals
      integer :: sz
    end subroutine
    subroutine writeF2(struct,vals,sz)
      import generic_reg_file
      class(generic_reg_file) :: struct
      real, dimension(:,:) :: vals
      integer :: sz
    end subroutine
    subroutine writeF3(struct,vals,sz)
      import generic_reg_file
      class(generic_reg_file) :: struct
      real, dimension(:,:,:) :: vals
      integer :: sz
    end subroutine
    subroutine writeF4(struct,vals,sz)
      import generic_reg_file
      class(generic_reg_file) :: struct
      real, dimension(:,:,:,:) :: vals
      integer :: sz
    end subroutine
    subroutine writeF5(struct,vals,sz)
      import generic_reg_file
      class(generic_reg_file) :: struct
      real, dimension(:,:,:,:,:) :: vals
      integer :: sz
    end subroutine
    subroutine putInts(struct,par,val)
      import generic_reg_file
      class(generic_reg_file) :: struct
      character(len=*) :: par
      integer,dimension(:) :: val
    end subroutine
      subroutine putReals(struct,par,val)
      import generic_reg_file
      class(generic_reg_file) :: struct
      character(len=*) :: par
      real,dimension(:) :: val
    end subroutine
      subroutine putString(struct,par,val)
      import generic_reg_file
      class(generic_reg_file) :: struct
      character(len=*) :: par
      character(len=*) :: val
    end subroutine
    subroutine putReal(struct,par,val)
      import generic_reg_file
      class(generic_reg_file) :: struct
      character(len=*) :: par
      real :: val
    end subroutine
    subroutine putLogical(struct,par,val)
      import generic_reg_file
      class(generic_reg_file) :: struct
      character(len=*) :: par
      logical :: val
    end subroutine
    subroutine putInt(struct,par,val)
      import generic_reg_file
      class(generic_reg_file) :: struct
      character(len=*) :: par
      integer :: val
    end subroutine
  end interface
contains
  function getHyper(struct)
    class(generic_reg_file) :: struct
    type(hypercube) :: getHyper
    if(.not. associated(struct%hyper)) then
       call struct%err("no hypercube associated with file")
    end if
    getHyper=createHypercube(struct%hyper)
  end function
  subroutine setHyper(struct,hyp) 
    class(generic_reg_file) :: struct
    type(hypercube) :: hyp
      if(associated(struct%hyper)) deallocate(struct%hyper)
      allocate(struct%hyper)
      struct%hyper=createHypercube(hyp)
  end subroutine
  subroutine setFile(struct,fle) 
    class(generic_reg_file) :: struct
    character(len=*) :: fle
    struct%fle=fle;
  end subroutine


end module
