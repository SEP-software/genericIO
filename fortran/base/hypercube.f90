module hypercubeGen_mod
  use axis_mod
  implicit none
  integer,parameter :: longlong = selected_int_kind(15)
  type hypercube
    
      integer(kind=longlong),private :: n123
      type(axis),dimension(:),allocatable,private :: axes
    contains
    procedure, pass :: set_axes
    procedure, pass :: set_axis
    procedure, pass :: get_axis
    procedure, pass :: get_axes
    procedure, pass :: get_n123
    procedure, pass :: getNdim=>get_ndim
    procedure, pass :: same_size
    procedure, pass :: return_ns
    procedure, pass :: get_ndim_g1
    procedure, pass :: setN123
  end type hypercube
  
  interface createHypercube
    module procedure hyp_hyp,hyp_ns,hyp_axes
  end interface
  
  
   
  contains
  function hyp_hyp(str)
    type(hypercube) :: hyp_hyp,str
    type(axis), allocatable :: axes(:)
    axes=str%get_axes()
    call hyp_hyp%set_axes(axes)
    deallocate(axes)
  end function
  function hyp_axes(axes)
    type(hypercube) :: hyp_axes
    type(axis) :: axes(:)
    call hyp_axes%set_axes(axes)
  end function
  function hyp_ns(ns)
    type(hypercube) :: hyp_ns
    integer :: ns(:),i
    type(axis),dimension(:),allocatable :: axes
    allocate(axes(size(ns)))
    do i=1,size(ns)
      axes(i)=createaxis(ns(i))
    end do
    call hyp_ns%set_axes(axes)
    deallocate(axes)
  end function
    
  
  subroutine destroyH(self)
    type(hypercube) self
    deallocate(self%axes)
  end subroutine
  
  subroutine setN123(self)
    class(hypercube) :: self
    integer :: i
    integer(kind=longlong) :: n
    self%n123=1
    do i=1,size(self%axes)
      n=self%axes(i)%n
      self%n123=self%n123*n
    end do
  end subroutine
  
  function get_ndim_g1(self)
    class(hypercube) :: self
    integer :: get_ndim_g1
    integer :: i
    logical :: found
    get_ndim_g1=size(self%axes)
    found=.false.
    do while(get_ndim_g1 >=1 .and. .not. found)
      if(self%axes(get_ndim_g1)%n >1) then
        found=.true.
      else
        get_ndim_g1=get_ndim_g1-1
      end if
    end do
    if(get_ndim_g1 <1 ) get_ndim_g1=1
  end function
  
  function return_ns(self)
    class(hypercube) :: self
    integer,pointer,dimension(:) :: return_ns
    integer :: i
    allocate(return_ns(size(self%axes)))
    do i=1,size(return_ns)
      return_ns(i)=self%axes(i)%n
    end do
  end function
  
  function same_size(self,hyper2)
    class(hypercube) :: self,hyper2
    logical :: same_size
    integer :: i
    same_size=.true.
    if(size(self%axes) == size(hyper2%axes)) then
      i=1
      do while(i/=size(self%axes) .and. same_size) 
        same_size=self%axes(i)%same_axis(hyper2%axes(i))
        i=i+1
      end do
    else
      same_size=.false.
    end if
  end function
    
    
  function get_ndim(self)
    class(hypercube) :: self
    integer :: get_ndim
    get_ndim=size(self%axes)
  end function
  
  function get_n123(self)
    class(hypercube) :: self
    integer(kind=longlong) :: get_n123
    get_n123=self%n123
  end function
  
  function get_axes(self)
    class(hypercube) self
    integer :: i
    type(axis), dimension(:),pointer :: get_axes
    allocate(get_axes(size(self%axes)))
    do i=1,size(self%axes)
      get_axes(i)=self%get_axis(i)
    end do
  end function

  function get_axis(self,iax)
    class(hypercube) :: self
    integer :: iax
    type(axis) :: get_axis
    
    get_axis=createaxis(self%axes(iax))
  end function
    
  
  subroutine set_axis(self,iax,axs)
    class(hypercube) :: self
    integer :: iax
    type(axis) :: axs
    
    self%axes(iax)=createaxis(axs)
    call self%setN123()
  end subroutine
  

  subroutine set_axes(self,axes)
    class(hypercube) :: self
    type(axis), dimension(:) ::  axes
    integer :: i
    if(allocated(self%axes)) deallocate(self%axes)
    allocate(self%axes(size(axes)))
    do i=1,size(axes)
      call self%set_axis(i,axes(i))
    end do
  end subroutine
  

end module