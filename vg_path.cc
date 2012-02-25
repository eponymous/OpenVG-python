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


static int
PyVGPath__tp_init(PyVGPath *self, PyObject *args, PyObject *kwargs)
{
    VGint pathFormat;
    VGPathDatatype datatype;
    VGfloat scale;
    VGfloat bias;
    VGint segmentCapacityHint;
    VGint coordCapacityHint;
    unsigned int capabilities;
    const char *keywords[] = {"pathFormat", "datatype", "scale", "bias",
                              "segmentCapacityHint", "coordCapacityHint",
                              "capabilities", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs,
                                    (char *) "iiffiiI", (char **) keywords,
                                    &pathFormat, &datatype, &scale, &bias,
                                    &segmentCapacityHint, &coordCapacityHint,
                                    &capabilities)) {
        return -1;
    }

    self->obj = vgCreatePath(pathFormat, datatype, scale, bias,
                             segmentCapacityHint, coordCapacityHint,
                             capabilities);

    return check_error() ? -1 : 0;
}


PyDoc_STRVAR(OpenVG_vgAppendPath__doc__,
".. function:: append(srcPath)\n"
"\n"
"   Append data from `srcPath'.\n"
"\n"
"   :arg srcPath: Source path.\n"
"   :type srcPath: VGPath.\n"
"\n"
"   :error: VG_BAD_HANDLE_ERROR.\n"
"   :error: VG_PATH_CAPABILITY_ERROR.\n"
);

static PyObject *
OpenVG_vgAppendPath(PyVGPath *self, PyObject *args, PyObject *kwargs)
{
    PyVGPath *srcPath;
    const char *keywords[] = {"srcPath", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!", (char **) keywords, &PyVGPath_Type, &srcPath)) {
        return NULL;
    }

    vgAppendPath(self->obj, srcPath->obj);

    if (check_error())
        return NULL;

    Py_RETURN_NONE;
}


PyDoc_STRVAR(OpenVG_vgAppendPathData__doc__,
".. function:: append_data(numSegments, pathSegments, pathData)\n"
"\n"
"   Append data from `pathData'.\n"
"\n"
"   :arg numSegments: Number of path segments.\n"
"   :type numSegments: int.\n"
"   :arg pathSegments: Path segments.\n"
"   :type pathSegments: list.\n"
"   :arg pathData: Path segments.\n"
"   :type pathData: list.\n"
"\n"
"   :error: VG_BAD_HANDLE_ERROR.\n"
"   :error: VG_PATH_CAPABILITY_ERROR.\n"
"   :error: VG_ILLEGAL_ARGUMENT_ERROR.\n"
);

