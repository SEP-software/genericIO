module generic_io_mod
 use generic_file_mod 
 implicit none
 
 type,abstract :: genericIO
    class(genericRegFile),pointer :: regFile
    class(paramObj),pointer       :: param
   contains
     procedure(genericInit),deferred,pass :: init
 end type
  abstract interface
    subroutine genericInit(struct)
      import genericIO
      class(genericIO) :: struct
    end subroutine
  end  interface

end module
