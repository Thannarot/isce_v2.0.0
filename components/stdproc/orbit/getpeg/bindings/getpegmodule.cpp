//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// copyright: 2013 to the present, california institute of technology.
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
// Authors: Piyush Agram, Giangi Sacco
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~




#include <Python.h>
#include "getpegmodule.h"
#include <cmath>
#include <sstream>
#include <iostream>
#include <string>
#include <stdint.h>
#include <vector>
#include <cstdio>
using namespace std;

static char * const __doc__ = "Python extension for getpeg";

PyModuleDef moduledef = {
    // header
    PyModuleDef_HEAD_INIT,
    // name of the module
    "getpeg",
    // module documentation string
    __doc__,
    // size of the per-interpreter state of the module;
    // -1 if this state is global
    -1,
    getpeg_methods,
};

// initialization function for the module
// *must* be called PyInit_getpeg
PyMODINIT_FUNC
PyInit_getpeg()
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

PyObject * allocate_xyz_C(PyObject* self, PyObject* args)
{
    int dim1 = 0;
    int dim2 = 0;
    if(!PyArg_ParseTuple(args, "ii", &dim1, &dim2))
    {
            return NULL;
    }
    allocate_xyz_f(&dim1, &dim2);
    return Py_BuildValue("i", 0);
}

PyObject * deallocate_xyz_C(PyObject* self, PyObject* args)
{
    deallocate_xyz_f();
    return Py_BuildValue("i", 0);
}

PyObject * allocate_vxyz_C(PyObject* self, PyObject* args)
{
    int dim1 = 0;
    int dim2 = 0;
    if(!PyArg_ParseTuple(args, "ii", &dim1, &dim2))
    {
        return NULL;
    }
    allocate_vxyz_f(&dim1, &dim2);
    return Py_BuildValue("i", 0);
}

PyObject * deallocate_vxyz_C(PyObject* self, PyObject* args)
{
    deallocate_vxyz_f();
    return Py_BuildValue("i", 0);
}

PyObject * getpeg_C(PyObject* self, PyObject* args)
{
    getpeg_f();
    return Py_BuildValue("i", 0);
}
PyObject * setPosition_C(PyObject* self, PyObject* args)
{
    PyObject * list;
    int dim1 = 0;
    int dim2 = 0;
    if(!PyArg_ParseTuple(args, "Oii", &list, &dim1, &dim2))
    {
        return NULL;
    }
    if(!PyList_Check(list))
    {
        cout << "Error in file " << __FILE__ << " at line " << __LINE__ <<
                ". Expecting a list type object" << endl;
        exit(1);
    }
    double *  vectorV = new double[dim1*dim2];
    for(int i = 0; i  < dim1; ++i)
    {
        PyObject * listEl = PyList_GetItem(list,i);
        if(!PyList_Check(listEl))
        {
            cout << "Error in file " << __FILE__ << " at line " << __LINE__ <<
                    ". Expecting a list type object" << endl;
            exit(1);
        }
        for(int j = 0; j < dim2; ++j)
        {
            PyObject * listElEl = PyList_GetItem(listEl,j);
            if(listElEl == NULL)
            {
                cout << "Error in file " << __FILE__ << " at line " <<
                        __LINE__ << ". Cannot retrieve list element" << endl;
                exit(1);
            }
            vectorV[dim2*i + j] = (double) PyFloat_AsDouble(listElEl);
            if(PyErr_Occurred() != NULL)
            {
                cout << "Error in file " << __FILE__ << " at line " <<
                        __LINE__ << ". Cannot convert Py Object to C " << endl;
                exit(1);
            }
        }
    }
    setPosition_f(vectorV, &dim1, &dim2);
    delete [] vectorV;
    return Py_BuildValue("i", 0);
}

PyObject * setVelocity_C(PyObject* self, PyObject* args)
{
    PyObject * list;
    int dim1 = 0;
    int dim2 = 0;
    if(!PyArg_ParseTuple(args, "Oii", &list, &dim1, &dim2))
    {
        return NULL;
    }
    if(!PyList_Check(list))
    {
        cout << "Error in file " << __FILE__ << " at line " << __LINE__ <<
                ". Expecting a list type object" << endl;
        exit(1);
    }
    double *  vectorV = new double[dim1*dim2];
    for(int i = 0; i  < dim1; ++i)
    {
        PyObject * listEl = PyList_GetItem(list,i);
        if(!PyList_Check(listEl))
        {
            cout << "Error in file " << __FILE__ << " at line " << __LINE__ <<
                    ". Expecting a list type object" << endl;
            exit(1);
        }
        for(int j = 0; j < dim2; ++j)
        {
            PyObject * listElEl = PyList_GetItem(listEl,j);
            if(listElEl == NULL)
            {
                cout << "Error in file " << __FILE__ << " at line " <<
                        __LINE__ << ". Cannot retrieve list element" << endl;
                exit(1);
            }
            vectorV[dim2*i + j] = (double) PyFloat_AsDouble(listElEl);
            if(PyErr_Occurred() != NULL)
            {
                cout << "Error in file " << __FILE__ << " at line " <<
                        __LINE__ << ". Cannot convert Py Object to C " << endl;
                exit(1);
            }
        }
    }
    setVelocity_f(vectorV, &dim1, &dim2);
    delete [] vectorV;
    return Py_BuildValue("i", 0);
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

PyObject * setPlanetGM_C(PyObject* self, PyObject* args)
{
    double var;
    if(!PyArg_ParseTuple(args, "d", &var))
    {
        return NULL;
    }
    setPlanetGM_f(&var);
    return Py_BuildValue("i", 0);
}
PyObject * setEllipsoidMajorSemiAxis_C(PyObject* self, PyObject* args)
{
    double var;
    if(!PyArg_ParseTuple(args, "d", &var))
    {
        return NULL;
    }
    setEllipsoidMajorSemiAxis_f(&var);
    return Py_BuildValue("i", 0);
}
PyObject * setEllipsoidEccentricitySquared_C(PyObject* self, PyObject* args)
{
    double var;
    if(!PyArg_ParseTuple(args, "d", &var))
    {
        return NULL;
    }
    setEllipsoidEccentricitySquared_f(&var);
    return Py_BuildValue("i", 0);
}
PyObject * getPegLatitude_C(PyObject* self, PyObject* args)
{
    double var;
    getPegLatitude_f(&var);
    return Py_BuildValue("d",var);
}
PyObject * getPegLongitude_C(PyObject* self, PyObject* args)
{
    double var;
    getPegLongitude_f(&var);
    return Py_BuildValue("d",var);
}
PyObject * getPegHeading_C(PyObject* self, PyObject* args)
{
    double var;
    getPegHeading_f(&var);
    return Py_BuildValue("d",var);
}
PyObject * getPegRadiusOfCurvature_C(PyObject* self, PyObject* args)
{
    double var;
    getPegRadiusOfCurvature_f(&var);
    return Py_BuildValue("d",var);
}
PyObject * getAverageHeight_C(PyObject* self, PyObject* args)
{
    double var;
    getAverageHeight_f(&var);
    return Py_BuildValue("d",var);
}
PyObject * getProcVelocity_C(PyObject* self, PyObject* args)
{
    double var;
    getProcVelocity_f(&var);
    return Py_BuildValue("d",var);
}
