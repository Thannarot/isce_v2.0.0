//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// copyright: 2010 to the present, california institute of technology.
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





#ifndef simamplitudemodule_h
#define simamplitudemodule_h

#include <Python.h>
#include <stdint.h>
#include "simamplitudemoduleFortTrans.h"

extern "C"
{
        void setStdWriter_f(uint64_t *);
        PyObject * setStdWriter_C(PyObject *, PyObject *);
        void simamplitude_f(uint64_t *,uint64_t *);
        PyObject * simamplitude_C(PyObject *, PyObject *);
        void setImageWidth_f(int *);
        PyObject * setImageWidth_C(PyObject *, PyObject *);
        void setImageLength_f(int *);
        PyObject * setImageLength_C(PyObject *, PyObject *);
        void setShadeScale_f(float *);
        PyObject * setShadeScale_C(PyObject *, PyObject *);

}

static PyMethodDef simamplitude_methods[] =
{
    {"setStdWriter_Py", setStdWriter_C, METH_VARARGS, " "},
        {"simamplitude_Py", simamplitude_C, METH_VARARGS, " "},
        {"setImageWidth_Py", setImageWidth_C, METH_VARARGS, " "},
        {"setImageLength_Py", setImageLength_C, METH_VARARGS, " "},
        {"setShadeScale_Py", setShadeScale_C, METH_VARARGS, " "},
        {NULL, NULL, 0, NULL}
};
#endif //simamplitudemodule_h
