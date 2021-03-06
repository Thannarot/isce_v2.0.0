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
# Author: Eric Belz
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



"""Some specialized arithmetic exceptions for
Vector and Affine Spaces.
"""
## \namespace geo::exceptions
## <a href="http://docs.python.org/2/library/exceptions.html">Exceptions</a>
## for Vector and Affines spaces.

## Base class for geometric errors
class GeometricException(ArithmeticError):
    """A base class- not to be raised"""
    pass

## A reminder to treat geometric objects properly.
class NonCovariantOperation(GeometricException):
    """Raise when you do something that is silly[1], like adding
    a Scalar to a Vector\.
    [1]Silly: (adj.) syn: non-covariant"""
    pass

## A reminder that Affine space are affine, and vector spaces are not.
class AffineSpaceError(GeometricException):
    """Raised when you forget the points in an affine space are
    not vector in a vector space, and visa versa"""
    pass

## A catch-all for overlaoded operations getting non-sense.
class UndefinedGeometricOperation(GeometricException):
    """This will raised if you get do an opeation that has been defined for
    a Tensor/Affine/Coordinate argument, but you just have a non-sense
    combinabtion, like vector**vector.
    """
    pass


## This function should make a generic error message
def error_message(op, left, right):
    """message = error_message(op, left, right)

    op             is a method or a function
    left           is a geo object
    right          is probably a geo object.

    message        is what did not work
    """
    return "%s(%s, %s)"%(op.__name__,
                         left.__class__.__name__,
                         right.__class__.__name__)
