#include <stdio.h>
#include <Python.h>
#include "rand.h"

static PyObject *Rand_lcg_random(PyObject *self, PyObject *args){
    long upper;
    int size;
    if (!PyArg_ParseTuple(args, "il", &size, &upper)){
        return NULL;
    }

    PyObject *list = PyList_New(size);
    long *series;
    series = malloc(size * sizeof(long));
    series = lcg(size, upper);
    int i;
    for (i = 0; i < size; i++){
        PyObject *n = PyLong_FromLong(series[i]);
        PyList_SetItem(list, i, n);
    }
    return list;
}

static PyMethodDef MatropyRandomMethods[] = {
    {"lcg_random", Rand_lcg_random, METH_VARARGS, "Returns a list of pseudorandom numbers of length 'size' using the Linear Congruential Generator"},
    {0, 0, NULL, 0}
};

static struct PyModuleDef matropyrand = {
    PyModuleDef_HEAD_INIT,
    "rand",
    "Submodule for random number generation and manipulation",
    -1,
    MatropyRandomMethods
};

PyMODINIT_FUNC PyInit_rand(void){
    return PyModule_Create(&matropyrand);
}
