module poisson_support
implicit none


contains

real elemental function func(x, y)
real, intent(in) :: x, y

func = -exp(-((x-0.5)**2+(y-0.5)**2)/0.2);

end function func


end module poisson_support

program poisson
use poisson_support
integer :: m, n, max_iter, i, j, k
! Arrays for x and y coordinates
real, dimension(:), allocatable :: x, y
! Finite element grid and an array to store precomputed values of func
real, dimension(:,:), allocatable :: u, f
real :: dx, dy, dx_neg2, dy_neg2, denom
character(80) :: c


if (command_argument_count() /=  3) stop  "Not enough input arguments."

call get_command_argument(1,c)
read(c,'(I)') m
call get_command_argument(2,c)
read(c,'(I)') n
call get_command_argument(3,c)
read(c,'(I)') max_iter

print '("Solving Poisson on a",I," by",I," grid for",I," iterations.")', m, n, max_iter

allocate(x(m), stat = ierror)
if (ierror /= 0) stop 'Error allocating x'

allocate(y(n), stat = ierror)
if (ierror /= 0) stop 'Error allocating y'

allocate(u(m,n), stat = ierror)
if (ierror /= 0) stop 'Error allocating u'

allocate(f(m-2,n-2), stat = ierror)
if (ierror /= 0) stop 'Error allocating f'

! Calculate dx and dy
dx = 1/(real(m)-1)
dy = 1/(real(n)-1)

! Set up x and y
forall (i=1:m) & x(i) = (i-1)*dx
forall (i=1:n) & y(i) = (i-1)*dy

! Set boundaries to 0
u(1,:) = 0
u(m,:) = 0
u(:,1) = 0
u(:,n) = 0

! Precompute some stuff. Premature optimization, my ass.
! Precompute the function at all interior points
forall (i=1:m-2,j=1:n-2) & f(i,j) = func(x(i+1),y(j+1))
! Precompute 1/dx^2 and 1/dy^2
dx_neg2 = (real(m)-1)**2
dy_neg2 = (real(n)-1)**2
! Precompute the denominator of the entire function
denom = -2*(dx_neg2+dy_neg2)

! Do the iteration
do k=1, max_iter
  forall (i=2:m-1, j=2:n-1) & u(i,j) = (f(i-1,j)+(u(i+1,j)+u(i-1,j))*dx_neg2+(u(i,j+1)+u(i,j-1))*dy_neg2)/denom
end do

open(unit=42, file = 'poisson.dat', status = 'unknown')
do i=1, m
  do j = 1, n
    write (42, '(2(e","),(e))') x(i),y(j),u(i,j)
  end do
end do
close(42)
end program poisson
