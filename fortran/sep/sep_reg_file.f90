module sep_regfile_mod
 use generic_file_mod
 use sep_mod
 

 implicit none
 
 type,extends(generic_reg_file) :: sepFile
 
   contains
       procedure::get_intN=>sfGetIntN
      procedure ::get_IntD=>sfGetIntD
      procedure ::get_FloatN=>sfGetFloatN
      procedure:: get_FloatD=>sfGetFloatD
      procedure:: get_StringN=>sfGetStringN
      procedure:: get_StringD=>sfGetStringD
      procedure ::get_BoolN=>sfGetBoolN
      procedure:: get_BoolD=>sfGetBoolD
      procedure:: get_IntsN=>sfGetIntsN
      procedure:: get_IntsD=>sfGetIntsD
      procedure:: get_FloatsN=>sfGetFloatsN
      procedure:: get_FloatsD=>sfGetFloatsD
      procedure:: put_logical=>sfPutLogical
      procedure:: put_int=>sfputInt
      procedure:: put_real=>sfputReal
      procedure:: put_string=>sfputString
      procedure:: put_reals=>sfPutReals
      procedure:: put_ints=>sfPutInts
      procedure:: readDescription=>sfReadDescription
      procedure:: writeDescription=>sfWriteDescription
      procedure::  err=>sfError
      procedure:: readF1=>sfreadF1
      procedure:: readF2=>sfreadF2
      procedure:: readF3=>sfreadF3
      procedure:: readF4=>sfreadF4
      procedure:: readF5=>sfreadF5
      
      procedure:: writeF1=>sfwriteF1
      procedure:: writeF2=>sfwriteF2
      procedure:: writeF3=>sfwriteF3
      procedure:: writeF4=>sfwriteF4
      procedure:: writeF5=>sfwriteF5
      
      procedure:: rfwind1=>sfrwind1
      procedure:: rfwind2=>sfrwind2
      procedure:: rfwind3=>sfrwind3
      procedure:: rfwind4=>sfrwind4
      procedure:: rfwind5=>sfrwind5
      
      procedure:: wfwind1=>sfwwind1
      procedure:: wfwind2=>sfwwind2
      procedure:: wfwind3=>sfwwind3
      procedure:: wfwind4=>sfwwind4
      procedure:: wfwind5=>sfwwind5
      
      
      procedure:: readc1=>screadF1
      procedure:: readc2=>screadF2
      procedure:: readc3=>screadF3
      procedure:: readc4=>screadF4
      procedure:: readc5=>screadF5
      
      procedure:: writec1=>scwriteF1
      procedure:: writec2=>scwriteF2
      procedure:: writec3=>scwriteF3
      procedure:: writec4=>scwriteF4
      procedure:: writec5=>scwriteF5
      
      procedure:: rcwind1=>scrwind1
      procedure:: rcwind2=>scrwind2
      procedure:: rcwind3=>scrwind3
      procedure:: rcwind4=>scrwind4
      procedure:: rcwind5=>scrwind5
      
      procedure:: wcwind1=>scwwind1
      procedure:: wcwind2=>scwwind2
      procedure:: wcwind3=>scwwind3
      procedure:: wcwind4=>scwwind4
      procedure:: wcwind5=>scwwind5
end type


contains 

subroutine sfrwind1(struct,vals,nw,fw,jw)
  class(sepFile) :: struct
  real :: vals(:)
  integer :: nw(:),fw(:),jw(:)
  type(hypercube) :: hy
  integer,allocatable :: ng(:)
   hy=struct%getHyper()
   ng=hy%return_ns()
  if(0/=sreed_window(trim(struct%getFileName()),size(nw), &
    ng,nw,fw,jw,4,vals)) then
       write(0,*) "FILE=",trim(struct%getFileName())
     call seperr("trouble reading data")
  end if
  deallocate(ng)
end subroutine

subroutine sfrwind2(struct,vals,nw,fw,jw)
  class(sepFile) :: struct
  real :: vals(:,:)
  integer :: nw(:),fw(:),jw(:)
  type(hypercube) :: hy
  integer,allocatable :: ng(:)
   hy=struct%getHyper()
   ng=hy%return_ns()
  if(0/=sreed_window(trim(struct%getFileName()),size(nw), &
    ng,nw,fw,jw,4,vals)) then
       write(0,*) "FILE=",trim(struct%getFileName())
     call seperr("trouble reading data")
  end if
  deallocate(ng)
