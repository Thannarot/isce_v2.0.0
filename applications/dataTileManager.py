#!/usr/bin/env python3 

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
# Author: Giangi Sacco
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~




import isce
import logging
import logging.config
from iscesys.Component.Application import Application
from iscesys.Component.Component import Component
import os
DATA_SOURCE = Component.Parameter('_dataSource',
    public_name='dataSource',
    default = '',
    type = str,
    mandatory =  True,
    doc = "Data source such as dem1 (3o m resolution), dem3 (90 m resolution) \n" +\
           "or wbd for water body mask")
ACTION = Component.Parameter('_action',
    public_name='action',
    default = 'stitch',
    type = str,
    mandatory =  False,
    doc = "Action to be performed: stitch, download or stitchcorrect"
    )
BBOX = Component.Parameter('_bbox',
    public_name='bbox',
    default = [],
    container=list,
    type = float,
    mandatory = False,
    doc = "Defines the spatial region in the format south north west east.\n" + \
        "The values should be  from (-90,90) for latitudes and (-180,180) for longitudes.")
PAIRS = Component.Parameter('_pairs',
    public_name='pairs',
    default = [],
    container=list,
    type = float,
    mandatory =  False,
    doc = "Set of latitude and longitude pairs for which action = 'download' is performed.\n" +\
         "The format is [lat0,lon0,lat1,lon1,...,latn,lonn ].\n" +\
         "The values should be from (-90,90) for latitudes and (-180,180) for longitudes")
MANAGER = Application.Facility(
    '_manager',
    public_name='manager',
    module='iscesys.DataManager',
    factory='createManager',
    mandatory=False,
    args=(DATA_SOURCE,),
    doc="Factory to instantiate the tile manager based on the DATA_SOURCE value" 
    )
class DataTileManager(Application):
    def main(self):       
        if(self._action == 'stitch' or self._action == 'stitchcorrect'):
            if(self._bbox):
                lat = self._bbox[0:2]
                lon = self._bbox[2:4]    
                if not(self.manager.stitch(lat,lon)):
                    print('Could not create a stitched file. Some tiles are missing')
                if(self.action == 'stitchcorrect'):
                    self.manager.correct()
            else:
                print('Error. The bbox parameter must be specified when action is stitch')
                raise ValueError
        
        elif(self.action == 'download'):
            if(self._bbox):
                lat = self._bbox[0:2]
                lon = self._bbox[2:4]
                fromBounds = True
            elif(self._pairs):
                lat = self._pairs[::2]
                lon = self._pairs[1::2]
                fromBounds = False
            if(not (self._bbox or self._pairs)):
                print('Error. Either the bbox or the pairs parameters must be specified when action is download')
                raise ValueError
            self.manager.download(lat,lon,fromBounds)

        else:
            print('Unrecognized action',self._action)
            return    
  
    def Usage(self):
        print("\nUsage: dataTileManager.py input.xml\n")
        print("NOTE: if you don't want to store your password in a file you can run it as\n" +\
              "'dataTileManager.py input.xml dataTileManager.manager.username=yourUsername\n" +\
              "dataTileManager.manager.password=yourPassword'\n\n" )
    
    family = 'datatilemanager'            
    
    parameter_list = (
                      DATA_SOURCE,
                      ACTION,
                      PAIRS,
                      BBOX
                      )
    facility_list = (MANAGER,)

    @property
    def manager(self):
        return self._manager
    @manager.setter
    def manager(self,val):
        self._manager = val    
    @property
    def action(self):
        return self._action
    @action.setter
    def action(self,val):
        self._action = val   
    @property
    def dataSource(self):
        return self._dataSource
    @dataSource.setter
    def dataSource(self,val):
        self._dataSource = val     
    @property
    def pairs(self):
        return self._pairs
    @pairs.setter
    def pairs(self,val):
        self._pairs = val     
    @property
    def bbox(self):
        return self._bbox
    @bbox.setter
    def bbox(self,val):
        self._bbox = val                                  
    def __init__(self,family = '', name = ''):
        super(DataTileManager, self).__init__(family if family else  self.__class__.family, name=name)
        self._test = None

if __name__ == "__main__":
    import sys
    dt = DataTileManager()
    dt.configure()
    dt.run()
    
