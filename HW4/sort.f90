! Thadeus Fleming
! Homework 4 Fortran Problem 1
! SSC 222
! Implementing bubble sort
! AKA Practice with subroutines
program test_sort
  implicit none
  integer                 :: i
  integer, parameter      :: length =10
  real, dimension(length) :: an_array_to_sort

  ! populate with random numbers
  call random_number(an_array_to_sort)

  ! let's print the unsorted array
  do i=1, length
    print *, "the value at: ", i, " is: ", an_array_to_sort(i)
  end do

  call sort(an_array_to_sort,length)

    ! let's print the unsorted array
  do i=1, length
    print *, "now sorted the value at: ", i," is: ", an_array_to_sort(i)
  end do
end program test_sort
subroutine sort(array,length)
  implicit none
  logical                                 :: noops = .true.
  real                                    :: temp_real
  integer                                 :: i
  integer, intent(in)                     :: length
  real, dimension(length), intent(inout)  :: array

  ! Now let's do the sort
  do
    noops = .true.

    do i=1,length-1
      if (array(i) > array(i+1)) then
        noops = .false.
        temp_real = array(i+1)
        array(i+1) = array(i)
        array(i) = temp_real
      end if
    end do

    if (noops) then
      exit
    end if
  end do

end subroutine sort