static PyObject *
OpenVG_vgAppendPathData(PyVGPath *self, PyObject *args, PyObject *kwargs)
{
    VGint numSegments;
    VGubyte *pathSegments;
    PyObject *py_segments;
    VGPathDatatype type;
    void *pathData = NULL;
    PyObject *py_data;
    int count, idx;

    const char *keywords[] = {"numSegments", "pathSegments", "pathData", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "iO!O!", (char **) keywords, &numSegments, &PyList_Type, &py_segments, &PyList_Type, &py_data)) {
        return NULL;
    }

    if (numSegments != PyList_Size(py_segments)) {
        PyErr_SetString(PyExc_TypeError,
                        "Length of `pathSegments' and `numSegments' do not match");
        return NULL;
    }

    pathSegments = (VGubyte*)malloc(sizeof(VGubyte) * numSegments);
    for (idx = 0; idx < numSegments; idx++) {
        PyObject *element = PyList_GET_ITEM(py_segments, idx);
        pathSegments[idx] = (VGubyte) PyLong_AsUnsignedLong(element);
    }

    count = PyList_Size(py_data);
    type = (VGPathDatatype)vgGetParameteri(self->obj, VG_PATH_DATATYPE);
    switch (type) {
        case VG_PATH_DATATYPE_S_8:
            pathData = malloc(sizeof(VGbyte) * count);
            break;
        case VG_PATH_DATATYPE_S_16:
            pathData = malloc(sizeof(VGshort) * count);
            break;
        case VG_PATH_DATATYPE_S_32:
            pathData = malloc(sizeof(VGint) * count);
            break;
        case VG_PATH_DATATYPE_F:
            pathData = malloc(sizeof(VGfloat) * count);
            break;
    }
    for (idx = 0; idx < count; idx++) {
        PyObject *element = PyList_GET_ITEM(py_data, idx);
        switch (type) {
            case VG_PATH_DATATYPE_S_8: {
                VGbyte *tmp = (VGbyte*)pathData;
                tmp[idx] = (VGbyte) PyLong_AsLong(element);
                break;
            }
            case VG_PATH_DATATYPE_S_16: {
                VGshort *tmp = (VGshort*)pathData;
                tmp[idx] = (VGshort) PyLong_AsLong(element);
                break;
            }
            case VG_PATH_DATATYPE_S_32: {
                VGint *tmp = (VGint*)pathData;
                tmp[idx] = (VGint) PyLong_AsLong(element);
                break;
            }
            case VG_PATH_DATATYPE_F: {
                VGfloat *tmp = (VGfloat*)pathData;
                tmp[idx] = (VGfloat) PyFloat_AsDouble(element);
                break;
            }
        }
    }

    vgAppendPathData(self->obj, numSegments, pathSegments, pathData);

    free(pathSegments);
    free(pathData);

    if (check_error())
        return NULL;

    Py_RETURN_NONE;
}


PyDoc_STRVAR(OpenVG_vgPathBounds__doc__,
".. function:: bounds()\n"
"\n"
"   The path's bounding box.\n"
"\n"
"   :return: the x, y, width and height of the path.\n"
"   :rtype: tuple of 4 floats.\n"
"\n"
"   :error: VG_BAD_HANDLE_ERROR.\n"
"   :error: VG_ILLEGAL_ARGUMENT_ERROR.\n"
"   :error: VG_PATH_CAPABILITY_ERROR.\n"
);

static PyObject *
OpenVG_vgPathBounds(PyVGPath *self, PyObject *args, PyObject *kwargs)
{
    PyObject *py_retval;
    VGfloat  minX;
    VGfloat  minY;
    VGfloat  width;
    VGfloat  height;

    vgPathBounds(self->obj, &minX, &minY, &width, &height);

    if (check_error())
        return NULL;

    py_retval = Py_BuildValue((char *) "ffff", minX, minY, width, height);
    return py_retval;
}


PyDoc_STRVAR(OpenVG_vgGetPathCapabilities__doc__,
".. function:: capabilities()\n"
"\n"
"   Get the current capabilities of the path.\n"
"\n"
"   :return: path capabilities.\n"
"   :rtype: bitwise OR of VGPathCapabilities.\n"
"\n"
"   :error: VG_BAD_HANDLE_ERROR.\n"
);

static PyObject *
OpenVG_vgGetPathCapabilities(PyVGPath *self, PyObject *args, PyObject *kwargs)
{
    PyObject *py_retval;
    VGbitfield retval;

    retval = vgGetPathCapabilities(self->obj);

    if (check_error())
        return NULL;

    py_retval = Py_BuildValue((char *) "N", PyLong_FromUnsignedLong(retval));
    return py_retval;
}


PyDoc_STRVAR(OpenVG_vgRemovePathCapabilities__doc__,
".. function:: capabilities_remove(capabilities)\n"
"\n"
"   Remove capabilities from the path.\n"
"\n"
"   :arg capabilities: Capabilities to remove.\n"
"   :type capabilities: bitwise OR of VGPathCapabilities.\n"
"\n"
"   :error: VG_BAD_HANDLE_ERROR.\n"
);

