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

from iscesys.ImageUtil.ImageUtil import ImageUtil as IU

logger = logging.getLogger('isce.insar.runFormSLCTSX')

def runFormSLC(self, patchSize=None, goodLines=None, numPatches=None):
    #NOTE tested the formslc() as a stand alone by passing the same inputs
    #computed in Howard terraSAR.py. The differences here arises from the
    #differences in the orbits when using the same orbits the results are very
    #close jng this will make the second term in coarseAz in offsetprf equal
    #zero. we do so since for tsx there is no such a term. Need to ask
    #confirmation
    self.insar.setPatchSize(self.insar.numberValidPulses)
    # the below value is zero because of we just did above, but just want to be
    #  explicit in the definition of is_mocomp
    self.is_mocomp = self.insar.get_is_mocomp

    v = self.insar.procVelocity
    h = self.insar.averageHeight
    imageSlc1 =  self.insar.masterRawImage
    imSlc1 = isceobj.createSlcImage()
    IU.copyAttributes(imageSlc1, imSlc1)
    imSlc1.setAccessMode('read')
    imSlc1.createImage()
    formSlc1 = stdproc.createFormSLC(self.sensorName)

    formSlc1.setBodyFixedVelocity(v)
    formSlc1.setSpacecraftHeight(h)
    formSlc1.wireInputPort(name='doppler',
                           object = self.insar.dopplerCentroid)
    formSlc1.wireInputPort(name='peg', object=self.insar.peg)
    formSlc1.wireInputPort(name='frame', object=self.insar.masterFrame)
    formSlc1.wireInputPort(name='orbit', object=self.insar.masterOrbit)
    formSlc1.wireInputPort(name='slcInImage', object=imSlc1)
    formSlc1.wireInputPort(name='planet',
        object=self.insar.masterFrame.instrument.platform.planet)
    self._stdWriter.setFileTag("formslcTSX", "log")
    self._stdWriter.setFileTag("formslcTSX", "err")
    self._stdWriter.setFileTag("formslcTSX", "out")
    formSlc1.setStdWriter(self._stdWriter)
    formSlc1.setLookSide(self.insar._lookSide)


#    self.insar.setMasterSlcImage(formSlc1.formslc())
    self.insar.masterSlcImage = formSlc1()

    imageSlc2 =  self.insar.slaveRawImage
    imSlc2 = isceobj.createSlcImage()
    IU.copyAttributes(imageSlc2, imSlc2)
    imSlc2.setAccessMode('read')
    imSlc2.createImage()
    formSlc2 = stdproc.createFormSLC(self.sensorName)

    formSlc2.setBodyFixedVelocity(v)
    formSlc2.setSpacecraftHeight(h)
    formSlc2.wireInputPort(name='doppler',
                           object=self.insar.dopplerCentroid)
    formSlc2.wireInputPort(name='peg', object=self.insar.peg)
    formSlc2.wireInputPort(name='frame', object=self.insar.slaveFrame)
    formSlc2.wireInputPort(name='orbit', object=self.insar.slaveOrbit)
    formSlc2.wireInputPort(name='slcInImage', object=imSlc2)
    formSlc2.wireInputPort(name='planet',
        object=self.insar.slaveFrame.instrument.platform.planet)

    self._stdWriter.setFileTag("formslcTSX", "log")
    self._stdWriter.setFileTag("formslcTSX", "err")
    self._stdWriter.setFileTag("formslcTSX", "out")
    formSlc2.setStdWriter(self._stdWriter)
    formSlc2.setLookSide(self.insar._lookSide)
#    self.insar.setSlaveSlcImage(formSlc2.formslc())
    self.insar.slaveSlcImage = formSlc2()
    self.insar.setNumberPatches(
        imSlc1.getLength()/float(self.insar.numberValidPulses)
        )
    imSlc1.finalizeImage()
    imSlc2.finalizeImage()
    self.insar.setFormSLC1(formSlc1)
    self.insar.setFormSLC2(formSlc2)
