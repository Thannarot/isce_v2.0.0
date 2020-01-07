!c    soi -- patch mode image formation processor
!c    
      subroutine estamb(rawAccessor)
      
      use arraymodule
      use estambStateSoi
      use fortranUtils
      implicit none
      include 'omp_lib.h'

!!      character*256  fname                PSA - debugging
      character*20000 MESSAGE              !Log message string
      integer*8 rawAccessor   !File pointers
      !Local variables
      integer*4    mmm,  ndiv, nbytesmax  
      integer*4    ranfft,i,j,k
      parameter    (nbytesmax = 32768, ndiv = 4)

      real*4       unpacki1(0:255),unpackq1(0:255) !Unpacking arrays
      real*4       kx01
      real*8       naz
      real*8       fd1, fdd1, fddd1, fd1save     !Doppler
      real*8       r, delr         ! range, spacing
      real*8       velin,focuscorr      !Velocity, Correction factor
      integer*4    ideskew, iflip       !Deskew flag, IQ flip flag
      integer*4    ngoodin              !Piyush - For using the full range line
      integer*4    FDSC3
      double precision rhww1,a41,a21,delw,dxsamp1,gcal,fwidth
      double precision omega,omega0,rc1,pi2,phase,phase1,r1
      double precision theta2,t,ts,theta1,win1,wgt
      real*4 t1,t0
      integer icaltone1,icaltone2,ifs,ifrst,iusedopp,ipatch,irec,k1start,k1end,k2,line
      integer lun,nl,npfin1,nwr,npts,iamb
      integer initdk,iowrit
      double precision :: sol,pi

      double precision, allocatable, dimension(:) :: ampsum, ampsq, numsamp

      !! For entropy calculations - PSA
      complex*8, allocatable, dimension(:,:) :: trans2
      real*8   entr


      !get speed of light and pi from fortranUtils module
      sol = getSpeedOfLight()
      pi = getPI()


      fd1 = dopplerCoefficients(1)
      fdd1 = dopplerCoefficients(2)
      fddd1 = dopplerCoefficients(3)
      
      write(MESSAGE,*), ' '
      call write_out(ptStdWriter,MESSAGE)
      !$omp parallel
      if(omp_get_thread_num().eq.1) then
          write(MESSAGE,*), 'Max threads used: ', omp_get_num_threads()
          call write_out(ptStdWriter,MESSAGE)
      end if
      !$omp end parallel

      write(MESSAGE,*), 'Min Amb: ', minamb, ' Max Amb: ', maxamb
      call write_out(ptStdWriter, MESSAGE)

      !!PSA
      if(minamb.ge.maxamb) then
          write(MESSAGE,*), 'ERROR: Max ambiguity must be greater than Min ambiguity'
          call write_out(ptStdWriter, MESSAGE)
          stop
      end if

!c    set mmm to nlinesazout and allocate arrays
      mmm=nlinesazout
     
!c    determine whether iq or offset video
      if(iqflip.eq.'O')iqflip='o'
      if(iqflip.eq.'o')then
!c         write(*,*)'Offset video format assumed.'
         ranfft=ranfftov

         if(ranfft.le.(2*nlinesazout)) then
             write(MESSAGE,*), 'Range FFT length is insufficient. Continuing ...'
             call write_out(ptStdWriter, MESSAGE)
         end if
      else
!c         write(*,*)'I/Q sampling format assumed.'
         ranfft=ranfftiq

         if(ranfft.le.nlinesazout) then
              write(MESSAGE,*), 'Range FFT length is insufficient. Continuing ...'
              call write_out(ptStdWriter, MESSAGE)
         end if
      end if
      

      ! the first 3 are deallocated when their values are retrieved form
      ! python 
      
      ! jng mocompSize is now defined in arraymodule. the value 100000
      ! turned out to be small when stitching frames together. use the
      ! dim1_time to allocate whci is an upper bound
      
      mocompSize = dim1_time
      allocate(s_mocomp(mocompSize))   !Mocomp S positions
      allocate(t_mocomp(mocompSize))   !Mocomp times
      allocate(i_mocomp(mocompSize))   !Mocomp indices
      allocate(ref1(ranfft+1))         !Array for reference chirp
      allocate(trans1(nnn,mmm))         !Patch of data
      allocate(trans2(nnn,mmm))         !For entropy - PSA
      allocate(schMoc(dim1_sch,dim2_sch))    !Making a copy
      allocate(vschMoc(dim1_vsch,dim2_vsch))
      allocate(timeMoc(dim1_time))
      allocate(phasegrad(ranfft))        !Storing phase gradients. Why not ranfft?

      allocate(ampsum(maxamb-minamb+1))
      allocate(ampsq(maxamb-minamb+1))
      allocate(numsamp(maxamb-minamb+1))
      do i = 1,dim1_sch
        do j = 1,dim2_sch
          schMoc(i,j) = sch(i,j)
        enddo
      enddo
      do i = 1,dim1_vsch
         do j = 1,dim2_vsch
            vschMoc(i,j) = vsch(i,j)
         enddo
      enddo
      do j = 1,dim2_sch
        timeMoc(j) = time(j)
      enddo
      !jng zero everything
      ref1 = 0
      s_mocomp = 0
      i_mocomp = 0
      t_mocomp = 0


