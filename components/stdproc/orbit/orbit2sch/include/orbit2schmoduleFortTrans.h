//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// copyright: 2010 to the present, california institute of technology.
// all rights reserved. united states government sponsorship acknowledged.
// any commercial use must be negotiated with the office of technology transfer
// at the california institute of technology.
// 
// this software may be subject to u.s. export control laws. by accepting this
// software, the user agrees to comply with all applicable u.s. export laws and
// regulations. user has the responsibility to obtain export licenses,  or other
// export authority as may be required before exporting such information to
// foreign countries or providing access to foreign persons.
// 
// installation and use of this software is restricted by a license agreement
// between the licensee and the california institute of technology. it is the
// user's responsibility to abide by the terms of the license agreement.
//
// Author: Giangi Sacco
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~





#ifndef orbit2schmoduleFortTrans_h
#define orbit2schmoduleFortTrans_h

        #if defined(NEEDS_F77_TRANSLATION)

                #if defined(F77EXTERNS_LOWERCASE_TRAILINGBAR)
            #define setStdWriter_f setstdwriter_
                        #define allocate_asch_f allocate_asch_
                        #define allocate_sch_f allocate_sch_
                        #define allocate_vsch_f allocate_vsch_
                        #define allocate_vxyz_f allocate_vxyz_
                        #define allocate_xyz_f allocate_xyz_
                        #define deallocate_asch_f deallocate_asch_
                        #define deallocate_sch_f deallocate_sch_
                        #define deallocate_vsch_f deallocate_vsch_
                        #define deallocate_vxyz_f deallocate_vxyz_
                        #define deallocate_xyz_f deallocate_xyz_
                        #define getSchGravitationalAcceleration_f getschgravitationalacceleration_
                        #define getSchPosition_f getschposition_
                        #define getSchVelocity_f getschvelocity_
                        #define orbit2sch_f orbit2sch_
                        #define setAverageHeight_f setaverageheight_
                        #define setComputePegInfoFlag_f setcomputepeginfoflag_
                        #define setEllipsoidEccentricitySquared_f setellipsoideccentricitysquared_
                        #define setEllipsoidMajorSemiAxis_f setellipsoidmajorsemiaxis_
                        #define setOrbitPosition_f setorbitposition_
                        #define setOrbitVelocity_f setorbitvelocity_
                        #define setPegHeading_f setpegheading_
                        #define setPegLatitude_f setpeglatitude_
                        #define setPegLongitude_f setpeglongitude_
                        #define setPlanetGM_f setplanetgm_
                #else
                        #error Unknown translation for FORTRAN external symbols
                #endif

        #endif

#endif //orbit2schmoduleFortTrans_h
