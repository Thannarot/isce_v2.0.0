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




        subroutine setStdWriter(varInt)
            use cpxmag2rgState
            implicit none
            integer*8 varInt
            ptStdWriter = varInt
        end

        subroutine setLineLength(varInt)
            use cpxmag2rgState
            implicit none
            integer varInt
            len = varInt
        end

        subroutine setFileLength(varInt)
            use cpxmag2rgState
            implicit none
            integer varInt
            lines = varInt
        end

        subroutine setAcOffset(varInt)
            use cpxmag2rgState
            implicit none
            integer varInt
            iacoff = varInt
        end

        subroutine setDnOffset(varInt)
            use cpxmag2rgState
            implicit none
            integer varInt
            idnoff = varInt
        end

