#!/usr/bin/env python3

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
# Author: Walter Szeliga
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~




import logging
from iscesys.Component.Component import Component
from isceobj.Filter import filter
from isceobj.Util.decorators import pickled, logged

## An decorator.object_wrapper style decoration, just for filter.
def filter_wrap(func):
    #2013-06-04 Kosal: new_method takes only *args
    #then we reorder and add new elements to argument list
    def new_method(self, *args):
        args = list(args)
        filterWidth = args[0]
        filterHeight = args[1]
        other_args = args[2:]
        new_args = [ self.inFile, self.outFile, self.width, self.length, filterWidth, filterHeight ]
        new_args.extend(other_args)
        return func(self, *new_args)
    #Kosal

    return new_method


@pickled
class Filter(Component):
    """A class for spatial filters"""

    logging_name = "isce.Filter"

    @logged
    def __init__(self, inFile=None, outFile=None, width=None, length=None):
        raw_input = ("In Filter")
        super(Filter, self).__init__()
        self.inFile = inFile
        self.outFile = outFile
        self.width = width
        self.length = length
        return None

    #2013-05-04 Kosal: added only *args as input parameters for functions below
    #so that they can be called twice with different arguments
    #first when called inside FR
    #and then when called by decorator.
    #C functions are just called with arguments and not returned.
    #logger is transferred inside FR._filterFaradayRotation
    @filter_wrap
    def meanFilter(self, *args):
        #should be first called with: filterWidth, filterHeight
        filter.meanFilter_Py(*args)

    @filter_wrap
    def gaussianFilter(self, *args):
        #should be first called with: filterWidth, filterHeight, sigma
        filter.gaussianFilter_Py(*args)

    @filter_wrap
    def medianFilter(self,filterWidth,filterHeight):
        #should be first called with: filterWidth, filterHeight
        filter.medianFilter_Py(*args)
