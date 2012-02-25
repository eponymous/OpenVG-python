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
#include "vgu.h"

/* --- module functions --- */

static void vgu_error(VGUErrorCode error)
{
    switch (error) {
        case VGU_NO_ERROR:
            break;
        case VGU_BAD_HANDLE_ERROR:
            PyErr_SetString(PyExc_TypeError, "VGU_BAD_HANDLE_ERROR");
            break;
        case VGU_ILLEGAL_ARGUMENT_ERROR:
            PyErr_SetString(PyExc_TypeError, "VGU_ILLEGAL_ARGUMENT_ERROR");
            break;
        case VGU_OUT_OF_MEMORY_ERROR:
            PyErr_SetString(PyExc_MemoryError, "VGU_OUT_OF_MEMORY_ERROR");
            break;
        case VGU_PATH_CAPABILITY_ERROR:
            PyErr_SetString(PyExc_ValueError, "VGU_PATH_CAPABILITY_ERROR");
            break;
        case VGU_BAD_WARP_ERROR:
            PyErr_SetString(PyExc_ValueError, "VGU_BAD_WARP_ERROR");
            break;
        default:
            break;
    }
}

static PyObject *
VGU_vguArc(PyObject * UNUSED(dummy), PyObject *args, PyObject *kwargs)
{
    VGUErrorCode error;
    PyVGPath *path;
    VGfloat x, y, width, height;
    VGfloat startAngle, angleExtent;
    VGUArcType arcType;

    const char *keywords[] = {"path", "x", "y", "width", "height",
                              "startAngle", "angleExtent", "arcType", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!ffffffi", (char **) keywords, &PyVGPath_Type, &path, &x, &y, &width, &height, &startAngle, &angleExtent, &arcType)) {
        return NULL;
    }

    error = vguArc(path->obj, x, y, width, height, startAngle, angleExtent, arcType);

    if (error) {
        vgu_error(error);
        return NULL;
    }

    Py_RETURN_NONE;
}

static PyObject *
VGU_vguLine(PyObject * UNUSED(dummy), PyObject *args, PyObject *kwargs)
{
    VGUErrorCode error;
    PyVGPath *path;
    VGfloat x0, y0, x1, y1;

    const char *keywords[] = {"path", "x0", "y0", "x1", "y1", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!ffff", (char **) keywords, &PyVGPath_Type, &path, &x0, &y0, &x1, &y1)) {
        return NULL;
    }

    error = vguLine(path->obj, x0, y0, x1, y1);

    if (error) {
        vgu_error(error);
        return NULL;
    }

    Py_RETURN_NONE;
}

static PyObject *
VGU_vguPolygon(PyObject * UNUSED(dummy), PyObject *args, PyObject *kwargs)
{
    VGUErrorCode error;
    PyVGPath *path;
    VGfloat *points;
    PyObject *py_list;
    VGint count;
    VGboolean closed;
    PyObject *py_closed;
    int idx;

    const char *keywords[] = {"path", "points", "closed", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!O!O", (char **) keywords, &PyVGPath_Type, &path, &PyList_Type, &py_list, &count, &py_closed)) {
        return NULL;
    }

    closed = (VGboolean) PyObject_IsTrue(py_closed);

    count = PyList_Size(py_list);
    if (count == 0 || count%2) {
        PyErr_SetString(PyExc_TypeError,
                        "Parameter `points' must be a multiple of 2");
        return NULL;
    }

    points = (VGfloat*)malloc(sizeof(VGfloat) * count);
    for (idx = 0; idx < count; idx++) {
        PyObject *element = PyList_GET_ITEM(py_list, idx);
        if (!PyFloat_Check(element)) {
            PyErr_SetString(PyExc_TypeError,
                            "Parameter `points' must be a list of floats");
            free(points);
            return NULL;
        }
        points[idx] = (VGfloat) PyFloat_AsDouble(element);
    }

    error = vguPolygon(path->obj, points, count/2, closed);

    free(points);

    if (error) {
        vgu_error(error);
        return NULL;
    }

    Py_RETURN_NONE;
}

static PyObject *
VGU_vguRoundRect(PyObject * UNUSED(dummy), PyObject *args, PyObject *kwargs)
{
    VGUErrorCode error;
    PyVGPath *path;
    VGfloat x, y, width, height;
    VGfloat arcWidth, arcHeight;

    const char *keywords[] = {"path", "x", "y", "width", "height",
                              "arcWidth", "arcHeight", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!ffffff", (char **) keywords, &PyVGPath_Type, &path, &x, &y, &width, &height, &arcWidth, &arcHeight)) {
        return NULL;
    }

    error = vguRoundRect(path->obj, x, y, width, height, arcWidth, arcHeight);

    if (error) {
        vgu_error(error);
        return NULL;
    }

    Py_RETURN_NONE;
}

