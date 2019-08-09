#include <Python.h>
#include <cassert>
#include <string>
#include <vector>
#include "core-src/greeter.h"
#include "core-src/hello.h"
#include "glue-src/greeter-py-object.h"

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

static PyObject *
greet_each(PyObject *self, PyObject *args)
{
    // https://stackoverflow.com/a/42868330/1424877
    PyObject *py_list = nullptr;
    if (PyArg_ParseTuple(args, "O!", &PyList_Type, &py_list)) {
        // pass
    } else {
        // `PyArg_ParseTuple` has already taken care of setting up the
        // appropriate exception to be raised in this case.
        return nullptr;
    }

    // Convert the Python list of strings into a C++ vector of strings.
    // In a real project, this should almost certainly be factored out
    // into a helper function. We inline it here for teaching purposes.

    std::vector<std::string> cpp_list;
    const int len = PyList_Size(py_list);
    for (int i=0; i < len; ++i) {
        PyObject *elt = PyList_GetItem(py_list, i);
        if (!PyUnicode_Check(elt)) {
            PyErr_Format(PyExc_TypeError, "sequence item %d: expected str instance, %s found", i, Py_TYPE(elt)->tp_name);
            return nullptr;
        }
        PyObject *bytes = PyUnicode_AsUTF8String(elt);
        const char *s = PyBytes_AsString(bytes);
        cpp_list.push_back(s);
        Py_DECREF(bytes);
    }

    std::vector<std::string> cpp_result = HelloWorld::greet_each(cpp_list);
    assert(cpp_result.size() == len);

    // Convert the C++ result back into a Python list of strings.
    // In a real project, this should almost certainly be factored out
    // into a helper function. We inline it here for teaching purposes.

    PyObject *py_result = PyList_New(cpp_result.size());
    for (int i=0; i < len; ++i) {
        PyList_SetItem(py_result, i, Py_BuildValue("s", cpp_result[i].c_str()));
    }
    return py_result;
}

static PyObject *
count_greeters(PyObject *self, PyObject *args)
{
    if (!PyArg_ParseTuple(args, "")) {
        return nullptr;
    }
    return Py_BuildValue("i", HelloWorld::Greeter::count());
}

// `PyMODINIT_FUNC` is a macro that includes `extern "C"` already.
PyMODINIT_FUNC PyInit_libhelloworld()
{
    // https://docs.python.org/3/extending/extending.html#the-module-s-method-table-and-initialization-function
    static constexpr PyMethodDef methods[] = {
        {"raise_error", raise_error, METH_VARARGS, "Invariably raise RuntimeError."},
        {"get_hello", get_hello, METH_VARARGS, "Return the string 'hello world'."},
        {"get_personalized_greeting", get_personalized_greeting, METH_VARARGS, "Return a personalized greeting."},
        {"greet_each", greet_each, METH_VARARGS, "Transform a list of names into a list of greetings."},
        {"count_greeters", count_greeters, METH_VARARGS, "Return the number of C++ Greeter objects in existence."},
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
    if (m == nullptr) {
        return nullptr;
    }

    PyObject *t = make_GreeterPyObject_type();
    if (t == nullptr) {
        Py_DECREF(m);
        return nullptr;
    }

    PyModule_AddObject(m, "Greeter", t);
    return m;
}
