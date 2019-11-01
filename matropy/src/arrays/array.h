#ifndef ARRAY_H
#define ARRAY_H

#include <Python.h>
#include "structmember.h"

double total(double *, int);
double mean(double *, int);
double stddev_pop(double *, int);
double stddev_sample(double *, int);

typedef struct {
    PyObject_HEAD
    int length;
    double *data;
} Array;

void Array_destroy(Array *self);

PyObject *Array_new(PyTypeObject *type, PyObject *args, PyObject *kwargs);

int Array_init(Array *self, PyObject *args, PyObject *kwargs);

static PyMemberDef Array_members[] = {
    {"length", T_INT, offsetof(Array, length), READONLY, "Length of array"},
    {NULL}
};

PyObject *Array_get(Array *self, PyObject *args);
PyObject *Array_aslist(Array *self, PyObject *args);

static PyMethodDef Array_methods[] = {
    {"get", (PyCFunction) Array_get, METH_VARARGS, "Fetch the value at the given index of the array"},
    {"aslist", (PyCFunction) Array_aslist, METH_NOARGS, "Return the array as a Python list"},
    {NULL}
};

static PyObject *tp_repr(Array *self){
    double *data = self -> data;
    int length = self -> length;
    PyObject *lst = PyList_New(length);
    int i;
    for (i = 0; i < length; i++){
        PyObject *d = PyFloat_FromDouble(data[i]);
        PyList_SetItem(lst, i, d);
    }
    PyObject* repr = PyObject_Repr(lst);
    PyObject* str = PyUnicode_AsEncodedString(repr, "utf-8", "~E~");
    const char *bytes = PyBytes_AS_STRING(str);
    if (self -> length > 0){
        return PyUnicode_FromFormat("%s(%s)", Py_TYPE(self) -> tp_name, bytes);
    }
}

static PyTypeObject PyArray = {
    PyVarObject_HEAD_INIT(NULL, 0)
	/* tp_name */           "matropy.arrays.Array",
	/* tp_basicsize */      sizeof(Array),
	/* tp_itemsize */       0,
	/* tp_dealloc */        (destructor)Array_destroy,
	/* tp_print */          0,
	/* tp_getattr */        0,
	/* tp_setattr */        0,
	/* tp_reserved */       0,
	/* tp_repr */           (reprfunc) tp_repr,
	/* tp_as_number */      0,
	/* tp_as_sequence */    0,
	/* tp_as_mapping */     0,
	/* tp_hash  */          0,
	/* tp_call */           0,
	/* tp_str */            0,
	/* tp_getattro */       0,
	/* tp_setattro */       0,
	/* tp_as_buffer */      0,
	/* tp_flags */          Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
	/* tp_doc */            "Base object for arrays",
	/* tp_traverse */       0,
	/* tp_clear */          0,
	/* tp_richcompare */    0,
	/* tp_weaklistoffset */ 0,
	/* tp_iter */           0,
	/* tp_iternext */       0,
	/* tp_methods */        Array_methods,
	/* tp_members */        Array_members,
	/* tp_getset */         0,
	/* tp_base */           0,
	/* tp_dict */           0,
	/* tp_descr_get */      0,
	/* tp_descr_set */      0,
	/* tp_dictoffset */     0,
	/* tp_init */           (initproc)Array_init,
	/* tp_alloc */          0,
	/* tp_new */            Array_new,
};

#endif
