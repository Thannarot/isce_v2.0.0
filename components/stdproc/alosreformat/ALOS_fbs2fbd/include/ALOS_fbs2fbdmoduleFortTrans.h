//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// copyright: 2011 to the present, california institute of technology.
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





#ifndef ALOS_fbs2fbdmoduleFortTrans_h
#define ALOS_fbs2fbdmoduleFortTrans_h

        #if defined(NEEDS_F77_TRANSLATION)

                #if defined(F77EXTERNS_LOWERCASE_TRAILINGBAR)
                        #define ALOS_fbs2fbd_f alos_fbs2fbd_
                        #define setFirstSample_f setfirstsample_
                        #define setInPhaseValue_f setinphasevalue_
                        #define setNumberBytesPerLine_f setnumberbytesperline_
                        #define setNumberGoodBytes_f setnumbergoodbytes_
                        #define setNumberLines_f setnumberlines_
                        #define setQuadratureValue_f setquadraturevalue_
                #else
                        #error Unknown translation for FORTRAN external symbols
                #endif

        #endif

#endif //ALOS_fbs2fbdmoduleFortTrans_h