end subroutine
subroutine sfrwind3(struct,vals,nw,fw,jw)
  class(sepFile) :: struct
  real :: vals(:,:,:)
  integer :: nw(:),fw(:),jw(:)
  type(hypercube) :: hy
  integer,allocatable :: ng(:)
   hy=struct%getHyper()
   ng=hy%return_ns()
  if(0/=sreed_window(trim(struct%getFileName()),size(nw), &
    ng,nw,fw,jw,4,vals)) then
       write(0,*) "FILE=",trim(struct%getFileName())
     call seperr("trouble reading data")
  end if
  deallocate(ng)
end subroutine

subroutine sfrwind4(struct,vals,nw,fw,jw)
  class(sepFile) :: struct
  real :: vals(:,:,:,:)
  integer :: nw(:),fw(:),jw(:)
  type(hypercube) :: hy
  integer,allocatable :: ng(:)
   hy=struct%getHyper()
   ng=hy%return_ns()
  if(0/=sreed_window(trim(struct%getFileName()),size(nw), &
    ng,nw,fw,jw,4,vals)) then
       write(0,*) "FILE=",trim(struct%getFileName())
     call seperr("trouble reading data")
  end if
  deallocate(ng)
end subroutine

subroutine sfrwind5(struct,vals,nw,fw,jw)
  class(sepFile) :: struct
  real :: vals(:,:,:,:,:)
  integer :: nw(:),fw(:),jw(:)
  type(hypercube) :: hy
  integer,allocatable :: ng(:)
   hy=struct%getHyper()
   ng=hy%return_ns()
  if(0/=sreed_window(trim(struct%getFileName()),size(nw), &
    ng,nw,fw,jw,4,vals)) then
       write(0,*) "FILE=",trim(struct%getFileName())
     call seperr("trouble reading data")
  end if
  deallocate(ng)
end subroutine

subroutine sfwwind1(struct,vals,nw,fw,jw)
  class(sepFile) :: struct
  real :: vals(:)
  integer :: nw(:),fw(:),jw(:)
  type(hypercube) :: hy
  integer,allocatable :: ng(:)
   hy=struct%getHyper()
   ng=hy%return_ns()
  if(0/=srite_window(trim(struct%getFileName()),size(nw), &
    ng,nw,fw,jw,4,vals)) then
       write(0,*) "FILE=",trim(struct%getFileName())
     call seperr("trouble writing data")
  end if
  deallocate(ng)
end subroutine


subroutine sfwwind2(struct,vals,nw,fw,jw)
  class(sepFile) :: struct
  real :: vals(:,:)
  integer :: nw(:),fw(:),jw(:)
  type(hypercube) :: hy
  integer,allocatable :: ng(:)
   hy=struct%getHyper()
   ng=hy%return_ns()
  if(0/=srite_window(trim(struct%getFileName()),size(nw), &
    ng,nw,fw,jw,4,vals)) then
       write(0,*) "FILE=",trim(struct%getFileName())
     call seperr("trouble writing data")
  end if
  deallocate(ng)
end subroutine


subroutine sfwwind3(struct,vals,nw,fw,jw)
  class(sepFile) :: struct
  real :: vals(:,:,:)
  integer :: nw(:),fw(:),jw(:)
  type(hypercube) :: hy
  integer,allocatable :: ng(:)
   hy=struct%getHyper()
   ng=hy%return_ns()
  if(0/=srite_window(trim(struct%getFileName()),size(nw), &
    ng,nw,fw,jw,4,vals)) then
       write(0,*) "FILE=",trim(struct%getFileName())
     call seperr("trouble writing data")
  end if
  deallocate(ng)
end subroutine


subroutine sfwwind4(struct,vals,nw,fw,jw)
  class(sepFile) :: struct
  real :: vals(:,:,:,:)
  integer :: nw(:),fw(:),jw(:)
  type(hypercube) :: hy
  integer,allocatable :: ng(:)
   hy=struct%getHyper()
   ng=hy%return_ns()
  if(0/=srite_window(trim(struct%getFileName()),size(nw), &
    ng,nw,fw,jw,4,vals)) then
       write(0,*) "FILE=",trim(struct%getFileName())
     call seperr("trouble writing data")
  end if
  deallocate(ng)
end subroutine


