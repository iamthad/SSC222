program mrzee
implicit none
integer :: temperature, month, coin

print *, "It is time for Mr. Zee to partake in some leisure activity. "
print *, "What is the temperature?"
read *, temperature
select case (temperature)
  case(72:80)
    print *, "Mr. Zee will go on a long walk."
    print *, "What is the number of the current month?"
    read *, month
    select case (month)
    case(8:10)
        print *, "Mr. Zee will bring his umbrella."
      case default
        print *, "Mr. Zee will not bring his umbrella."
    end select
  case default
    print *, "Mr. Zee will stay in and read."
    print *, "Flip a coin. Input 1 if heads, anything else if tails."
    read *, coin
    if(coin == 1) then
      print *, "Mr. Zee will read science fiction."
    else
      print *, "Mr. Zee will read Greek mythology."
    endif
end select

end program mrzee