!c    need to compute effective velocity for chirp rate due to orbit
!c    curvature.

      write(MESSAGE,"('Effective S/C Body fixed velocity 1 (m/s) ', f15.10)"), vel1
      call write_out(ptStdWriter,MESSAGE)
      velin= vel1           !Input velocity
      vel1 = vel1 * sqrt(rcurv/(rcurv+ht1))  !vel1 itself modified?
      dxsamp1 = vel1/prf1                    !Azimuth spacing on ground
      delr=sol/fs/2.                         !Range pixel spacing

      !Updating the starting range to reflect extensions - Piyush
      !c r01 = r001 + (isave-nextend-1) * delr  !Now computed in python

      write(MESSAGE,*)'Satellite Look Side ', ilrl
      call write_out(ptStdWriter,MESSAGE)
      !Length of azimuth reference function at far range
      naz = wavl*(r01 + real(nlinesazout*delr))/(2.D0*azres*dxsamp1)
      write(MESSAGE,*)'First line to read in file 1 (start at 0) ', ifirstline 
      call write_out(ptStdWriter,MESSAGE)
      write(MESSAGE,*)'# of range input patches ', npatches
      call write_out(ptStdWriter,MESSAGE)
      write(MESSAGE,*)'First sample pair to use ',ifirst
      call write_out(ptStdWriter,MESSAGE)
      write(MESSAGE,*)'Number of valid points in azimuth ',na_valid
      call write_out(ptStdWriter,MESSAGE)
      write(MESSAGE,*)'Deskew the image? ',deskew
      call write_out(ptStdWriter,MESSAGE)
      write(MESSAGE,*)'First range bin to save in file 1 ', isave
      call write_out(ptStdWriter,MESSAGE)
      write(MESSAGE,*)'Number of range bins to process ', nlinesaz
      call write_out(ptStdWriter, MESSAGE)
      write(MESSAGE,*)'Number of output range bins', nlinesazout
      call write_out(ptStdWriter,MESSAGE)
      write(MESSAGE,*) 'Caltone location',caltone1
      call write_out(ptStdWriter,MESSAGE)
      write(MESSAGE,*) 'Doppler centroid quad coef 1 (Hz/prf) ', fd1, fdd1, fddd1
      call write_out(ptStdWriter,MESSAGE)
      write(MESSAGE,*) 'Using Doppler flag ', iusedopp
      call write_out(ptStdWriter,MESSAGE)
      write(MESSAGE,*) 'Effective S/C Body fixed velocity 1 (m/s) ', vel1
      call write_out(ptStdWriter,MESSAGE)
      write(MESSAGE,*) 'Effective Azimuth sample spacing 1 (m) ', dxsamp1
      call write_out(ptStdWriter,MESSAGE)
      write(MESSAGE,*) 'Earth Radius of Curvature(m) ', rcurv
      call write_out(ptStdWriter,MESSAGE)
      write(MESSAGE,*) 'Spacecraft height 1 (m) ', ht1
      call write_out(ptStdWriter,MESSAGE)
      write(MESSAGE,*) 'Range of first pixel in range compressed file 1 (m) ',r001 
      call write_out(ptStdWriter,MESSAGE)
      write(MESSAGE,*) 'PRF 1 (pps) ', prf1
      call write_out(ptStdWriter,MESSAGE)
      write(MESSAGE,*) 'i/q means, i1,q1,', xmi1, xmq1
      call write_out(ptStdWriter,MESSAGE)
      write(MESSAGE,*) 'Flip i/q ', iqflip
      call write_out(ptStdWriter,MESSAGE)
      write(MESSAGE,*) 'Desired azimuth resolution (m) ', azres
      call write_out(ptStdWriter,MESSAGE)
      write(MESSAGE,*) 'Range sampling rate (Hz) ', fs
      call write_out(ptStdWriter,MESSAGE)
      write(MESSAGE,*) 'Chirp Slope (Hz/s) ', slope
      call write_out(ptStdWriter,MESSAGE)
      write(MESSAGE,*) 'Pulse Duration (s) ', pulsedur
      call write_out(ptStdWriter,MESSAGE)
      write(MESSAGE,*) 'Chirp extension ', nextend
      call write_out(ptStdWriter,MESSAGE)
      write(MESSAGE,*) 'Secondary Range Correction ', srm
      call write_out(ptStdWriter,MESSAGE)
      write(MESSAGE,"('Radar Wavelength (m) ',f10.8 )"), wavl
      call write_out(ptStdWriter,MESSAGE)
      write(MESSAGE,*) 'Synthetic Aperature Length (pixels)', naz
      call write_out(ptStdWriter,MESSAGE)
      write(MESSAGE,*) 'Range Spectral Weighting ', rhww
      call write_out(ptStdWriter,MESSAGE)
      write(MESSAGE,*) 'Fractional bandwidth to remove ', pctbw
      call write_out(ptStdWriter,MESSAGE)

      t0 = secnds(0.0)          ! start timer

      pi2 = 2.d0 * pi
      theta1=0.
      theta2=0.
