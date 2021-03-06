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





        module resampState
            integer*8 ptStdWriter    !c Std Writer
            integer i_ma             !c Number of fit Coefficients
            integer npl              !c Width of image 1 
            integer npl2             !c Width of image 2
            integer ist              !c Starting line 
            integer nl               !c Number of lines
            integer istoff           !c First line offset
            integer NR               !c Number of range looks
            integer NAZ              !c Number of azimuth looks
            real*4 WVL               !c Wavelength
            real*4 SLR               !c Slant range pixel spacing
            integer iflatten         !c Flattening flag

            !c Doppler coefficients
       double precision, allocatable, dimension(:)::dopplerCoefficients 
            integer dim1_dopplerCoefficients

            !c Location across array 1
            double precision, allocatable, dimension(:) ::  r_ranposV
            integer dim1_r_ranpos

            !c Location across offset array 1
            double precision, allocatable, dimension(:) ::  r_ranoffV
            integer dim1_r_ranoff

            !c Location down array 1
            double precision, allocatable, dimension(:) ::  r_azposV
            integer dim1_r_azpos

            !c Location down offset array 1
            double precision, allocatable, dimension(:) ::  r_azoffV
            integer dim1_r_azoff

            !c SNR array 1
            double precision, allocatable, dimension(:) ::  r_sigV
            integer dim1_r_sig

            !c Location across array 2
            double precision, allocatable, dimension(:) ::  r_ranpos2V
            integer dim1_r_ranpos2

            !c Location across offset array 2
            double precision, allocatable, dimension(:) ::  r_ranoff2V
            integer dim1_r_ranoff2

            !c Location down array 2
            double precision, allocatable, dimension(:) ::  r_azpos2V
            integer dim1_r_azpos2

            !c Location down offset array 2
            double precision, allocatable, dimension(:) ::  r_azoff2V
            integer dim1_r_azoff2

            !c SNR array 2
            double precision, allocatable, dimension(:) ::  r_sig2V
            integer dim1_r_sig2

            !c Range / Across offset array
            double precision, allocatable, dimension(:) ::  acrossOffset
            integer dim1_acrossOffset

            !c Azimuth / Down offset array
            double precision, allocatable, dimension(:) ::  downOffset
            integer dim1_downOffset
        end module 
