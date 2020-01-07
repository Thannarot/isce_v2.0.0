//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Copyright: 2010 to the present, California Institute of Technology.
// ALL RIGHTS RESERVED. United States Government Sponsorship acknowledged.
// Any commercial use must be negotiated with the Office of Technology Transfer
// at the California Institute of Technology.
// 
// This software may be subject to U.S. export control laws. By accepting this
// software, the user agrees to comply with all applicable U.S. export laws and
// regulations. User has the responsibility to obtain export licenses,  or other
// export authority as may be required before exporting such information to
// foreign countries or providing access to foreign persons.
// 
// Installation and use of this software is restricted by a license agreement
// between the licensee and the California Institute of Technology. It is the
// User's responsibility to abide by the terms of the license agreement.
//
// Author: Giangi Sacco
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~




#include <Python.h>
#include "formslcmodule.h"
#include <cmath>
#include <sstream>
#include <iostream>
#include <string>
#include <stdint.h>
#include <vector>
using namespace std;

static char * const __doc__ = "Python extension for formslc.F";

PyModuleDef moduledef = {
    // header
    PyModuleDef_HEAD_INIT,
    // name of the module
    "formslc",
    // module documentation string
    __doc__,
    // size of the per-interpreter state of the module;
    // -1 if this state is global
    -1,
    formslc_methods,
};

// initialization function for the module
// *must* be called PyInit_formslc
PyMODINIT_FUNC
PyInit_formslc()
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

PyObject * allocate_vsch_C(PyObject *self, PyObject *args)
{
    int dim1 = 0;
    int dim2 = 0;
    if(!PyArg_ParseTuple(args,"ii",&dim1,&dim2))
    {
        return NULL;
    }
    allocate_vsch_f(&dim1, &dim2);
    return Py_BuildValue("i",0);
}

PyObject * deallocate_vsch_C(PyObject *self, PyObject *args)
{
    deallocate_vsch_f();
    return Py_BuildValue("i",0);
}

PyObject * allocate_time_C(PyObject* self, PyObject* args)
{
    int dim1 = 0;
    if(!PyArg_ParseTuple(args, "i", &dim1))
    {
        return NULL;
    }
    allocate_time_f(&dim1);
    return Py_BuildValue("i", 0);
}

PyObject * deallocate_time_C(PyObject* self, PyObject* args)
{
    deallocate_time_f();
    return Py_BuildValue("i", 0);
}

PyObject * allocate_dopplerCoefficients_C(PyObject* self, PyObject* args)
{
    int dim1 = 0;
    if(!PyArg_ParseTuple(args, "i", &dim1))
    {
        return NULL;
    }
    allocate_dopplerCoefficients_f(&dim1);
    return Py_BuildValue("i", 0);
}

PyObject * deallocate_dopplerCoefficients_C(PyObject* self, PyObject* args)
{
    deallocate_dopplerCoefficients_f();
    return Py_BuildValue("i", 0);
}

PyObject * formslc_C(PyObject* self, PyObject* args)
{
    uint64_t var0;
    uint64_t var1;
    if(!PyArg_ParseTuple(args, "KK",&var0,&var1))
    {
        return NULL;
    }
    formslc_f(&var0,&var1);
    return Py_BuildValue("i", 0);
}

PyObject * setNumberGoodBytes_C(PyObject* self, PyObject* args)
{
    int var;
    if(!PyArg_ParseTuple(args, "i", &var))
    {
        return NULL;
    }
    setNumberGoodBytes_f(&var);
    return Py_BuildValue("i", 0);
}

