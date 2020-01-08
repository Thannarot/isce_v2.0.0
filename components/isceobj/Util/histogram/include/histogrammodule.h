//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// copyright: 2012 to the present, california institute of technology.
// all rights reserved. united states government sponsorship acknowledged.
// any commercial use must be negotiated with the office of technology transfer
// at the california institute of technology.
// 
// this software may be subject to u.s. export control laws. by accepting this
// software, the user agrees to comply with all applicable u.s. export laws and
// regulations. user has the responsibility to obtain export licenses,  or other
// export authority as may be required before exporting such information to
// foreign countries or providing access to foreign persons.
// 
// installation and use of this software is restricted by a license agreement
// between the licensee and the california institute of technology. it is the
// user's responsibility to abide by the terms of the license agreement.
//
// Author: Giangi Sacco
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~




#ifndef histogrammodule_h
#define histogrammodule_h 1

#include <Python.h>
#include <complex>
#include "DataAccessor.h"
#include "p2.h"

extern "C"
{
  PyObject *realHistogram_C(PyObject *self,PyObject *args);
//  PyObject *complexHistogram_C(PyObject *self,PyObject *args);
}

static PyMethodDef histogram_methods[] =
{
    {"realHistogram_Py",realHistogram_C,METH_VARARGS," "},
//    {"complexHistogram_Py",complexHistogram_C,METH_VARARGS," "},
    {NULL,NULL,0,NULL}
};

#endif
