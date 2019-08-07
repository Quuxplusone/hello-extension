#include <Python.h>
#include <string>
#include "core-src/hello.h"

static PyObject *
raise_error(PyObject *self, PyObject *args)
{
    // https://pythonextensionpatterns.readthedocs.io/en/latest/exceptions.html
    PyErr_SetString(PyExc_RuntimeError, "raise_error always raises this exception");
    return nullptr;
}

static PyObject *
get_hello(PyObject *self, PyObject *args)
{
    // https://docs.python.org/3/c-api/arg.html#building-values
    return Py_BuildValue("s", "hello world");
}

static PyObject *
get_personalized_greeting(PyObject *self, PyObject *args)
{
    const char *who = "whoever you are";
    if (PyArg_ParseTuple(args, "|s", &who)) {
        // `PyArg_ParseTuple` has set `who` appropriately,
        // or left it untouched if the user didn't provide a value.
    } else {
        // `PyArg_ParseTuple` has already taken care of setting up the
        // appropriate exception to be raised in this case.
        return nullptr;
    }
    std::string result = HelloWorld::get_personalized_greeting(who);
    return Py_BuildValue("s#", result.data(), result.size());
}

// `PyMODINIT_FUNC` is a macro that includes `extern "C"` already.
PyMODINIT_FUNC PyInit_libhelloworld()
{
    // https://docs.python.org/3/extending/extending.html#the-module-s-method-table-and-initialization-function
    static constexpr PyMethodDef methods[] = {
        {"raise_error", raise_error, METH_VARARGS, "Invariably raise RuntimeError."},
        {"get_hello", get_hello, METH_VARARGS, "Return the string 'hello world'."},
        {"get_personalized_greeting", get_personalized_greeting, METH_VARARGS, "Return a personalized greeting."},
        {nullptr, nullptr, 0, nullptr},
    };

    // https://docs.python.org/3/c-api/module.html
    static PyModuleDef module = {
        PyModuleDef_HEAD_INIT,
        "libhelloworld-modulename",  // m_name
        nullptr,  // m_doc
        0,        // m_size
        const_cast<PyMethodDef*>(methods),  // m_methods
        nullptr,  // m_slots
        nullptr,  // m_traverse
        nullptr,  // m_clear
        nullptr,  // m_free
    };

    PyObject *m = PyModule_Create(&module);
    return m;
}
