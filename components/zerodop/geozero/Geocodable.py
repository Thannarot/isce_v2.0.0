#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# copyright: 2010 to the present, california institute of technology.
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
import isce 
import sys 
import math
from iscesys.Component.Component import Component, Port
import os 


class Geocodable(Component):
    
    def __init__(self):
        super(Geocodable, self).__init__()
        self._image = None
        self._method = ''
        self._interp_map = {
                            'amp' : 'sinc',
                            'cpx' : 'sinc',
                            'cor' : 'nearest',
                            'unw' : 'nearest',
                            'rmg' : 'nearest'
                           }
    #there should be no need for a setter since this is a creator class
    @property
    def image(self):
        return self._image
    @property
    def method(self):
        return self._method
    def create(self,filename):
        from iscesys.Parsers.FileParserFactory import createFileParser
        from isceobj import createImage
        parser = createFileParser('xml')
        prop, fac, misc = parser.parse(filename + '.xml')

        self._image  = createImage()
        self._image.init(prop,fac,misc)
        self._image.accessMode = 'read'
        #try few ways. If the image type is not part of the map use sinc for complex and nearest for float 
        if self._image.imageType in self._interp_map:
            self._method = self._interp_map[self._image.imageType]
        elif self.image.dataType == 'CFLOAT':
            self._method = 'sinc'
        elif self.image.dataType == 'FLOAT':
            self._method = 'nearest'
        else:
            self._image = None
            self._method = None
        #allow to get image and method from the instance or as return value
        return self._image,self._method

def main(argv):
    ge = Geocodable()
    ge.create(argv[0])
    

if __name__ == '__main__':
    sys.exit(main(sys.argv[1:]))


    
