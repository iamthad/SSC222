! Thadeus Fleming
! Homework 4 Fortran Problem 2
! SSC 222
! Crew transfer between several Starfleet vessels and sorting by values
! AKA Practice with subroutines and functions
module starfleet
  implicit none
  type Starship
    character(len=16) :: ship_name
    integer :: crew_complement 
    real :: maximum_warp
  end type Starship

  contains

  integer function get_ship_index(ship_name,fleet,fleet_size)
    integer :: i
    integer,intent(in) :: fleet_size
    character(len=16),intent(in) :: ship_name
    type(Starship),dimension(fleet_size),intent(in):: fleet
    logical :: ship_found = .false.
    do i=1,fleet_size
      if (trim(fleet(i)%ship_name) == trim(ship_name)) then
        get_ship_index= i
        ship_found =.true. 
      endif
    enddo
    if (ship_found ==.false.) then
      ! Ship not found, return -1
      get_ship_index=-1
    endif
  end function get_ship_index

  subroutine print_fleet_status(fleet,fleet_size)
    integer :: i
    integer, intent(in) :: fleet_size
    type(starship),dimension(fleet_size),intent(in) :: fleet
      print *, "This is the current state of the fleet:"
      print *, "Total crew size: ", total_crew(fleet,fleet_size)
      print *, "Ship Name	", "Crew Complement	", "Maximum Warp"
      do i=1,fleet_size
        print *, fleet(i)%ship_name, fleet(i)%crew_complement,&
        fleet(i)%maximum_warp
      enddo
  end subroutine print_fleet_status

  integer function total_crew(fleet,fleet_size)
    integer, intent(in)                             :: fleet_size
    type(starship),dimension(fleet_size),intent(in) :: fleet
    integer                                         :: i=0
    total_crew = 0
    do i=1,fleet_size
      total_crew=total_crew+fleet(i)%crew_complement
    end do
  end function total_crew

  subroutine crew_transfer(fleet,fleet_size)
    integer, parameter  :: skeleton_crew = 5
    integer,intent(in) :: fleet_size
    type(starship),dimension(fleet_size),intent(inout) :: fleet
    integer :: number_transferred, sending_ship,&
    receiving_ship,trans,transfers_remaining,i
    character(len=16) :: sending_ship_name, receiving_ship_name,answer
    logical :: sending_ship_set, receiving_ship_set, crew_members_sent

    trans = 1
    print *, "How many transfers would you like to make?"
    read *, transfers_remaining
    do i=1,transfers_remaining
      if (trans .ne. 1) then
        call print_fleet_status(Fleet,fleet_size)
      endif
      sending_ship_set = .false.
      do while (sending_ship_set == .false.)
        print *, "Admiral, which ship do you want to transfer crew from?"
        read *, sending_ship_name
        sending_ship = get_ship_index(sending_ship_name,Fleet,fleet_size)
        if (sending_ship >0 .and. sending_ship <=fleet_size) then
          print *, "Very well, Admiral. The ", Fleet(sending_ship)%ship_name,&
          "has a crew of", Fleet(sending_ship)%crew_complement
          sending_ship_set = .true.
        else
          print *, "I'm sorry, Admiral, I didn't find that ship in our records."
        endif
      enddo
      receiving_ship_set = .false.
      do while (receiving_ship_set == .false.)
        print *, "Admiral, to which ship do you want to transfer those crew members?"
        read *, receiving_ship_name
        receiving_ship = get_ship_index(receiving_ship_name,Fleet,fleet_size)
        if (receiving_ship >0 .and. receiving_ship <=fleet_size) then
          print *, "Very well, Admiral. The ", Fleet(receiving_ship)%ship_name,&
          "has a crew of", Fleet(receiving_ship)%crew_complement
          receiving_ship_set = .true.
        else
          print *, "I'm sorry, Admiral, I didn't find that ship in our records."
        endif
      enddo
      crew_members_sent = .false.
      do while (crew_members_sent == .false.)
        print *, "How many crew members should be sent?"
        read *, number_transferred
        if (number_transferred < 0) then
          print *, "I'm sorry, Admiral, but you're sending crew, not requesting it."
        else if (number_transferred > Fleet(sending_ship)%crew_complement) then
          print *, "I'm sorry, Admiral, but the ",Fleet(sending_ship)%ship_name,&
          "doesn't have that many crew members!"
        else if (Fleet(sending_ship)%crew_complement - number_transferred <&
        skeleton_crew) then
          print *, "I'm sorry, Admiral, but the ",Fleet(sending_ship)%ship_name,&
          "can't make do with only ", Fleet(sending_ship)%crew_complement -&
          number_transferred, "crew members."
        else
          print *, "Very well, Admiral. I'll make the arrangements. "
          Fleet(sending_ship)%crew_complement = Fleet(sending_ship)%crew_complement - number_transferred
          Fleet(receiving_ship)%crew_complement = Fleet(receiving_ship)%crew_complement + number_transferred
          print *, "Admiral, the crew transfer has been made. ", Fleet(sending_ship)%ship_name, "now stands at ", Fleet(sending_ship)%crew_complement, "and the ", Fleet(receiving_ship)%ship_name, "now has ", Fleet(receiving_ship)%crew_complement,"crew members. The extra ", number_transferred, "personnel will be of great value to their mission."
          crew_members_sent = .true.
         endif
      enddo
      transfers_remaining = transfers_remaining - 1
      trans = trans + 1
    enddo
  end subroutine crew_transfer

  subroutine sort_by_crew(fleet,fleet_size)
    integer,intent(in)                                 :: fleet_size
    type(starship),dimension(fleet_size),intent(inout) :: fleet
    real,dimension(fleet_size)                         :: array
    integer                                            :: i
    do i=1,fleet_size
      array(i)=fleet(i)%crew_complement
    end do

    call sort_fleet(fleet,fleet_size,array)

  end subroutine sort_by_crew

  subroutine sort_by_warp(fleet,fleet_size)
    integer,intent(in)                                 :: fleet_size
    type(starship),dimension(fleet_size),intent(inout) :: fleet
    real,dimension(fleet_size)                         :: array
    integer                                            :: i
    do i=1,fleet_size
      array(i)=fleet(i)%maximum_warp
    end do

    call sort_fleet(fleet,fleet_size,array)

  end subroutine sort_by_warp

  subroutine sort_fleet(fleet,fleet_size,array)
    integer,intent(in)                                 :: fleet_size
    type(starship),dimension(fleet_size),intent(inout) :: fleet
    real,dimension(fleet_size), intent(inout)          :: array
    logical                                            :: noops = .true.
    real                                               :: temp_real
    type(starship)                                     :: temp_ship
    integer                                            :: i

    ! Now let's do the sort
    do
      noops = .true.

      do i=1,fleet_size-1
        if (array(i) > array(i+1)) then
          noops = .false.
          temp_real = array(i+1)
          array(i+1) = array(i)
          array(i) = temp_real

          ! Sort the fleet at the same time
          temp_ship = fleet(i+1)
          fleet(i+1) = fleet(i)
          fleet(i) = temp_ship

        end if
      end do

      if (noops) then
        exit
      end if
    end do

  end subroutine sort_fleet
    