static PyObject *
OpenVG_vgRemovePathCapabilities(PyVGPath *self, PyObject *args, PyObject *kwargs)
{
    unsigned int capabilities;
    const char *keywords[] = {"capabilities", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "I", (char **) keywords, &capabilities)) {
        return NULL;
    }

    vgRemovePathCapabilities(self->obj, capabilities);

    if (check_error())
        return NULL;

    Py_RETURN_NONE;
}


PyDoc_STRVAR(OpenVG_vgClearPath__doc__,
".. function:: clear(capabilities)\n"
"\n"
"   Clear command and coordinate data from path.\n"
"\n"
"   :arg capabilities: Desired capabilities.\n"
"   :type capabilities: bitwise OR of VGPathCapabilities.\n"
"\n"
"   :error: VG_BAD_HANDLE_ERROR.\n"
);

static PyObject *
OpenVG_vgClearPath(PyVGPath *self, PyObject *args, PyObject *kwargs)
{
    unsigned int capabilities;
    const char *keywords[] = {"capabilities", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "I", (char **) keywords, &capabilities)) {
        return NULL;
    }

    if (check_error())
        return NULL;

    vgClearPath(self->obj, capabilities);

    Py_RETURN_NONE;
}


PyDoc_STRVAR(OpenVG_vgDrawPath__doc__,
".. function:: draw(paintModes)\n"
"\n"
"   Draw the path on the current drawing surface.\n"
"\n"
"   :arg paintModes: Fill and/or stroke the path.\n"
"   :type paintModes: bitwise OR of VGPaintMode.\n"
"\n"
"   :error: VG_BAD_HANDLE_ERROR.\n"
"   :error: VG_ILLEGAL_ARGUMENT_ERROR.\n"
);

static PyObject *
OpenVG_vgDrawPath(PyVGPath *self, PyObject *args, PyObject *kwargs)
{
    VGPaintMode paintModes;
    const char *keywords[] = {"paintModes", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "I", (char **) keywords, &paintModes)) {
        return NULL;
    }

    if (check_error())
        return NULL;

    vgDrawPath(self->obj, paintModes);

    Py_RETURN_NONE;
}


PyDoc_STRVAR(OpenVG_vgInterpolatePath__doc__,
".. function:: interpolate(startPath, endPath, amount)\n"
"\n"
"   Interpolate between two paths by `amount'.\n"
"\n"
"   :arg startPath: Start path.\n"
"   :type startPath: VGPath.\n"
"   :arg endPath: End path.\n"
"   :type endPath: VGPath.\n"
"   :arg amount: Interpolation amount.\n"
"   :type amount: float.\n"
"   :return: True on success.\n"
"   :rtype: bool.\n"
"\n"
"   :error: VG_BAD_HANDLE_ERROR.\n"
"   :error: VG_PATH_CAPABILITY_ERROR.\n"
"   :error: VG_ILLEGAL_ARGUMENT_ERROR.\n"
);

static PyObject *
OpenVG_vgInterpolatePath(PyVGPath *self, PyObject *args, PyObject *kwargs)
{
    PyObject *py_retval;
    bool retval;
    PyVGPath *startPath;
    PyVGPath *endPath;
    VGfloat amount;
    const char *keywords[] = {"startPath", "endPath", "amount", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!O!f", (char **) keywords, &PyVGPath_Type, &startPath, &PyVGPath_Type, &endPath, &amount)) {
        return NULL;
    }

    retval = vgInterpolatePath(self->obj, startPath->obj, endPath->obj, amount);

    if (check_error())
        return NULL;

    py_retval = Py_BuildValue((char *) "N", PyBool_FromLong(retval));
    return py_retval;
}


