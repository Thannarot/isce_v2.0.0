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





#include <Python.h>
#include "simamplitudemodule.h"
#include <cmath>
#include <sstream>
#include <iostream>
#include <string>
#include <stdint.h>
#include <vector>
using namespace std;

static const char * const __doc__ = "Python extension for simamplitude.F";

PyModuleDef moduledef = {
    // header
    PyModuleDef_HEAD_INIT,
    // name of the module
    "simamplitude",
    // module documentation string
    __doc__,
    // size of the per-interpreter state of the module;
    // -1 if this state is global
    -1,
    simamplitude_methods,
};

// initialization function for the module
// *must* be called PyInit_formslc
PyMODINIT_FUNC
PyInit_simamplitude()
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


PyObject * setStdWriter_C(PyObject* self, PyObject* args)
{
    uint64_t var;
    if(!PyArg_ParseTuple(args, "K", &var))
    {
        return NULL;
    }
    setStdWriter_f(&var);
    return Py_BuildValue("i", 0);
}
PyObject * simamplitude_C(PyObject* self, PyObject* args)
{
        uint64_t var0;
        uint64_t var1;
        if(!PyArg_ParseTuple(args, "KK",&var0,&var1))
        {
                return NULL;
        }
        simamplitude_f(&var0,&var1);
        return Py_BuildValue("i", 0);
}
PyObject * setImageWidth_C(PyObject* self, PyObject* args)
{
        int var;
        if(!PyArg_ParseTuple(args, "i", &var))
        {
                return NULL;
        }
        setImageWidth_f(&var);
        return Py_BuildValue("i", 0);
}
PyObject * setImageLength_C(PyObject* self, PyObject* args)
{
        int var;
        if(!PyArg_ParseTuple(args, "i", &var))
        {
                return NULL;
        }
        setImageLength_f(&var);
        return Py_BuildValue("i", 0);
}
PyObject * setShadeScale_C(PyObject* self, PyObject* args)
{
        float var;
        if(!PyArg_ParseTuple(args, "f", &var))
        {
                return NULL;
        }
        setShadeScale_f(&var);
        return Py_BuildValue("i", 0);
}
