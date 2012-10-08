program mrzee
implicit none
integer :: temperature, month, coin

print *, "It is time for Mr. Zee to partake in some leisure activity. "
print *, "What is the temperature?"
read *, temperature

if (temperature >=72 .and. temperature <=80) then
  print *, "Mr. Zee will go on a long walk."
  print *, "What is the number of the current month?"
  read *, month
  if (month >6 .and. month<10) then
    print *, "Mr. Zee will bring his umbrella."
  else
    print *, "Mr. Zee will not bring his umbrella."
  endif
else
  print *, "Mr. Zee will stay in and read."
  print *, "Flip a coin. Input 1 if heads, anything else if tails."
  read *, coin
  if(coin == 1) then
    print *, "Mr. Zee will read science fiction."
  else
    print *, "Mr. Zee will read Greek mythology."
  endif
endif

end program mrzee