end module starfleet


program crew_transfer_2
  use starfleet
  implicit none

  type(Starship), dimension(5) :: Fleet
  integer, parameter :: fleet_size = 5
  Fleet(1)%ship_name = 'Defiant'
  Fleet(1)%crew_complement = 50
  Fleet(1)%maximum_warp = 9.20

  Fleet(2)%ship_name = 'Valiant'
  Fleet(2)%crew_complement = 48
  Fleet(2)%maximum_warp = 9.16

  Fleet(3)%ship_name = 'Spitfire'
  Fleet(3)%crew_complement = 53
  Fleet(3)%maximum_warp = 9.14

  Fleet(4)%ship_name = 'Enterprise'
  Fleet(4)%crew_complement = 885
  Fleet(4)%maximum_warp = 9.985

  Fleet(5)%ship_name = 'Sovereign'
  Fleet(5)%crew_complement = 664
  Fleet(5)%maximum_warp = 9.983

  print *, "Good day, Admiral."
  call print_fleet_status(Fleet,fleet_size)
  call crew_transfer(Fleet,fleet_size)
  print *, "Here are the ships listed by maximum warp:"
  call sort_by_warp(Fleet,fleet_size)
  call print_fleet_status(Fleet,fleet_size)
  print *, "Here are the ships listed by crew complement:"
  call sort_by_crew(Fleet,fleet_size)
  call print_fleet_status(Fleet,fleet_size)

  print *, "Very well, Admiral. Good day."
end program crew_transfer_2