PyDoc_STRVAR(OpenVG_vgPathLength__doc__,
".. function:: length(startSegment, numSegments)\n"
"\n"
"   Calculate the length of a path segment.\n"
"\n"
"   :arg startSegment: Index of the start segment.\n"
"   :type startSegment: int.\n"
"   :arg numSegments: Number of segments.\n"
"   :type numSegments: int.\n"
"   :return: Length of path or -1.0 on error.\n"
"   :rtype: float.\n"
"\n"
"   :error: VG_BAD_HANDLE_ERROR.\n"
"   :error: VG_PATH_CAPABILITY_ERROR.\n"
"   :error: VG_ILLEGAL_ARGUMENT_ERROR.\n"
);

static PyObject *
OpenVG_vgPathLength(PyVGPath *self, PyObject *args, PyObject *kwargs)
{
    PyObject *py_retval;
    VGfloat retval;
    VGint startSegment;
    VGint numSegments;
    const char *keywords[] = {"startSegment", "numSegments", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "ii", (char **) keywords, &startSegment, &numSegments)) {
        return NULL;
    }

    retval = vgPathLength(self->obj, startSegment, numSegments);

    if (check_error())
        return NULL;

    py_retval = Py_BuildValue((char *) "f", retval);
    return py_retval;
}


PyDoc_STRVAR(OpenVG_vgModifyPathCoords__doc__,
".. function:: modify_coords(startPath, endPath, pathData)\n"
"\n"
"   Modify coordinates stored in a path.\n"
"\n"
"   :arg startSegment: Index of the start segment.\n"
"   :type startSegment: int.\n"
"   :arg numSegments: Number of segments.\n"
"   :type numSegments: int.\n"
"   :arg pathData: List of modified path segments.\n"
"   :type: list.\n"
"\n"
"   :error: VG_BAD_HANDLE_ERROR.\n"
"   :error: VG_PATH_CAPABILITY_ERROR.\n"
"   :error: VG_ILLEGAL_ARGUMENT_ERROR.\n"
);

static PyObject *
OpenVG_vgModifyPathCoords(PyVGPath *self, PyObject *args, PyObject *kwargs)
{
    VGint startIndex;
    VGint numSegments;
    VGPathDatatype type;
    void *pathData = NULL;
    PyObject *py_data;
    int count, idx;

    const char *keywords[] = {"startIndex", "numSegments", "pathData", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "iiO!", (char **) keywords, &startIndex, &numSegments, &PyList_Type, &py_data)) {
        return NULL;
    }

    count = PyList_Size(py_data);
    type = (VGPathDatatype)vgGetParameteri(self->obj, VG_PATH_DATATYPE);
    switch (type) {
        case VG_PATH_DATATYPE_S_8:
            pathData = malloc(sizeof(VGbyte) * count);
            break;
        case VG_PATH_DATATYPE_S_16:
            pathData = malloc(sizeof(VGshort) * count);
            break;
        case VG_PATH_DATATYPE_S_32:
            pathData = malloc(sizeof(VGint) * count);
            break;
        case VG_PATH_DATATYPE_F:
            pathData = malloc(sizeof(VGfloat) * count);
            break;
    }
    for (idx = 0; idx < count; idx++) {
        PyObject *element = PyList_GET_ITEM(py_data, idx);
        switch (type) {
            case VG_PATH_DATATYPE_S_8: {
                VGbyte *tmp = (VGbyte*)pathData;
                tmp[idx] = (VGbyte) PyLong_AsLong(element);
                break;
            }
            case VG_PATH_DATATYPE_S_16: {
                VGshort *tmp = (VGshort*)pathData;
                tmp[idx] = (VGshort) PyLong_AsLong(element);
                break;
            }
            case VG_PATH_DATATYPE_S_32: {
                VGint *tmp = (VGint*)pathData;
                tmp[idx] = (VGint) PyLong_AsLong(element);
                break;
            }
            case VG_PATH_DATATYPE_F: {
                VGfloat *tmp = (VGfloat*)pathData;
                tmp[idx] = (VGfloat) PyFloat_AsDouble(element);
                break;
            }
        }
    }

    vgModifyPathCoords(self->obj, startIndex, numSegments, pathData);

    free(pathData);

    if (check_error())
        return NULL;

    Py_RETURN_NONE;
}


