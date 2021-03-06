#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# copyright: 2012 to the present, california institute of technology.
# all rights reserved. united states government sponsorship acknowledged.
# any commercial use must be negotiated with the office of technology transfer
# at the california institute of technology.
# 
# this software may be subject to u.s. export control laws. by accepting this
# software, the user agrees to comply with all applicable u.s. export laws and
# regulations. user has the responsibility to obtain export licenses,  or other
# export authority as may be required before exporting such information to
# foreign countries or providing access to foreign persons.
# 
# installation and use of this software is restricted by a license agreement
# between the licensee and the california institute of technology. it is the
# user's responsibility to abide by the terms of the license agreement.
#
# Author: Brett George
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



import logging
import stdproc
import isceobj

logger = logging.getLogger('isce.insar.runMocompbaseline')

# index of the position in the  mocompPosition array (the 0 element is the
# time)
posIndx = 1

def runMocompbaseline(self):
    logger.info("Calculating Baseline")
    ellipsoid = self._insar.getMasterFrame().getInstrument().getPlatform().getPlanet().get_elp()
    # schPositions computed in orbit2sch
    # objFormSlc's  created during formSlc

    h = self.insar.averageHeight
    objFormSlc1  =  self.insar.formSLC1
    objFormSlc2  =  self.insar.formSLC2
    mocompPosition1 = objFormSlc1.getMocompPosition()
    mocompIndex1 = objFormSlc1.getMocompIndex()
    mocompPosition2 = objFormSlc2.getMocompPosition()
    mocompIndex2 = objFormSlc2.getMocompIndex()

    objMocompbaseline = stdproc.createMocompbaseline()

    objMocompbaseline.setMocompPosition1(mocompPosition1[posIndx])
    objMocompbaseline.setMocompPositionIndex1(mocompIndex1)
    objMocompbaseline.setMocompPosition2(mocompPosition2[posIndx])
    objMocompbaseline.setMocompPositionIndex2(mocompIndex2)

    objMocompbaseline.wireInputPort(name='masterOrbit',
                                    object=self.insar.masterOrbit)
    objMocompbaseline.wireInputPort(name='slaveOrbit',
                                    object=self.insar.slaveOrbit)
    objMocompbaseline.wireInputPort(name='ellipsoid', object=ellipsoid)
    objMocompbaseline.wireInputPort(name='peg', object=self.insar.peg)
    objMocompbaseline.setHeight(h)

    #set the tag used in the outfile. each message is precided by this tag
    #is the writer is not of "file" type the call has no effect
    self._stdWriter.setFileTag("mocompbaseline", "log")
    self._stdWriter.setFileTag("mocompbaseline", "err")
    self._stdWriter.setFileTag("mocompbaseline", "out")
    objMocompbaseline.setStdWriter(self._stdWriter)

    objMocompbaseline.mocompbaseline()

    # Record the inputs and outputs
    from isceobj.Catalog import recordInputsAndOutputs
    recordInputsAndOutputs(self._insar.procDoc, objMocompbaseline,
                           "runMocompbaseline",
                           logger, "runMocompbaseline")

    self.insar.mocompBaseline = objMocompbaseline
    return None
