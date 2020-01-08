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
# Author: Eric Gurrola
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



from .InsarProc import *
from .Factories import *

def getFactoriesInfo():
    return  {'InsarProc':
                     {'args':
                           {
                            'procDoc':{'value':None,'type':'Catalog','optional':True}
                            },
                     'factory':'createInsarProc'                     
                     }
              
              }

def createInsarProc(name=None, procDoc= None):
    from .InsarProc import InsarProc
    return InsarProc(name = name,procDoc = procDoc)