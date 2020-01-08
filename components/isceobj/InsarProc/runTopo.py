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
# Author: Giangi Sacco
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



import isceobj
import stdproc
from iscesys.ImageUtil.ImageUtil import ImageUtil as IU
from isceobj.Util.Polynomial import Polynomial
from isceobj.Util.Poly2D import Poly2D
from contrib.demUtils.SWBDStitcher import SWBDStitcher

import logging
logger = logging.getLogger('isce.insar.runTopo') 

def runTopo(self):
    logger.info("Running topo")


    objMocompbaseline = self.insar.mocompBaseline
    objFormSlc1  =  self.insar.formSLC1

    #objDem = isceobj.createDemImage()
    #demImage = self.insar.demImage

    #IU.copyAttributes(demImage, objDem)
    objDem = self.insar.demImage.clone()

    topoIntImage = self._insar.getTopoIntImage()
    #intImage = isceobj.createIntImage()
    #IU.copyAttributes(topoIntImage, intImage)
    intImage = topoIntImage.clone()
    intImage.setAccessMode('read')

    posIndx = 1
    mocompPosition1 = objFormSlc1.getMocompPosition()



    planet = self.insar.masterFrame.getInstrument().getPlatform().getPlanet()
    prf1 = self.insar.masterFrame.getInstrument().getPulseRepetitionFrequency()
    
    objTopo = stdproc.createTopo()
    objTopo.wireInputPort(name='peg', object=self.insar.peg)
    objTopo.wireInputPort(name='frame', object=self.insar.masterFrame)
    objTopo.wireInputPort(name='planet', object=planet)
    objTopo.wireInputPort(name='dem', object=objDem)
    objTopo.wireInputPort(name='interferogram', object=intImage)
    objTopo.wireInputPort(name='masterslc', object = self.insar.formSLC1) #Piyush
    
    centroid = self.insar.dopplerCentroid.getDopplerCoefficients(inHz=False)[0]
    objTopo.setDopplerCentroidConstantTerm(centroid)

    v = self.insar.procVelocity
    h = self.insar.averageHeight


    objTopo.setBodyFixedVelocity(v)
    objTopo.setSpacecraftHeight(h)

    objTopo.setReferenceOrbit(mocompPosition1[posIndx]) 

    # Options
    objTopo.setNumberRangeLooks(self.insar.numberRangeLooks)
    objTopo.setNumberAzimuthLooks(self.insar.numberAzimuthLooks)
    objTopo.setNumberIterations(self.insar.topophaseIterations)
    objTopo.setHeightSchFilename(self.insar.heightSchFilename)
    objTopo.setHeightRFilename(self.insar.heightFilename)
    objTopo.setLatFilename(self.insar.latFilename)
    objTopo.setLonFilename(self.insar.lonFilename)
    objTopo.setLosFilename(self.insar.losFilename)

    if self.insar.is_mocomp is None:
        self.insar.get_is_mocomp()

    objTopo.setISMocomp(self.insar.is_mocomp)
    #set the tag used in the outfile. each message is precided by this tag
    #is the writer is not of "file" type the call has no effect
    objTopo.stdWriter = self._writer_set_file_tags("topo", "log",
                                                   "err", "out")
    objTopo.setLookSide(self.insar._lookSide)
    objTopo.topo()

    # Record the inputs and outputs
    from isceobj.Catalog import recordInputsAndOutputs
    recordInputsAndOutputs(self._insar.procDoc, objTopo, "runTopo",
                           logger, "runTopo")

    self._insar.setTopo(objTopo)
    if self.insar.applyWaterMask:
        sw = SWBDStitcher()
        sw.toRadar(self.insar.wbdImage.filename,self.insar.latFilename,
                   self.insar.lonFilename,self.insar.waterMaskImageName)

    return objTopo
