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
# Author: Pietro Milillo
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



# Comment: Adapted from InsarProc/runRgoffsetprf.py
import logging
import isceobj
import mroipac

from iscesys.ImageUtil.ImageUtil import ImageUtil as IU
from mroipac.ampcor.Ampcor import Ampcor
from isceobj import Constants as CN

logger = logging.getLogger('isce.insar.runRgoffset')

def runRgoffset(self):
    numLocationAcross =  self._insar.getNumberLocationAcrossPrf()
    numLocationDown =  self._insar.getNumberLocationDownPrf()
    firstAc = self._insar.getFirstSampleAcrossPrf()
    firstDown = self._insar.getFirstSampleDownPrf()
  
    #Fake amplitude image as a complex image
    imageAmp = self._insar.getResampAmpImage()
    objAmp = isceobj.createImage()
    objAmp.setAccessMode('read')
    objAmp.dataType = 'CFLOAT'
    objAmp.bands = 1
    objAmp.setFilename(imageAmp.filename)
    objAmp.setWidth(imageAmp.width)
    objAmp.createImage()
    widthAmp = objAmp.getWidth()
    intLength = objAmp.getLength()

    imageSim = self._insar.getSimAmpImage()
    objSim = isceobj.createImage()
    objSim.setFilename(imageSim.filename)
    objSim.setWidth(imageSim.width)
    objSim.dataType='FLOAT'
    objSim.setAccessMode('read')
    objSim.createImage()
  
    simWidth = imageSim.getWidth()
    simLength = imageSim.getLength()
    fs1 = self._insar.getMasterFrame().getInstrument().getRangeSamplingRate()  ##check
    delRg1 = CN.SPEED_OF_LIGHT / (2*fs1)                                          ## if it's correct
  
    objAmpcor = Ampcor(name='insarapp_intsim_ampcor')
    objAmpcor.configure()
    objAmpcor.setImageDataType1('real')
    objAmpcor.setImageDataType2('mag')

    ####Adjust first and last values using window sizes
    xMargin = 2*objAmpcor.searchWindowSizeWidth + objAmpcor.windowSizeWidth
    yMargin = 2*objAmpcor.searchWindowSizeHeight + objAmpcor.windowSizeHeight

    if not objAmpcor.acrossGrossOffset:
        coarseAcross = 0
    else:
        coarseAcross = objAmpcor.acrossGrossOffset

    if not objAmpcor.downGrossOffset:
        coarseDown = 0
    else:
        coarseDown = objAmpcor.downGrossOffset

    offAc = max(firstAc, -coarseAcross) + xMargin + 1
    offDn = max(firstDown, -coarseDown) + yMargin + 1
    lastAc = int(min(widthAmp, simWidth-offAc) - xMargin -1)
    lastDn = int(min(intLength, simLength-offDn) - yMargin -1)

    if not objAmpcor.firstSampleAcross:
        objAmpcor.setFirstSampleAcross(offAc)

    if not objAmpcor.lastSampleAcross:
        objAmpcor.setLastSampleAcross(lastAc)

    if not objAmpcor.numberLocationAcross:
        objAmpcor.setNumberLocationAcross(numLocationAcross)

    if not objAmpcor.firstSampleDown:
        objAmpcor.setFirstSampleDown(offDn)

    if not objAmpcor.lastSampleDown:
        objAmpcor.setLastSampleDown(lastDn)

    if not objAmpcor.numberLocationDown:
        objAmpcor.setNumberLocationDown(numLocationDown)

    #set the tag used in the outfile. each message is precided by this tag
    #is the writer is not of "file" type the call has no effect
    self._stdWriter.setFileTag("rgoffset", "log")
    self._stdWriter.setFileTag("rgoffset", "err")
    self._stdWriter.setFileTag("rgoffset", "out")
    objAmpcor.setStdWriter(self._stdWriter)
    prf = self._insar.getMasterFrame().getInstrument().getPulseRepetitionFrequency()
    
    
    objAmpcor.setFirstPRF(prf)
    objAmpcor.setSecondPRF(prf)
    
    if not objAmpcor.acrossGrossOffset:
        objAmpcor.setAcrossGrossOffset(coarseAcross)

    if not objAmpcor.downGrossOffset:
        objAmpcor.setDownGrossOffset(coarseDown)

    objAmpcor.setFirstRangeSpacing(delRg1)
    objAmpcor.setSecondRangeSpacing(delRg1)
    
    objAmpcor.ampcor(objSim,objAmp)
    
    # Record the inputs and outputs
    from isceobj.Catalog import recordInputsAndOutputs
    recordInputsAndOutputs(self._insar.procDoc, objAmpcor, "runRgoffset_ampcor", \
                  logger, "runRgoffset_ampcor")

    self._insar.setOffsetField(objAmpcor.getOffsetField())
    self._insar.setRefinedOffsetField(objAmpcor.getOffsetField())
   
    objAmp.finalizeImage()
    objSim.finalizeImage()
