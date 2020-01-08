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




#ifndef bistaticgeo2rdrmodule_h
#define bistaticgeo2rdrmodule_h

#include <Python.h>
#include <stdint.h>
#include "bistaticgeo2rdrmoduleFortTrans.h"

extern "C"
{
    #include "orbit.h"
    #include "poly1d.h"

    void bistaticgeo2rdr_f(uint64_t *, uint64_t *, uint64_t *, uint64_t *, 
        uint64_t*, uint64_t*, uint64_t*);
    PyObject * bistaticgeo2rdr_C(PyObject *, PyObject *);
    void setEllipsoidMajorSemiAxis_f(double *);
    PyObject * setEllipsoidMajorSemiAxis_C(PyObject *, PyObject *);
    void setEllipsoidEccentricitySquared_f(double *);
    PyObject * setEllipsoidEccentricitySquared_C(PyObject *, PyObject *);
    void setRangePixelSpacing_f(double *);
    PyObject * setRangePixelSpacing_C(PyObject *, PyObject *);
    void setActiveRangeFirstSample_f(double *);
    PyObject * setActiveRangeFirstSample_C(PyObject *, PyObject *);
    void setPassiveRangeFirstSample_f(double *);
    PyObject * setPassiveRangeFirstSample_C(PyObject *, PyObject *);
    void setDopplerAccessor_f(cPoly1d *);
    PyObject * setDopplerAccessor_C(PyObject *, PyObject *);
    void setPRF_f(double *);
    PyObject * setPRF_C(PyObject *, PyObject *);
    void setRadarWavelength_f(double *);
    PyObject * setRadarWavelength_C(PyObject *, PyObject *);
    void setSensingStart_f(double *);
    PyObject * setSensingStart_C(PyObject *, PyObject *);
    void setLength_f(int *);
    PyObject * setLength_C(PyObject *, PyObject *);
    void setLookSide_f(int *);
    PyObject * setLookSide_C(PyObject *, PyObject *);
    void setWidth_f(int *);
    PyObject * setWidth_C(PyObject *, PyObject *);
    void setDemWidth_f(int *);
    PyObject * setDemWidth_C(PyObject *, PyObject *);
    void setDemLength_f(int *);
    PyObject * setDemLength_C(PyObject *, PyObject *);
    void setNumberRangeLooks_f(int*);
    PyObject * setNumberRangeLooks_C(PyObject*, PyObject*);
    void setNumberAzimuthLooks_f(int*);
    PyObject * setNumberAzimuthLooks_C(PyObject*, PyObject*);
    void setActiveOrbit_f(cOrbit *);
    PyObject * setActiveOrbit_C(PyObject *, PyObject *);
    void setPassiveOrbit_f(cOrbit *);
    PyObject * setPassiveOrbit_C(PyObject *, PyObject *);
    void setBistaticFlag_f(int*);
    PyObject * setBistaticFlag_C(PyObject*, PyObject*);
    void setOrbitMethod_f(int*);
    PyObject * setOrbitMethod_C(PyObject*, PyObject*);
}

static PyMethodDef bistaticgeo2rdr_methods[] =
{
    {"bistaticgeo2rdr_Py", bistaticgeo2rdr_C, METH_VARARGS, " "},
    {"setEllipsoidMajorSemiAxis_Py", setEllipsoidMajorSemiAxis_C, METH_VARARGS,
        " "},
    {"setEllipsoidEccentricitySquared_Py", setEllipsoidEccentricitySquared_C,
        METH_VARARGS, " "},
    {"setRangePixelSpacing_Py", setRangePixelSpacing_C, METH_VARARGS, " "},
    {"setActiveRangeFirstSample_Py", setActiveRangeFirstSample_C, METH_VARARGS, " "},
    {"setPassiveRangeFirstSample_Py", setPassiveRangeFirstSample_C, METH_VARARGS, " "},
    {"setDopplerAccessor_Py", setDopplerAccessor_C,METH_VARARGS, " "},
    {"setPRF_Py", setPRF_C, METH_VARARGS, " "},
    {"setRadarWavelength_Py", setRadarWavelength_C, METH_VARARGS, " "},
    {"setSensingStart_Py", setSensingStart_C, METH_VARARGS," "},
    {"setLength_Py", setLength_C, METH_VARARGS, " "},
    {"setWidth_Py", setWidth_C, METH_VARARGS, " "},
    {"setLookSide_Py", setLookSide_C, METH_VARARGS, " "},
    {"setDemWidth_Py", setDemWidth_C, METH_VARARGS, " "},
    {"setDemLength_Py", setDemLength_C, METH_VARARGS, " "},
    {"setNumberRangeLooks_Py", setNumberRangeLooks_C, METH_VARARGS, " "},
    {"setNumberAzimuthLooks_Py", setNumberAzimuthLooks_C, METH_VARARGS, " "},
    {"setActiveOrbit_Py", setActiveOrbit_C, METH_VARARGS, " "},
    {"setPassiveOrbit_Py", setPassiveOrbit_C, METH_VARARGS, " "},
    {"setBistaticCorrectionFlag_Py", setBistaticFlag_C, METH_VARARGS, " "},
    {"setOrbitMethod_Py", setOrbitMethod_C, METH_VARARGS, " "},
    {NULL, NULL, 0, NULL}
};
#endif

// end of file
