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
#include "orbit2schmodule.h"
#include <cmath>
#include <sstream>
#include <iostream>
#include <string>
#include <stdint.h>
#include <vector>
using namespace std;

static const char * const __doc__ = "Python extension for orbit2sch";

PyModuleDef moduledef = {
    // header
    PyModuleDef_HEAD_INIT,
    // name of the module
    "orbit2sch",
    // module documentation string
    __doc__,
    // size of the per-interpreter state of the module;
    // -1 if this state is global
    -1,
    orbit2sch_methods,
};

// initialization function for the module
// *must* be called PyInit_orbit2sch
PyMODINIT_FUNC
PyInit_orbit2sch()
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

PyObject * allocate_sch_C(PyObject* self, PyObject* args)
{
    int dim1 = 0;
    int dim2 = 0;
    if(!PyArg_ParseTuple(args, "ii", &dim1, &dim2))
    {
        return NULL;
    }
    allocate_sch_f(&dim1, &dim2);
    return Py_BuildValue("i", 0);
}

PyObject * deallocate_sch_C(PyObject* self, PyObject* args)
{
    deallocate_sch_f();
    return Py_BuildValue("i", 0);
}

PyObject * allocate_vsch_C(PyObject* self, PyObject* args)
{
    int dim1 = 0;
    int dim2 = 0;
    if(!PyArg_ParseTuple(args, "ii", &dim1, &dim2))
    {
        return NULL;
    }
    allocate_vsch_f(&dim1, &dim2);
    return Py_BuildValue("i", 0);
}

PyObject * deallocate_vsch_C(PyObject* self, PyObject* args)
{
    deallocate_vsch_f();
    return Py_BuildValue("i", 0);
}

PyObject * allocate_asch_C(PyObject* self, PyObject* args)
{
    int dim1 = 0;
    int dim2 = 0;
    if(!PyArg_ParseTuple(args, "ii", &dim1, &dim2))
    {
        return NULL;
    }
    allocate_asch_f(&dim1, &dim2);
    return Py_BuildValue("i", 0);
}

PyObject * deallocate_asch_C(PyObject* self, PyObject* args)
{
    deallocate_asch_f();
    return Py_BuildValue("i", 0);
}

PyObject * orbit2sch_C(PyObject* self, PyObject* args)
{
    orbit2sch_f();
    return Py_BuildValue("i", 0);
}
PyObject * setOrbitPosition_C(PyObject* self, PyObject* args)
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
    setOrbitPosition_f(vectorV, &dim1, &dim2);
    delete [] vectorV;
    return Py_BuildValue("i", 0);
}

PyObject * setOrbitVelocity_C(PyObject* self, PyObject* args)
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
    setOrbitVelocity_f(vectorV, &dim1, &dim2);
    delete [] vectorV;
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
PyObject * setComputePegInfoFlag_C(PyObject* self, PyObject* args)
{
    int var;
    if(!PyArg_ParseTuple(args, "i", &var))
    {
        return NULL;
    }
    setComputePegInfoFlag_f(&var);
    return Py_BuildValue("i", 0);
}
PyObject * setPegLatitude_C(PyObject* self, PyObject* args)
{
    double var;
    if(!PyArg_ParseTuple(args, "d", &var))
    {
        return NULL;
    }
    setPegLatitude_f(&var);
    return Py_BuildValue("i", 0);
}
PyObject * setPegLongitude_C(PyObject* self, PyObject* args)
{
    double var;
    if(!PyArg_ParseTuple(args, "d", &var))
    {
        return NULL;
    }
    setPegLongitude_f(&var);
    return Py_BuildValue("i", 0);
}
PyObject * setPegHeading_C(PyObject* self, PyObject* args)
{
    double var;
    if(!PyArg_ParseTuple(args, "d", &var))
    {
        return NULL;
    }
    setPegHeading_f(&var);
    return Py_BuildValue("i", 0);
}
PyObject * setAverageHeight_C(PyObject* self, PyObject* args)
{
    double var;
    if(!PyArg_ParseTuple(args, "d", &var))
    {
        return NULL;
    }
    setAverageHeight_f(&var);
    return Py_BuildValue("i", 0);
}
PyObject * getSchPosition_C(PyObject* self, PyObject* args)
{
    int dim1 = 0;
    int dim2 = 0;
    if(!PyArg_ParseTuple(args, "ii", &dim1, &dim2))
    {
        return NULL;
    }
    PyObject * list1 = PyList_New(dim1);
    double *  vectorV = new double[dim1*dim2];
    getSchPosition_f(vectorV, &dim1, &dim2);
    for(int i = 0; i  < dim1; ++i)
    {
        PyObject * list2 = PyList_New(dim2);
        for(int j = 0; j  < dim2; ++j)
        {
            PyObject * listEl =  PyFloat_FromDouble(
                (double) vectorV[i*dim2 + j]);
            if(listEl == NULL)
            {
                cout << "Error in file " << __FILE__ << " at line " <<
                        __LINE__ << ". Cannot set list element" << endl;
                exit(1);
            }
            PyList_SetItem(list2,j,listEl);
        }
        PyList_SetItem(list1,i,list2);
    }
    delete [] vectorV;
    return Py_BuildValue("N",list1);
}

PyObject * getSchVelocity_C(PyObject* self, PyObject* args)
{
    int dim1 = 0;
    int dim2 = 0;
    if(!PyArg_ParseTuple(args, "ii", &dim1, &dim2))
    {
        return NULL;
    }
    PyObject * list1 = PyList_New(dim1);
    double *  vectorV = new double[dim1*dim2];
    getSchVelocity_f(vectorV, &dim1, &dim2);
    for(int i = 0; i  < dim1; ++i)
    {
        PyObject * list2 = PyList_New(dim2);
        for(int j = 0; j  < dim2; ++j)
        {
            PyObject * listEl =  PyFloat_FromDouble(
                (double) vectorV[i*dim2 + j]);
            if(listEl == NULL)
            {
                cout << "Error in file " << __FILE__ << " at line " <<
                        __LINE__ << ". Cannot set list element" << endl;
                exit(1);
            }
            PyList_SetItem(list2,j,listEl);
        }
        PyList_SetItem(list1,i,list2);
    }
    delete [] vectorV;
    return Py_BuildValue("N",list1);
}

PyObject * getSchGravitationalAcceleration_C(PyObject* self, PyObject* args)
{
    int dim1 = 0;
    int dim2 = 0;
    if(!PyArg_ParseTuple(args, "ii", &dim1, &dim2))
    {
        return NULL;
    }
    PyObject * list1 = PyList_New(dim1);
    double *  vectorV = new double[dim1*dim2];
    getSchGravitationalAcceleration_f(vectorV, &dim1, &dim2);
    for(int i = 0; i  < dim1; ++i)
    {
        PyObject * list2 = PyList_New(dim2);
        for(int j = 0; j  < dim2; ++j)
        {
            PyObject * listEl =  PyFloat_FromDouble(
                (double) vectorV[i*dim2 + j]);
            if(listEl == NULL)
            {
                cout << "Error in file " << __FILE__ << " at line " <<
                        __LINE__ << ". Cannot set list element" << endl;
                exit(1);
            }
            PyList_SetItem(list2,j,listEl);
        }
        PyList_SetItem(list1,i,list2);
    }
    delete [] vectorV;
    return Py_BuildValue("N",list1);
}
