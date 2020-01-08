!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
! copyright: 2010 to the present, california institute of technology.
! all rights reserved. united states government sponsorship acknowledged.
! any commercial use must be negotiated with the office of technology transfer
! at the california institute of technology.
! 
! this software may be subject to u.s. export control laws. by accepting this
! software, the user agrees to comply with all applicable u.s. export laws and
! regulations. user has the responsibility to obtain export licenses,  or other
! export authority as may be required before exporting such information to
! foreign countries or providing access to foreign persons.
! 
! installation and use of this software is restricted by a license agreement
! between the licensee and the california institute of technology. it is the
! user's responsibility to abide by the terms of the license agreement.
!
! Author: Giangi Sacco
!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~




      module fortranUtils
        integer :: UNIT_STDERR = 0
        integer :: UNIT_STDOUT = 6
        integer :: UNIT_LOG = 1
        character*16 :: FILE_LOG = "isce_fortran.log"

        contains
            function getPI()
                double precision ::getPI
                 getPI = 4.d0*atan(1.d0)
            end function getPI

            function getSpeedOfLight()
                double precision:: getSpeedOfLight
                getSpeedOfLight = 299792458.0d0
            end function getSpeedOfLight

            subroutine set_stdoel_units()
                implicit none
                logical UNITOK, UNITOP
                inquire (unit=UNIT_LOG, exist=UNITOK, opened=UNITOP)
                if (UNITOK .and. .not. UNITOP) then
                   open(unit=UNIT_LOG, file=FILE_LOG, form="formatted", access="append", status="unknown")
                end if
            end subroutine

            subroutine c_to_f_string(pName,cString, cStringLen, fString, fStringLen)
                use iso_c_binding, only: c_char, c_null_char
                implicit none
                integer*4 fStringLen
                integer*4 cStringLen, i
                character*(*), intent(in) :: pName
                character*(*), intent(out) :: fString
                character(kind=c_char, len=1),dimension(cStringLen),intent(in)::  cString
                !Check to amke sure the fString is large enough to hold the cString
                if( cStringLen-1 .gt. fStringLen ) then
                    write(UNIT_STDOUT,*) "*** Error in fortranUtils::c_to_f_string ", &
                      " called from program, ", pName
                    write(UNIT_STDOUT,*) "variable fString of length, ", fStringLen, &
                      "is not large enough to hold variable cString = ", &
                      cString(1:cStringLen), " of length, ", cStringLen
                    stop
                end if

                fString  = ''
                do i = 1, cStringLen
                    if(cString(i) .eq. c_null_char) then
                        fStringLen = i-1
                        exit
                    else
                        fString(i:i) = cString(i)
                    end if
                end do
            end subroutine c_to_f_string

      end module
