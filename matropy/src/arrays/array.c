#include <stdio.h>
#include "array.h"
#include <math.h>
#include "debug.h"

double mean(double *arr, int len){
    double total = 0.0;
    int i;
    for (i = 0; i < len; i++){
        total = total + *(arr + i);
    }
    return total / len;
}

double total(double *arr, int len){
    double total = 0.0;
    int i;
    for (i = 0; i < len; i++){
        total = total + *(arr + i);
    }
    return total;
}

double stddev_pop(double *arr, int len){
    double stddev = 0.0;
    int i;
    double avg = mean(arr, len);
    for (i = 0; i < len; i++){
        stddev += pow((arr[i] - avg), 2);
    }
    return sqrt(stddev / len);
}

double stddev_sample(double *arr, int len){
    double stddev = 0.0;
    int i;
    double avg = mean(arr, len);
    for (i = 0; i < len; i++){
        stddev += pow((arr[i] - avg), 2);
    }
    return sqrt(stddev / (len - 1));
}

void Array_destroy(Array *self){
    Py_TYPE(self) -> tp_free((PyObject *) self);
}

PyObject *Array_new(PyTypeObject *type, PyObject *args, PyObject *kwargs){
    Array *self = (Array *) type -> tp_alloc(type, 0);
    return (PyObject *)self;
}
//
int Array_init(Array *self, PyObject *args, PyObject *kwargs){
    if (self == NULL) return 0;
    PyObject *data;
    if (!PyArg_ParseTuple(args, "O", &data)){
        return -1;
    }
    data = PySequence_Fast(data, "Argument must be an iterable");
    if (!data){
        return 0;
    }
    int len = PySequence_Fast_GET_SIZE(data);
    self -> data = malloc(len * sizeof(double));
    if (!self -> data){
        Py_DECREF(data);
        return 0;
    }
    int i;
    for (i = 0; i < len; i++){
        PyObject *float_item;
        PyObject *item = PySequence_Fast_GET_ITEM(data, i);
        if (!item){
            Py_DECREF(data);
            free(self -> data);
            return 0;
        }
        float_item = PyNumber_Float(item);
        if (!float_item){
            Py_DECREF(data);
            free(self -> data);
            PyErr_SetString(PyExc_TypeError, "Item encountered is not float");
            return 0;
        }
        self -> data[i] = PyFloat_AS_DOUBLE(float_item);
        Py_DECREF(float_item);
    }
    self -> length = len;
    return 0;
}
//
PyObject *Array_get(Array *self, PyObject *args){
    if (self == NULL) return NULL;

    int index = 0;
    if (!PyArg_ParseTuple(args, "i", &index)) return NULL;

    if (index > self -> length - 1 || index < 0){
        PyErr_SetString(PyExc_IndexError, "Invalid index for array");
        return NULL;
    }

    return PyFloat_FromDouble(self -> data[index]);
}

PyObject *Array_aslist(Array *self, PyObject *args){
    if (self == NULL) return NULL;
    double *data = self -> data;
    PyObject *list = PyList_New(self -> length);
    int i;
    for (i = 0; i < self -> length; i++){
        PyObject *d = PyFloat_FromDouble(data[i]);
        PyList_SetItem(list, i, d);
    }
    return list;
}
