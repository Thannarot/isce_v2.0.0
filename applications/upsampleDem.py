#!/usr/bin/env python3

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




import os
import logging
import sys

import isce
import argparse
from contrib.demUtils.UpsampleDem import UpsampleDem
from iscesys.Parsers.FileParserFactory import createFileParser
from isceobj.Image import createDemImage

class customArgparseFormatter(argparse.ArgumentDefaultsHelpFormatter, argparse.RawDescriptionHelpFormatter):
    '''
    For better help message that also shows the defaults.
    '''
    pass

def cmdLineParse():
    '''
    Command Line Parser.
    '''
    parser = argparse.ArgumentParser(description='Oversample DEM by integer factor.',
            formatter_class=customArgparseFormatter,
            epilog = '''

Example: 

upsampleDem.py -i input.dem -o output.dem -f 4 4
            
This oversamples the input dem in both lat and lon by a factor of 4.''')
    parser.add_argument('-i','--input', type=str, required=True, help='Input ISCE DEM with a corresponding .xml file.', dest='infile')
    parser.add_argument('-o','--output',type=str, default=None, help='Output ISCE DEM with a corresponding .xml file.', dest='outfile')
    parser.add_argument('-m', '--method', type=str, default='BIQUINTIC', help='Interpolation method out of Akima / Biquintic. Default: biquintic.', dest='method')
    parser.add_argument('-f','--factor',type=int, nargs='+', required=True, help='Oversampling factor in lat and lon (or a single value for both).', dest='factor')

    values = parser.parse_args()
    if len(values.factor) > 2:
        raise Exception('Factor should be a single number or a list of two. Undefined input for -f or --factor : '+str(values.factor))
    elif len(values.factor) == 1:
        values.factor = [values.factor[0], values.factor[0]]

    return values

if __name__ == "__main__":
    inps = cmdLineParse()

    if inps.infile.endswith('.xml'):
        inFileXml = inps.infile
        inFile = os.path.splitext(inps.infile)[0]
    else:
        inFile = inps.infile
        inFileXml = inps.infile + '.xml'

    if inps.outfile.endswith('.xml'):
        outFile = os.path.splitext(inps.outfile)[0]
    else:
        outFile = inps.outfile

    parser = createFileParser('xml')
    prop, fac, misc = parser.parse(inFileXml)


    inImage = createDemImage()
    inImage.init(prop,fac,misc)
    inImage.filename = inFile 
    inImage.createImage()

    upsampObj = UpsampleDem()
    upsampObj.method = inps.method
    upsampObj.setOutputFilename(outFile)
    upsampObj.upsampledem(demImage=inImage, yFactor=inps.factor[0], xFactor=inps.factor[1])