!c    compute range reference function

      fwidth=slope*pulsedur
      if(iqflip.eq.'o')then
         npts=2.*fs*pulsedur     !Range chirp in pixels
         ts=1./(2.*fs)           !Range time sampling
      else
         npts=fs*pulsedur        !Range chirp in pixels
         ts=1./fs                !Range time sampling
      end if
      if(mod(npts,2) .eq. 0) npts=npts+1
!      write(*,*)'Pulse length in points, time/sample in us: ',npts,ts*1.e6
      fd1 = fd1 * prf1
      fdd1 = fdd1 * prf1
      fddd1 = fddd1 * prf1
      entropy = 0.

!c    reference doppler coefficients to range

      call radopp(fd1,fdd1,fddd1,r001,delr)
      
      write(MESSAGE,*) 'Doppler check: ',fd1+fdd1*r01+fddd1*r01*r01
      call write_out(ptStdWriter,MESSAGE)

!c    update r001 to reflect the offsets given in isave,
!c    iradelta, and nextend

      !Updating the far range of the valid part of raw data
      r1  = r01 + delr*(nlinesazout-1)   

      ! Length of the azimuth reference signal at far range
      npfin1 = r1*wavl/(2.0*azres*dxsamp1)+2

      a21 = -2.0*pi/(dxsamp1*float(nnn)) ! for deskew
      a41 = wavl/(2.0*azres*dxsamp1)     ! for np
!!$      write(*,*)'coefficient for filter points a4 ',a41
!!$      write(*,*) 'near range chirp rate ', -2. * vel1**2/(wavl*r01)
!!$      write(*,*) 'far  range chirp rate ', -2. * vel1**2/(wavl*r1)
      
      theta1 = theta1*pi/180.0  !use only if deskew desired

      ! Range and azimuth spectra weighting
      rhww1 = 1.0-rhww

      k=0
      if(pctbw.ge.0.0)then
         k1start=abs(pctbw)*npts
         k1end=npts
      else
         k1start=0
         k1end=npts-abs(pctbw)*npts
      end if
      
!!$      write(*,*)'npts, k1 start, end'
!!$      write(*,*)npts,k1start,k1end

      !Create the reference chirp signal for OV / IQ
      do i=-npts/2,npts/2
         k=k+1
         t=i*ts
         if(iqflip.eq.'o')then
            phase = pi*slope*t*t+pi*fs*t                !Reference chirp + Carrier (Real value)
            if(k.ge.k1start.and.k.le.k1end) &
                ref1(i+npts/2+1)=cmplx(cos(phase),0.)
         else
            phase = pi*slope*t*t                        !Reference chirp   (Complex value)
            if(k.ge.k1start.and.k.le.k1end) &
                ref1(i+npts/2+1)=cmplx(cos(phase),sin(phase))
         end if
      end do

      ! Apply range spectra window
      do i=1,npts
         win1 = (rhww-rhww1*cos((2.*pi*float(i-1))/float(npts-1)))
         ref1(i)=ref1(i)*win1
      end do


      !Apply chirp range extension
      if(nextend .gt. 0) then
         do i = 1 , npts
            k = i - nextend
            if(k .le. 0) k = k + ranfft
            ref1(k) = ref1(i)
         end do
         do i = 1 , nextend     
            k = npts - nextend+i
            if(k .le. 0) k = k + ranfft
            ref1(k) = cmplx(0.,0.)
         end do
      end if
      