subroutine sfwwind5(struct,vals,nw,fw,jw)
  class(sepFile) :: struct
  real :: vals(:,:,:,:,:)
  integer :: nw(:),fw(:),jw(:)
  type(hypercube) :: hy
  integer,allocatable :: ng(:)
   hy=struct%getHyper()
   ng=hy%return_ns()
  if(0/=srite_window(trim(struct%getFileName()),size(nw), &
    ng,nw,fw,jw,4,vals)) then
       write(0,*) "FILE=",trim(struct%getFileName())
     call seperr("trouble writing data")
  end if
  deallocate(ng)
end subroutine

subroutine sfwriteF1(struct,vals,sz)
  class(sepFile) :: struct
  real :: vals(:)
  integer :: sz
  if(sz/=srite(trim(struct%getFileName()),vals,sz)) then
       write(0,*) "FILE=",trim(struct%getFileName())
     call seperr("trouble writing data")
  end if
end subroutine

subroutine sfwriteF2(struct,vals,sz)
  class(sepFile) :: struct
  real :: vals(:,:)
  integer :: sz
  if(sz/=srite(trim(struct%getFileName()),vals,sz)) then
       write(0,*) "FILE=",trim(struct%getFileName())
     call seperr("trouble writing data")
  end if
end subroutine

subroutine sfwriteF3(struct,vals,sz)
  class(sepFile) :: struct
  real :: vals(:,:,:)
  integer :: sz
  if(sz/=srite(trim(struct%getFileName()),vals,sz)) then
       write(0,*) "FILE=",trim(struct%getFileName())
     call seperr("trouble writing data")
  end if
end subroutine

subroutine sfwriteF4(struct,vals,sz)
  class(sepFile) :: struct
  real :: vals(:,:,:,:)
  integer :: sz
  if(sz/=srite(trim(struct%getFileName()),vals,sz)) then
       write(0,*) "FILE=",trim(struct%getFileName())
     call seperr("trouble writing data")
  end if
end subroutine

subroutine sfwriteF5(struct,vals,sz)
  class(sepFile) :: struct
  real :: vals(:,:,:,:,:)
  integer :: sz
  if(sz/=srite(trim(struct%getFileName()),vals,sz)) then
       write(0,*) "FILE=",trim(struct%getFileName())
     call seperr("trouble writing data")
  end if
end subroutine


subroutine sfreadF1(struct,vals,sz)
  class(sepFile) :: struct
  real :: vals(:)
  integer :: sz
  if(sz/=sreed(trim(struct%getFileName()),vals,sz)) then
       write(0,*) "FILE=",trim(struct%getFileName())
     call seperr("trouble reading data")
  end if
end subroutine


subroutine sfreadF2(struct,vals,sz)
  class(sepFile) :: struct
  real :: vals(:,:)
  integer :: sz
  if(sz/=sreed(trim(struct%getFileName()),vals,sz)) then
       write(0,*) "FILE=",trim(struct%getFileName())
     call seperr("trouble reading data")
  end if
end subroutine



subroutine sfreadF3(struct,vals,sz)
  class(sepFile) :: struct
  real :: vals(:,:,:)
  integer :: sz
  if(sz/=sreed(trim(struct%getFileName()),vals,sz)) then
       write(0,*) "FILE=",trim(struct%getFileName())
     call seperr("trouble reading data")
  end if
end subroutine


subroutine sfreadF4(struct,vals,sz)
  class(sepFile) :: struct
  real :: vals(:,:,:,:)
  integer :: sz
  if(sz/=sreed(trim(struct%getFileName()),vals,sz)) then
       write(0,*) "FILE=",trim(struct%getFileName())
     call seperr("trouble reading data")
  end if
end subroutine


subroutine sfreadF5(struct,vals,sz)
  class(sepFile) :: struct
  real :: vals(:,:,:,:,:)
  integer :: sz
  if(sz/=sreed(trim(struct%getFileName()),vals,sz)) then
       write(0,*) "FILE=",trim(struct%getFileName())
     call seperr("trouble reading data")
  end if
end subroutine


subroutine sfPutLogical(struct,arg,val)
  class(sepFile) :: struct
  character(len=*) :: arg
  logical  :: val
  integer :: ierr
   ierr=auxputch(arg,"l",val,struct%getFileName())
   if(ierr<1) then
     write(0,*) "FILE=",trim(struct%getFileName())
     call seperr("trouble writing parameter")
   end if 
end subroutine

