module cio_mod
 use c_regfile_mod
 use generic_io_mod
 use c_param_mod

 implicit none
 
 
 
 type,extends(genericIO) :: cio
   contains
    procedure init=>cInit
 end type
 
 contains
    subroutine cInit(struct)
      class(cIO) :: struct
      type(cFile) :: dumF
      type(cParam) :: dumP
      character(len=1000) ,allocatable :: ar(:)
      character(len=99000) :: tmp
      integer :: narg,i
      
      narg=command_argument_count()
      allocate(ar(narg));
      do i=1,narg
        call get_command_argument(i,ar(i))
      end do
      call to1DCharArray(ar,1000,narg,tmp)
      call initializeIO(narg,1000,narg,ar)
      allocate(struct%regFile,source=dumF)
      allocate(struct%param,source=dumP)
    end subroutine
    


end module
