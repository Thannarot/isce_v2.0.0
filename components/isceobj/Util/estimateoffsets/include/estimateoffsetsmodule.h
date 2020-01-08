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





#ifndef estimateoffsetsmodule_h
#define estimateoffsetsmodule_h

#include <Python.h>
#include <stdint.h>
#include "estimateoffsetsmoduleFortTrans.h"

extern "C"
{
        void estimateoffsets_f(uint64_t *, uint64_t *);
        PyObject * estimateoffsets_C(PyObject *, PyObject *);
        void getLocationAcross_f(int *, int *);
        void allocate_locationAcross_f(int *);
        void deallocate_locationAcross_f();
        PyObject * allocate_locationAcross_C(PyObject *, PyObject *);
        PyObject * deallocate_locationAcross_C(PyObject *, PyObject *);
        PyObject * getLocationAcross_C(PyObject *, PyObject *);
        void getLocationAcrossOffset_f(float *, int *);
        void allocate_locationAcrossOffset_f(int *);
        void deallocate_locationAcrossOffset_f();
        PyObject * allocate_locationAcrossOffset_C(PyObject *, PyObject *);
        PyObject * deallocate_locationAcrossOffset_C(PyObject *, PyObject *);
        PyObject * getLocationAcrossOffset_C(PyObject *, PyObject *);
        void getLocationDown_f(int *, int *);
        void allocate_locationDown_f(int *);
        void deallocate_locationDown_f();
        PyObject * allocate_locationDown_C(PyObject *, PyObject *);
        PyObject * deallocate_locationDown_C(PyObject *, PyObject *);
        PyObject * getLocationDown_C(PyObject *, PyObject *);
        void getLocationDownOffset_f(float *, int *);
        void allocate_locationDownOffset_f(int *);
        void deallocate_locationDownOffset_f();
        PyObject * allocate_locationDownOffset_C(PyObject *, PyObject *);
        PyObject * deallocate_locationDownOffset_C(PyObject *, PyObject *);
        PyObject * getLocationDownOffset_C(PyObject *, PyObject *);
        void getSNR_f(float *, int *);
        void allocate_snrRet_f(int *);
        void deallocate_snrRet_f();
        PyObject * allocate_snrRet_C(PyObject *, PyObject *);
        PyObject * deallocate_snrRet_C(PyObject *, PyObject *);
        PyObject * getSNR_C(PyObject *, PyObject *);
        void setLineLength1_f(int *);
        PyObject * setLineLength1_C(PyObject *, PyObject *);
        void setLineLength2_f(int *);
        PyObject * setLineLength2_C(PyObject *, PyObject *);
        void setFileLength1_f(int *);
        PyObject * setFileLength1_C(PyObject *, PyObject *);
        void setFileLength2_f(int *);
        PyObject * setFileLength2_C(PyObject *, PyObject *);
        void setFirstSampleAcross_f(int *);
        PyObject * setFirstSampleAcross_C(PyObject *, PyObject *);
        void setLastSampleAcross_f(int *);
        PyObject * setLastSampleAcross_C(PyObject *, PyObject *);
        void setNumberLocationAcross_f(int *);
        PyObject * setNumberLocationAcross_C(PyObject *, PyObject *);
        void setFirstSampleDown_f(int *);
        PyObject * setFirstSampleDown_C(PyObject *, PyObject *);
        void setLastSampleDown_f(int *);
        PyObject * setLastSampleDown_C(PyObject *, PyObject *);
        void setNumberLocationDown_f(int *);
        PyObject * setNumberLocationDown_C(PyObject *, PyObject *);
        void setAcrossGrossOffset_f(int *);
        PyObject * setAcrossGrossOffset_C(PyObject *, PyObject *);
        void setDownGrossOffset_f(int *);
        PyObject * setDownGrossOffset_C(PyObject *, PyObject *);
        void setFirstPRF_f(float *);
        PyObject * setFirstPRF_C(PyObject *, PyObject *);
        void setSecondPRF_f(float *);
        PyObject * setSecondPRF_C(PyObject *, PyObject *);
        void setDebugFlag_f(char *, int *);
        PyObject * setDebugFlag_C(PyObject *, PyObject *);
        void setWindowSize_f(int *);
        PyObject * setWindowSize_C(PyObject *, PyObject *);
        void setSearchWindowSize_f(int *);
        PyObject * setSearchWindowSize_C(PyObject *, PyObject *);
        void setZoomWindowSize_f(int *);
        PyObject * setZoomWindowSize_C(PyObject *, PyObject *);
        void setOversamplingFactor_f(int *);
        PyObject * setOversamplingFactor_C(PyObject *, PyObject *);
        void setIsComplex1_f(int *);
        PyObject * setIsComplex1_C(PyObject *, PyObject *);
        void setIsComplex2_f(int *);
        PyObject * setIsComplex2_C(PyObject *, PyObject *);
        void setBand1_f(int *);
        PyObject * setBand1_C(PyObject *, PyObject *);
        void setBand2_f(int *);
        PyObject * setBand2_C(PyObject *, PyObject *);
}

