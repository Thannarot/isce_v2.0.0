#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# copyright: 2011 to the present, california institute of technology.
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



from __future__ import print_function

from iscesys.Component.Component import Component,Port
from iscesys.Compatibility import Compatibility
from isceobj import Constants as CN
from stdproc.alosreformat.ALOS_fbs2fbd import ALOS_fbs2fbd

class ALOS_fbs2fbdPy(Component):

    def ALOS_fbs2fbd(self):
        for port in self.inputPorts:
            port()

        self.setState()
        ALOS_fbs2fbd.ALOS_fbs2fbd_Py()
        self.updateValues()
        return None

    def run(self):
        self.ALOS_fbs2fbd()

    def setState(self):
        ALOS_fbs2fbd.setNumberGoodBytes_Py(int(self.numberGoodBytes))
        ALOS_fbs2fbd.setNumberBytesPerLine_Py(int(self.numberBytesPerLine))
        ALOS_fbs2fbd.setNumberLines_Py(int(self.numberLines))
        ALOS_fbs2fbd.setFirstSample_Py(int(self.firstSample))
        ALOS_fbs2fbd.setInPhaseValue_Py(float(self.inPhaseValue))
        ALOS_fbs2fbd.setQuadratureValue_Py(float(self.quadratureValue))
        ALOS_fbs2fbd.setInputFilename_Py(str(self.inputFilename))
        ALOS_fbs2fbd.setOutputFilename_Py(str(self.outputFilename))
        return None

    ## TODO:fix harcoded values
    def updateValues(self):
        self.quadratureValue = 63.5
        self.inPhaseValue = 63.5
        self.rangeChirpExtensionPoints /= 2.0
        fbdsamp = int((self.numberGoodBytes/2 - self.firstSample)/2)
        self.numberGoodBytes = 2*(fbdsamp + self.firstSample)
        self.bytesPerLine = 2*(fbdsamp + self.firstSample)
        self.rangePulseDuration /= 2
        self.rangeSamplingRate /= 2
        self.rangePixelSize *=2
        halfLen = int(self.rangeSamplingRate * self.rangePulseDuration)//2
        self.rangeFirstSample = (
            self.rangeFirstSample -
            (halfLen*CN.SPEED_OF_LIGHT)/(2*self.rangeSamplingRate)
            )

    def updateFrame(self,frame):
        frame.getImage().setXmax(self.bytesPerLine)
        frame.getImage().setWidth(self.bytesPerLine)
        frame.getImage().setFilename(self.outputFilename)
        frame.setNumberOfSamples(self.bytesPerLine)
        frame.setStartingRange(self.rangeFirstSample)            
        instrument = frame.getInstrument()
        instrument.setInPhaseValue(self.inPhaseValue)
        instrument.setQuadratureValue(self.quadratureValue)
        instrument.setRangeSamplingRate(self.rangeSamplingRate)
        instrument.setPulseLength(self.rangePulseDuration)
        instrument.setRangePixelSize(self.rangePixelSize)

    def setRangePulseDuration(self,var):
        self.rangePulseDuration = float(var)

    def setRangeSamplingRate(self,var):
        self.rangeSamplingRate = float(var)
    
    def setRangeFirstSample(self,var):
        self.rangeFirstSample = float(var)

    def setRangeChirpExtensionPoints(self,var):
        self.rangeChirpExtensionPoints = float(var)
    
    def setNumberGoodBytes(self,var):
        self.numberGoodBytes = int(var)
        return None

    def setNumberBytesPerLine(self,var):
        self.numberBytesPerLine = int(var)
        return None

    def setNumberLines(self,var):
        self.numberLines = int(var)
        return None
    
    def setFirstSample(self,var):
        self.firstSample = int(var)
        return None

    def setInPhaseValue(self,var):
        self.inPhaseValue = float(var)
        return None

    def setQuadratureValue(self,var):
        self.quadratureValue = float(var)
        return None

    def setInputFilename(self,var):
        self.inputFilename = str(var)
        return None

    def setOutputFilename(self,var):
        self.outputFilename = str(var)
        return None
 
    def getRangePulseDuration(self):
        return self.rangePulseDuration

    def getRangeSamplingRate(self):
        return self.rangeSamplingRate
    
    def getRangeFirstSample(self):
        return self.rangeFirstSample

    def getRangeChirpExtensionPoints(self):
        return self.rangeChirpExtensionPoints
    
    def getNumberGoodBytes(self):
        return self.numberGoodBytes

    def getNumberBytesPerLine(self):
        return self.numberBytesPerLine

    def getInPhaseValue(self):
        return self.inPhaseValue

    def getQuadratureValue(self):
        return self.quadratureValue

    def addFrame(self):
        frame = self._inputPorts.getPort('frame').getObject()
        if (frame):
            try:
                self.numberLines = frame.getNumberOfLines()
                self.rangeFirstSample = frame.getStartingRange()            
                self.numberBytesPerLine = frame.getImage().getXmax()
                self.firstSample = frame.getImage().getXmin()/2
                self.numberGoodBytes = frame.getImage().getXmax() - frame.getImage().getXmin()
                instrument = frame.getInstrument()
                self.inPhaseValue = instrument.getInPhaseValue()
                self.quadratureValue = instrument.getQuadratureValue()
                self.rangeSamplingRate = instrument.getRangeSamplingRate()
                self.rangePulseDuration = instrument.getPulseLength()
                self.rangePixelSize = instrument.getRangePixelSize()
            except AttributeError as strerr:
                self.logger.error(strerr)
                raise AttributeError

    
    logging_name = "stdproc.alosreformat.ALOS_fbs2fbd"
    def __init__(self):
        super(ALOS_fbs2fbdPy, self).__init__()
        self.rangePulseDuration = None
        self.rangeChirpExtensionPoints = 0
        self.rangeSamplingRate = None
        self.rangeFirstSample = None
        self.numberGoodBytes = None
        self.numberBytesPerLine = None
        self.numberLines = None
        self.firstSample = None
        self.inPhaseValue = None
        self.quadratureValue = None
        self.rangePixelSize = None
        self.inputFilename = ''
        self.outputFilename = ''
        self.dictionaryOfVariables = { 
            'NUMBER_RANGE_BIN' : ['self.numberRangeBin', 'int','mandatory'], 
            'NUMBER_GOOD_BYTES' : ['self.numberGoodBytes', 'int','mandatory'], 
            'RANGE_FIRST_SAMPLE' : ['self.rangeFirstSample', 'float','mandatory'], 
            'RANGE_PULSE_DURATION' : ['self.rangePulseDuration', 'float','mandatory'], 
            'RANGE_SAMPLING_RATE' : ['self.rangeSamplingRate', 'float','mandatory'], 
            'RANGE_CHIRP_EXTENSION_POINTS':['self.rangeChirpExtensionPoints','float','mandatory'], 
            'NUMBER_BYTES_PER_LINE' : ['self.numberBytesPerLine', 'int','mandatory'], 
            'FIRST_SAMPLE' : ['self.firstSample', 'int','mandatory'], 
            'NUMBER_LINES' : ['self.numberLines', 'int','mandatory'], 
            'INPHASE_VALUE' : ['self.inPhaseValue', 'float','mandatory'], 
            'QUADRATURE_VALUE' : ['self.quadratureValue', 'float','mandatory'], 
            'INPUT_FILENAME' : ['self.inputFilename', 'str','mandatory'], 
            'OUTPUT_FILENAME' : ['self.outputFilename', 'str','mandatory'] 
            }
        self.dictionaryOfOutputVariables = {                                            
            'NUMBER_GOOD_BYTES' : 'self.numberGoodBytes', 
            'RANGE_FIRST_SAMPLE' : 'self.rangeFirstSample', 
            'RANGE_PULSE_DURATION' : 'self.rangePulseDuration', 
            'RANGE_SAMPLING_RATE' : 'self.rangeSamplingRate', 
            'RANGE_CHIRP_EXTENSION_POINTS' : 'self.rangeChirpExtensionPoints', 
            'NUMBER_BYTES_PER_LINE' : 'self.numberBytesPerLine', 
            'INPHASE_VALUE' : 'self.inPhaseValue', 
            'QUADRATURE_VALUE' : 'self.quadratureValue'                                      }
        self.descriptionOfVariables = {}
        self.mandatoryVariables = []
        self.optionalVariables = []
        typePos = 2
        for key , val in self.dictionaryOfVariables.items():
            if val[typePos] == 'mandatory':
                self.mandatoryVariables.append(key)
            elif val[typePos] == 'optional':
                self.optionalVariables.append(key)
            else:
                print('Error. Variable can only be optional or mandatory')
                raise Exception
        return None

    def createPorts(self):
        framePort = Port(name='frame',method=self.addFrame)
        self._inputPorts.add(framePort)
        return None

    pass