PyDoc_STRVAR(OpenVG_vgPointAlongPath__doc__,
".. function:: point_along_path(startSegment, numSegments, distance)\n"
"\n"
"   Calculate point and normalized tangent vectors along the path segment.\n"
"\n"
"   :arg startSegment: Index of the start segment.\n"
"   :type startSegment: int.\n"
"   :arg numSegments: Number of segments.\n"
"   :type numSegments: int.\n"
"   :arg distance: Distance along path segment.\n"
"   :type distance: int.\n"
"   :return: x, y, tangentX and tangentY.\n"
"   :rtype: tuple of 4 floats.\n"
"\n"
"   :error: VG_BAD_HANDLE_ERROR.\n"
"   :error: VG_PATH_CAPABILITY_ERROR.\n"
"   :error: VG_ILLEGAL_ARGUMENT_ERROR.\n"
);

static PyObject *
OpenVG_vgPointAlongPath(PyVGPath *self, PyObject *args, PyObject *kwargs)
{
    PyObject *py_retval;
    VGint startSegment;
    VGint numSegments;
    VGfloat distance;
    VGfloat  x;
    VGfloat  y;
    VGfloat  tangentX;
    VGfloat  tangentY;
    const char *keywords[] = {"startSegment", "numSegments", "distance", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "iif", (char **) keywords, &startSegment, &numSegments, &distance)) {
        return NULL;
    }

    vgPointAlongPath(self->obj, startSegment, numSegments, distance, &x, &y, &tangentX, &tangentY);

    if (check_error())
        return NULL;

    py_retval = Py_BuildValue((char *) "ffff", x, y, tangentX, tangentY);
    return py_retval;
}


PyDoc_STRVAR(OpenVG_vgTransformPath__doc__,
".. function:: transform(srcPath)\n"
"\n"
"   Appends a transformed copy of `srcPath'.\n"
"\n"
"   :arg srcPath: Source path.\n"
"   :type srcPath: VGPath.\n"
"\n"
"   :error: VG_BAD_HANDLE_ERROR.\n"
"   :error: VG_PATH_CAPABILITY_ERROR.\n"
);

static PyObject *
OpenVG_vgTransformPath(PyVGPath *self, PyObject *args, PyObject *kwargs)
{
    PyVGPath *srcPath;
    const char *keywords[] = {"srcPath", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!", (char **) keywords, &PyVGPath_Type, &srcPath)) {
        return NULL;
    }

    vgTransformPath(self->obj, srcPath->obj);

    if (check_error())
        return NULL;

    Py_RETURN_NONE;
}


PyDoc_STRVAR(OpenVG_vgPathTransformedBounds__doc__,
".. function:: transformed_bounds()\n"
"\n"
"   The path's transformed bounding box.\n"
"\n"
"   :return: the x, y, width and height of the transformed path.\n"
"   :rtype: tuple of 4 floats.\n"
"\n"
"   :error: VG_BAD_HANDLE_ERROR.\n"
"   :error: VG_ILLEGAL_ARGUMENT_ERROR.\n"
"   :error: VG_PATH_CAPABILITY_ERROR.\n"
);

static PyObject *
OpenVG_vgPathTransformedBounds(PyVGPath *self, PyObject *args, PyObject *kwargs)
{
    PyObject *py_retval;
    VGfloat  minX;
    VGfloat  minY;
    VGfloat  width;
    VGfloat  height;

    vgPathTransformedBounds(self->obj, &minX, &minY, &width, &height);

    if (check_error())
        return NULL;

    py_retval = Py_BuildValue((char *) "ffff", minX, minY, width, height);
    return py_retval;
}