static PyMethodDef estimateoffsets_methods[] =
{
        {"estimateoffsets_Py", estimateoffsets_C, METH_VARARGS, " "},
        {"allocate_locationAcross_Py", allocate_locationAcross_C, METH_VARARGS, " "},
        {"deallocate_locationAcross_Py", deallocate_locationAcross_C, METH_VARARGS, " "},
        {"getLocationAcross_Py", getLocationAcross_C, METH_VARARGS, " "},
        {"allocate_locationAcrossOffset_Py", allocate_locationAcrossOffset_C, METH_VARARGS, " "},
        {"deallocate_locationAcrossOffset_Py", deallocate_locationAcrossOffset_C, METH_VARARGS, " "},
        {"getLocationAcrossOffset_Py", getLocationAcrossOffset_C, METH_VARARGS, " "},
        {"allocate_locationDown_Py", allocate_locationDown_C, METH_VARARGS, " "},
        {"deallocate_locationDown_Py", deallocate_locationDown_C, METH_VARARGS, " "},
        {"getLocationDown_Py", getLocationDown_C, METH_VARARGS, " "},
        {"allocate_locationDownOffset_Py", allocate_locationDownOffset_C, METH_VARARGS, " "},
        {"deallocate_locationDownOffset_Py", deallocate_locationDownOffset_C, METH_VARARGS, " "},
        {"getLocationDownOffset_Py", getLocationDownOffset_C, METH_VARARGS, " "},
        {"allocate_snrRet_Py", allocate_snrRet_C, METH_VARARGS, " "},
        {"deallocate_snrRet_Py", deallocate_snrRet_C, METH_VARARGS, " "},
        {"getSNR_Py", getSNR_C, METH_VARARGS, " "},
        {"setLineLength1_Py", setLineLength1_C, METH_VARARGS, " "},
        {"setLineLength2_Py", setLineLength2_C, METH_VARARGS, " "},
        {"setFileLength1_Py", setFileLength1_C, METH_VARARGS, " "},
        {"setFileLength2_Py", setFileLength2_C, METH_VARARGS, " "},
        {"setFirstSampleAcross_Py", setFirstSampleAcross_C, METH_VARARGS, " "},
        {"setLastSampleAcross_Py", setLastSampleAcross_C, METH_VARARGS, " "},
        {"setNumberLocationAcross_Py", setNumberLocationAcross_C, METH_VARARGS, " "},
        {"setFirstSampleDown_Py", setFirstSampleDown_C, METH_VARARGS, " "},
        {"setLastSampleDown_Py", setLastSampleDown_C, METH_VARARGS, " "},
        {"setNumberLocationDown_Py", setNumberLocationDown_C, METH_VARARGS, " "},
        {"setAcrossGrossOffset_Py", setAcrossGrossOffset_C, METH_VARARGS, " "},
        {"setDownGrossOffset_Py", setDownGrossOffset_C, METH_VARARGS, " "},
        {"setFirstPRF_Py", setFirstPRF_C, METH_VARARGS, " "},
        {"setSecondPRF_Py", setSecondPRF_C, METH_VARARGS, " "},
        {"setDebugFlag_Py", setDebugFlag_C, METH_VARARGS, " "},
        {"setWindowSize_Py", setWindowSize_C, METH_VARARGS, " "},
        {"setSearchWindowSize_Py", setSearchWindowSize_C, METH_VARARGS, " "},
        {"setZoomWindowSize_Py", setZoomWindowSize_C, METH_VARARGS, " "},
        {"setOversamplingFactor_Py", setOversamplingFactor_C, METH_VARARGS, " "},
        {"setIsComplex1_Py", setIsComplex1_C, METH_VARARGS, " "},
        {"setIsComplex2_Py", setIsComplex2_C, METH_VARARGS, " "},
        {"setBand1_Py", setBand1_C, METH_VARARGS, " "},
        {"setBand2_Py", setBand2_C, METH_VARARGS, " "},
        {NULL, NULL, 0, NULL}
};
#endif //estimateoffsetsmodule_h
