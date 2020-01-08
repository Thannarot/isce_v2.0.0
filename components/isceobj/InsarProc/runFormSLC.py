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
import pickle
from isceobj.Util.decorators import use_api

logger = logging.getLogger('isce.insar.runFormSLC')

#Run FormSLC for master
def master(self, deltaf=None):
    from isceobj.Catalog import recordInputsAndOutputs
    from iscesys.ImageUtil.ImageUtil import ImageUtil as IU




    v,h = self.insar.vh()
   
    objRaw = self.insar.rawMasterIQImage.clone()
    objRaw.accessMode = 'read'
    objFormSlc = stdproc.createFormSLC(name='insarapp_formslc_master')
    objFormSlc.setBodyFixedVelocity(v)
    objFormSlc.setSpacecraftHeight(h)
    objFormSlc.setAzimuthPatchSize(self.patchSize)
    objFormSlc.setNumberValidPulses(self.goodLines)
    objFormSlc.setNumberPatches(self.numPatches)
    objFormSlc.setLookSide(self.insar._lookSide)
    objFormSlc.setNumberAzimuthLooks(self.insar.numberAzimuthLooks)
    logger.info("Focusing Master image")
    objFormSlc.stdWriter = self.stdWriter

    if (deltaf is not None) and (objFormSlc.azimuthResolution is None):
        ins = self.insar.masterFrame.getInstrument()
        prf = ins.getPulseRepetitionFrequency()
        res = ins.getPlatform().getAntennaLength() / 2.0
        azbw = min(v/res, prf)
        res = v/azbw 

        factor = 1.0 - (abs(deltaf)/azbw)
        logger.info('MASTER AZIMUTH BANDWIDTH FACTOR = %f'%(factor))
        azres = res / factor
        #jng This is a temporary solution seems it looks that same banding problem
        #can be resolved by doubling the azres. The default azResFactor  is still one.
        objFormSlc.setAzimuthResolution(azres*self.insar.azResFactor)
   
    ####newInputs
    objSlc = objFormSlc(rawImage=objRaw,
                orbit=self.insar.masterOrbit,
                frame=self.insar.masterFrame,
                planet=self.insar.masterFrame.instrument.platform.planet,
                doppler=self.insar.dopplerCentroid,
                peg=self.insar.peg)

    imageSlc = isceobj.createSlcImage()
    IU.copyAttributes(objSlc, imageSlc)
    imageSlc.setAccessMode('read')
    objSlc.finalizeImage()
    objRaw.finalizeImage()
    recordInputsAndOutputs(self.insar.procDoc, objFormSlc,
        "runFormSLC.master", logger, "runFormSLC.master")

    logger.info('New Width = %d'%(imageSlc.getWidth()))
    self.insar.masterSlcImage = imageSlc
    self.insar.formSLC1 = objFormSlc
    return objFormSlc.numberPatches

#Run FormSLC on slave
def slave(self, deltaf=None):
    from isceobj.Catalog import recordInputsAndOutputs
    from iscesys.ImageUtil.ImageUtil import ImageUtil as IU

    v,h = self.insar.vh()

    objRaw = self.insar.rawSlaveIQImage.clone()
    objRaw.accessMode = 'read'
    objFormSlc = stdproc.createFormSLC(name='insarapp_formslc_slave')
    objFormSlc.setBodyFixedVelocity(v)
    objFormSlc.setSpacecraftHeight(h)
    objFormSlc.setAzimuthPatchSize(self.patchSize)
    objFormSlc.setNumberValidPulses(self.goodLines)
    objFormSlc.setNumberPatches(self.numPatches)
    objFormSlc.setNumberAzimuthLooks(self.insar.numberAzimuthLooks)
    objFormSlc.setLookSide(self.insar._lookSide)
    logger.info("Focusing Master image")
    objFormSlc.stdWriter = self.stdWriter

    if (deltaf is not None) and (objFormSlc.azimuthResolution is None):
        ins = self.insar.slaveFrame.getInstrument()
        prf = ins.getPulseRepetitionFrequency()
        res = ins.getPlatform().getAntennaLength()/2.0
        azbw = min(v / res, prf)
        res = v / azbw
        factor = 1.0 - (abs(deltaf) / azbw)
        logger.info('SLAVE AZIMUTH BANDWIDTH FACTOR = %f'%(factor))
        azres = res/factor
        objFormSlc.setAzimuthResolution(azres)

    objSlc = objFormSlc(rawImage=objRaw,
                orbit=self.insar.slaveOrbit,
                frame=self.insar.slaveFrame,
                planet=self.insar.slaveFrame.instrument.platform.planet,
                doppler=self.insar.dopplerCentroid,
                peg=self.insar.peg)

    imageSlc = isceobj.createSlcImage()
    IU.copyAttributes(objSlc, imageSlc)
    imageSlc.setAccessMode('read')
    objSlc.finalizeImage()
    objRaw.finalizeImage()
    recordInputsAndOutputs(self.insar.procDoc, objFormSlc,
        "runFormSLC.slave", logger, "runFormSLC.slave")

    logger.info('New Width = %d'%(imageSlc.getWidth()))
    self.insar.slaveSlcImage = imageSlc
    self.insar.formSLC2 = objFormSlc
    return objFormSlc.numberPatches

@use_api
def runFormSLC(self):

    mDoppler = self.insar.masterDoppler.getDopplerCoefficients(inHz=True)
    sDoppler = self.insar.slaveDoppler.getDopplerCoefficients(inHz=True)
    deltaf = abs(mDoppler[0] - sDoppler[0])
    n_master = master(self, deltaf=deltaf)
    n_slave = slave(self, deltaf=deltaf)
    self.insar.setNumberPatches(min(n_master, n_slave))
    self.is_mocomp = int(
        (self.insar.formSLC1.azimuthPatchSize -
         self.insar.formSLC1.numberValidPulses)/2
        )
    self.insar.is_mocomp = self.is_mocomp
    self.insar.patchSize = self.insar.formSLC1.azimuthPatchSize
    self.insar.numberValidPulses = self.insar.formSLC1.numberValidPulses
    logger.info('Number of Valid Pulses = %d'%(self.insar.numberValidPulses))

    return None



###PSA - for testing
def wgs84_to_sch(orbit, peg, pegHavg, planet):
    '''
    Convert WGS84 orbits to SCH orbits and return it.
    '''
    import stdproc
    from iscesys.StdOEL.StdOELPy import create_writer
    import copy

    stdWriter = create_writer("log","",True,filename='orb.log')
    orbSch = stdproc.createOrbit2sch(averageHeight=pegHavg)
    orbSch.setStdWriter(stdWriter)
    orbSch(planet=planet, orbit=orbit, peg=peg)
    schOrigOrbit = copy.copy(orbSch.orbit)

    return schOrigOrbit