!c    init transform lengths
!c    calculate fft of range reference function
      call cfft1d_jpl(ranfft,ref1, 0)    !Create FFTW plan
      call cfft1d_jpl(ranfft,ref1,-1)    !Forward FFT 
      
      !c    zero out dc and caltone location
      icaltone1=nint(caltone1*ranfft)
      icaltone2=icaltone1
     
      do i = 1, 6
         wgt = 0.5 - 0.5 * cos((i-1)/5.*pi)
         ref1(i) = ref1(i) * wgt
         if(iqflip.eq.'o')then
            ref1(i+ranfft/2) = ref1(i+ranfft/2) * wgt
            ref1(ranfft/2+1-i) = ref1(ranfft/2+1-i) * wgt
         end if
         ref1(i+icaltone1) = ref1(i+icaltone1) * wgt
         k=icaltone1+1-i
         k2=icaltone2+1-i
         if(k.le.0)k=k+ranfft
         if(k2.le.0)k2=k2+ranfft
         ref1(k) = ref1(k) * wgt
         if(iqflip.eq.'o')then
            k=i+ranfft-icaltone1
            k2=i+ranfft-icaltone2
            if(k.gt.ranfft)k=k-ranfft
            if(k2.gt.ranfft)k2=k2-ranfft
            ref1(k) = ref1(k) * wgt
            ref1(ranfft-icaltone1+1-i) = ref1(ranfft-icaltone1+1-i) * wgt
         end if
         ref1(ranfft+1-i) = ref1(ranfft+1-i) * wgt
      end do

      if(srm .eq. 'y' .or. srm .eq. 'Y') then
         write(MESSAGE,*),'Using secondary range correction.'
         call write_out(ptStdWriter,MESSAGE)

!c    include secondary range migration correction to the
!c    chirp transform

         delw = pi2 * fs / ranfft

         rc1 = r01 + delr*nlinesazout/2
         kx01 = pi2*(fd1 + fdd1*rc1 + fddd1*rc1**2)/vel1
         omega0 = pi2 * sol / wavl
         write(MESSAGE,*) 'delw =    ',delw
         call write_out(ptStdWriter,MESSAGE)
         write(MESSAGE,*) 'rc =      ',rc1
         call write_out(ptStdWriter,MESSAGE)
         write(MESSAGE,*) 'kx0 =     ',kx01
         call write_out(ptStdWriter,MESSAGE)
         write(MESSAGE,*) 'omega0 =  ',omega0
         call write_out(ptStdWriter,MESSAGE)
         phase1 = - 0.25 * rc1 * (wavl / pi2) * &
             kx01**2 * ((omega0+ranfft/2.*delw)/omega0)**2 
         write(MESSAGE,*) 'phaser =   ',phase1
         call write_out(ptStdWriter,MESSAGE)
         phase1 = - 0.25 * rc1 * (wavl / pi2) * kx01**2
         write(MESSAGE,*) 'phase0 =   ',phase1
         call write_out(ptStdWriter,MESSAGE)
         phase1 = - 0.25 * rc1 * (wavl / pi2) * &
             kx01**2 * ((omega0-ranfft/2.*delw)/omega0)**2 
         write(MESSAGE,*) 'phasel =   ',phase1
         call write_out(ptStdWriter,MESSAGE)
         
         do i = 0 , ranfft/2
            omega = omega0 + (i-ranfft/2)* delw
            phase1 = - 0.25 * rc1 * (wavl / pi2) * &
                kx01**2 * (omega/omega0)**2 
            ref1(i+1) = ref1(i+1) * cmplx(cos(phase1),sin(phase1))
         end do
         do i = 0 , ranfft/2
            omega = omega0 - i* delw
            phase1 = - 0.25 * rc1 * (wavl / pi2) * &
                kx01**2 * (omega/omega0)**2 
            ref1(ranfft+1-i) =ref1(ranfft+1-i) * cmplx(cos(phase1),sin(phase1))
         end do

      end if

!c    scale reference for channel gain, conjugate

      gcal=1./ranfft
      do i=1,ranfft
         ref1(i)=conjg(ref1(i))*gcal
      end do