subroutine sfPutString(struct,arg,val)
  class(sepFile) :: struct
  character(len=*) :: arg
  character(len=*) :: val
  integer :: ierr
   ierr=auxputch(arg,"s",val,struct%getFileName())
   if(ierr<1) then
     write(0,*) "FILE=",trim(struct%getFileName())
     call seperr("trouble writing parameter")
   end if 
end subroutine


subroutine sfPutInt(struct,arg,val)
  class(sepFile) :: struct
  character(len=*) :: arg
  integer :: val
  integer :: ierr
   ierr=auxputch(arg,"d",val,struct%getFileName())
   if(ierr<1) then
     write(0,*) "FILE=",trim(struct%getFileName())
     call seperr("trouble writing parameter")
   end if 
end subroutine

subroutine sfPutReal(struct,arg,val)
  class(sepFile) :: struct
  character(len=*) :: arg
  real :: val
  integer :: ierr
   ierr=auxputch(arg,"f",val,struct%getFileName())
   if(ierr<1) then
     write(0,*) "FILE=",trim(struct%getFileName())
     call seperr("trouble writing parameter")
   end if 
end subroutine

subroutine sfPutReals(struct,arg,val)
  class(sepFile) :: struct
  character(len=*) :: arg
  real :: val(:)
  integer :: ierr
   ierr=auxpu_f_f_a (arg,"f",val,struct%getFileName())
   if(ierr<1) then
     write(0,*) "FILE=",trim(struct%getFileName())
     call seperr("trouble writing parameter")
   end if 
end subroutine

subroutine sfPutInts(struct,arg,val)
  class(sepFile) :: struct
  character(len=*) :: arg
  integer :: val(:)
  integer :: ierr
   ierr=auxputch(arg,"d",val,struct%getFileName())
   if(ierr<1) then
     write(0,*) "FILE=",trim(struct%getFileName())
     call seperr("trouble writing parameter")
   end if 
end subroutine

   subroutine sfError(struct,arg)
   class(sepFile) :: struct
   character(len=*) :: arg
   call seperr(arg)
 end subroutine

subroutine sfWriteDescription(struct)
 class(sepFile) :: struct
 type(hypercube) :: hy,hy2
 type(axis) :: ax
 type(axis), pointer ::axes(:)
 character(len=1024) :: fle
 integer :: iax,ierr
 hy=struct%getHyper()
 axes=hy%get_axes()
! axes=hyper%get_axes()
 fle=struct%getFileName()
 do iax=1,hy%getNdim()
    if(0/=sep_put_data_axis_par(fle,iax,axes(iax)%n,axes(iax)%o,axes(iax)%d,axes(iax)%label)) then
      write(0,*) "FILE=",trim(fle)," axis=",iax
      call seperr("trouble writing axis")
    end if
 end do
 deallocate(axes)
 end subroutine


subroutine sfReadDescription(struct)
 class(sepFile) :: struct
 type(hypercube) :: hyper
 type(axis), pointer :: axes(:)
 integer :: ndim,iax,ierr
 ierr=sep_get_number_data_axes(struct%getFileName(),ndim)
 if(ierr/=0) then
   write(0,*) "FILE=",trim(struct%getFileName())
   call seperr("trouble getting the number of dimensions")
 end if
 allocate(axes(ndim))
 do iax=1,ndim 
   if(0/=sep_get_data_axis_par(struct%getFileName(),iax,axes(iax)%n,axes(iax)%o,axes(iax)%d,axes(iax)%label)) then
     write(0,*) "FILE",trim(struct%getFileName())," axis=",iax
     call seperr("trouble getting axis")
   end if
 end do
 hyper=hyp_axes(axes)
 call struct%setHyper(hyper)
 deallocate(axes)
end subroutine




