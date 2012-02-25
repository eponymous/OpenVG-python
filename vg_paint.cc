/*
 * Copyright (c) 2012 Dan Eicher
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library in the file COPYING;
 * if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include "openvg_module.h"

static PyObject*
PyVGPaint__get_color(PyVGPaint *self, void * UNUSED(closure))
{
    PyObject *py_retval;
    
    py_retval = Py_BuildValue((char *) "N", PyLong_FromUnsignedLong(vgGetColor(self->obj)));

    if (check_error()) {
        Py_DECREF(py_retval);
        return NULL;
    }

    return py_retval;
}

static int
PyVGPaint__set_color(PyVGPaint *self, PyObject *value, void * UNUSED(closure))
{
    PyObject *py_retval;
    VGuint tmp_value;
    
    py_retval = Py_BuildValue((char *) "(O)", value);
    if (!PyArg_ParseTuple(py_retval, (char *) "I", &tmp_value)) {
        Py_DECREF(py_retval);
        return -1;
    }
    vgSetColor(self->obj, tmp_value);
    Py_DECREF(py_retval);

    return check_error() ? -1 : 0;
}

PyDoc_STRVAR(PyVGPaint_color__doc__,
".. attribute:: color\n"
"\n"
"   Shorthand method for setting the VG_PAINT_COLOR attribute.\n"
"\n"
"   :type int: 32-bit non-premultiplied sRGBA_8888 color.\n"
);

static PyGetSetDef PyVGPaint__getsets[] = {
    {
        (char*) "color", /* attribute name */
        (getter) PyVGPaint__get_color, /* C function to get the attribute */
        (setter) PyVGPaint__set_color, /* C function to set the attribute */
        PyVGPaint_color__doc__, /* optional doc string */
        NULL /* optional additional data for getter and setter */
    },
    { NULL, NULL, NULL, NULL, NULL }
};

static int
PyVGPaint__tp_init(PyVGPaint *self, PyObject *args, PyObject *kwargs)
{
    const char *keywords[] = {NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "", (char **) keywords)) {
        return -1;
    }

    if ((self->obj = vgCreatePaint()) == VG_INVALID_HANDLE)
        return -1;

    /* no check_error */
    return 0;
}


PyDoc_STRVAR(OpenVG_vgPaintPattern__doc__,
".. function:: pattern(pattern)\n"
"\n"
"   Set or clear the current pattern.\n"
"\n"
"   :arg pattern: The pattern.\n"
"   :type pattern: VGImage or None.\n"
"\n"
"   :error: VG_BAD_HANDLE_ERROR.\n"
"   :error: VG_IMAGE_IN_USE_ERROR.\n"
);

static PyObject *
OpenVG_vgPaintPattern(PyVGPaint *self, PyObject *args, PyObject *kwargs)
{
    PyObject *pattern;
    const char *keywords[] = {"pattern", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O", (char **) keywords, &pattern)) {
        return NULL;
    }

    if (PyObject_TypeCheck(pattern, &PyVGImage_Type))
        vgPaintPattern(self->obj, ((PyVGImage*)pattern)->obj);
    else if (pattern == Py_None)
        vgPaintPattern(self->obj, VG_INVALID_HANDLE);
    else {
        PyErr_SetString(PyExc_TypeError,
                        "VGPaint.pattern(): arg must be a VGImage or None");
        return NULL;
    }

    if (check_error())
        return NULL;

    Py_RETURN_NONE;
}


static PyMethodDef PyVGPaint_methods[] = {
    {(char *) "pattern",
     (PyCFunction) OpenVG_vgPaintPattern,
     METH_KEYWORDS|METH_VARARGS,
     OpenVG_vgPaintPattern__doc__
    },
    {NULL, NULL, 0, NULL}
};

static PyObject *
PyVGPaint__mp_subscript(PyVGPaint *self, PyObject *value)
{
    PyObject *py_retval = NULL;
    VGuint key = PyLong_AsUnsignedLong(value);

    switch (key) {
        case VG_PAINT_TYPE:
        case VG_PAINT_COLOR_RAMP_SPREAD_MODE:
        case VG_PAINT_PATTERN_TILING_MODE:
            py_retval = PyLong_FromUnsignedLong(vgGetParameteri(self->obj, key));
            break;
        case VG_PAINT_COLOR_RAMP_PREMULTIPLIED:
            py_retval = PyBool_FromLong(vgGetParameteri(self->obj, key));
            break;
        case VG_PAINT_COLOR:
        case VG_PAINT_COLOR_RAMP_STOPS:
        case VG_PAINT_LINEAR_GRADIENT:
        case VG_PAINT_RADIAL_GRADIENT: {
            int idx;
            int count = vgGetParameterVectorSize(self->obj, key);
            VGfloat *values = (VGfloat*)malloc(sizeof(VGfloat) * count);

            if (count) {
                vgGetParameterfv(self->obj, key, count, values);

                py_retval = PyList_New(count);

                for (idx = 0; idx < count; idx++) {
                    PyList_SET_ITEM(py_retval, idx, PyFloat_FromDouble(values[idx]));
                }
            }
            free(values);
            break;
        }
        default:
            PyErr_SetString(PyExc_IndexError,
                            "VGPaint[key]: key must be a VGPaintParamType");
            return NULL;
    }

    if (check_error()) {
        Py_XDECREF(py_retval);
        return NULL;
    }

    return Py_BuildValue((char *) "N", py_retval);
}

