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



# Comment: Adapted from InsarProc/runTopo.py
import os
import isceobj
import stdproc
from iscesys.ImageUtil.ImageUtil import ImageUtil as IU

import logging
logger = logging.getLogger('isce.isceProc.runTopo')

def runTopo(self):
    v, h = self._isce.vh()
    if self._isce.is_mocomp is None:
        self._isce.is_mocomp = self._isce.get_is_mocomp()

    infos = {}
    for attribute in ['dopplerCentroid', 'peg', 'demImage', 'numberRangeLooks', 'numberAzimuthLooks', 'topophaseIterations', 'is_mocomp', 'heightSchFilename', 'heightFilename', 'latFilename', 'lonFilename', 'losFilename', 'lookSide']:
        infos[attribute] = getattr(self._isce, attribute)

    stdWriter = self._stdWriter

    refScene = self._isce.refScene
    refPol = self._isce.refPol
    imgSlc1 = self._isce.slcImages[refScene][refPol]
    infos['intWidth'] = int(imgSlc1.getWidth() / infos ['numberRangeLooks'])
    infos['intLength'] = int(imgSlc1.getLength() / infos['numberAzimuthLooks'])
    objFormSlc1  =  self._isce.formSLCs[refScene][refPol]
    frame1 = self._isce.frames[refScene][refPol]
    infos['outputPath'] = os.path.join(self.getoutputdir(refScene), refScene)
    catalog = isceobj.Catalog.createCatalog(self._isce.procDoc.name)
    sid = self._isce.formatname(refScene)

    refPair = self._isce.selectedPairs[0]#ML 2014-09-26
    topoIntImage = self._isce.topoIntImages[refPair][refPol]
    intImage = isceobj.createIntImage()
    IU.copyAttributes(topoIntImage, intImage)
    intImage.setAccessMode('read')

    objTopo = run(objFormSlc1, intImage, frame1, v, h, infos, stdWriter, catalog=catalog, sceneid=sid)
    self._isce.topo = objTopo



def run(objFormSlc1, intImage, frame1, velocity, height, infos, stdWriter, catalog=None, sceneid='NO_ID'):
    logger.info("Running Topo: %s" % sceneid)

    demImage = infos['demImage']
    objDem = isceobj.createDemImage()
    IU.copyAttributes(demImage, objDem)

    posIndx = 1
    mocompPosition1 = objFormSlc1.getMocompPosition()

    planet = frame1.getInstrument().getPlatform().getPlanet()
    prf1 = frame1.getInstrument().getPulseRepetitionFrequency()

    centroid = infos['dopplerCentroid'].getDopplerCoefficients(inHz=False)[0]

    objTopo = stdproc.createTopo()
    objTopo.wireInputPort(name='peg', object=infos['peg'])
    objTopo.wireInputPort(name='frame', object=frame1)
    objTopo.wireInputPort(name='planet', object=planet)
    objTopo.wireInputPort(name='dem', object=objDem)
    objTopo.wireInputPort(name='interferogram', object=intImage) #ML 2014-09-26
    objTopo.wireInputPort(name='masterslc', object=objFormSlc1) #Piyush
    objTopo.setDopplerCentroidConstantTerm(centroid)

    objTopo.setBodyFixedVelocity(velocity)
    objTopo.setSpacecraftHeight(height)

    objTopo.setReferenceOrbit(mocompPosition1[posIndx])

    #objTopo.setWidth(infos['intWidth']) #ML 2014-09-26
    #objTopo.setLength(infos['intLength']) #ML 2014-09-26

    # Options
    objTopo.setNumberRangeLooks(infos['numberRangeLooks'])
    objTopo.setNumberAzimuthLooks(infos['numberAzimuthLooks'])
    objTopo.setNumberIterations(infos['topophaseIterations'])
    objTopo.setHeightSchFilename(infos['outputPath'] + '.' + infos['heightSchFilename']) #sch height file
    # KK 2013-12-12: added output paths to real height, latitude, longitude and los files
    objTopo.setHeightRFilename(infos['outputPath'] + '.' + infos['heightFilename'])
    objTopo.setLatFilename(infos['outputPath'] + '.' + infos['latFilename'])
    objTopo.setLonFilename(infos['outputPath'] + '.' + infos['lonFilename'])
    objTopo.setLosFilename(infos['outputPath'] + '.' + infos['losFilename'])
    # KK

    objTopo.setISMocomp(infos['is_mocomp'])
    objTopo.setLookSide(infos['lookSide'])
    #set the tag used in the outfile. each message is precided by this tag
    #is the writer is not of "file" type the call has no effect
    objTopo.stdWriter = stdWriter.set_file_tags("topo",
                                                "log",
                                                "err",
                                                "out")
    objTopo.topo()

    if catalog is not None:
        # Record the inputs and outputs
        isceobj.Catalog.recordInputsAndOutputs(catalog, objTopo,
                                               "runTopo.%s" % sceneid,
                                               logger,
                                               "runTopo.%s" % sceneid)

    return objTopo
