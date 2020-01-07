//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//                                  Giangi Sacco
//                        NASA Jet Propulsion Laboratory
//                      California Institute of Technology
//                        (C) 2009  All Rights Reserved
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



#ifndef formslcmoduleFortTrans_h
#define formslcmoduleFortTrans_h

	#if defined(NEEDS_F77_TRANSLATION)

		#if defined(F77EXTERNS_LOWERCASE_TRAILINGBAR)
			#define allocate_dopplerCoefficients_f allocate_dopplercoefficients_
			#define allocate_linearResampCoeff_f allocate_linearresampcoeff_
			#define allocate_linearResampDeltas_f allocate_linearresampdeltas_
			#define allocate_r_platacc1_f allocate_r_platacc1_
			#define allocate_r_platvel1_f allocate_r_platvel1_
			#define allocate_spectralShiftFrac_f allocate_spectralshiftfrac_
			#define deallocate_dopplerCoefficients_f deallocate_dopplercoefficients_
			#define deallocate_linearResampCoeff_f deallocate_linearresampcoeff_
			#define deallocate_linearResampDeltas_f deallocate_linearresampdeltas_
			#define deallocate_r_platacc1_f deallocate_r_platacc1_
			#define deallocate_r_platvel1_f deallocate_r_platvel1_
			#define deallocate_spectralShiftFrac_f deallocate_spectralshiftfrac_
			#define formslc_f formslc_
			#define setAntennaSCHAcceleration_f setantennaschacceleration_
			#define setAntennaSCHVelocity_f setantennaschvelocity_
			#define setAzimuthPatchSize_f setazimuthpatchsize_
			#define setAzimuthResolution_f setazimuthresolution_
			#define setBodyFixedVelocity_f setbodyfixedvelocity_
			#define setCaltoneLocation_f setcaltonelocation_
			#define setChirpSlope_f setchirpslope_
			#define setDebugFlag_f setdebugflag_
			#define setDeskewFlag_f setdeskewflag_
			#define setDopplerCentroidCoefficients_f setdopplercentroidcoefficients_
			#define setFirstLine_f setfirstline_
			#define setFirstSample_f setfirstsample_
			#define setIQFlip_f setiqflip_
			#define setInPhaseValue_f setinphasevalue_
			#define setLinearResamplingCoefficiets_f setlinearresamplingcoefficiets_
			#define setLinearResamplingDeltas_f setlinearresamplingdeltas_
			#define setNumberAzimuthLooks_f setnumberazimuthlooks_
			#define setNumberBytesPerLine_f setnumberbytesperline_
			#define setNumberGoodBytes_f setnumbergoodbytes_
			#define setNumberPatches_f setnumberpatches_
			#define setNumberRangeBin_f setnumberrangebin_
			#define setNumberValidPulses_f setnumbervalidpulses_
			#define setPRF_f setprf_
			#define setPlanetGravitationalConstant_f setplanetgravitationalconstant_
			#define setPlanetRadiusOfCurvature_f setplanetradiusofcurvature_
			#define setPointingDirection_f setpointingdirection_
			#define setQuadratureValue_f setquadraturevalue_
			#define setRadarWavelength_f setradarwavelength_
			#define setRangeChirpExtensionPoints_f setrangechirpextensionpoints_
			#define setRangeFirstSample_f setrangefirstsample_
			#define setRangePulseDuration_f setrangepulseduration_
			#define setRangeSamplingRate_f setrangesamplingrate_
			#define setRangeSpectralWeighting_f setrangespectralweighting_
			#define setSecondaryRangeMigrationFlag_f setsecondaryrangemigrationflag_
			#define setSpacecraftHeight_f setspacecraftheight_
			#define setSpectralShiftFractions_f setspectralshiftfractions_
			#define setStartRangeBin_f setstartrangebin_
		#elif defined(F77EXTERNS_NOTRAILINGBAR)
			#define allocate_dopplerCoefficients_f allocate_dopplerCoefficients
			#define allocate_linearResampCoeff_f allocate_linearResampCoeff
			#define allocate_linearResampDeltas_f allocate_linearResampDeltas
			#define allocate_r_platacc1_f allocate_r_platacc1
			#define allocate_r_platvel1_f allocate_r_platvel1
			#define allocate_spectralShiftFrac_f allocate_spectralShiftFrac
			#define deallocate_dopplerCoefficients_f deallocate_dopplerCoefficients
			#define deallocate_linearResampCoeff_f deallocate_linearResampCoeff
			#define deallocate_linearResampDeltas_f deallocate_linearResampDeltas
			#define deallocate_r_platacc1_f deallocate_r_platacc1
			#define deallocate_r_platvel1_f deallocate_r_platvel1
			#define deallocate_spectralShiftFrac_f deallocate_spectralShiftFrac
			#define formslc_f formslc
			#define setAntennaSCHAcceleration_f setAntennaSCHAcceleration
			#define setAntennaSCHVelocity_f setAntennaSCHVelocity
			#define setAzimuthPatchSize_f setAzimuthPatchSize
			#define setAzimuthResolution_f setAzimuthResolution
			#define setBodyFixedVelocity_f setBodyFixedVelocity
			#define setCaltoneLocation_f setCaltoneLocation
			#define setChirpSlope_f setChirpSlope
			#define setDebugFlag_f setDebugFlag
			#define setDeskewFlag_f setDeskewFlag
			#define setDopplerCentroidCoefficients_f setDopplerCentroidCoefficients
			#define setFirstLine_f setFirstLine
			#define setFirstSample_f setFirstSample
			#define setIQFlip_f setIQFlip
			#define setInPhaseValue_f setInPhaseValue
			#define setLinearResamplingCoefficiets_f setLinearResamplingCoefficiets
			#define setLinearResamplingDeltas_f setLinearResamplingDeltas
			#define setNumberAzimuthLooks_f setNumberAzimuthLooks
			#define setNumberBytesPerLine_f setNumberBytesPerLine
			#define setNumberGoodBytes_f setNumberGoodBytes
			#define setNumberPatches_f setNumberPatches
			#define setNumberRangeBin_f setNumberRangeBin
			#define setNumberValidPulses_f setNumberValidPulses
			#define setPRF_f setPRF
			#define setPlanetGravitationalConstant_f setPlanetGravitationalConstant
			#define setPlanetRadiusOfCurvature_f setPlanetRadiusOfCurvature
			#define setPointingDirection_f setPointingDirection
			#define setQuadratureValue_f setQuadratureValue
			#define setRadarWavelength_f setRadarWavelength
			#define setRangeChirpExtensionPoints_f setRangeChirpExtensionPoints
			#define setRangeFirstSample_f setRangeFirstSample
			#define setRangePulseDuration_f setRangePulseDuration
			#define setRangeSamplingRate_f setRangeSamplingRate
			#define setRangeSpectralWeighting_f setRangeSpectralWeighting
			#define setSecondaryRangeMigrationFlag_f setSecondaryRangeMigrationFlag
			#define setSpacecraftHeight_f setSpacecraftHeight
			#define setSpectralShiftFractions_f setSpectralShiftFractions
			#define setStartRangeBin_f setStartRangeBin
		#elif defined(F77EXTERNS_EXTRATRAILINGBAR)
			#define allocate_dopplerCoefficients_f allocate_dopplerCoefficients__
			#define allocate_linearResampCoeff_f allocate_linearResampCoeff__
			#define allocate_linearResampDeltas_f allocate_linearResampDeltas__
			#define allocate_r_platacc1_f allocate_r_platacc1__
			#define allocate_r_platvel1_f allocate_r_platvel1__
			#define allocate_spectralShiftFrac_f allocate_spectralShiftFrac__
			#define deallocate_dopplerCoefficients_f deallocate_dopplerCoefficients__
			#define deallocate_linearResampCoeff_f deallocate_linearResampCoeff__
			#define deallocate_linearResampDeltas_f deallocate_linearResampDeltas__
			#define deallocate_r_platacc1_f deallocate_r_platacc1__
			#define deallocate_r_platvel1_f deallocate_r_platvel1__
			#define deallocate_spectralShiftFrac_f deallocate_spectralShiftFrac__
			#define formslc_f formslc__
			#define setAntennaSCHAcceleration_f setAntennaSCHAcceleration__
			#define setAntennaSCHVelocity_f setAntennaSCHVelocity__
			#define setAzimuthPatchSize_f setAzimuthPatchSize__
			#define setAzimuthResolution_f setAzimuthResolution__
			#define setBodyFixedVelocity_f setBodyFixedVelocity__
			#define setCaltoneLocation_f setCaltoneLocation__
			#define setChirpSlope_f setChirpSlope__
			#define setDebugFlag_f setDebugFlag__
			#define setDeskewFlag_f setDeskewFlag__
			#define setDopplerCentroidCoefficients_f setDopplerCentroidCoefficients__
			#define setFirstLine_f setFirstLine__
			#define setFirstSample_f setFirstSample__
			#define setIQFlip_f setIQFlip__
			#define setInPhaseValue_f setInPhaseValue__
			#define setLinearResamplingCoefficiets_f setLinearResamplingCoefficiets__
			#define setLinearResamplingDeltas_f setLinearResamplingDeltas__
			#define setNumberAzimuthLooks_f setNumberAzimuthLooks__
			#define setNumberBytesPerLine_f setNumberBytesPerLine__
			#define setNumberGoodBytes_f setNumberGoodBytes__
			#define setNumberPatches_f setNumberPatches__
			#define setNumberRangeBin_f setNumberRangeBin__
			#define setNumberValidPulses_f setNumberValidPulses__
			#define setPRF_f setPRF__
			#define setPlanetGravitationalConstant_f setPlanetGravitationalConstant__
			#define setPlanetRadiusOfCurvature_f setPlanetRadiusOfCurvature__
			#define setPointingDirection_f setPointingDirection__
			#define setQuadratureValue_f setQuadratureValue__
			#define setRadarWavelength_f setRadarWavelength__
			#define setRangeChirpExtensionPoints_f setRangeChirpExtensionPoints__
			#define setRangeFirstSample_f setRangeFirstSample__
			#define setRangePulseDuration_f setRangePulseDuration__
			#define setRangeSamplingRate_f setRangeSamplingRate__
			#define setRangeSpectralWeighting_f setRangeSpectralWeighting__
			#define setSecondaryRangeMigrationFlag_f setSecondaryRangeMigrationFlag__
			#define setSpacecraftHeight_f setSpacecraftHeight__
			#define setSpectralShiftFractions_f setSpectralShiftFractions__
			#define setStartRangeBin_f setStartRangeBin__
		#elif defined(F77EXTERNS_UPPERCASE_NOTRAILINGBAR)
			#define allocate_dopplerCoefficients_f ALLOCATE_DOPPLERCOEFFICIENTS
			#define allocate_linearResampCoeff_f ALLOCATE_LINEARRESAMPCOEFF
			#define allocate_linearResampDeltas_f ALLOCATE_LINEARRESAMPDELTAS
			#define allocate_r_platacc1_f ALLOCATE_R_PLATACC1
			#define allocate_r_platvel1_f ALLOCATE_R_PLATVEL1
			#define allocate_spectralShiftFrac_f ALLOCATE_SPECTRALSHIFTFRAC
			#define deallocate_dopplerCoefficients_f DEALLOCATE_DOPPLERCOEFFICIENTS
			#define deallocate_linearResampCoeff_f DEALLOCATE_LINEARRESAMPCOEFF
			#define deallocate_linearResampDeltas_f DEALLOCATE_LINEARRESAMPDELTAS
			#define deallocate_r_platacc1_f DEALLOCATE_R_PLATACC1
			#define deallocate_r_platvel1_f DEALLOCATE_R_PLATVEL1
			#define deallocate_spectralShiftFrac_f DEALLOCATE_SPECTRALSHIFTFRAC
			#define formslc_f FORMSLC
			#define setAntennaSCHAcceleration_f SETANTENNASCHACCELERATION
			#define setAntennaSCHVelocity_f SETANTENNASCHVELOCITY
			#define setAzimuthPatchSize_f SETAZIMUTHPATCHSIZE
			#define setAzimuthResolution_f SETAZIMUTHRESOLUTION
			#define setBodyFixedVelocity_f SETBODYFIXEDVELOCITY
			#define setCaltoneLocation_f SETCALTONELOCATION
			#define setChirpSlope_f SETCHIRPSLOPE
			#define setDebugFlag_f SETDEBUGFLAG
			#define setDeskewFlag_f SETDESKEWFLAG
			#define setDopplerCentroidCoefficients_f SETDOPPLERCENTROIDCOEFFICIENTS
			#define setFirstLine_f SETFIRSTLINE
			#define setFirstSample_f SETFIRSTSAMPLE
			#define setIQFlip_f SETIQFLIP
			#define setInPhaseValue_f SETINPHASEVALUE
			#define setLinearResamplingCoefficiets_f SETLINEARRESAMPLINGCOEFFICIETS
			#define setLinearResamplingDeltas_f SETLINEARRESAMPLINGDELTAS
			#define setNumberAzimuthLooks_f SETNUMBERAZIMUTHLOOKS
			#define setNumberBytesPerLine_f SETNUMBERBYTESPERLINE
			#define setNumberGoodBytes_f SETNUMBERGOODBYTES
			#define setNumberPatches_f SETNUMBERPATCHES
			#define setNumberRangeBin_f SETNUMBERRANGEBIN
			#define setNumberValidPulses_f SETNUMBERVALIDPULSES
			#define setPRF_f SETPRF
			#define setPlanetGravitationalConstant_f SETPLANETGRAVITATIONALCONSTANT
			#define setPlanetRadiusOfCurvature_f SETPLANETRADIUSOFCURVATURE
			#define setPointingDirection_f SETPOINTINGDIRECTION
			#define setQuadratureValue_f SETQUADRATUREVALUE
			#define setRadarWavelength_f SETRADARWAVELENGTH
			#define setRangeChirpExtensionPoints_f SETRANGECHIRPEXTENSIONPOINTS
			#define setRangeFirstSample_f SETRANGEFIRSTSAMPLE
			#define setRangePulseDuration_f SETRANGEPULSEDURATION
			#define setRangeSamplingRate_f SETRANGESAMPLINGRATE
			#define setRangeSpectralWeighting_f SETRANGESPECTRALWEIGHTING
			#define setSecondaryRangeMigrationFlag_f SETSECONDARYRANGEMIGRATIONFLAG
			#define setSpacecraftHeight_f SETSPACECRAFTHEIGHT
			#define setSpectralShiftFractions_f SETSPECTRALSHIFTFRACTIONS
			#define setStartRangeBin_f SETSTARTRANGEBIN
		#elif defined(F77EXTERNS_COMPAQ_F90)
			#define allocate_dopplerCoefficients_f allocate_dopplerCoefficients_
			#define allocate_linearResampCoeff_f allocate_linearResampCoeff_
			#define allocate_linearResampDeltas_f allocate_linearResampDeltas_
			#define allocate_r_platacc1_f allocate_r_platacc1_
			#define allocate_r_platvel1_f allocate_r_platvel1_
			#define allocate_spectralShiftFrac_f allocate_spectralShiftFrac_
			#define deallocate_dopplerCoefficients_f deallocate_dopplerCoefficients_
			#define deallocate_linearResampCoeff_f deallocate_linearResampCoeff_
			#define deallocate_linearResampDeltas_f deallocate_linearResampDeltas_
			#define deallocate_r_platacc1_f deallocate_r_platacc1_
			#define deallocate_r_platvel1_f deallocate_r_platvel1_
			#define deallocate_spectralShiftFrac_f deallocate_spectralShiftFrac_
			#define formslc_f formslc_
			#define setAntennaSCHAcceleration_f setAntennaSCHAcceleration_
			#define setAntennaSCHVelocity_f setAntennaSCHVelocity_
			#define setAzimuthPatchSize_f setAzimuthPatchSize_
			#define setAzimuthResolution_f setAzimuthResolution_
			#define setBodyFixedVelocity_f setBodyFixedVelocity_
			#define setCaltoneLocation_f setCaltoneLocation_
			#define setChirpSlope_f setChirpSlope_
			#define setDebugFlag_f setDebugFlag_
			#define setDeskewFlag_f setDeskewFlag_
			#define setDopplerCentroidCoefficients_f setDopplerCentroidCoefficients_
			#define setFirstLine_f setFirstLine_
			#define setFirstSample_f setFirstSample_
			#define setIQFlip_f setIQFlip_
			#define setInPhaseValue_f setInPhaseValue_
			#define setLinearResamplingCoefficiets_f setLinearResamplingCoefficiets_
			#define setLinearResamplingDeltas_f setLinearResamplingDeltas_
			#define setNumberAzimuthLooks_f setNumberAzimuthLooks_
			#define setNumberBytesPerLine_f setNumberBytesPerLine_
			#define setNumberGoodBytes_f setNumberGoodBytes_
			#define setNumberPatches_f setNumberPatches_
			#define setNumberRangeBin_f setNumberRangeBin_
			#define setNumberValidPulses_f setNumberValidPulses_
			#define setPRF_f setPRF_
			#define setPlanetGravitationalConstant_f setPlanetGravitationalConstant_
			#define setPlanetRadiusOfCurvature_f setPlanetRadiusOfCurvature_
			#define setPointingDirection_f setPointingDirection_
			#define setQuadratureValue_f setQuadratureValue_
			#define setRadarWavelength_f setRadarWavelength_
			#define setRangeChirpExtensionPoints_f setRangeChirpExtensionPoints_
			#define setRangeFirstSample_f setRangeFirstSample_
			#define setRangePulseDuration_f setRangePulseDuration_
			#define setRangeSamplingRate_f setRangeSamplingRate_
			#define setRangeSpectralWeighting_f setRangeSpectralWeighting_
			#define setSecondaryRangeMigrationFlag_f setSecondaryRangeMigrationFlag_
			#define setSpacecraftHeight_f setSpacecraftHeight_
			#define setSpectralShiftFractions_f setSpectralShiftFractions_
			#define setStartRangeBin_f setStartRangeBin_
		#else
			#error Unknown traslation for FORTRAN external symbols
		#endif

	#endif

#endif formslcmoduleFortTrans_h