static int
PyVGPaint__mp_ass_subscript(PyVGPaint *self, PyObject *pykey, PyObject *value)
{
    VGuint key = PyLong_AsUnsignedLong(pykey);
    
    switch (key) {
        case VG_PAINT_TYPE:
        case VG_PAINT_COLOR_RAMP_SPREAD_MODE:
        case VG_PAINT_PATTERN_TILING_MODE:
            vgSetParameteri(self->obj, key, PyLong_AsUnsignedLong(value));
            break;
        case VG_PAINT_COLOR_RAMP_PREMULTIPLIED:
            if (PyBool_Check(value) == 0) {
                PyErr_SetString(PyExc_TypeError, "VGPaint[key]: expected a bool");
                return -1;
            }
            vgSetParameteri(self->obj, key, PyObject_IsTrue(value));
            break;
        case VG_PAINT_COLOR:
        case VG_PAINT_COLOR_RAMP_STOPS:
        case VG_PAINT_LINEAR_GRADIENT:
        case VG_PAINT_RADIAL_GRADIENT: {
            if (PyList_Check(value) == 0) {
                PyErr_SetString(PyExc_TypeError,
                                "VGPaint[key]: expected a list of floats");
                return -1;
            }

            int idx;
            int count = PyList_Size(value);
            VGfloat *tmp_values = (VGfloat*)malloc(sizeof(VGfloat) * count);

            for (idx = 0; idx < count; idx++) {
                PyObject *py_tmp = PyList_GetItem(value, idx);
                tmp_values[idx] = (float) PyFloat_AsDouble(py_tmp);
            }

            vgSetParameterfv(self->obj, key, count, tmp_values);

            free(tmp_values);
            break;
        }
        default:
            PyErr_SetString(PyExc_IndexError,
                            "VGPaint[key]: key must be a VGPaintParamType");
            return -1;
    }

    return check_error() ? -1 : 0;
}

static PyMappingMethods PyVGPaint__tp_as_mapping = {
	(lenfunc) NULL,	                                /* mp_length */
	(binaryfunc) PyVGPaint__mp_subscript,	        /* mp_subscript */
	(objobjargproc) PyVGPaint__mp_ass_subscript,  /* mp_ass_subscript */
};

static void
PyVGPaint__tp_dealloc(PyVGPaint *self)
{
    if (self->obj) {
        VGPaint tmp = self->obj;
        self->obj = NULL;
        vgDestroyPaint(tmp);
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}

PyTypeObject PyVGPaint_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    (char *) "VG.VGPaint",                     /* tp_name */
    sizeof(PyVGPaint),                             /* tp_basicsize */
    0,                                             /* tp_itemsize */
    /* methods */
    (destructor)PyVGPaint__tp_dealloc,             /* tp_dealloc */
    (printfunc)0,                                  /* tp_print */
    (getattrfunc)NULL,                             /* tp_getattr */
    (setattrfunc)NULL,                             /* tp_setattr */
    (cmpfunc)NULL,                                 /* tp_compare */
    (reprfunc)NULL,                                /* tp_repr */
    (PyNumberMethods*)NULL,                        /* tp_as_number */
    (PySequenceMethods*)NULL,                      /* tp_as_sequence */
    (PyMappingMethods*)&PyVGPaint__tp_as_mapping,   /* tp_as_mapping */
    (hashfunc)NULL,                                /* tp_hash */
    (ternaryfunc)NULL,                             /* tp_call */
    (reprfunc)NULL,                                /* tp_str */
    (getattrofunc)NULL,                            /* tp_getattro */
    (setattrofunc)NULL,                            /* tp_setattro */
    (PyBufferProcs*)NULL,                          /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,                            /* tp_flags */
    NULL,                                          /* Documentation string */
    (traverseproc)NULL,                            /* tp_traverse */
    (inquiry)NULL,                                 /* tp_clear */
    (richcmpfunc)NULL,                             /* tp_richcompare */
    0,                                             /* tp_weaklistoffset */
    (getiterfunc)NULL,                             /* tp_iter */
    (iternextfunc)NULL,                            /* tp_iternext */
    (struct PyMethodDef*)PyVGPaint_methods,        /* tp_methods */
    (struct PyMemberDef*)0,                        /* tp_members */
    PyVGPaint__getsets,                            /* tp_getset */
    NULL,                                          /* tp_base */
    NULL,                                          /* tp_dict */
    (descrgetfunc)NULL,                            /* tp_descr_get */
    (descrsetfunc)NULL,                            /* tp_descr_set */
    0,                                             /* tp_dictoffset */
    (initproc)PyVGPaint__tp_init,                  /* tp_init */
    (allocfunc)PyType_GenericAlloc,                /* tp_alloc */
    (newfunc)PyType_GenericNew,                    /* tp_new */
    (freefunc)0,                                   /* tp_free */
    (inquiry)NULL,                                 /* tp_is_gc */
    NULL,                                          /* tp_bases */
    NULL,                                          /* tp_mro */
    NULL,                                          /* tp_cache */
    NULL,                                          /* tp_subclasses */
    NULL,                                          /* tp_weaklist */
    (destructor) NULL                              /* tp_del */
};


