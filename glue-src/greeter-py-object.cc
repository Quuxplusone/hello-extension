#include <Python.h>
#include "core-src/greeter.h"

namespace {

struct GreeterPyObject {
    PyObject_HEAD
    HelloWorld::Greeter *obj_;

    static int init(PyObject *self_, PyObject *args, PyObject *kwargs) {
        GreeterPyObject *self = reinterpret_cast<GreeterPyObject *>(self_);
        const char *who = nullptr;
        if (!PyArg_ParseTuple(args, "s", &who)) {
            // `PyArg_ParseTuple` has already taken care of setting up the
            // appropriate exception to be raised in this case.
            return -1;
        }

        self->obj_ = new HelloWorld::Greeter(who);
        return 0;
    }

    static void dealloc(PyObject *self_) {
        GreeterPyObject *self = reinterpret_cast<GreeterPyObject *>(self_);
        delete self->obj_;
        Py_TYPE(self)->tp_free(self);
    }

    static PyObject *get_greeting(PyObject *self_, PyObject *args) {
        GreeterPyObject *self = reinterpret_cast<GreeterPyObject *>(self_);
        if (!PyArg_ParseTuple(args, "")) {
            // `PyArg_ParseTuple` has already taken care of setting up the
            // appropriate exception to be raised in this case.
            return nullptr;
        }
        std::string result = self->obj_->get_greeting();
        return Py_BuildValue("s", result.c_str());
    }

    static PyObject *repr(PyObject *self_) {
        GreeterPyObject *self = reinterpret_cast<GreeterPyObject *>(self_);
        PyObject *who = Py_BuildValue("s", self->obj_->get_who().c_str());
        PyObject *repr_of_who = PyObject_Repr(who);
        PyObject *bytes_in_repr_of_who = PyUnicode_AsUTF8String(repr_of_who);
        const char *s = PyBytes_AsString(bytes_in_repr_of_who);
        std::string result = "libhelloworld.Greeter(" + std::string(s) + ")";
        Py_DECREF(bytes_in_repr_of_who);
        Py_DECREF(repr_of_who);
        Py_DECREF(who);
        return Py_BuildValue("s", result.c_str());
    }

    static PyObject *str(PyObject *self_) {
        GreeterPyObject *self = reinterpret_cast<GreeterPyObject *>(self_);
        std::string result = self->obj_->get_greeting();
        return Py_BuildValue("s", result.c_str());
    }

};

} // anonymous namespace

PyObject *make_GreeterPyObject_type()
{
    static constexpr PyMethodDef methods[] = {
        { "get_greeting", GreeterPyObject::get_greeting, METH_VARARGS, "return the greeting" },
        { nullptr, nullptr, 0, nullptr },
    };

    static PyTypeObject type = {
        PyVarObject_HEAD_INIT(NULL, 0)
        "libhelloworld.Greeter",  // tp_name
        sizeof(GreeterPyObject),  // tp_basicsize
        0,        // tp_itemsize
        GreeterPyObject::dealloc,  // tp_dealloc
        nullptr,  // tp_print
        nullptr,  // tp_getattr
        nullptr,  // tp_setattr
        nullptr,  // tp_as_async
        GreeterPyObject::repr,  // tp_repr
        nullptr,  // tp_as_number
        nullptr,  // tp_as_sequence
        nullptr,  // tp_as_mapping
        nullptr,  // tp_hash
        nullptr,  // tp_call
        GreeterPyObject::str,  // tp_str
        nullptr,  // tp_getattro
        nullptr,  // tp_setattro
        nullptr,  // tp_as_buffer
        Py_TPFLAGS_DEFAULT,  // tp_flags
        "An object that can store a greeting and deliver it later",  // tp_doc
        nullptr,  // tp_traverse
        nullptr,  // tp_clear
        nullptr,  // tp_richcompare
        0,        // tp_weaklistoffset
        nullptr,  // tp_iter
        nullptr,  // tp_iternext
        const_cast<PyMethodDef*>(methods),  // tp_methods
        nullptr,  // tp_members
        nullptr,  // tp_getset
        nullptr,  // tp_base
        nullptr,  // tp_dict
        nullptr,  // tp_descr_get
        nullptr,  // tp_descr_set
        0,        // tp_dictoffset
        GreeterPyObject::init,  // tp_init
        nullptr,  // tp_alloc
        PyType_GenericNew,  // tp_new
        nullptr,  // tp_free
        nullptr,  // tp_is_gc
        nullptr,  // tp_bases
        nullptr,  // tp_mro
        nullptr,  // tp_cache
        nullptr,  // tp_subclasses
        nullptr,  // tp_weaklist
        nullptr,  // tp_del
        0,        // tp_version_tag
        nullptr,  // tp_finalize
    };

    if (PyType_Ready(&type) != 0) {
        // `PyType_Ready` has already taken care of setting up the
        // appropriate exception to be raised in this case.
        return nullptr;
    }
    Py_INCREF(&type);
    return reinterpret_cast<PyObject *>(&type);
}