PyObject * setNumberBytesPerLine_C(PyObject* self, PyObject* args)
{
    int var;
    if(!PyArg_ParseTuple(args, "i", &var))
    {
        return NULL;
    }
    setNumberBytesPerLine_f(&var);
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

PyObject * setLookSide_C(PyObject* self, PyObject* args)
{
    int var;
    if(!PyArg_ParseTuple(args, "i", &var))
    {
        return NULL;
    }
    setLookSide_f(&var);
    return Py_BuildValue("i",0);
}

PyObject * setNumberValidPulses_C(PyObject* self, PyObject* args)
{
    int var;
    if(!PyArg_ParseTuple(args, "i", &var))
    {
        return NULL;
    }
    setNumberValidPulses_f(&var);
    return Py_BuildValue("i", 0);
}

PyObject * setFirstSample_C(PyObject* self, PyObject* args)
{
    int var;
    if(!PyArg_ParseTuple(args, "i", &var))
    {
        return NULL;
    }
    setFirstSample_f(&var);
    return Py_BuildValue("i", 0);
}

PyObject * setNumberPatches_C(PyObject* self, PyObject* args)
{
    int var;
    if(!PyArg_ParseTuple(args, "i", &var))
    {
        return NULL;
    }
    setNumberPatches_f(&var);
    return Py_BuildValue("i", 0);
}

PyObject * setStartRangeBin_C(PyObject* self, PyObject* args)
{
    int var;
    if(!PyArg_ParseTuple(args, "i", &var))
    {
        return NULL;
    }
    setStartRangeBin_f(&var);
    return Py_BuildValue("i", 0);
}

PyObject * setNumberRangeBin_C(PyObject* self, PyObject* args)
{
    int var;
    if(!PyArg_ParseTuple(args, "i", &var))
    {
        return NULL;
    }
    setNumberRangeBin_f(&var);
    return Py_BuildValue("i", 0);
}

PyObject * setNumberAzimuthLooks_C(PyObject* self, PyObject* args)
{
    int var;
    if(!PyArg_ParseTuple(args, "i", &var))
    {
        return NULL;
    }
    setNumberAzimuthLooks_f(&var);
    return Py_BuildValue("i", 0);
}

PyObject * setRangeChirpExtensionPoints_C(PyObject* self, PyObject* args)
{
    int var;
    if(!PyArg_ParseTuple(args, "i", &var))
    {
        return NULL;
    }
    setRangeChirpExtensionPoints_f(&var);
    return Py_BuildValue("i", 0);
}

PyObject * setAzimuthPatchSize_C(PyObject* self, PyObject* args)
{
    int var;
    if(!PyArg_ParseTuple(args, "i", &var))
    {
        return NULL;
    }
    setAzimuthPatchSize_f(&var);
    return Py_BuildValue("i", 0);
}

PyObject * setOverlap_C(PyObject* self, PyObject* args)
{
    int var;
    if(!PyArg_ParseTuple(args, "i", &var))
    {
        return NULL;
    }
    setOverlap_f(&var);
    return Py_BuildValue("i", 0);
}

PyObject * setRanfftov_C(PyObject* self, PyObject* args)
{
    int var;
    if(!PyArg_ParseTuple(args, "i", &var))
    {
        return NULL;
    }
    setRanfftov_f(&var);
    return Py_BuildValue("i", 0);
}

PyObject * setRanfftiq_C(PyObject* self, PyObject* args)
{
    int var;
    if(!PyArg_ParseTuple(args, "i", &var))
    {
        return NULL;
    }
    setRanfftiq_f(&var);
    return Py_BuildValue("i", 0);
}

PyObject * setDebugFlag_C(PyObject* self, PyObject* args)
{
    int var;
    if(!PyArg_ParseTuple(args, "i", &var))
    {
        return NULL;
    }
    setDebugFlag_f(&var);
    return Py_BuildValue("i", 0);
}

PyObject * setCaltoneLocation_C(PyObject* self, PyObject* args)
{
    double var;
    if(!PyArg_ParseTuple(args, "d", &var))
    {
        return NULL;
    }
    setCaltoneLocation_f(&var);
    return Py_BuildValue("i", 0);
}

PyObject * setPlanetLocalRadius_C(PyObject* self, PyObject* args)
{
    double var;
    if(!PyArg_ParseTuple(args, "d", &var))
    {
        return NULL;
    }
    setPlanetLocalRadius_f(&var);
    return Py_BuildValue("i", 0);
}

PyObject * setBodyFixedVelocity_C(PyObject* self, PyObject* args)
{
    double var;
    if(!PyArg_ParseTuple(args, "d", &var))
    {
        return NULL;
    }
    setBodyFixedVelocity_f(&var);
    return Py_BuildValue("i", 0);
}

PyObject * setSpacecraftHeight_C(PyObject* self, PyObject* args)
{
    double var;
    if(!PyArg_ParseTuple(args, "d", &var))
    {
        return NULL;
    }
    setSpacecraftHeight_f(&var);
    return Py_BuildValue("i", 0);
}

PyObject * setPRF_C(PyObject* self, PyObject* args)
{
    double var;
    if(!PyArg_ParseTuple(args, "d", &var))
    {
        return NULL;
    }
    setPRF_f(&var);
    return Py_BuildValue("i", 0);
}

PyObject * setInPhaseValue_C(PyObject* self, PyObject* args)
{
    double var;
    if(!PyArg_ParseTuple(args, "d", &var))
    {
        return NULL;
    }
    setInPhaseValue_f(&var);
    return Py_BuildValue("i", 0);
}

PyObject * setQuadratureValue_C(PyObject* self, PyObject* args)
{
    double var;
    if(!PyArg_ParseTuple(args, "d", &var))
    {
        return NULL;
    }
    setQuadratureValue_f(&var);
    return Py_BuildValue("i", 0);
}

PyObject * setAzimuthResolution_C(PyObject* self, PyObject* args)
{
    double var;
    if(!PyArg_ParseTuple(args, "d", &var))
    {
        return NULL;
    }
    setAzimuthResolution_f(&var);
    return Py_BuildValue("i", 0);
}

PyObject * setRangeSamplingRate_C(PyObject* self, PyObject* args)
{
    double var;
    if(!PyArg_ParseTuple(args, "d", &var))
    {
        return NULL;
    }
    setRangeSamplingRate_f(&var);
    return Py_BuildValue("i", 0);
}

PyObject * setChirpSlope_C(PyObject* self, PyObject* args)
{
    double var;
    if(!PyArg_ParseTuple(args, "d", &var))
    {
        return NULL;
    }
    setChirpSlope_f(&var);
    return Py_BuildValue("i", 0);
}

PyObject * setRangePulseDuration_C(PyObject* self, PyObject* args)
{
    double var;
    if(!PyArg_ParseTuple(args, "d", &var))
    {
        return NULL;
    }
    setRangePulseDuration_f(&var);
    return Py_BuildValue("i", 0);
}

PyObject * setRadarWavelength_C(PyObject* self, PyObject* args)
{
    double var;
    if(!PyArg_ParseTuple(args, "d", &var))
    {
        return NULL;
    }
    setRadarWavelength_f(&var);
    return Py_BuildValue("i", 0);
}

PyObject * setRangeFirstSample_C(PyObject* self, PyObject* args)
{
    double var;
    if(!PyArg_ParseTuple(args, "d", &var))
    {
        return NULL;
    }
    setRangeFirstSample_f(&var);
    return Py_BuildValue("i", 0);
}

PyObject * setRangeSpectralWeighting_C(PyObject* self, PyObject* args)
{
    double var;
    if(!PyArg_ParseTuple(args, "d", &var))
    {
        return NULL;
    }
    setRangeSpectralWeighting_f(&var);
    return Py_BuildValue("i", 0);
}

PyObject * setSpectralShiftFraction_C(PyObject* self, PyObject* args)
{
    double var;
    if(!PyArg_ParseTuple(args, "d", &var))
    {
        return NULL;
    }
    setSpectralShiftFraction_f(&var);
    return Py_BuildValue("i", 0);
}

PyObject * setIMRC1_C(PyObject* self, PyObject* args)
{
    uint64_t var;
    if(!PyArg_ParseTuple(args, "K", &var))
    {
        return NULL;
    }
    setIMRC1_f(&var);
    return Py_BuildValue("i", 0);
}

PyObject * setIMMocomp_C(PyObject* self, PyObject* args)
{
    uint64_t var;
    if(!PyArg_ParseTuple(args, "K", &var))
    {
        return NULL;
    }
    setIMMocomp_f(&var);
    return Py_BuildValue("i", 0);
}

PyObject * setIMRCAS1_C(PyObject* self, PyObject* args)
{
    uint64_t var;
    if(!PyArg_ParseTuple(args, "K", &var))
    {
        return NULL;
    }
    setIMRCAS1_f(&var);
    return Py_BuildValue("i", 0);
}

PyObject * setIMRCRM1_C(PyObject* self, PyObject* args)
{
    uint64_t var;
    if(!PyArg_ParseTuple(args, "K", &var))
    {
        return NULL;
    }
    setIMRCRM1_f(&var);
    return Py_BuildValue("i", 0);
}

PyObject * setTransDat_C(PyObject* self, PyObject* args)
{
    uint64_t var;
    if(!PyArg_ParseTuple(args, "K", &var))
    {
        return NULL;
    }
    setTransDat_f(&var);
    return Py_BuildValue("i", 0);
}

PyObject * setIQFlip_C(PyObject* self, PyObject* args)
{
    char * var;
    int  varInt;
    if(!PyArg_ParseTuple(args, "s#", &var ,&varInt))
    {
        return NULL;
    }
    setIQFlip_f(var,&varInt);
    return Py_BuildValue("i", 0);
}

PyObject * setDeskewFlag_C(PyObject* self, PyObject* args)
{
    char * var;
    int  varInt;
    if(!PyArg_ParseTuple(args, "s#", &var ,&varInt))
    {
        return NULL;
    }
    setDeskewFlag_f(var,&varInt);
    return Py_BuildValue("i", 0);
}

PyObject * setSecondaryRangeMigrationFlag_C(PyObject* self, PyObject* args)
{
    char * var;
    int  varInt;
    if(!PyArg_ParseTuple(args, "s#", &var ,&varInt))
    {
        return NULL;
    }
    setSecondaryRangeMigrationFlag_f(var,&varInt);
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

PyObject * setTime_C(PyObject* self, PyObject* args)
{
    int dim1 = 0;
    PyObject * list;
    if(!PyArg_ParseTuple(args, "Oi", &list,&dim1))
    {
        return NULL;
    }
    if(!PyList_Check(list))
    {
        cout << "Error in file " << __FILE__ << " at line " << __LINE__ <<
                ". Expecting a list type object" << endl;
        exit(1);
    }
    double *  vectorV = new double[dim1];
    for(int i = 0; i  < dim1; ++i)
    {
        PyObject * listEl = PyList_GetItem(list,i);
        if(listEl == NULL)
        {
            cout << "Error in file " << __FILE__ << " at line " << __LINE__ <<
                    ". Cannot retrieve list element" << endl;
            exit(1);
        }
        vectorV[i] = (double) PyFloat_AsDouble(listEl);
        if(PyErr_Occurred() != NULL)
        {
            cout << "Error in file " << __FILE__ << " at line " << __LINE__ <<
                    ". Cannot convert Py Object to C " << endl;
            exit(1);
        }
    }
    setTime_f(vectorV, &dim1);
    delete [] vectorV;
    return Py_BuildValue("i", 0);
}

PyObject * setDopplerCentroidCoefficients_C(PyObject* self, PyObject* args)
{
    int dim1 = 0;
    PyObject * list;
    if(!PyArg_ParseTuple(args, "Oi", &list,&dim1))
    {
        return NULL;
    }
    if(!PyList_Check(list))
    {
        cout << "Error in file " << __FILE__ << " at line " << __LINE__ <<
                ". Expecting a list type object" << endl;
        exit(1);
    }
    double *  vectorV = new double[dim1];
    for(int i = 0; i  < dim1; ++i)
    {
        PyObject * listEl = PyList_GetItem(list,i);
        if(listEl == NULL)
        {
            cout << "Error in file " << __FILE__ << " at line " << __LINE__ <<
                    ". Cannot retrieve list element" << endl;
            exit(1);
        }
        vectorV[i] = (double) PyFloat_AsDouble(listEl);
        if(PyErr_Occurred() != NULL)
        {
            cout << "Error in file " << __FILE__ << " at line " << __LINE__ <<
                    ". Cannot convert Py Object to C " << endl;
            exit(1);
        }
    }
    setDopplerCentroidCoefficients_f(vectorV, &dim1);
    delete [] vectorV;
    return Py_BuildValue("i", 0);
}

PyObject * getMocompPosition_C(PyObject* self, PyObject* args)
{
    int dim1 = 0;
    int dim2 = 0;
    if(!PyArg_ParseTuple(args, "ii", &dim1, &dim2))
    {
        return NULL;
    }
    PyObject * list1 = PyList_New(dim1);
    double *  vectorV = new double[dim1*dim2];
    getMocompPosition_f(vectorV, &dim1, &dim2);
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

PyObject * getMocompIndex_C(PyObject* self, PyObject* args)
{
    int dim1 = 0;
    if(!PyArg_ParseTuple(args, "i", &dim1))
    {
        return NULL;
    }
    PyObject * list = PyList_New(dim1);
    int *  vectorV = new int[dim1];
    getMocompIndex_f(vectorV, &dim1);
    for(int i = 0; i  < dim1; ++i)
    {
        PyObject * listEl = PyLong_FromLong((long int) vectorV[i]);
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

PyObject * getMocompPositionSize_C(PyObject* self, PyObject* args)
{
    int var;
    getMocompPositionSize_f(&var);
    return Py_BuildValue("i",var);
}

PyObject *setPegPoint_C(PyObject *self, PyObject *args)
{
    double latitude;
    double longitude;
    double heading;
    if(!PyArg_ParseTuple(args,"ddd",&latitude,&longitude,&heading))
    {
        return NULL;
    }
    setPegPoint_f(&latitude,&longitude,&heading);
    return Py_BuildValue("i", 0);
}

PyObject *setPlanet_C(PyObject *self, PyObject *args)
{
    double a;
    double e2;
    if(!PyArg_ParseTuple(args,"dd",&a,&e2))
    {
        return NULL;
    }
    setPlanet_f(&a,&e2);
    return Py_BuildValue("i", 0);
}

PyObject *setEllipsoid_C(PyObject *self, PyObject *args)
{
    double spin;
    double gm;
    if(!PyArg_ParseTuple(args,"dd",&spin,&gm))
    {
        return NULL;
    }
    setEllipsoid_f(&spin,&gm);
    return Py_BuildValue("i", 0);
}

PyObject *setSlcWidth_C(PyObject *self, PyObject *args)
{
    int var;
    if(!PyArg_ParseTuple(args, "i", &var))
    {
        return NULL;
    }
    setSlcWidth_f(&var);
    return Py_BuildValue("i", 0);
}

PyObject *getStartingRange_C(PyObject *self, PyObject *args)
{
    double var;
    getStartingRange_f(&var);
    return Py_BuildValue("d", var);
}

PyObject *setStartingRange_C(PyObject *self, PyObject *args)
{
    double var;
    if(!PyArg_ParseTuple(args, "d", &var))
    {
        return NULL;
    }
    setStartingRange_f(&var);
    return Py_BuildValue("i", 0);
}

// ML 08-23-2013
PyObject *setShift_C(PyObject* self, PyObject* args)
{
    double var;
    if(!PyArg_ParseTuple(args, "d", &var))
    {
        return NULL;
    }
    setShift_f(&var);
    return Py_BuildValue("d", 0);
}
//ML

//end of file
