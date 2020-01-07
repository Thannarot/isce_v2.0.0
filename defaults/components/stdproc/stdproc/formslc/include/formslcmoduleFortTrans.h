//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Copyright: 2010 to the present, California Institute of Technology.
// ALL RIGHTS RESERVED. United States Government Sponsorship acknowledged.
// Any commercial use must be negotiated with the Office of Technology Transfer
// at the California Institute of Technology.
// 
// This software may be subject to U.S. export control laws. By accepting this
// software, the user agrees to comply with all applicable U.S. export laws and
// regulations. User has the responsibility to obtain export licenses,  or other
// export authority as may be required before exporting such information to
// foreign countries or providing access to foreign persons.
// 
// Installation and use of this software is restricted by a license agreement
// between the licensee and the California Institute of Technology. It is the
// User's responsibility to abide by the terms of the license agreement.
//
// Author: Giangi Sacco
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~





#ifndef formslcmoduleFortTrans_h
#define formslcmoduleFortTrans_h

	#if defined(NEEDS_F77_TRANSLATION)

		#if defined(F77EXTERNS_LOWERCASE_TRAILINGBAR)
                        #define setStdWriter_f setstdwriter_
			#define allocate_dopplerCoefficients_f allocate_dopplercoefficients_
			#define allocate_sch_f allocate_sch_
                        #define allocate_vsch_f allocate_vsch_
			#define allocate_time_f allocate_time_
			#define deallocate_dopplerCoefficients_f deallocate_dopplercoefficients_
			#define deallocate_sch_f deallocate_sch_
			#define deallocate_vsch_f deallocate_vsch_
			#define deallocate_time_f deallocate_time_
			#define formslc_f formslc_
			#define getMocompIndex_f getmocompindex_
			#define getMocompPosition_f getmocompposition_
			#define getMocompPositionSize_f getmocomppositionsize_
			#define setAzimuthPatchSize_f setazimuthpatchsize_
			#define setAzimuthResolution_f setazimuthresolution_
			#define setBodyFixedVelocity_f setbodyfixedvelocity_
			#define setCaltoneLocation_f setcaltonelocation_
			#define setChirpSlope_f setchirpslope_
			#define setDebugFlag_f setdebugflag_
			#define setDeskewFlag_f setdeskewflag_
			#define setDopplerCentroidCoefficients_f setdopplercentroidcoefficients_
                        #define setEllipsoid_f setellipsoid_
			#define setFirstLine_f setfirstline_
			#define setFirstSample_f setfirstsample_
			#define setIMMocomp_f setimmocomp_
			#define setIMRC1_f setimrc1_
			#define setIMRCAS1_f setimrcas1_
			#define setIMRCRM1_f setimrcrm1_
			#define setInPhaseValue_f setinphasevalue_
			#define setIQFlip_f setiqflip_
			#define setNumberAzimuthLooks_f setnumberazimuthlooks_
			#define setNumberBytesPerLine_f setnumberbytesperline_
			#define setNumberGoodBytes_f setnumbergoodbytes_
			#define setNumberPatches_f setnumberpatches_
			#define setNumberRangeBin_f setnumberrangebin_
			#define setNumberValidPulses_f setnumbervalidpulses_
			#define setOverlap_f setoverlap_
			#define setPlanetLocalRadius_f setplanetlocalradius_
			#define setPosition_f setposition_
			#define setVelocity_f setvelocity_
                        #define setPegPoint_f setpegpoint_
                        #define setPlanet_f setplanet_
			#define setPRF_f setprf_
			#define setQuadratureValue_f setquadraturevalue_
			#define setRadarWavelength_f setradarwavelength_
			#define setRanfftiq_f setranfftiq_
			#define setRanfftov_f setranfftov_
			#define setRangeChirpExtensionPoints_f setrangechirpextensionpoints_
			#define setRangeFirstSample_f setrangefirstsample_
			#define setRangePulseDuration_f setrangepulseduration_
			#define setRangeSamplingRate_f setrangesamplingrate_
			#define setRangeSpectralWeighting_f setrangespectralweighting_
			#define setSecondaryRangeMigrationFlag_f setsecondaryrangemigrationflag_
			#define setSpacecraftHeight_f setspacecraftheight_
			#define setSpectralShiftFraction_f setspectralshiftfraction_
			#define setStartRangeBin_f setstartrangebin_
			#define setTime_f settime_
			#define setTransDat_f settransdat_
			#define setSlcWidth_f setslcwidth_
			#define getStartingRange_f getstartingrange_
			#define setStartingRange_f setstartingrange_
                        #define setLookSide_f setlookside_
                        #define setShift_f setshift_
		#else
			#error Unknown translation for FORTRAN external symbols
		#endif

	#endif

#endif formslcmoduleFortTrans_h
