#include <Python.h>
#include "array.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "debug.h"

static PyObject *Array_total(PyObject *self, PyObject *args){
    PyObject *seq;
    double result;
    int len;
    int i;

    double *buffer;

    if (!PyArg_ParseTuple(args, "O", &seq)){
        return NULL;
    }
    seq = PySequence_Fast(seq, "Argument must be an iterable");
    if (!seq){
        return 0;
    }
    len = PySequence_Fast_GET_SIZE(seq);
    buffer = malloc(len * sizeof(double));

    if (!buffer){
        Py_DECREF(seq);
        return PyErr_NoMemory();
    }
    for (i = 0; i < len; i++){
        PyObject *float_item;
        PyObject *item = PySequence_Fast_GET_ITEM(seq, i);
        if (!item){
            Py_DECREF(seq);
            free(buffer);
            return 0;
        }
        float_item = PyNumber_Float(item);
        if (!float_item){
            Py_DECREF(seq);
            free(buffer);
            PyErr_SetString(PyExc_TypeError, "Item encountered is not float");
            return 0;
        }
        buffer[i] = PyFloat_AS_DOUBLE(float_item);
        Py_DECREF(float_item);
    }
    Py_DECREF(seq);
    result = total(buffer, len);
    return Py_BuildValue("d", result);
}

static PyObject *Array_mean(PyObject *self, PyObject *args){
    PyObject *seq;
    double result;
    int len;
    int i;

    double *buffer;

    if (!PyArg_ParseTuple(args, "O", &seq)){
        return NULL;
    }
    seq = PySequence_Fast(seq, "Argument must be an iterable");
    if (!seq){
        return 0;
    }
    len = PySequence_Fast_GET_SIZE(seq);
    buffer = malloc(len * sizeof(double));

    if (!buffer){
        Py_DECREF(seq);
        return PyErr_NoMemory();
    }
    for (i = 0; i < len; i++){
        PyObject *float_item;
        PyObject *item = PySequence_Fast_GET_ITEM(seq, i);
        if (!item){
            Py_DECREF(seq);
            free(buffer);
            return 0;
        }
        float_item = PyNumber_Float(item);
        if (!float_item){
            Py_DECREF(seq);
            free(buffer);
            PyErr_SetString(PyExc_TypeError, "Item encountered is not float");
            return 0;
        }
        buffer[i] = PyFloat_AS_DOUBLE(float_item);
        Py_DECREF(float_item);
    }
    Py_DECREF(seq);
    result = mean(buffer, len);
    return Py_BuildValue("d", result);
}

static PyObject *Array_stddev(PyObject *self, PyObject *args, PyObject *kwargs){
    PyObject *seq;
    double result;
    int len;
    int i;
    double *buffer;

    static char *argnames[] = {"l", "type", NULL};
    char *type = "pop";

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O|s", argnames, &seq, &type)){
        return NULL;
    }
    seq = PySequence_Fast(seq, "Argument must be an iterable");
    if (!seq){
        return 0;
    }
    len = PySequence_Fast_GET_SIZE(seq);
    buffer = malloc(len * sizeof(double));

    if (!buffer){
        Py_DECREF(seq);
        return PyErr_NoMemory();
    }
    for (i = 0; i < len; i++){
        PyObject *float_item;
        PyObject *item = PySequence_Fast_GET_ITEM(seq, i);
        if (!item){
            Py_DECREF(seq);
            free(buffer);
            return 0;
        }
        float_item = PyNumber_Float(item);
        if (!float_item){
            Py_DECREF(seq);
            free(buffer);
            PyErr_SetString(PyExc_TypeError, "Item encountered is not float");
            return 0;
        }
        buffer[i] = PyFloat_AS_DOUBLE(float_item);
        Py_DECREF(float_item);
    }
    Py_DECREF(seq);
    if (strcmp(type, "pop") == 0)
        result = stddev_pop(buffer, len);
    else if (strcmp(type, "sample") == 0)
        result = stddev_sample(buffer, len);
    else
        PyErr_SetString(PyExc_ValueError, "Undefined 'type' string: Input 'pop' or 'sample'");
    return Py_BuildValue("d", result);
}

static PyMethodDef MatropyArrayMethods[] = {
    {"total", Array_total, METH_VARARGS, "Finds the sum of a given sequence of numbers"},
    {"mean", Array_mean, METH_VARARGS, "Finds the mean of a given sequence of numbers"},
    {"stddev", Array_stddev, METH_VARARGS | METH_KEYWORDS, "Finds the standard deviation of a given sample or population"},
    {0, 0, NULL, 0}
};

static struct PyModuleDef matropyarray = {
    PyModuleDef_HEAD_INIT,
    "arrays",
    "The submodule that deals with array computation",
    -1,
    MatropyArrayMethods
};

PyMODINIT_FUNC PyInit_arrays(void){
    PyObject *m;
    m = PyModule_Create(&matropyarray);

    if (m == NULL) return NULL;

    if (PyType_Ready(&PyArray) < 0) return NULL;
    Py_INCREF(&PyArray);
    PyModule_AddObject(m, "Array", (PyObject *) &PyArray);
    return m;
}