!c    offset into valid data in a patch

      ifs = (nnn-na_valid)/2

      iflip = 0
      if(iqflip .eq. 'Y' .or. iqflip .eq. 'y') iflip = 1

!c    load the unpacking array

      if(iflip .eq. 0) then
         do i=0,255
            unpacki1(i)=float(i)-xmi1
            unpackq1(i)=float(i)-xmq1
         end do
      else
         do i=0,255
            unpacki1(i)=float(i)-xmq1
            unpackq1(i)=float(i)-xmi1
         end do
      end if

      ideskew = 0
      if(deskew .eq. 'y' .or. deskew .eq. 'Y') ideskew = 1

!c   
!c      write(*,*)'Range size: ', nlinesazout
!c      write(*,*)'Azimuth Size:', nnn
!c      write(*,*)'Valid Size: ', na_valid
!c      write(*,*)'Offset size:', ifs
!c    begin loop to range process data
!c    
      
      !!For entropy
      ampsum = 0.
      ampsq = 0.
      numsamp = 0

      !!!!Create FFT plan
      call cfft1d_jpl(nnn,trans1(1,1),0)

      do ipatch=1,npatches
         
!c    compress channels

         irec=ifirstline+(ipatch-1)*na_valid    !Starting line of the patch
         ifrst= ifirst+isave-1                  !Starting pixel of the patch
         ngoodin = ngood -2*(isave-1)           !Number of good bytes after removing isave samples

         if(iqflip.eq.'o')then
            ngoodin = ngood - (isave-1)         !Number of good bytes after removing isave samples- Piyush
            call rcov(rawAccessor,nnn,nlinesazout,unpacki1,unpackq1, &
                irec,ifrst,nbytes,ngoodin, ranfft)
         else
            ngoodin = ngood - 2*(isave-1)       !Number of good bytes after removing isave samples- Piyush
            call rciq(rawAccessor,nnn,nlinesazout,unpacki1,unpackq1, &
                irec,ifrst,nbytes,ngoodin,iflip, ranfft)
         end if

         trans2 = cmplx(0.,0.)
         !c         Make a copy for reference - PSA
         do i=1,nnn
            do j=1,nlinesazout
                trans2(i,j) = trans1(i,j)
            end do
         end do

         if(ipatch.eq.1 .and. (iand(iflag,32) .eq. 32))then
            write(MESSAGE,*) 'writing range compressed data '
            call write_out(ptStdWriter,MESSAGE)
            FDSC3 =initdk(lun,'im.rc1 ')
            nwr = iowrit(FDSC3,trans1,8*nnn*nlinesazout)
            call closedk(lun,fdsc3)
         end if

         t1=secnds(t0)
         write(MESSAGE,*)'Range processing elapsed time: ',t1,' sec'
         call write_out(ptStdWriter,MESSAGE)

         !!!!Include code for estamb - PSA
         do iamb=minamb,maxamb
            trans1 =  cmplx(0.,0.)
           !Restore transformed data - PSA
            do i=1,nnn
                do j=1,nlinesazout
                    trans1(i,j) = trans2(i,j)
                end do
            end do

            !!!!Perform mocomp
            nl = nlinesazout
            r = r01
            
            !!!Modify the constant doppler term
            fd1save = fd1 + iamb*prf1

            call mocomp(nnn,nlinesazout,irec,r,delr,ht1,rcurv,wavl,&
                 velin,fd1save,fdd1,fddd1,focuscorr,dim1_time,ilrl)

            write(MESSAGE,*) 'Amb = ', iamb, ' Doppler = ', fd1save
            call write_out(ptStdWriter, MESSAGE)


!c    transform lines in Azimuth
         
            !$omp parallel do shared(trans1,nlinesazout)
            do i=1,nlinesazout
               call cfft1d_jpl(nnn,trans1(1,i),-1)
            end do
            !$omp end parallel do

            t1=secnds(t0)
            write(MESSAGE,*) 'transformed lines ',t1, ' sec'
            call write_out(ptStdWriter,MESSAGE)

!c    start the range migration correction
            call RMpatch(nnn,nl,r,delr,wavl,fd1save,fdd1, &
                   fddd1,prf1,ideskew,velin,ht1,rcurv,focuscorr,azres, &
                   peg,elp,pln,ilrl, shift) !ML added shift

!c    multiply by reference and inverse transform lines
         
            t1=secnds(t0)
            write(MESSAGE,*) 'Inverse transforming lines ',t1, ' sec'
            call write_out(ptStdWriter,MESSAGE)

