! Thadeus Fleming
! Homework 3 Problem 1
! SSC 222
! Computing the arithmetic mean of an array of reals

program averageReal
implicit none

integer, parameter :: n = 10
integer :: i
real, dimension(n) :: squares
real :: arraysum, average
arraysum = 0
average = 0
do i = 1, n
  squares(i) = i**2
  arraysum = arraysum + squares(i)
enddo
average = arraysum/n
print *, "The array is", squares
print *, "Their sum is", arraysum
print *, "Their average is", average
end program averageReal
