! Thadeus Fleming
! Homework 2 Problem 2
! SSC 222
! Crew transfer between two Starfleet vessels 
! AKA Practice with derived data types


program crew_transfer
implicit none

type Starship
  character(len=16) :: ship_name
  integer :: crew_complement 
  real :: maximum_warp
end type Starship

type(Starship) :: Defiant, Sovereign
integer, parameter  :: skeleton_crew = 5
integer :: number_transferred, state

Defiant%ship_name = 'Defiant'
Defiant%crew_complement = 50
Defiant%maximum_warp = 9.20

Sovereign%ship_name = 'Sovereign'
Sovereign%crew_complement = 885
Sovereign%maximum_warp = 9.985

state = 1
print *, "Captain, the Sovereign is requesting additional crew."
print *, "We currently have", Defiant%crew_complement, "crew members, and Sovereign has", Sovereign%crew_complement, "crew members."
do while (state > 0)
  print *, "How many can we spare?"
  read *, number_transferred
  if (number_transferred < 0) then
    print *, "I'm sorry, Captain, but they're asking US for crew."
  else if (number_transferred > Defiant%crew_complement) then
    print *, "I'm sorry, Captain, but we don't have that many crew members!"
  else if (Defiant%crew_complement - number_transferred < skeleton_crew) then
    print *, "I'm sorry, Captain, but we can't make do with only ", Defiant%crew_complement - number_transferred, "crew members."
  else
    print *, "Very well, Captain. I'll make the arrangements. "
    Defiant%crew_complement = Defiant%crew_complement - number_transferred
    Sovereign%crew_complement = Sovereign%crew_complement + number_transferred
    print *, "Captain, the crew transfer has been made. We now stand at ", Defiant%crew_complement, "and Sovereign now has ", Sovereign%crew_complement,". The extra ", number_transferred, "crew members will be of great value to their mission."
    state = 0
   endif
enddo

end program crew_transfer
