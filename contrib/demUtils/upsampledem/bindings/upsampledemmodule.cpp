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




#include <Python.h>
#include "upsampledemmodule.h"
#include <cmath>
#include <sstream>
#include <iostream>
#include <string>
#include <stdint.h>
#include <vector>
using namespace std;

static const char * const __doc__ = "module for upsampledem.f";

PyModuleDef moduledef = {
    // header
    PyModuleDef_HEAD_INIT,
    // name of the module
    "upsampledem",
    // module documentation string
    __doc__,
    // size of the per-interpreter state of the module;
    // -1 if this state is global
    -1,
    upsampledem_methods,
};

// initialization function for the module
// *must* be called PyInit_upsampledem
PyMODINIT_FUNC
PyInit_upsampledem()
{
    // create the module using moduledef struct defined above
    PyObject * module = PyModule_Create(&moduledef);
    // check whether module creation succeeded and raise an exception if not
    if (!module) {
        return module;
    }
    // otherwise, we have an initialized module
    // and return the newly created module
    return module;
}

PyObject * upsampledem_C(PyObject* self, PyObject* args)
{
    uint64_t var0;
    uint64_t var1;
    int var2;
    if(!PyArg_ParseTuple(args, "KKi",&var0,&var1,&var2))
    {
        return NULL;
    }
    upsampledem_f(&var0,&var1,&var2);
    return Py_BuildValue("i", 0);
}
PyObject * setStdWriter_C(PyObject* self, PyObject* args)
{
    uint64_t var0;
    if(!PyArg_ParseTuple(args, "K",&var0))
    {
        return NULL;
    }
    setStdWriter_f(&var0);
    return Py_BuildValue("i", 0);
}

PyObject * setWidth_C(PyObject* self, PyObject* args)
{
    int var;
    if(!PyArg_ParseTuple(args, "i", &var))
    {
        return NULL;
    }
    setWidth_f(&var);
    return Py_BuildValue("i", 0);
}

PyObject * setXFactor_C(PyObject* self, PyObject* args)
{
    int var;
    if(!PyArg_ParseTuple(args, "i", &var))
    {
        return NULL;
    }
    setXFactor_f(&var);
    return Py_BuildValue("i", 0);
}

PyObject * setYFactor_C(PyObject* self, PyObject* args)
{
    int var;
    if(!PyArg_ParseTuple(args, "i", &var))
    {
        return NULL;
    }
    setYFactor_f(&var);
    return Py_BuildValue("i", 0);
}

PyObject * setNumberLines_C(PyObject* self, PyObject* args)
{
    int var;
    if(!PyArg_ParseTuple(args, "i", &var))
    {
        return NULL;
    }
    setNumberLines_f(&var);
    return Py_BuildValue("i", 0);
}
PyObject * setPatchSize_C(PyObject* self, PyObject* args)
{
    int var;
    if(!PyArg_ParseTuple(args, "i", &var))
    {
        return NULL;
    }
    setPatchSize_f(&var);
    return Py_BuildValue("i", 0);
}