static PyMethodDef PyVGPath_methods[] = {
    {(char *) "append",
     (PyCFunction) OpenVG_vgAppendPath,
     METH_KEYWORDS|METH_VARARGS,
     OpenVG_vgAppendPath__doc__
    },
    {(char *) "append_data",
     (PyCFunction) OpenVG_vgAppendPathData,
     METH_KEYWORDS|METH_VARARGS,
     OpenVG_vgAppendPathData__doc__
    },
    {(char *) "bounds",
     (PyCFunction) OpenVG_vgPathBounds,
     METH_NOARGS,
     OpenVG_vgPathBounds__doc__
    },
    {(char *) "capabilities",
     (PyCFunction) OpenVG_vgGetPathCapabilities,
     METH_NOARGS,
     OpenVG_vgGetPathCapabilities__doc__
    },
    {(char *) "capabilities_remove",
     (PyCFunction) OpenVG_vgRemovePathCapabilities,
     METH_KEYWORDS|METH_VARARGS,
     OpenVG_vgRemovePathCapabilities__doc__
    },
    {(char *) "clear",
     (PyCFunction) OpenVG_vgClearPath,
     METH_KEYWORDS|METH_VARARGS,
     OpenVG_vgClearPath__doc__
    },
    {(char *) "draw",
     (PyCFunction) OpenVG_vgDrawPath,
     METH_KEYWORDS|METH_VARARGS,
     OpenVG_vgDrawPath__doc__
    },
    {(char *) "interpolate",
     (PyCFunction) OpenVG_vgInterpolatePath,
     METH_KEYWORDS|METH_VARARGS,
     OpenVG_vgInterpolatePath__doc__
    },
    {(char *) "length",
     (PyCFunction) OpenVG_vgPathLength,
     METH_KEYWORDS|METH_VARARGS,
     OpenVG_vgPathLength__doc__
    },
    {(char *) "modify_coords",
     (PyCFunction) OpenVG_vgModifyPathCoords,
     METH_KEYWORDS|METH_VARARGS,
     OpenVG_vgModifyPathCoords__doc__
    },
    {(char *) "point_along_path",
     (PyCFunction) OpenVG_vgPointAlongPath,
     METH_KEYWORDS|METH_VARARGS,
     OpenVG_vgPointAlongPath__doc__
    },
    {(char *) "transform",
     (PyCFunction) OpenVG_vgTransformPath,
     METH_KEYWORDS|METH_VARARGS,
     OpenVG_vgTransformPath__doc__
     },
    {(char *) "transformed_bounds",
     (PyCFunction) OpenVG_vgPathTransformedBounds,
     METH_NOARGS,
     OpenVG_vgPathTransformedBounds__doc__
    },
    {NULL, NULL, 0, NULL}
};

static PyObject *
PyVGPath__mp_subscript(PyVGPath *self, PyObject *value)
{
    PyObject *py_retval;
    VGuint key = PyLong_AsUnsignedLong(value);

    switch (key) {
        case VG_PATH_FORMAT:
        case VG_PATH_DATATYPE:
        case VG_PATH_NUM_SEGMENTS:
        case VG_PATH_NUM_COORDS:
            py_retval = PyLong_FromLong(vgGetParameteri(self->obj, key));
            break;
        case VG_PATH_SCALE:
        case VG_PATH_BIAS:
            py_retval = PyFloat_FromDouble(vgGetParameterf(self->obj, key));
            break;
        default:
            PyErr_SetString(PyExc_IndexError,
                            "VGPath[key]: key must be a VGPathParamType");
            return NULL;
    }
    return Py_BuildValue((char *) "N", py_retval);
}

