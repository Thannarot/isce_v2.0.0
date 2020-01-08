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
# Author: Piyush Agram
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~




import sys
import isceobj
from contrib.Snaphu.Snaphu import Snaphu
from iscesys.Component.Component import Component
from isceobj.Constants import SPEED_OF_LIGHT


class snaphu(Component):
    '''Specific connector from an insarApp object to a Snaphu object.'''
    def __init__(self, obj):

        basename = obj.insar.topophaseFlatFilename
        self.wrapName = basename
        self.unwrapName = basename.replace('.flat', '.unw')

        self.wavelength = obj.insar.masterFrame.getInstrument().getRadarWavelength()
        self.width      = obj.insar.resampIntImage.width 
        self.costMode   = 'DEFO'
        self.initMethod = 'MST'
        self.earthRadius = obj.insar.peg.radiusOfCurvature 
        self.altitude   = obj.insar.averageHeight
        self.corrfile  = obj.insar.getCoherenceFilename()
        self.rangeLooks = obj.insar.topo.numberRangeLooks
        self.azimuthLooks = obj.insar.topo.numberAzimuthLooks

        azres = obj.insar.masterFrame.platform.antennaLength/2.0
        azfact = obj.insar.topo.numberAzimuthLooks *azres / obj.insar.topo.azimuthSpacing

        rBW = obj.insar.masterFrame.instrument.pulseLength * obj.insar.masterFrame.instrument.chirpSlope
        rgres = abs(SPEED_OF_LIGHT / (2.0 * rBW))
        rngfact = rgres/obj.insar.topo.slantRangePixelSpacing

        self.corrLooks = obj.insar.topo.numberRangeLooks * obj.insar.topo.numberAzimuthLooks/(azfact*rngfact) 
        self.maxComponents = 20
        self.defomax = 4.0

    def unwrap(self):
        snp = Snaphu()
        snp.setInput(self.wrapName)
        snp.setOutput(self.unwrapName)
        snp.setWidth(self.width)
        snp.setCostMode(self.costMode)
        snp.setEarthRadius(self.earthRadius)
        snp.setWavelength(self.wavelength)
        snp.setAltitude(self.altitude)
        snp.setCorrfile(self.corrfile)
        snp.setInitMethod(self.initMethod)
        snp.setCorrLooks(self.corrLooks)
        snp.setMaxComponents(self.maxComponents)
        snp.setDefoMaxCycles(self.defomax)
        snp.setRangeLooks(self.rangeLooks)
        snp.setAzimuthLooks(self.azimuthLooks)
        snp.prepare()
        snp.unwrap()

        ######Render XML
        outImage = isceobj.Image.createImage()
        outImage.setFilename(self.unwrapName)
        outImage.setWidth(self.width)
        outImage.bands = 2
        outImage.scheme = 'BIL'
        outImage.imageType='unw'
        outImage.dataType='FLOAT'
        outImage.setAccessMode('read')
        outImage.createImage()
        outImage.finalizeImage()
        outImage.renderHdr()
