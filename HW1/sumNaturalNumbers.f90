program sumNaturalNumbers
implicit none
integer, parameter:: N=10
integer:: sum
sum = N*(N+1)/2
print *, 'The sum of the first', N, 'natural numbers is', sum, '.'
end program sumNaturalNumbers
