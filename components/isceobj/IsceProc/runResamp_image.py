#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# copyright: 2013 to the present, california institute of technology.
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
# Authors: Kosal Khun, Marco Lavalle
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



# Comment: Adapted from InsarProc/runResamp_image.py
import os
import logging
import isceobj
import stdproc

from iscesys.ImageUtil.ImageUtil import ImageUtil as IU

logger = logging.getLogger('isce.isceProc.runResamp_image')

def runResamp_image(self):
    refPol = self._isce.refPol
    stdWriter = self._stdWriter
    dopplerCentroid = self._isce.dopplerCentroid
    looks = self._isce.numberLooks
    numFitCoeff = self._isce.numberFitCoefficients
    offsetImageName = self._isce.offsetImageName
    pixelSpacing = self._isce.slantRangePixelSpacing
    lines = self._isce.numberResampLines
    for sceneid1, sceneid2 in self._isce.pairsToCoreg:
        pair = (sceneid1, sceneid2)
        imageSlc1 = self._isce.slcImages[sceneid1][refPol]
        frame1 = self._isce.frames[sceneid1][refPol]
        instrument = frame1.getInstrument()
        offsetField = self._isce.refinedOffsetFields[pair] #offsetField is the same for all pols
        imageSlc2 = self._isce.slcImages[sceneid2][refPol]
        catalog = isceobj.Catalog.createCatalog(self._isce.procDoc.name)
        sid = self._isce.formatname(pair)
        offsetFilename = os.path.join(self.getoutputdir(sceneid1, sceneid2), self._isce.formatname(pair, ext=offsetImageName))
        imageAz, imageRn = run(imageSlc1, imageSlc2, offsetField, instrument, dopplerCentroid, looks, lines, numFitCoeff, pixelSpacing, offsetFilename, stdWriter, catalog=catalog, sceneid=sid)
        self._isce.offsetAzimuthImages[pair] = imageAz
        self._isce.offsetRangeImages[pair] = imageRn


def run(imageSlc1, imageSlc2, offsetField, instrument, dopplerCentroid, looks, lines, numFitCoeff, pixelSpacing, offsetFilename, stdWriter, catalog=None, sceneid='NO_ID'):
    widthSlc = max(imageSlc1.getWidth(), imageSlc2.getWidth())
    dopplerCoeff = dopplerCentroid.getDopplerCoefficients(inHz=False)

    path, filename = os.path.split(offsetFilename)
    offsetAz = os.path.join(path, 'azimuth_' + filename)
    offsetRn = os.path.join(path, 'range_' + filename)
    widthOffset = int(widthSlc / looks)
    imageAz = isceobj.createOffsetImage()
    imageAz.setFilename(offsetAz)
    imageAz.setWidth(widthOffset)
    imageRn = isceobj.createOffsetImage()
    imageRn.setFilename(offsetRn)
    imageRn.setWidth(widthOffset)


    objAz = isceobj.createOffsetImage()
    objRn = isceobj.createOffsetImage()
    IU.copyAttributes(imageAz, objAz)
    IU.copyAttributes(imageRn, objRn)
    objAz.setAccessMode('write')
    objAz.createImage()
    objRn.setAccessMode('write')
    objRn.createImage()


    objResamp_image = stdproc.createResamp_image()
    objResamp_image.wireInputPort(name='offsets', object=offsetField)
    objResamp_image.wireInputPort(name='instrument', object=instrument)
    objResamp_image.setSlantRangePixelSpacing(pixelSpacing)
    objResamp_image.setDopplerCentroidCoefficients(dopplerCoeff)
    objResamp_image.setNumberLooks(looks)
    objResamp_image.setNumberLines(lines)
    objResamp_image.setNumberRangeBin(widthSlc)
    objResamp_image.setNumberFitCoefficients(numFitCoeff)
    #set the tag used in the outfile. each message is precided by this tag
    #is the writer is not of "file" type the call has no effect
    objResamp_image.stdWriter = stdWriter.set_file_tags("resamp_image",
                                                        "log",
                                                        "err",
                                                        "out")

    objResamp_image.resamp_image(objRn, objAz)

    if catalog is not None:
        # Record the inputs and outputs
        isceobj.Catalog.recordInputsAndOutputs(catalog, objResamp_image,
                                               "runResamp_image.%s" % sceneid,
                                               logger,
                                               "runResamp_image.%s" % sceneid)

    objRn.finalizeImage()
    objAz.finalizeImage()

    return imageAz, imageRn
