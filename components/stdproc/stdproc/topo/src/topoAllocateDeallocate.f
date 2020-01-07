!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
! Copyright: 2012 to the present, California Institute of Technology.
! ALL RIGHTS RESERVED. United States Government Sponsorship acknowledged.
! Any commercial use must be negotiated with the Office of Technology Transfer
! at the California Institute of Technology.
! 
! This software may be subject to U.S. export control laws. By accepting this
! software, the user agrees to comply with all applicable U.S. export laws and
! regulations. User has the responsibility to obtain export licenses,  or other
! export authority as may be required before exporting such information to
! foreign countries or providing access to foreign persons.
! 
! Installation and use of this software is restricted by a license agreement
! between the licensee and the California Institute of Technology. It is the
! User's responsibility to abide by the terms of the license agreement.
!
! Author: Giangi Sacco
!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~





        subroutine allocate_s_mocompArray(dim1)
            use topoState
            implicit none
            integer dim1
            dim1_s_mocompArray = dim1
            allocate(s_mocomp(dim1)) 
        end

        subroutine deallocate_s_mocompArray()
            use topoState
            deallocate(s_mocomp) 
        end

        subroutine allocate_squintshift(dim1)
            use topoState
            implicit none
            integer dim1
            dim1_squintshift = dim1
            allocate(squintshift(dim1)) 
        end

        subroutine deallocate_squintshift()
            use topoState
            deallocate(squintshift) 
        end

