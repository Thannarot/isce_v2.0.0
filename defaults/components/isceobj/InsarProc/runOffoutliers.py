#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Copyright: 2012 to the present, California Institute of Technology.
# ALL RIGHTS RESERVED. United States Government Sponsorship acknowledged.
# Any commercial use must be negotiated with the Office of Technology Transfer
# at the California Institute of Technology.
# 
# This software may be subject to U.S. export control laws. By accepting this
# software, the user agrees to comply with all applicable U.S. export laws and
# regulations. User has the responsibility to obtain export licenses,  or other
# export authority as may be required before exporting such information to
# foreign countries or providing access to foreign persons.
# 
# Installation and use of this software is restricted by a license agreement
# between the licensee and the California Institute of Technology. It is the
# User's responsibility to abide by the terms of the license agreement.
#
# Author: Brett George
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



import logging
import isceobj

logger = logging.getLogger('isce.insar.runOffoutliers') 

def runOffoutliers(self, distance, errorLimit=100):
    #offoutliers returns a list of modified locations 
    #the list of lists is
    #list[0] = location across
    #list[1] = location  across offset
    #list[2] = location down
    #list[3] = location  down offset
    #list[4] = snr
    #list[5] = sig 
    logger.info('Error limit = %d'%(errorLimit)) 
    warnLimit = errorLimit*3
    logger.info("Culling offset field outliers")
    rgOffsets = self._insar.getRefinedOffsetField()               
    logger.info('Number of input offsets: %d'%(len(rgOffsets._offsets)))
    logger.info('Distance: %f'%(distance))
    objOff = isceobj.createOffoutliers()
    objOff.wireInputPort(name='offsets', object=rgOffsets)
    objOff.setSNRThreshold(2.0)
    objOff.setDistance(distance)
    #set the tag used in the outfile. each message is precided by this tag
    #is the writer is not of "file" type the call has no effect
    self._stdWriter.setFileTag("offoutliers", "log")
    self._stdWriter.setFileTag("offoutliers", "err")
    self._stdWriter.setFileTag("offoutliers", "out")
    objOff.setStdWriter(self._stdWriter)

    objOff.offoutliers()

    # Record the inputs and outputs
    from isceobj.Catalog import recordInputsAndOutputs
    recordInputsAndOutputs(self._insar.procDoc, objOff, "runOffoutliers",
                  logger, "runOffoutliers")

    refinedOffsets = objOff.getRefinedOffsetField()
    lenOut = len(refinedOffsets._offsets)
    logger.info('Number of offsets left after culling: %d'%(lenOut))
    if lenOut < errorLimit:
        logger.error('Small number of output Offsets after culling: %d .\n Increase number of windows (or) window sizes (or) provide gross offset manually.'%(lenOut))
        raise Exception('Offset estimation Failed.')
    elif lenOut < warnLimit:
        logger.warn('Number of output offsets after culling are low: %d. Might be ok to continue.')

    self._insar.setRefinedOffsetField(refinedOffsets)