static PyObject *
VGU_vguEllipse(PyObject * UNUSED(dummy), PyObject *args, PyObject *kwargs)
{
    VGUErrorCode error;
    PyVGPath *path;
    VGfloat cx, cy, width, height;
    const char *keywords[] = {"path", "cx", "cy", "width", "height", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!ffff", (char **) keywords, &PyVGPath_Type, &path, &cx, &cy, &width, &height)) {
        return NULL;
    }

    error = vguEllipse(path, cx, cy, width, height);

    if (error) {
        vgu_error(error);
        return NULL;
    }

    Py_RETURN_NONE;
}

static PyObject *
VGU_vguRect(PyObject * UNUSED(dummy), PyObject *args, PyObject *kwargs)
{
    VGUErrorCode error;
    PyVGPath *path;
    VGfloat x, y, width, height;

    const char *keywords[] = {"path", "x", "y", "width", "height", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!ffff", (char **) keywords, &PyVGPath_Type, &path, &x, &y, &width, &height)) {
        return NULL;
    }

    error = vguRect(path->obj, x, y, width, height);

    if (error) {
        vgu_error(error);
        return NULL;
    }

    Py_RETURN_NONE;
}

static PyObject *
VGU_vguComputeWarpQuadToSquare(PyObject * UNUSED(dummy), PyObject *args, PyObject *kwargs)
{
    VGUErrorCode error;
    VGfloat sx0, sy0, sx1, sy1, sx2, sy2, sx3, sy3;
    VGfloat  matrix[9];
    PyObject *py_list;
    int idx;

    const char *keywords[] = {"sx0", "sy0", "sx1", "sy1",
                              "sx2", "sy2", "sx3", "sy3", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "ffffffff", (char **) keywords, &sx0, &sy0, &sx1, &sy1, &sx2, &sy2, &sx3, &sy3)) {
        return NULL;
    }

    error = vguComputeWarpQuadToSquare(sx0, sy0, sx1, sy1, sx2, sy2, sx3, sy3, matrix);

    if (error) {
        vgu_error(error);
        return NULL;
    }

    py_list = PyList_New(9);

    for (idx = 0; idx < 9; idx++) {
        PyList_SET_ITEM(py_list, idx, PyFloat_FromDouble(matrix[idx]));
    }

    return Py_BuildValue((char *) "N", py_list);

}

static PyObject *
VGU_vguComputeWarpQuadToQuad(PyObject * UNUSED(dummy), PyObject *args, PyObject *kwargs)
{
    VGUErrorCode error;
    VGfloat dx0, dy0, dx1, dy1, dx2, dy2, dx3, dy3;
    VGfloat sx0, sy0, sx1, sy1, sx2, sy2, sx3, sy3;
    VGfloat  matrix[9];
    PyObject *py_list;
    int idx;

    const char *keywords[] = {"dx0", "dy0", "dx1", "dy1",
                              "dx2", "dy2", "dx3", "dy3",
                              "sx0", "sy0", "sx1", "sy1",
                              "sx2", "sy2", "sx3", "sy3", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "ffffffffffffffff", (char **) keywords, &dx0, &dy0, &dx1, &dy1, &dx2, &dy2, &dx3, &dy3, &sx0, &sy0, &sx1, &sy1, &sx2, &sy2, &sx3, &sy3)) {
        return NULL;
    }

    error = vguComputeWarpQuadToQuad(dx0, dy0, dx1, dy1, dx2, dy2, dx3, dy3, sx0, sy0, sx1, sy1, sx2, sy2, sx3, sy3, matrix);

    if (error) {
        vgu_error(error);
        return NULL;
    }

    py_list = PyList_New(9);

    for (idx = 0; idx < 9; idx++) {
        PyList_SET_ITEM(py_list, idx, PyFloat_FromDouble(matrix[idx]));
    }

    return Py_BuildValue((char *) "N", py_list);
}

