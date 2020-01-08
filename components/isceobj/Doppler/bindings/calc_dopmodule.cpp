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
#include "calc_dopmodule.h"
#include <cmath>
#include <sstream>
#include <iostream>
#include <string>
#include <stdint.h>
#include <vector>
using namespace std;

static const char * const __doc__ = "module for calc_dop.F";

PyModuleDef moduledef = {
    // header
    PyModuleDef_HEAD_INIT,
    // name of the module
    "calc_dop",
    // module documentation string
    __doc__,
    // size of the per-interpreter state of the module;
    // -1 if this state is global
    -1,
    calc_dop_methods,
};

// initialization function for the module
// *must* be called PyInit_calc_dop
PyMODINIT_FUNC
PyInit_calc_dop()
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

PyObject * allocate_rngDoppler_C(PyObject* self, PyObject* args)
{
    int dim1 = 0;
    if(!PyArg_ParseTuple(args, "i", &dim1))
    {
        return NULL;
    }
    allocate_rngDoppler_f(&dim1);
    return Py_BuildValue("i", 0);
}

PyObject * deallocate_rngDoppler_C(PyObject* self, PyObject* args)
{
    deallocate_rngDoppler_f();
    return Py_BuildValue("i", 0);
}

PyObject * calc_dop_C(PyObject* self, PyObject* args)
{
    uint64_t var0;
    if(!PyArg_ParseTuple(args, "K",&var0))
    {
        return NULL;
    }
    calc_dop_f(&var0);
    return Py_BuildValue("i", 0);
}
PyObject * setHeader_C(PyObject* self, PyObject* args)
{
    int var;
    if(!PyArg_ParseTuple(args, "i", &var))
    {
        return NULL;
    }
    setHeader_f(&var);
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
PyObject * setLastLine_C(PyObject* self, PyObject* args)
{
    int var;
    if(!PyArg_ParseTuple(args, "i", &var))
    {
        return NULL;
    }
    setLastLine_f(&var);
    return Py_BuildValue("i", 0);
}
PyObject * setFirstLine_C(PyObject* self, PyObject* args)
{
    int var;
    if(!PyArg_ParseTuple(args, "i", &var))
    {
        return NULL;
    }
    setFirstLine_f(&var);
    return Py_BuildValue("i", 0);
}
PyObject * setIoffset_C(PyObject* self, PyObject* args)
{
    double var;
    if(!PyArg_ParseTuple(args, "d", &var))
    {
        return NULL;
    }
    setIoffset_f(&var);
    return Py_BuildValue("i", 0);
}
PyObject * setQoffset_C(PyObject* self, PyObject* args)
{
    double var;
    if(!PyArg_ParseTuple(args, "d", &var))
    {
        return NULL;
    }
    setQoffset_f(&var);
    return Py_BuildValue("i", 0);
}
PyObject * getRngDoppler_C(PyObject* self, PyObject* args)
{
    int dim1 = 0;
    if(!PyArg_ParseTuple(args, "i", &dim1))
    {
        return NULL;
    }
    PyObject * list = PyList_New(dim1);
    double *  vectorV = new double[dim1];
    getRngDoppler_f(vectorV, &dim1);
    for(int i = 0; i  < dim1; ++i)
    {
        PyObject * listEl =  PyFloat_FromDouble((double) vectorV[i]);
        if(listEl == NULL)
        {
            cout << "Error in file " << __FILE__ << " at line " << __LINE__ <<
                    ". Cannot set list element" << endl;
            exit(1);
        }
        PyList_SetItem(list,i, listEl);
    }
    delete [] vectorV;
    return Py_BuildValue("N",list);
}

PyObject * getDoppler_C(PyObject* self, PyObject* args)
{
    double var;
    getDoppler_f(&var);
    return Py_BuildValue("d",var);
}