function sfGetIntN(struct,arg)
   class(sepFile) :: struct
   character(len=*) :: arg
   integer:: sfGetIntN
   integer :: ierr 
   ierr=auxpar(arg,"f",sfGetIntN,struct%getFileName())
   if(ierr==0) &
     call seperr(arg//" param unspecified in parameters")
 end function
 
 function sfGetIntD(struct,arg,def)
   class(sepFile) :: struct
   character(len=*) :: arg
   integer :: sfGetIntD,def
   integer :: ierr
   sfGetIntD=def
   ierr=auxpar(arg,"f",sfGetIntD,struct%getFileName())
 end function



function sfGetFloatN(struct,arg)
   class(sepFile) :: struct
   character(len=*) :: arg
   real:: sfGetFloatN
   integer :: ierr 
   ierr=auxpar(arg,"f",sfGetFloatN,struct%getFileName())
   if(ierr==0) &
     call seperr(arg//" param unspecified in parameters")
 end function
 
 function sfGetFloatD(struct,arg,def)
   class(sepFile) :: struct
   character(len=*) :: arg
   real :: sfGetFloatD,def
   integer :: ierr
   sfGetFloatD=def
   ierr=auxpar(arg,"f",sfGetFloatD,struct%getFileName())
 end function



function sfGetStringN(struct,arg)
   class(sepFile) :: struct
   character(len=*) :: arg
   character(len=1024) :: sfGetStringN
   integer :: ierr 
   ierr=auxpar(arg,"s",sfGetStringN,struct%getFileName())
   if(ierr==0) &
     call seperr(arg//" param unspecified in parameters")
 end function
 
 function sfGetStringD(struct,arg,def)
   class(sepFile) :: struct
   character(len=*) :: arg,def
   character(len=1024) :: sfGetStringD
   integer :: ierr
   sfGetStringD=def
   ierr=auxpar(arg,"s",sfGetStringD,struct%getFileName())
 end function


function sfGetBoolN(struct,arg)
   class(sepFile) :: struct
   character(len=*) :: arg
   logical :: sfGetBoolN
   integer :: ierr 
   ierr=auxpar(arg,"l",sfGetBoolN,struct%getFileName())
   if(ierr==0) &
     call seperr(arg//" param unspecified in parameters")
 end function
 function sfGetBoolD(struct,arg,def)
   class(sepFile) :: struct
   character(len=*) :: arg
   logical :: sfGetBoolD,def
   integer :: ierr
   sfGetBoolD=def
   ierr=auxpar(arg,"l",sfGetBoolD,struct%getFileName())
 end function


 function sfGetIntsN(struct,arg)
   class(sepFile) :: struct
   character(len=*) :: arg
   integer, dimension(:), pointer :: sfGetIntsN
   integer :: ierr 
   integer :: tmp(10000)
   ierr=auxpar(arg,"d",tmp,struct%getFileName())
   if(ierr==0) &
     call seperr(arg//" param unspecified in parameters")
   allocate(sfGetIntsN(ierr))
   sfGetIntsN=tmp(1:ierr)
 end function
 
 function sfGetIntsD(struct,arg,def)
   class(sepFile) :: struct
   character(len=*) :: arg
   integer, dimension(:), pointer :: sfGetIntsD
   integer ::  def(:)
   integer :: ierr
   allocate(sfGetIntsD(size(def)))
   sfGetIntsD=def
   ierr=auxpar(arg,"f",sfGetIntsD,struct%getFileName())
 end function

 function sfGetFloatsN(struct,arg)
   class(sepFile) :: struct
   character(len=*) :: arg
   real, dimension(:), pointer :: sfGetFloatsN
   integer :: ierr 
   real :: tmp(10000)
   ierr=auxpar(arg,"f",tmp,struct%getFileName())
   if(ierr==0) &
     call seperr(arg//" param unspecified in parameters")
   allocate(sfGetFloatsN(ierr))
   sfGetFloatsN=tmp(1:ierr)
 end function
 
 function sfGetFloatsD(struct,arg,def)
   class(sepFile) :: struct
   character(len=*) :: arg
   real, dimension(:), pointer :: sfGetFloatsD
   real ::  def(:)
   integer :: ierr
   allocate(sfGetFloatsD(size(def)))
   sfGetFloatsD=def
   ierr=auxpar(arg,"f",sfGetFloatsD,struct%getFileName())
 end function
 
 
 subroutine scrwind1(struct,vals,nw,fw,jw)
  class(sepFile) :: struct
  complex :: vals(:)
  integer :: nw(:),fw(:),jw(:)
  type(hypercube) :: hy
  integer,allocatable :: ng(:)
   hy=struct%getHyper()
   ng=hy%return_ns()
  if(0/=sreed_window(trim(struct%getFileName()),size(nw), &
    ng,nw,fw,jw,4,vals)) then
       write(0,*) "FILE=",trim(struct%getFileName())
     call seperr("trouble reading data")
  end if
  deallocate(ng)
end subroutine

subroutine scrwind2(struct,vals,nw,fw,jw)
  class(sepFile) :: struct
  complex :: vals(:,:)
  integer :: nw(:),fw(:),jw(:)
  type(hypercube) :: hy
  integer,allocatable :: ng(:)
   hy=struct%getHyper()
   ng=hy%return_ns()
  if(0/=sreed_window(trim(struct%getFileName()),size(nw), &
    ng,nw,fw,jw,4,vals)) then
       write(0,*) "FILE=",trim(struct%getFileName())
     call seperr("trouble reading data")
  end if
  deallocate(ng)
end subroutine
subroutine scrwind3(struct,vals,nw,fw,jw)
  class(sepFile) :: struct
  complex :: vals(:,:,:)
  integer :: nw(:),fw(:),jw(:)
  type(hypercube) :: hy
  integer,allocatable :: ng(:)
   hy=struct%getHyper()
   ng=hy%return_ns()
  if(0/=sreed_window(trim(struct%getFileName()),size(nw), &
    ng,nw,fw,jw,4,vals)) then
       write(0,*) "FILE=",trim(struct%getFileName())
     call seperr("trouble reading data")
  end if
  deallocate(ng)
end subroutine

subroutine scrwind4(struct,vals,nw,fw,jw)
  class(sepFile) :: struct
  complex :: vals(:,:,:,:)
  integer :: nw(:),fw(:),jw(:)
  type(hypercube) :: hy
  integer,allocatable :: ng(:)
   hy=struct%getHyper()
   ng=hy%return_ns()
  if(0/=sreed_window(trim(struct%getFileName()),size(nw), &
    ng,nw,fw,jw,4,vals)) then
       write(0,*) "FILE=",trim(struct%getFileName())
     call seperr("trouble reading data")
  end if
  deallocate(ng)
end subroutine

subroutine scrwind5(struct,vals,nw,fw,jw)
  class(sepFile) :: struct
  complex :: vals(:,:,:,:,:)
  integer :: nw(:),fw(:),jw(:)
  type(hypercube) :: hy
  integer,allocatable :: ng(:)
   hy=struct%getHyper()
   ng=hy%return_ns()
  if(0/=sreed_window(trim(struct%getFileName()),size(nw), &
    ng,nw,fw,jw,4,vals)) then
       write(0,*) "FILE=",trim(struct%getFileName())
     call seperr("trouble reading data")
  end if
  deallocate(ng)
end subroutine

subroutine scwwind1(struct,vals,nw,fw,jw)
  class(sepFile) :: struct
  complex :: vals(:)
  integer :: nw(:),fw(:),jw(:)
  type(hypercube) :: hy
  integer,allocatable :: ng(:)
   hy=struct%getHyper()
   ng=hy%return_ns()
  if(0/=srite_window(trim(struct%getFileName()),size(nw), &
    ng,nw,fw,jw,4,vals)) then
       write(0,*) "FILE=",trim(struct%getFileName())
     call seperr("trouble writing data")
  end if
  deallocate(ng)
end subroutine


subroutine scwwind2(struct,vals,nw,fw,jw)
  class(sepFile) :: struct
  complex :: vals(:,:)
  integer :: nw(:),fw(:),jw(:)
  type(hypercube) :: hy
  integer,allocatable :: ng(:)
   hy=struct%getHyper()
   ng=hy%return_ns()
  if(0/=srite_window(trim(struct%getFileName()),size(nw), &
    ng,nw,fw,jw,4,vals)) then
       write(0,*) "FILE=",trim(struct%getFileName())
     call seperr("trouble writing data")
  end if
  deallocate(ng)
end subroutine


subroutine scwwind3(struct,vals,nw,fw,jw)
  class(sepFile) :: struct
  complex :: vals(:,:,:)
  integer :: nw(:),fw(:),jw(:)
  type(hypercube) :: hy
  integer,allocatable :: ng(:)
   hy=struct%getHyper()
   ng=hy%return_ns()
  if(0/=srite_window(trim(struct%getFileName()),size(nw), &
    ng,nw,fw,jw,4,vals)) then
       write(0,*) "FILE=",trim(struct%getFileName())
     call seperr("trouble writing data")
  end if
  deallocate(ng)
end subroutine


subroutine scwwind4(struct,vals,nw,fw,jw)
  class(sepFile) :: struct
  complex :: vals(:,:,:,:)
  integer :: nw(:),fw(:),jw(:)
  type(hypercube) :: hy
  integer,allocatable :: ng(:)
   hy=struct%getHyper()
   ng=hy%return_ns()
  if(0/=srite_window(trim(struct%getFileName()),size(nw), &
    ng,nw,fw,jw,4,vals)) then
       write(0,*) "FILE=",trim(struct%getFileName())
     call seperr("trouble writing data")
  end if
  deallocate(ng)
end subroutine


subroutine scwwind5(struct,vals,nw,fw,jw)
  class(sepFile) :: struct
  complex :: vals(:,:,:,:,:)
  integer :: nw(:),fw(:),jw(:)
  type(hypercube) :: hy
  integer,allocatable :: ng(:)
   hy=struct%getHyper()
   ng=hy%return_ns()
  if(0/=srite_window(trim(struct%getFileName()),size(nw), &
    ng,nw,fw,jw,4,vals)) then
       write(0,*) "FILE=",trim(struct%getFileName())
     call seperr("trouble writing data")
  end if
  deallocate(ng)
end subroutine

subroutine scwriteF1(struct,vals,sz)
  class(sepFile) :: struct
  complex :: vals(:)
  integer :: sz
  if(sz/=srite(trim(struct%getFileName()),vals,sz)) then
       write(0,*) "FILE=",trim(struct%getFileName())
     call seperr("trouble writing data")
  end if
end subroutine

subroutine scwriteF2(struct,vals,sz)
  class(sepFile) :: struct
  complex :: vals(:,:)
  integer :: sz
  if(sz/=srite(trim(struct%getFileName()),vals,sz)) then
       write(0,*) "FILE=",trim(struct%getFileName())
     call seperr("trouble writing data")
  end if
end subroutine

subroutine scwriteF3(struct,vals,sz)
  class(sepFile) :: struct
  complex :: vals(:,:,:)
  integer :: sz
  if(sz/=srite(trim(struct%getFileName()),vals,sz)) then
       write(0,*) "FILE=",trim(struct%getFileName())
     call seperr("trouble writing data")
  end if
end subroutine

subroutine scwriteF4(struct,vals,sz)
  class(sepFile) :: struct
  complex :: vals(:,:,:,:)
  integer :: sz
  if(sz/=srite(trim(struct%getFileName()),vals,sz)) then
       write(0,*) "FILE=",trim(struct%getFileName())
     call seperr("trouble writing data")
  end if
end subroutine

subroutine scwriteF5(struct,vals,sz)
  class(sepFile) :: struct
  complex :: vals(:,:,:,:,:)
  integer :: sz
  if(sz/=srite(trim(struct%getFileName()),vals,sz)) then
       write(0,*) "FILE=",trim(struct%getFileName())
     call seperr("trouble writing data")
  end if
end subroutine


subroutine screadF1(struct,vals,sz)
  class(sepFile) :: struct
  complex :: vals(:)
  integer :: sz
  if(sz/=sreed(trim(struct%getFileName()),vals,sz)) then
       write(0,*) "FILE=",trim(struct%getFileName())
     call seperr("trouble reading data")
  end if
end subroutine


subroutine screadF2(struct,vals,sz)
  class(sepFile) :: struct
  complex :: vals(:,:)
  integer :: sz
  if(sz/=sreed(trim(struct%getFileName()),vals,sz)) then
       write(0,*) "FILE=",trim(struct%getFileName())
     call seperr("trouble reading data")
  end if
end subroutine



subroutine screadF3(struct,vals,sz)
  class(sepFile) :: struct
  complex :: vals(:,:,:)
  integer :: sz
  if(sz/=sreed(trim(struct%getFileName()),vals,sz)) then
       write(0,*) "FILE=",trim(struct%getFileName())
     call seperr("trouble reading data")
  end if
end subroutine


subroutine screadF4(struct,vals,sz)
  class(sepFile) :: struct
  complex :: vals(:,:,:,:)
  integer :: sz
  if(sz/=sreed(trim(struct%getFileName()),vals,sz)) then
       write(0,*) "FILE=",trim(struct%getFileName())
     call seperr("trouble reading data")
  end if
end subroutine


subroutine screadF5(struct,vals,sz)
  class(sepFile) :: struct
  complex :: vals(:,:,:,:,:)
  integer :: sz
  if(sz/=sreed(trim(struct%getFileName()),vals,sz)) then
       write(0,*) "FILE=",trim(struct%getFileName())
     call seperr("trouble reading data")
  end if
end subroutine


 
 
 
end module

      
