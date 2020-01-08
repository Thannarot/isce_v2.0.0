/*#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Author: Piyush Agram
# Copyright 2014, by the California Institute of Technology. ALL RIGHTS RESERVED.
# United States Government Sponsorship acknowledged.
# Any commercial use must be negotiated with the Office of Technology Transfer at
# the California Institute of Technology.
# This software may be subject to U.S. export control laws.
# By accepting this software, the user agrees to comply with all applicable U.S.
# export laws and regulations. User has the responsibility to obtain export licenses,
# or other export authority as may be required before exporting such information to
# foreign countries or providing access to foreign persons.
#
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef watermaskmodule_h
#define watermaskmodule_h


#include <Python.h>
#include <stdint.h>
#include "watermask.h"

extern "C"
{
    PyObject* watermask_C(PyObject *, PyObject *);
    PyObject* watermaskxy_C(PyObject *, PyObject *);
}

static PyMethodDef watermask_methods[] =
{
    {"watermask_Py", watermask_C, METH_VARARGS, " "},
    {"watermaskxy_Py", watermaskxy_C, METH_VARARGS, " "},
    {NULL, NULL, 0, NULL}
};

#endif watermaskmodule_h
