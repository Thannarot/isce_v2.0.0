!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
! copyright: 2013 to the present, california institute of technology.
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





        subroutine setStartingRange(var)
            use fdmocompState
            implicit none
            double precision var
            r001 = var
        end

        subroutine setPRF(var)
            use fdmocompState
            implicit none
            double precision var
            prf = var
        end

        subroutine setRadarWavelength(var)
            use fdmocompState
            implicit none
            double precision var
            wavl = var
        end

        subroutine setWidth(var)
            use fdmocompState
            implicit none
            integer var
            nlinesaz = var
        end

        subroutine setHeigth(var)
            use fdmocompState
            implicit none
            integer var
            nlines = var
        end

        subroutine setPlatformHeigth(var)
            use fdmocompState
            implicit none
            integer var
            ht1 = var
        end

        subroutine setLookSide(var)
            use fdmocompState
            implicit none
            integer var
            ilrl = var
        end

        subroutine setRangeSamplingRate(var)
            use fdmocompState
            implicit none
            double precision var
            fs = var
        end

        subroutine setRadiusOfCurvature(var)
            use fdmocompState
            implicit none
            double precision var
            rcurv = var
        end

        subroutine setDopplerCoefficients(array1d,dim1)
            use fdmocompState
            implicit none
            integer dim1,i
            double precision, dimension(dim1):: array1d
            do i = 1, dim1
                fdArray(i) = array1d(i)
            enddo
        end

        subroutine setSchVelocity(array2dT,dim1,dim2)
            use fdmocompState
            implicit none
            integer dim1,dim2,i,j
            double precision, dimension(dim2,dim1):: array2dT
            do i = 1, dim2
                do j = 1, dim1
                    vsch(i,j) = array2dT(i,j)
                enddo
            enddo
        end