static int
PyVGPath__mp_ass_subscript(PyVGPath *self, PyObject *pykey, PyObject *value)
{
    VGuint key = PyLong_AsUnsignedLong(pykey);
    
    switch (key) {
        case VG_PATH_FORMAT:
        case VG_PATH_DATATYPE:
        case VG_PATH_NUM_SEGMENTS:
        case VG_PATH_NUM_COORDS:
            vgSetParameteri(self->obj, key, PyLong_AsLong(value));
            break;
        case VG_PATH_SCALE:
        case VG_PATH_BIAS:
            vgSetParameterf(self->obj, key, (float) PyFloat_AsDouble(value));
            break;
        default:
            PyErr_SetString(PyExc_IndexError,
                            "VGPath[key]: key must be a VGPathParamType");
            return -1;
    }
    return 0;
}

static PyMappingMethods PyVGPath__tp_as_mapping = {
	(lenfunc) NULL,	                                /* mp_length */
	(binaryfunc) PyVGPath__mp_subscript,	        /* mp_subscript */
	(objobjargproc) PyVGPath__mp_ass_subscript,  /* mp_ass_subscript */
};

static void
PyVGPath__tp_dealloc(PyVGPath *self)
{
    if (self->obj) {
        VGPath tmp = self->obj;
        self->obj = NULL;
        vgDestroyPath(tmp);
    }
    Py_TYPE(self)->tp_free((PyObject*)self);
}

PyTypeObject PyVGPath_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    (char *) "VG.VGPath",                     /* tp_name */
    sizeof(PyVGPath),                             /* tp_basicsize */
    0,                                            /* tp_itemsize */
    /* methods */
    (destructor)PyVGPath__tp_dealloc,             /* tp_dealloc */
    (printfunc)0,                                 /* tp_print */
    (getattrfunc)NULL,                            /* tp_getattr */
    (setattrfunc)NULL,                            /* tp_setattr */
    (cmpfunc)NULL,                                /* tp_compare */
    (reprfunc)NULL,                               /* tp_repr */
    (PyNumberMethods*)NULL,                       /* tp_as_number */
    (PySequenceMethods*)NULL,                     /* tp_as_sequence */
    (PyMappingMethods*)&PyVGPath__tp_as_mapping,   /* tp_as_mapping */
    (hashfunc)NULL,                               /* tp_hash */
    (ternaryfunc)NULL,                            /* tp_call */
    (reprfunc)NULL,                               /* tp_str */
    (getattrofunc)NULL,                           /* tp_getattro */
    (setattrofunc)NULL,                           /* tp_setattro */
    (PyBufferProcs*)NULL,                         /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,                           /* tp_flags */
    NULL,                                         /* Documentation string */
    (traverseproc)NULL,                           /* tp_traverse */
    (inquiry)NULL,                                /* tp_clear */
    (richcmpfunc)NULL,                            /* tp_richcompare */
    0,                                            /* tp_weaklistoffset */
    (getiterfunc)NULL,                            /* tp_iter */
    (iternextfunc)NULL,                           /* tp_iternext */
    (struct PyMethodDef*)PyVGPath_methods,        /* tp_methods */
    (struct PyMemberDef*)0,                       /* tp_members */
    0,                                            /* tp_getset */
    NULL,                                         /* tp_base */
    NULL,                                         /* tp_dict */
    (descrgetfunc)NULL,                           /* tp_descr_get */
    (descrsetfunc)NULL,                           /* tp_descr_set */
    0,                                            /* tp_dictoffset */
    (initproc)PyVGPath__tp_init,                  /* tp_init */
    (allocfunc)PyType_GenericAlloc,               /* tp_alloc */
    (newfunc)PyType_GenericNew,                   /* tp_new */
    (freefunc)0,                                  /* tp_free */
    (inquiry)NULL,                                /* tp_is_gc */
    NULL,                                         /* tp_bases */
    NULL,                                         /* tp_mro */
    NULL,                                         /* tp_cache */
    NULL,                                         /* tp_subclasses */
    NULL,                                         /* tp_weaklist */
    (destructor) NULL                             /* tp_del */
};