!c Inverse azimuth transform
            !$omp parallel do shared(trans1,nlinesazout)
            do i=1,nlinesazout
               call cfft1d_jpl(nnn,trans1(1,i),1)
            end do
            !$omp end parallel do
         
            t1=secnds(t0)
            write(MESSAGE,*)'patch finished, time =', t1, ' seconds.'
            call write_out(ptStdWriter,MESSAGE)

            !PSA - debugging
            !!!!Write a temporary file
            ! write(fname,'(I2)') iamb
            !fname = 'slc' // trim(adjustl(fname))
            !open(31,file=fname,access='direct',recl=8*nlinesazout,form='unformatted')
            !do i=1,na_valid
            !     write(31,rec=i)(trans1(i+ifs,j),j=1,nlinesazout)
            !end do
            !close(31)

            call compute_stats(trans1,nlinesazout,na_valid,ifs,&
                ampsum(iamb-minamb+1),ampsq(iamb-minamb+1),numsamp(iamb-minamb+1))
        end do                 !end ambiguity
      end do                    !end patch loop

      do iamb=minamb,maxamb
         call compute_entropy(ampsum(iamb-minamb+1), ampsq(iamb-minamb+1),&
             numsamp(iamb-minamb+1),entropy(iamb-minamb+1))
      end do
      t1=secnds(t0)
      write(MESSAGE,*)'Elapsed time =', t1, ' seconds.'
      call write_out(ptStdWriter,MESSAGE)

      entr = entropy(1)
      iamb = minamb

      write(MESSAGE,*)'     Ambiguity        Entropy'
      call write_out(ptStdWriter, MESSAGE)

      write(MESSAGE,*)'**********************************'
      call write_out(ptStdWriter, MESSAGE)

      do i=minamb,maxamb
      write(MESSAGE,*) i,'      ', entropy(i-minamb+1)
      call write_out(ptStdWriter, MESSAGE)

        if(entropy(i-minamb+1).gt.entr)then
            iamb=i
            entr= entropy(i-minamb+1)
        end if
      end do

      write(MESSAGE,*)'***********************************'
      call write_out(ptStdWriter, MESSAGE)

      write(MESSAGE,*)'Estimated ambiguity: ', iamb
      call write_out(ptStdWriter, MESSAGE)

      !destroy the plans. the array is just a place holder
      call cfft1d_jpl(nnn,trans1(1,1),2)
      call cfft1d_jpl(ranfft,ref1,2)
      
      deallocate(ref1)
      deallocate(trans1)
      deallocate(trans2)
      deallocate(schMoc)
      deallocate(vschMoc)
      deallocate(timeMoc)
      deallocate(phasegrad)
      deallocate(ampsum)
      deallocate(ampsq)
      deallocate(numsamp)
      
      
      end
      subroutine radopp(fd, fdd, fddd, r, del)

      real*8    fd, fdd, fddd, r, del, temp1, temp2, temp3

      temp1 = fd - fdd * (r/del) + fddd * (r/del)**2
      temp2 = fdd/del - 2.d0 * fddd*(r/del)/del
      temp3 = fddd / del**2

      fd   = temp1
      fdd  = temp2
      fddd = temp3

      return
      end

      subroutine compute_stats(trans, nlinesaz, na_valid, ifs, psum, sumsq, nsum)
          implicit none
          integer nlinesaz, na_valid, ifs
          double precision entr, temp, nsum
          complex*8, dimension(na_valid+ifs,nlinesaz) :: trans
          double precision  psum, sumsq, pwr
          integer i,j

!          psum = 0.
!          sumsq = 0.
!          nsum = 0

          do i=nlinesaz/8, nlinesaz*7/8
            do j=1,na_valid
                pwr = cabs(trans(ifs+j,i))**2
                psum = psum + pwr
                sumsq = sumsq + pwr**2
                nsum = nsum + 1
            end do
         end do
!!         write(*,*)'Ampsum = ', psum
!!         write(*,*)'Sq sum = ', sumsq
!!         write(*,*)'Num samp = ', nsum

      end

      subroutine compute_entropy(psum, sumsq, nsum, entr)
         implicit none
         double precision  psum, sumsq, entr, temp, nsum

!!         write(*,*)'Ampsum = ', psum
!!         write(*,*)'Sq sum = ', sumsq
!!         write(*,*)'Num samp = ', nsum
         temp = (sumsq/nsum)-(psum/nsum)**2
         entr = temp*nsum*nsum/(psum*psum)
      end
