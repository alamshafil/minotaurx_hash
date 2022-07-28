#define PY_SSIZE_T_CLEAN

#include <Python.h>

#include "x16r.h"

static PyObject *minotaurx_getpowhash(PyObject *self, PyObject *args)
{
    char *output;
    PyObject *value;
#if PY_MAJOR_VERSION >= 3
    PyBytesObject *input;
#else
    PyStringObject *input;
#endif
    if (!PyArg_ParseTuple(args, "S", &input))
        return NULL;
    Py_INCREF(input);
    output = PyMem_Malloc(32);

#if PY_MAJOR_VERSION >= 3
    minotaurx_hash((char *)PyBytes_AsString((PyObject*) input), output);
#else
    minotaurx_hash((char *)PyString_AsString((PyObject*) input), output);
#endif
    Py_DECREF(input);
#if PY_MAJOR_VERSION >= 3
    value = Py_BuildValue("y#", output, 32);
#else
    value = Py_BuildValue("s#", output, 32);
#endif
    PyMem_Free(output);
    return value;
}

static PyMethodDef MinotaurXMethods[] = {
    { "getPoWHash", minotaurx_getpowhash, METH_VARARGS, "Returns the proof of work hash using MinotaurX hash" },
    { NULL, NULL, 0, NULL }
};

#if PY_MAJOR_VERSION >= 3
static struct PyModuleDef MinotaurXModule = {
    PyModuleDef_HEAD_INIT,
    "minotaurx_hash",
    "...",
    -1,
    MinotaurXMethods
};

PyMODINIT_FUNC PyInit_minotaurx_hash(void) {
    return PyModule_Create(&MinotaurXModule);
}

#else

PyMODINIT_FUNC initminotaurx_hash(void) {
    (void) Py_InitModule("minotaurx_hash", MinotaurXMethods);
}
#endif
