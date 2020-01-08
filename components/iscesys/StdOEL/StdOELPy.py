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
import os
from contextlib import contextmanager
import sys
from . import StdOEL as ST


## A convinence constructor to make the writer the way applications need it
def create_writer(where, fileTag, flag, filename=None,
                  out=None, err=None, log=None):
    """create_writer(*args, **kwargs) takes the args/kwargs needed to
    make a ready-for Application StdOEL instance.
    """
    result = StdOEL()
    result.createWriters(out=out, err=err, log=log)
    result.configWriter(where, fileTag, flag, filename=filename)
    result.init()
    return result


@contextmanager
def context_writer(where, fileTag, flag, filename=None,
                   out=None, err=None, log=None):
    """create_writer as a context manager, see that for signature.

    Usage:
    >>>with context_writer as <writer>:
    >>>... <suite>
    >>>"""
    result = create_writer(where, fileTag, flag, filename=filename,
                           out=out, err=err, log=log)
    yield result
    result.finalize()


## Any class that talks to StdOEL, needs these methods.
class _WriterInterface(object):
    _stdWriter = None

    def __init__(self):
        self._create_writer("log" ,"", True, "insar.log")
        return None

    def getStdWriter(self):
        return self._stdWriter

    def setStdWriter(self,var):
        self._stdWriter = var

    stdWriter = property(getStdWriter, setStdWriter)

    def _create_writer(self, where, fileTag, flag, filename=None,
                       out=None, err=None, log=None):
        self._stdWriter = create_writer(where, fileTag, flag,
                                       filename=filename,
                                       out=out, err=err, log=log)
        return None

    def _writer_set_file_tags(self, *args):
        return self.stdWriter.set_file_tags(*args)

    ## What does this mean?
    def setState(self, obj):
        obj.setStdWriter_Py(int(self.stdWriter))

    pass


## The StdOEL object
class StdOEL(object):

    _writer = None
    _factory = None
    _out = 'screen'
    _err = 'screen'
    _log = 'file'
    _logFilename = 'log.log'
    _outFilename = 'log.out'
    _errFilename = 'log.err'

    def finalize(self):
        ST.finalize(self._writer, self._factory)
        return None

    def init(self):
        ST.init(self._writer)
        return None

    def createWriters(self, out=None, err=None, log=None):
        #if std type is not defined use the defaults
        if out is None:
            out = self._out

        else:
            self._out = out

        if err is None:
            err = self._err
        else:
            self._err = err

        if log is None:
            log = self._log
        else:
            self._log = log

        self._writer, self._factory = ST.createWriters(out, err, log)
        return None

    def getWriter(self):
        return self._writer

    def setWriter(self, *args, **kwargs):
        raise NotImplementedError("Use createWriters and configWriters")

    writer = property(getWriter, setWriter)

    ## A variable that is an int should be callable by int().
    def __int__(self):
        return self.writer

    def configWriter(self, where, fileTag, flag, filename=None):
        if where == 'out':
            if filename is None:
                filename = self._outFilename
            else:
                self._outFilename = filename
        if where == 'err':
            if filename is None:
                filename = self._errFilename
            else:
                self._logFilename = filename
        if where == 'log':
            if filename is None:
                filename = self._logFilename
            else:
                self._logFilename = filename

        self.setFilename(filename, where)
        self.setFileTag(fileTag, where)
        self.setTimeStampFlag(flag, where)
        return None

    def setFilename(self,name,where):
        ST.setFilename(self._writer, name, where)
        return None

    def setFileTag(self, name, where):
        ST.setFileTag(self._writer, name, where)
        return None

    ## a convinience method
    def set_file_tags(self, name, *args):
        for where in args:
            self.setFileTag(name, where)
        return self


    def setTimeStampFlag(self, flag, where):
        #cannot pass bool to C, so convert to int
        ST.setTimeStampFlag(self._writer,
                            int(bool(flag)),
                            where)
        return None
