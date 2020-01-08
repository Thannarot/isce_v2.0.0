#!/usr/bin/env python3

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# copyright: 2014 to the present, california institute of technology.
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





class Polynomial(object):
    '''
    Class to store 2D polynomials in ISCE.
    Implented as a list of lists, the coefficients
    are stored as shown below:

    [ [    1,     x^1,     x^2, ....],
      [  y^1, x^1 y^1, x^2 y^1, ....],
      [  y^2, x^1 y^2, x^2 y^2, ....],
      [    :        :        :     :]]

    where "x" corresponds to pixel index in range and
    "y" corresponds to pixel index in azimuth.

    The size of the 2D matrix will correspond to 
    [rangeOrder+1, azimuthOrder+1].
    '''

    def __init__(self, rangeOrder=None, azimuthOrder=None):
        '''
        Constructor for the polynomial object.
        '''
        self._coeffs = []
        for k in range(azimuthOrder+1):
            rng =[]
            for kk in range(rangeOrder+1):
                rng.append(0.)
            self._coeffs.append(rng)

        self._rangeOrder = int(rangeOrder)
        self._azimuthOrder = int(azimuthOrder)
        self._normRange = 1.0
        self._normAzimuth = 1.0
        self._meanRange = 0.0
        self._meanAzimuth = 0.0
        
        return

    def setCoeffs(self, parms):
        '''
        Set the coefficients using another nested list.
        '''
        for ii,row in enumerate(parms):
            for jj,col in enumerate(row):
                self._coeffs[ii][jj] = float(col)

        return

    def getCoeffs(self):
        return self._coeffs

    def setNormRange(self, parm):
        self._normRange = float(parm)

    def getNormRange(self):
        return self._normRange

    def setNormAzimuth(self, parm):
        self._normAzimuth = float(parm)

    def getNormAzimuth(self):
        return self._normAzimuth

    def __call__(self, azi,rng):
        '''
        Evaluate the polynomial.
        This is much slower than the C implementation - only for sparse usage.
        '''
        y = (azi - self._meanAzimuth)/self._normAzimuth
        x = (rng - self._meanRange)/self._normRange
        res = 0.
        for ii,row in enumerate(self._coeffs):
            yfact = y**ii
            for jj,col in enumerate(row):
                res += col*yfact * (x**jj)

        return res

    def exportToC(self):
        '''
        Use the extension module and return a pointer in C.
        '''
        pass
        
def createPolynomial(order=None,
        norm=None, offset=None):
    '''
    Create a polynomial with given parameters.
    Order, Norm and Offset are iterables.
    '''
    
    poly = Polynomial(rangeOrder=order[0], azimuthOrder=order[1])

    if norm:
        poly.setNormRange(norm[0])
        poly.setNormAzimuth(norm[1])

    if offset:
        poly.setMeanRange(offset[0])
        poly.setMeanAzimuth(offset[1])
        
    return poly

def createRangePolynomial(order=None, offset=None, norm=None):
    '''
    Create a polynomial in range.
    '''
    poly = Polynomial(rangeOrder=order, azimuthOrder=0)

    if offset:
        poly.setMeanRange(offset)
    
    if norm:
        poly.setNormRange(norm)

    return poly

def createAzimuthPolynomial(order=None, offset=None, norm=None):
    '''
    Create a polynomial in azimuth.
    '''
    poly = Polynomial(rangeOrder=0, azimuthOrder=order)

    if offset:
        poly.setMeanAzimuth(offset)

    if norm:
        poly.setNormAzimuth(norm)

    return poly

def createFromC(pointer):
    '''
    Uses information from the  extension module structure to create Python object.
    '''
    pass


