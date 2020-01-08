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
# Author: Giangi Sacco
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~





from __future__ import print_function
import sys
import os
import math
import isce
from iscesys.Compatibility import Compatibility
Compatibility.checkPythonVersion()
from iscesys.Display.Display import Display
##
# Call mdx.py argv.
# The first element in argv must be the metadata file (i.e. metadata.rsc or metadata.xml) when displaying an image (could be something else when printing help info). If the file does not end by .rsc or .xml, then one needs to specify
# the -type flag that could be  rsc or xml. For rsc type of metadata the rsc ROI_PAC format is assumed. For xml type the ISCE xml format is assumed.
# In case the data file name is not simply the metadata file name with the extension  removed (for instance metadata file image.int.rsc and data file image.int)
# then use the -image flag and specify the filename.
# If the type of image that needs to be displayed cannot be inferred from the extension (for ROI_PAC type) or from the metadata doc string (ISCE type) then specify the -ext flag.
# To print a list of extensions run mdx.py -ext.
# To print the usage with the list of options just run mdx.py with no arguments.
# The flags -cw,-e,-amp1,-amp2,-chdr,-RMG-Mag,-RMG_Hgt -wrap,-wrap and -cmap have some defaults value depending on the image type. By specifying these flags in the command line the default values can be overwritten.
# Whatever flags in the argv that are not part of the abovementioned ones, will be passed to mdx as arguments at the end of the command.  
##
def main(argv = None):
    DS = Display()
    DS.mdx(argv)

if __name__ == "__main__":
    if len(sys.argv) == 1:
        sys.exit(main())
    else:
        sys.exit(main(sys.argv[1:]))
