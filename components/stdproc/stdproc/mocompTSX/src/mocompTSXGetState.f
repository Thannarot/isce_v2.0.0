!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
! copyright: 2012 to the present, california institute of technology.
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





        subroutine getMocompIndex(array1d,dim1)
            use mocompTSXState
            use arraymodule
            implicit none
            integer dim1,i
            double precision, dimension(dim1):: array1d
            do i = 1, dim1
                array1d(i) = i_mocomp(i)
            enddo
            deallocate(i_mocomp)
        end subroutine getMocompIndex

        subroutine getMocompPositionSize(var)
            use mocompTSXState
            implicit none
            integer var
            var = mocompPositionSize
        end subroutine getMocompPositionSize

        subroutine getMocompPosition(array2d,dim1,dim2)
            use arraymodule
            use mocompTSXState
            implicit none
            integer dim1,dim2,i,j
            double precision, dimension(dim2,dim1):: array2d
                do j = 1, dim2
                    array2d(j,1) = t_mocomp(j)
                    array2d(j,2) = s_mocomp(j)
                enddo
                deallocate(t_mocomp)
                deallocate(s_mocomp)
        end subroutine getMocompPosition

        subroutine getStartingRange(vardbl)
            use arraymodule
            use mocompTSXState
            implicit none
            double precision vardbl
            vardbl = adjustr0
        end subroutine getStartingRange

        subroutine getSlcSensingStart(varDbl)
            use mocompTSXState
            implicit none
            double precision varDbl
            varDbl = slcSensingStart
        end subroutine

        subroutine getMocompRange(varDbl)
            use mocompTSXState
            implicit none
            double precision varDbl
            varDbl = rho_mocomp
        end subroutine