static PyObject *
VGU_vguComputeWarpSquareToQuad(PyObject * UNUSED(dummy), PyObject *args, PyObject *kwargs)
{
    VGUErrorCode error;
    VGfloat dx0, dy0, dx1, dy1, dx2, dy2, dx3, dy3;
    VGfloat  matrix[9];
    PyObject *py_list;
    int idx;

    const char *keywords[] = {"dx0", "dy0", "dx1", "dy1", "dx2", "dy2",
                              "dx3", "dy3", "matrix", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "ffffffff", (char **) keywords, &dx0, &dy0, &dx1, &dy1, &dx2, &dy2, &dx3, &dy3)) {
        return NULL;
    }

    error = vguComputeWarpSquareToQuad(dx0, dy0, dx1, dy1, dx2, dy2, dx3, dy3, matrix);

    if (error) {
        vgu_error(error);
        return NULL;
    }

    py_list = PyList_New(9);

    for (idx = 0; idx < 9; idx++) {
        PyList_SET_ITEM(py_list, idx, PyFloat_FromDouble(matrix[idx]));
    }

    return Py_BuildValue((char *) "N", py_list);
}


static PyMethodDef VGU_functions[] = {
    {(char *) "arc",
     (PyCFunction) VGU_vguArc,
     METH_KEYWORDS|METH_VARARGS,
     NULL
    },
    {(char *) "line",
     (PyCFunction) VGU_vguLine,
     METH_KEYWORDS|METH_VARARGS,
     NULL
    },
    {(char *) "ellipse",
     (PyCFunction) VGU_vguEllipse,
     METH_KEYWORDS|METH_VARARGS,
     NULL
    },
    {(char *) "polygon",
     (PyCFunction) VGU_vguPolygon,
     METH_KEYWORDS|METH_VARARGS,
     NULL
    },
    {(char *) "rect",
     (PyCFunction) VGU_vguRect,
     METH_KEYWORDS|METH_VARARGS,
     NULL
    },
    {(char *) "round_rect",
     (PyCFunction) VGU_vguRoundRect,
     METH_KEYWORDS|METH_VARARGS,
     NULL
    },
    {(char *) "compute_warp_square_to_quad",
     (PyCFunction) VGU_vguComputeWarpSquareToQuad,
     METH_KEYWORDS|METH_VARARGS,
     NULL
    },
    {(char *) "compute_warp_quad_to_sphere",
     (PyCFunction) VGU_vguComputeWarpQuadToSquare,
     METH_KEYWORDS|METH_VARARGS,
     NULL
    },
    {(char *) "compute_warp_quad_to_quad",
     (PyCFunction) VGU_vguComputeWarpQuadToQuad,
     METH_KEYWORDS|METH_VARARGS,
     NULL
    },
    {NULL, NULL, 0, NULL}
};


#if PY_VERSION_HEX >= 0x03000000
static struct PyModuleDef VGU_moduledef = {
    PyModuleDef_HEAD_INIT,
    "VGU",
    NULL,
    -1,
    VGU_functions,
};
#endif

#if PY_VERSION_HEX >= 0x03000000
static struct PyModuleDef VGUArcType_moduledef = {
    PyModuleDef_HEAD_INIT,
    "OpenVG.VGUArcType",
    NULL,
    -1,
    NULL,
};
#endif

static PyObject *
initVGU_VGUArcType(void)
{
    PyObject *m;
    #if PY_VERSION_HEX >= 0x03000000
    m = PyModule_Create(&VGUArcType_moduledef);
    #else
    m = Py_InitModule3((char *) "OpenVG.VGUArcType", NULL, NULL);
    #endif
    if (m == NULL) {
        return NULL;
    }
    PyModule_AddIntConstant(m, (char *) "VGU_ARC_OPEN", VGU_ARC_OPEN);
    PyModule_AddIntConstant(m, (char *) "VGU_ARC_CHORD", VGU_ARC_CHORD);
    PyModule_AddIntConstant(m, (char *) "VGU_ARC_PIE", VGU_ARC_PIE);
    return m;
}

PyObject *
initVGU(void)
{
    PyObject *m;
    PyObject *submodule;
    #if PY_VERSION_HEX >= 0x03000000
    m = PyModule_Create(&VGU_moduledef);
    #else
    m = Py_InitModule3((char *) "VGU", VGU_functions, NULL);
    #endif
    if (m == NULL) {
        return NULL;
    }

    submodule = initVGU_VGUArcType();
    if (submodule == NULL) {
        return NULL;
    }
    Py_INCREF(submodule);
    PyModule_AddObject(m, (char *) "VGUArcType", submodule);

    return m;
}
