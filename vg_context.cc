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

PyDoc_STRVAR(PyVGContext__get_paint_fill__doc__,
".. attribute:: paint_fill\n"
"\n"
"   :type VGPaint: The current paint fill VGPaint.\n"
);

static PyObject*
PyVGContext__get_paint_fill(PyVGContext *self, void * UNUSED(closure))
{
    PyVGPaint *py_VGPaint;
    
    py_VGPaint = PyObject_New(PyVGPaint, &PyVGPaint_Type);
    py_VGPaint->obj = vgGetPaint(VG_FILL_PATH);

    if (check_error()) {
        Py_DECREF(py_VGPaint);
        return NULL;
    }

    return Py_BuildValue((char *) "N", py_VGPaint);
}
static int
PyVGContext__set_paint_fill(PyVGContext *self, PyObject *value, void * UNUSED(closure))
{
    PyObject *py_retval;
    PyVGPaint *py_VGPaint;
    
    py_retval = Py_BuildValue((char *) "(O)", value);
    if (!PyArg_ParseTuple(py_retval, (char *) "O!", &PyVGPaint_Type, &py_VGPaint)) {
        Py_DECREF(py_retval);
        return -1;
    }

    vgSetPaint(py_VGPaint->obj, VG_FILL_PATH);

    Py_DECREF(py_retval);

    return check_error() ? -1 : 0;
}


PyDoc_STRVAR(PyVGContext__get_paint_stroke__doc__,
".. attribute:: paint_stroke\n"
"\n"
"   :type VGPaint: The current paint stroke VGPaint.\n"
);

static PyObject*
PyVGContext__get_paint_stroke(PyVGContext *self, void * UNUSED(closure))
{
    PyVGPaint *py_VGPaint;
    
    py_VGPaint = PyObject_New(PyVGPaint, &PyVGPaint_Type);
    py_VGPaint->obj = vgGetPaint(VG_STROKE_PATH);

    if (check_error()) {
        Py_DECREF(py_VGPaint);
        return NULL;
    }

    return Py_BuildValue((char *) "N", py_VGPaint);
}
static int
PyVGContext__set_paint_stroke(PyVGContext *self, PyObject *value, void * UNUSED(closure))
{
    PyObject *py_retval;
    PyVGPaint *py_VGPaint;
    
    py_retval = Py_BuildValue((char *) "(O)", value);
    if (!PyArg_ParseTuple(py_retval, (char *) "O!", &PyVGPaint_Type, &py_VGPaint)) {
        Py_DECREF(py_retval);
        return -1;
    }

    vgSetPaint(py_VGPaint->obj, VG_STROKE_PATH);

    Py_DECREF(py_retval);

    return check_error() ? -1 : 0;
}
static PyGetSetDef PyVGContext__getsets[] = {
    {
        (char*) "paint_fill", /* attribute name */
        (getter) PyVGContext__get_paint_fill, /* C function to get the attribute */
        (setter) PyVGContext__set_paint_fill, /* C function to set the attribute */
        PyVGContext__get_paint_fill__doc__, /* optional doc string */
        NULL /* optional additional data for getter and setter */
    },
    {
        (char*) "paint_stroke", /* attribute name */
        (getter) PyVGContext__get_paint_stroke, /* C function to get the attribute */
        (setter) PyVGContext__set_paint_stroke, /* C function to set the attribute */
        PyVGContext__get_paint_stroke__doc__, /* optional doc string */
        NULL /* optional additional data for getter and setter */
    },
    { NULL, NULL, NULL, NULL, NULL }
};

static PyObject *
PyVGContext__tp_new(PyTypeObject *type, PyObject *args, PyObject *kwargs)
{
    static PyVGContext *self = NULL;

    if (self == NULL) {
        self = (PyVGContext *)type->tp_alloc(type, 0);
    }

    Py_XINCREF(self);

    return (PyObject*)self;
}

static int
PyVGContext__tp_init(PyVGContext *self, PyObject *args, PyObject *kwargs)
{
    VGint width, height;

    const char *keywords[] = {"width", "height", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "ii", (char **) keywords, &width, &height)) {
        return -1;
    }

    if (!self->init) {
        if (!vgCreateContextSH(width, height)) {
            PyErr_SetString(PyExc_RuntimeError,
                "Unable to create OpenVG context");
            return -1;
        }
        self->init = 1;
    }
    else if (self->dimensions[0] != width || self->dimensions[1] != height) {
        vgResizeSurfaceSH(width, height);
        self->dimensions[0] = width;
        self->dimensions[1] = height;
    }
    return check_error() ? -1 : 0;
}


PyDoc_STRVAR(OpenVG_vgClear__doc__,
".. function:: clear(x, y, width, height)\n"
"\n"
"   Fill region with the VG_CLEAR_COLOR color.\n"
"\n"
"   :arg x: Start position x.\n"
"   :type x: int\n"
"   :arg y: Start position y.\n"
"   :type y: int\n"
"   :arg width: Width of the sub-region.\n"
"   :type width: int\n"
"   :arg height: Height of the sub-region.\n"
"\n"
"   :error: VG_ILLEGAL_ARGUMENT_ERROR.\n"
);

static PyObject *
OpenVG_vgClear(PyVGContext *self, PyObject *args, PyObject *kwargs)
{
    VGint x, y, width, height;

    const char *keywords[] = {"x", "y", "width", "height", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "iiii", (char **) keywords, &x, &y, &width, &height)) {
        return NULL;
    }

    vgClear(x, y, width, height);

    if (check_error()) {
        return NULL;
    }

    Py_RETURN_NONE;
}


PyDoc_STRVAR(OpenVG_vgLoadIdentity__doc__,
".. function:: load_identity()\n"
"\n"
"   Sets current matrix to identity matrix.\n"
);

static PyObject *
OpenVG_vgLoadIdentity(PyVGContext *self, PyObject *args, PyObject *kwargs)
{
    vgLoadIdentity();

    Py_RETURN_NONE;
}


PyDoc_STRVAR(OpenVG_vgRotate__doc__,
".. function:: rotate(angle)\n"
"\n"
"   Rotate the current matrix.\n"
"\n"
"   :arg angle: angle in degrees to rotate.\n"
"   :type angle: float\n"
);

static PyObject *
OpenVG_vgRotate(PyVGContext *self, PyObject *args, PyObject *kwargs)
{
    VGfloat angle;

    const char *keywords[] = {"angle", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "f", (char **) keywords, &angle)) {
        return NULL;
    }

    vgRotate(angle);

    Py_RETURN_NONE;
}


PyDoc_STRVAR(OpenVG_vgGetMatrix__doc__,
".. function:: get_matrix(get_matrix)\n"
"\n"
"   Get the current transformation matrix.\n"
"\n"
"   :return: matrix.\n"
"   :rtype: list of 9 floats.\n"
"\n"
"   :error: VG_ILLEGAL_ARGUMENT_ERROR.\n"
);

static PyObject *
OpenVG_vgGetMatrix(PyVGContext *self, PyObject *args, PyObject *kwargs)
{
    PyObject *py_retval;
    VGfloat matrix[MATRIX_SIZE];
    PyObject *py_list;
    int idx;

    vgGetMatrix(matrix);

    if (check_error())
        return NULL;

    py_list = PyList_New(MATRIX_SIZE);
    for (idx = 0; idx < MATRIX_SIZE; idx++) {
        PyList_SET_ITEM(py_list, idx, PyFloat_FromDouble(matrix[idx]));
    }
    py_retval = Py_BuildValue((char *) "N", py_list);
    return py_retval;
}


PyDoc_STRVAR(OpenVG_vgSetPixels__doc__,
".. function:: set_pixels(dx, dy, src, sx, sy, width, height)\n"
"\n"
"   Copy pixels from `src' to the drawing surface.\n"
"\n"
"   :arg dx: Destination start position x.\n"
"   :type dx: int\n"
"   :arg dy: Destination start position y.\n"
"   :type dy: int\n"
"   :arg src: Source image.\n"
"   :type src: VGImage\n"
"   :arg sx: Source start position x.\n"
"   :type sx: int\n"
"   :arg sy: Source start position y.\n"
"   :type sy: int\n"
"   :arg width: Width of the sub-region.\n"
"   :type width: int\n"
"   :arg height: Height of the sub-region.\n"
"   :type height: int\n"
"\n"
"   :error: VG_BAD_HANDLE_ERROR.\n"
"   :error: VG_IMAGE_IN_USE_ERROR.\n"
"   :error: VG_ILLEGAL_ARGUMENT_ERROR.\n"
);

static PyObject *
OpenVG_vgSetPixels(PyVGContext *self, PyObject *args, PyObject *kwargs)
{
    PyVGImage *src;
    VGint dx, dy, sx, sy, width, height;

    const char *keywords[] = {"dx", "dy", "src", "sx", "sy", "width", "height", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "iiO!iiii", (char **) keywords, &dx, &dy, &PyVGImage_Type, &src, &sx, &sy, &width, &height)) {
        return NULL;
    }

    vgSetPixels(dx, dy, src->obj, sx, sy, width, height);

    if (check_error())
        return NULL;

    Py_RETURN_NONE;
}


PyDoc_STRVAR(OpenVG_vgMultMatrix__doc__,
".. function:: mult_matrix(angle)\n"
"\n"
"   Multiply the current matrix by `matrix'.\n"
"\n"
"   :arg matrix: multiplication matrix.\n"
"   :type angle: list of 9 floats\n"
"\n"
"   :error: VG_ILLEGAL_ARGUMENT_ERROR.\n"
);

static PyObject *
OpenVG_vgMultMatrix(PyVGContext *self, PyObject *args, PyObject *kwargs)
{
    VGfloat matrix[MATRIX_SIZE];
    PyObject *py_list;
    int idx;

    const char *keywords[] = {"matrix", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!", (char **) keywords, &PyList_Type, &py_list)) {
        return NULL;
    }
    if (PyList_Size(py_list) != MATRIX_SIZE) {
        PyErr_SetString(PyExc_TypeError, "Parameter `matrix' must be a list of 9 floats");
        return NULL;
    }
    for (idx = 0; idx < MATRIX_SIZE; idx++) {
        PyObject *element = PyList_GET_ITEM(py_list, idx);
        if (!PyFloat_Check(element)) {
            PyErr_SetString(PyExc_TypeError, "Parameter `matrix' must be a list of 9 floats");
            return NULL;
        }
        matrix[idx] = (float) PyFloat_AsDouble(element);
    }

    vgMultMatrix(matrix);

    if (check_error())
        return NULL;

    Py_RETURN_NONE;
}


PyDoc_STRVAR(OpenVG_vgReadPixels__doc__,
".. function:: read_pixels(dataStride, dataFormat, sx, sy, width, height)\n"
"\n"
"   Copy pixel values to `data'.\n"
"\n"
"   :arg dataStride: Stride between pixel rows.\n"
"   :type dataStride: int\n"
"   :arg dataFormat: Pixel data format.\n"
"   :type dataFormat: VGImageFormat\n"
"   :arg sx: Start position x.\n"
"   :type sx: int\n"
"   :arg sy: Start position y.\n"
"   :type sy: int\n"
"   :arg width: Width of the sub-region.\n"
"   :type width: int\n"
"   :arg height: Height of the sub-region.\n"
"   :return: Raw pixel data.\n"
"   :rtype: bytearray\n"
"\n"
"   :error: VG_UNSUPPORTED_IMAGE_FORMAT_ERROR.\n"
"   :error: VG_ILLEGAL_ARGUMENT_ERROR.\n"
);

static PyObject *
OpenVG_vgReadPixels(PyVGContext *self, PyObject *args, PyObject *kwargs)
{
    PyObject *py_retval;
    char *data;
    VGint dataStride;
    VGImageFormat dataFormat;
    VGint sx, sy, width, height;
    int bytes;

    const char *keywords[] = {"dataStride", "dataFormat", "sx", "sy", "width", "height", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "iiiiii", (char **) keywords, &dataStride, &dataFormat, &sx, &sy, &width, &height)) {
        return NULL;
    }

    bytes = width*height;
    switch (dataFormat) {
        case VG_sL_8:
        case VG_lL_8:
        case VG_A_8:  /* 1 byte/pixel */
            break;
        case VG_sRGB_565:
        case VG_sRGBA_5551:
        case VG_sRGBA_4444:  /* 2 bytes/pixel */
            bytes *= 2;
            break;
        default:  /* 4 bytes/pixel */
            bytes *= 4;
    }

    data = (char *)malloc(sizeof(char) * bytes);

    vgReadPixels(data, dataStride, dataFormat, sx, sy, width, height);

    if (check_error()) {
        free(data);
        return NULL;
    }

    py_retval = Py_BuildValue((char *) "N", PyByteArray_FromStringAndSize(data, bytes));

    free(data);

    return py_retval;
}


PyDoc_STRVAR(OpenVG_vgWritePixels__doc__,
".. function:: write_pixels(data, dataStride, dataFormat, dx, dy, width, height)\n"
"\n"
"   Fill region with `data'.\n"
"\n"
"   :arg data: Raw pixel data.\n"
"   :type data: bytes\n"
"   :arg dataStride: Stride between pixel rows.\n"
"   :type dataStride: int\n"
"   :arg dataFormat: Pixel data format.\n"
"   :type dataFormat: VGImageFormat\n"
"   :arg dx: Start position x.\n"
"   :type dx: int\n"
"   :arg dy: Start position y.\n"
"   :type dy: int\n"
"   :arg width: Width of the sub-region.\n"
"   :type width: int\n"
"   :arg height: Height of the sub-region.\n"
"\n"
"   :error: VG_UNSUPPORTED_IMAGE_FORMAT_ERROR.\n"
"   :error: VG_ILLEGAL_ARGUMENT_ERROR.\n"
);

static PyObject *
OpenVG_vgWritePixels(PyVGContext *self, PyObject *args, PyObject *kwargs)
{
    PyObject *data;
    VGint dataStride;
    VGImageFormat dataFormat;
    VGint dx, dy, width, height;

    const char *keywords[] = {"data", "dataStride", "dataFormat", "dx", "dy", "width", "height", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs,
                                     (char *) "O!iiiiii",
                                     (char **) keywords,
                                     &PyByteArray_Type, &data,
                                     &dataStride, &dataFormat,
                                     &dx, &dy, &width, &height)) {
        return NULL;
    }

    vgWritePixels(PyByteArray_AsString(data),
                  dataStride, dataFormat, dx, dy, width, height);

    if (check_error()) {
        return NULL;
    }

    Py_RETURN_NONE;
}


PyDoc_STRVAR(OpenVG_vgMask__doc__,
".. function:: mask(mask, operation, x, y, width, height)\n"
"\n"
"   Fill region with `data'.\n"
"\n"
"   :arg mask: Image mask.\n"
"   :type mask: VGImage\n"
"   :arg operation: Masking operation.\n"
"   :type operation: VGMaskOperation\n"
"   :arg x: Start position x.\n"
"   :type x: int\n"
"   :arg y: Start position y.\n"
"   :type y: int\n"
"   :arg width: Width of the sub-region.\n"
"   :type width: int\n"
"   :arg height: Height of the sub-region.\n"
"\n"
"   :error: VG_BAD_HANDLE_ERROR.\n"
"   :error: VG_IMAGE_IN_USE_ERROR.\n"
"   :error: VG_ILLEGAL_ARGUMENT_ERROR.\n"
);

static PyObject *
OpenVG_vgMask(PyVGContext *self, PyObject *args, PyObject *kwargs)
{
    PyVGImage *mask;
    VGMaskOperation operation;
    VGint x, y, width, height;
    const char *keywords[] = {"mask", "operation", "x", "y", "width", "height", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!iiiii", (char **) keywords, &PyVGImage_Type, &mask, &operation, &x, &y, &width, &height)) {
        return NULL;
    }

    vgMask(mask->obj, operation, x, y, width, height);

    if (check_error()) {
        return NULL;
    }

    Py_RETURN_NONE;
}


PyDoc_STRVAR(OpenVG_vgFinish__doc__,
".. function:: finish()\n"
"\n"
"   Force outstanding requests to complete.\n"
);

static PyObject *
OpenVG_vgFinish(PyVGContext *self, PyObject *args, PyObject *kwargs)
{
    vgFinish();

    Py_RETURN_NONE;
}


PyDoc_STRVAR(OpenVG_vgScale__doc__,
".. function:: scale(sx, sy)\n"
"\n"
"   Scale the current transform matrix.\n"
"\n"
"   :arg sx: x factor.\n"
"   :type sx: float\n"
"   :arg sy: y factor.\n"
"   :type sy: float\n"
);

static PyObject *
OpenVG_vgScale(PyVGContext *self, PyObject *args, PyObject *kwargs)
{
    VGfloat sx;
    VGfloat sy;
    const char *keywords[] = {"sx", "sy", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "ff", (char **) keywords, &sx, &sy)) {
        return NULL;
    }
    vgScale(sx, sy);

    Py_RETURN_NONE;
}


PyDoc_STRVAR(OpenVG_vgTranslate__doc__,
".. function:: translate(tx, ty)\n"
"\n"
"   Apply a translation to the current transform matrix.\n"
"\n"
"   :arg tx: x factor.\n"
"   :type tx: float\n"
"   :arg ty: y factor.\n"
"   :type ty: float\n"
);

static PyObject *
OpenVG_vgTranslate(PyVGContext *self, PyObject *args, PyObject *kwargs)
{
    VGfloat tx;
    VGfloat ty;
    const char *keywords[] = {"tx", "ty", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "ff", (char **) keywords, &tx, &ty)) {
        return NULL;
    }
    vgTranslate(tx, ty);

    Py_RETURN_NONE;
}


PyDoc_STRVAR(OpenVG_vgCopyPixels__doc__,
".. function:: copy_pixels(dx, dy, sx, sy, width, height)\n"
"\n"
"   Copy pixels from one region of the drawing surface to another.\n"
"\n"
"   :arg dx: Destination start position x.\n"
"   :type dx: int\n"
"   :arg dy: Destination start position y.\n"
"   :type dy: int\n"
"   :arg sx: Source start position x.\n"
"   :type sx: int\n"
"   :arg sy: Source start position y.\n"
"   :type sy: int\n"
"   :arg width: Width of the sub-region.\n"
"   :type width: int\n"
"   :arg height: Height of the sub-region.\n"
"   :type height: int\n"
"\n"
"   :error: VG_ILLEGAL_ARGUMENT_ERROR.\n"
);

static PyObject *
OpenVG_vgCopyPixels(PyVGContext *self, PyObject *args, PyObject *kwargs)
{
    VGint dx, dy, sx, sy, width, height;

    const char *keywords[] = {"dx", "dy", "sx", "sy", "width", "height", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "iiiiii", (char **) keywords, &dx, &dy, &sx, &sy, &width, &height)) {
        return NULL;
    }

    vgCopyPixels(dx, dy, sx, sy, width, height);

    if (check_error()) {
        return NULL;
    }

    Py_RETURN_NONE;
}


PyDoc_STRVAR(OpenVG_vgFlush__doc__,
".. function:: flush()\n"
"\n"
"   Force outstanding requests to complete in finite time.\n"
);

static PyObject *
OpenVG_vgFlush(PyVGContext *self, PyObject *args, PyObject *kwargs)
{
    vgFlush();

    Py_RETURN_NONE;
}


PyDoc_STRVAR(OpenVG_vgGetPixels__doc__,
".. function:: copy_pixels(dst, dx, dy, sx, sy, width, height)\n"
"\n"
"   Copy pixels from one region of the drawing surface to another.\n"
"\n"
"   :arg dst: Destination image.\n"
"   :type dst: VGImage\n"
"   :arg dx: Destination start position x.\n"
"   :type dx: int\n"
"   :arg dy: Destination start position y.\n"
"   :type dy: int\n"
"   :arg sx: Source start position x.\n"
"   :type sx: int\n"
"   :arg sy: Source start position y.\n"
"   :type sy: int\n"
"   :arg width: Width of the sub-region.\n"
"   :type width: int\n"
"   :arg height: Height of the sub-region.\n"
"   :type height: int\n"
"\n"
"   :error: VG_ILLEGAL_ARGUMENT_ERROR.\n"
);

static PyObject *
OpenVG_vgGetPixels(PyVGContext *self, PyObject *args, PyObject *kwargs)
{
    PyVGImage *dst;
    VGint dx, dy, sx, sy, width, height;
    const char *keywords[] = {"dst", "dx", "dy", "sx", "sy", "width", "height", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!iiiiii", (char **) keywords, &PyVGImage_Type, &dst, &dx, &dy, &sx, &sy, &width, &height)) {
        return NULL;
    }

    vgGetPixels(dst->obj, dx, dy, sx, sy, width, height);

    if (check_error()) {
        return NULL;
    }

    Py_RETURN_NONE;
}


PyDoc_STRVAR(OpenVG_vgLoadMatrix__doc__,
".. function:: load_matrix(matrix)\n"
"\n"
"   Load `matrix' into the current transformation matrix.\n"
"\n"
"   :arg matrix: Matrix to load.\n"
"   :type matrix: list of 9 floats\n"
"\n"
"   :error: VG_ILLEGAL_ARGUMENT_ERROR.\n"
);

static PyObject *
OpenVG_vgLoadMatrix(PyVGContext *self, PyObject *args, PyObject *kwargs)
{
    VGfloat matrix[MATRIX_SIZE];
    PyObject *py_list;
    int idx;

    const char *keywords[] = {"matrix", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!", (char **) keywords, &PyList_Type, &py_list)) {
        return NULL;
    }
    if (PyList_Size(py_list) != MATRIX_SIZE) {
        PyErr_SetString(PyExc_TypeError, "Parameter `matrix' must be a list of 9 floats");
        return NULL;
    }
    for (idx = 0; idx < MATRIX_SIZE; idx++) {
        PyObject *element = PyList_GET_ITEM(py_list, idx);
        if (!PyFloat_Check(element)) {
            PyErr_SetString(PyExc_TypeError, "Parameter `matrix' must be a list of 9 floats");
            return NULL;
        }
        matrix[idx] = (float) PyFloat_AsDouble(element);
    }

    vgLoadMatrix(matrix);

    if (check_error()) {
        return NULL;
    }

    Py_RETURN_NONE;
}


PyDoc_STRVAR(OpenVG_vgResizeSurfaceSH__doc__,
".. function:: resize(width, height)\n"
"\n"
"   Resize the drawing surface.\n"
"\n"
"   :arg width: Width of the drawing surface.\n"
"   :type width: int\n"
"   :arg height: Height of the drawing surface.\n"
"   :type height: int\n"
"\n"
"   :error: VG_ILLEGAL_ARGUMENT_ERROR.\n"
);

static PyObject *
OpenVG_vgResizeSurfaceSH(PyVGContext *self, PyObject *args, PyObject *kwargs)
{
    VGint width;
    VGint height;
    const char *keywords[] = {"width", "height", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "ii", (char **) keywords, &width, &height)) {
        return NULL;
    }
    vgResizeSurfaceSH(width, height);

    if (check_error()) {
        return NULL;
    }

    self->dimensions[0] = width;
    self->dimensions[1] = height;

    Py_RETURN_NONE;
}


PyDoc_STRVAR(OpenVG_vgShear__doc__,
".. function:: shear(shx, shy)\n"
"\n"
"   Append a shear to the current transformation matrix.\n"
"\n"
"   :arg shx: Shear x factor.\n"
"   :type shx: float\n"
"   :arg shy: Shear y factor.\n"
"   :type shy: float\n"
);

static PyObject *
OpenVG_vgShear(PyVGContext *self, PyObject *args, PyObject *kwargs)
{
    VGfloat shx;
    VGfloat shy;
    const char *keywords[] = {"shx", "shy", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "ff", (char **) keywords, &shx, &shy)) {
        return NULL;
    }
    vgShear(shx, shy);

    Py_RETURN_NONE;
}


static PyMethodDef PyVGContext_methods[] = {
    {(char *) "clear",
     (PyCFunction) OpenVG_vgClear,
     METH_KEYWORDS|METH_VARARGS,
     OpenVG_vgClear__doc__
    },
    {(char *) "flush",
     (PyCFunction) OpenVG_vgFlush,
     METH_NOARGS,
     OpenVG_vgFlush__doc__
    },
    {(char *) "finish",
     (PyCFunction) OpenVG_vgFinish,
     METH_NOARGS,
     OpenVG_vgFinish__doc__
    },
    {(char *) "resize",
     (PyCFunction) OpenVG_vgResizeSurfaceSH,
     METH_KEYWORDS|METH_VARARGS,
     OpenVG_vgResizeSurfaceSH__doc__
    },
    {(char *) "rotate",
     (PyCFunction) OpenVG_vgRotate,
     METH_KEYWORDS|METH_VARARGS,
     OpenVG_vgRotate__doc__
    },
    {(char *) "scale",
     (PyCFunction) OpenVG_vgScale,
     METH_KEYWORDS|METH_VARARGS,
     OpenVG_vgScale__doc__
    },
    {(char *) "shear",
     (PyCFunction) OpenVG_vgShear,
     METH_KEYWORDS|METH_VARARGS,
     OpenVG_vgShear__doc__
    },
    {(char *) "translate",
     (PyCFunction) OpenVG_vgTranslate,
     METH_KEYWORDS|METH_VARARGS,
     OpenVG_vgTranslate__doc__
    },
    {(char *) "get_matrix",
     (PyCFunction) OpenVG_vgGetMatrix,
     METH_NOARGS,
     OpenVG_vgGetMatrix__doc__
    },
    {(char *) "load_matrix",
     (PyCFunction) OpenVG_vgLoadMatrix,
     METH_KEYWORDS|METH_VARARGS,
     OpenVG_vgLoadMatrix__doc__
    },
    {(char *) "load_identity",
     (PyCFunction) OpenVG_vgLoadIdentity,
     METH_NOARGS,
     OpenVG_vgLoadIdentity__doc__
    },
    {(char *) "mult_matrix",
     (PyCFunction) OpenVG_vgMultMatrix,
     METH_KEYWORDS|METH_VARARGS,
     OpenVG_vgMultMatrix__doc__
    },
    {(char *) "mask",
     (PyCFunction) OpenVG_vgMask,
     METH_KEYWORDS|METH_VARARGS,
     OpenVG_vgMask__doc__
    },
    {(char *) "copy_pixels",
     (PyCFunction) OpenVG_vgCopyPixels,
     METH_KEYWORDS|METH_VARARGS,
     OpenVG_vgCopyPixels__doc__
    },
    {(char *) "get_pixels",
     (PyCFunction) OpenVG_vgGetPixels,
     METH_KEYWORDS|METH_VARARGS,
     OpenVG_vgGetPixels__doc__
    },
    {(char *) "set_pixels",
     (PyCFunction) OpenVG_vgSetPixels,
     METH_KEYWORDS|METH_VARARGS,
     OpenVG_vgSetPixels__doc__
    },
    {(char *) "read_pixels",
     (PyCFunction) OpenVG_vgReadPixels,
     METH_KEYWORDS|METH_VARARGS,
     OpenVG_vgReadPixels__doc__
    },
    {(char *) "write_pixels",
     (PyCFunction) OpenVG_vgWritePixels,
     METH_KEYWORDS|METH_VARARGS,
     OpenVG_vgWritePixels__doc__
    },
    {NULL, NULL, 0, NULL}
};

static PyObject *
PyVGContext__mp_subscript(PyVGContext *self, PyObject *value)
{
    PyObject *py_retval;
    VGuint key = PyLong_AsUnsignedLong(value);
    
    switch (key) {
        case VG_STROKE_LINE_WIDTH:
        case VG_STROKE_MITER_LIMIT:
        case VG_STROKE_DASH_PHASE:
            py_retval = PyFloat_FromDouble(vgGetf((VGParamType)key));
            break;
        case VG_SCISSOR_RECTS: {
            int idx;
            int count = vgGetVectorSize((VGParamType)key);
            VGint *values = (VGint*)malloc(sizeof(VGint) * count);

            vgGetiv((VGParamType)key, count, values);

            py_retval = PyList_New(count);

            for (idx = 0; idx < count; idx++) {
                PyList_SET_ITEM(py_retval, idx, PyLong_FromLong(values[idx]));
            }
            free(values);
            break;
        }
        case VG_STROKE_DASH_PATTERN:
        case VG_TILE_FILL_COLOR:
        case VG_CLEAR_COLOR: {
            int idx;
            int count = vgGetVectorSize((VGParamType)key);
            VGfloat *values = (VGfloat*)malloc(sizeof(VGfloat) * count);

            vgGetfv((VGParamType)key, count, values);

            py_retval = PyList_New(count);

            for (idx = 0; idx < count; idx++) {
                PyList_SET_ITEM(py_retval, idx, PyFloat_FromDouble(values[idx]));
            }
            free(values);
            break;
        }
        case VG_MATRIX_MODE:
        case VG_FILL_RULE:
        case VG_IMAGE_QUALITY:
        case VG_RENDERING_QUALITY:
        case VG_BLEND_MODE:
        case VG_IMAGE_MODE:
        case VG_STROKE_CAP_STYLE:
        case VG_STROKE_JOIN_STYLE:
        case VG_STROKE_DASH_PHASE_RESET:
        case VG_MASKING:
        case VG_SCISSORING:
        case VG_PIXEL_LAYOUT:
        case VG_SCREEN_LAYOUT:
        case VG_FILTER_FORMAT_LINEAR:
        case VG_FILTER_FORMAT_PREMULTIPLIED:
        case VG_FILTER_CHANNEL_MASK:
        case VG_MAX_SCISSOR_RECTS:
        case VG_MAX_DASH_COUNT:
        case VG_MAX_KERNEL_SIZE:
        case VG_MAX_SEPARABLE_KERNEL_SIZE:
        case VG_MAX_COLOR_RAMP_STOPS:
        case VG_MAX_IMAGE_WIDTH:
        case VG_MAX_IMAGE_HEIGHT:
        case VG_MAX_IMAGE_PIXELS:
        case VG_MAX_IMAGE_BYTES:
        case VG_MAX_FLOAT:
        case VG_MAX_GAUSSIAN_STD_DEVIATION:
            py_retval = PyLong_FromLong(vgGeti((VGParamType)key));
            break;
        default:
            PyErr_SetString(PyExc_IndexError,
                            "VGContext[key]: key must be a VGParamType");
            return NULL;
    }

    return Py_BuildValue((char *) "N", py_retval);
}

static int
PyVGContext__mp_ass_subscript(PyVGContext *self, PyObject *pykey, PyObject *value)
{
    VGuint key = PyLong_AsUnsignedLong(pykey);

    switch (key) {
        case VG_STROKE_LINE_WIDTH:
        case VG_STROKE_MITER_LIMIT:
        case VG_STROKE_DASH_PHASE:
            vgSetf((VGParamType)key, (float) PyFloat_AsDouble(value));
            break;
        case VG_SCISSOR_RECTS: {
            if (PyList_Check(value) == 0) {
                PyErr_SetString(PyExc_TypeError,
                                "VGContext[key]: expected a list of ints");
                return -1;
            }

            int idx;
            int count = PyList_Size(value);
            VGint *tmp_values = (VGint*)malloc(sizeof(VGint) * count);

            for (idx = 0; idx < count; idx++) {
                PyObject *py_tmp = PyList_GetItem(value, idx);
                tmp_values[idx] = PyLong_AsLong(py_tmp);
            }

            vgSetiv((VGParamType)key, count, tmp_values);

            free(tmp_values);
            break;
        }
        case VG_STROKE_DASH_PATTERN:
        case VG_TILE_FILL_COLOR:
        case VG_CLEAR_COLOR: {
            if (PyList_Check(value) == 0) {
                PyErr_SetString(PyExc_TypeError,
                                "VGContext[key]: expected a list of floats");
                return -1;
            }

            int idx;
            int count = PyList_Size(value);
            VGfloat *tmp_values = (VGfloat*)malloc(sizeof(VGfloat) * count);

            for (idx = 0; idx < count; idx++) {
                PyObject *py_tmp = PyList_GetItem(value, idx); 
                tmp_values[idx] = (float) PyFloat_AsDouble(py_tmp);
            }

            vgSetfv((VGParamType)key, count, tmp_values);

            free(tmp_values);
            break;
        }
        case VG_MATRIX_MODE:
        case VG_FILL_RULE:
        case VG_IMAGE_QUALITY:
        case VG_RENDERING_QUALITY:
        case VG_BLEND_MODE:
        case VG_IMAGE_MODE:
        case VG_STROKE_CAP_STYLE:
        case VG_STROKE_JOIN_STYLE:
        case VG_STROKE_DASH_PHASE_RESET:
        case VG_MASKING:
        case VG_SCISSORING:
        case VG_PIXEL_LAYOUT:
        case VG_SCREEN_LAYOUT:
        case VG_FILTER_FORMAT_LINEAR:
        case VG_FILTER_FORMAT_PREMULTIPLIED:
        case VG_FILTER_CHANNEL_MASK:
            vgSeti((VGParamType)key, PyLong_AsLong(value));
            break;
        /* Implementation limits (read-only) */
        case VG_MAX_SCISSOR_RECTS:
        case VG_MAX_DASH_COUNT:
        case VG_MAX_KERNEL_SIZE:
        case VG_MAX_SEPARABLE_KERNEL_SIZE:
        case VG_MAX_COLOR_RAMP_STOPS:
        case VG_MAX_IMAGE_WIDTH:
        case VG_MAX_IMAGE_HEIGHT:
        case VG_MAX_IMAGE_PIXELS:
        case VG_MAX_IMAGE_BYTES:
        case VG_MAX_FLOAT:
        case VG_MAX_GAUSSIAN_STD_DEVIATION:
                PyErr_SetString(PyExc_TypeError,
                                "VGContext[key]: value is read-only");
                return -1;
        default:
            PyErr_SetString(PyExc_IndexError,
                            "VGContext[key]: key must be a VGParamType");
            return -1;
    }

    return 0;
}

static PyMappingMethods PyVGContext__tp_as_mapping = {
	(lenfunc) NULL,	                                /* mp_length */
	(binaryfunc) PyVGContext__mp_subscript,	        /* mp_subscript */
	(objobjargproc) PyVGContext__mp_ass_subscript,  /* mp_ass_subscript */
};

static void
PyVGContext__tp_dealloc(PyObject *self)
{
    vgDestroyContextSH();
    Py_TYPE(self)->tp_free(self);

}


PyTypeObject PyVGContext_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    (char *) "VG.VGContext",                      /* tp_name */
    sizeof(PyVGContext),                              /* tp_basicsize */
    0,                                                /* tp_itemsize */
    /* methods */
    (destructor)PyVGContext__tp_dealloc,              /* tp_dealloc */
    (printfunc)0,                                     /* tp_print */
    (getattrfunc)NULL,                                /* tp_getattr */
    (setattrfunc)NULL,                                /* tp_setattr */
    (cmpfunc)NULL,                                    /* tp_compare */
    (reprfunc)NULL,                                   /* tp_repr */
    (PyNumberMethods*)NULL,                           /* tp_as_number */
    (PySequenceMethods*)NULL,                         /* tp_as_sequence */
    (PyMappingMethods*)&PyVGContext__tp_as_mapping,   /* tp_as_mapping */
    (hashfunc)NULL,                                   /* tp_hash */
    (ternaryfunc)NULL,                                /* tp_call */
    (reprfunc)NULL,                                   /* tp_str */
    (getattrofunc)NULL,                               /* tp_getattro */
    (setattrofunc)NULL,                               /* tp_setattro */
    (PyBufferProcs*)NULL,                             /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,                               /* tp_flags */
    NULL,                                             /* Documentation string */
    (traverseproc)NULL,                               /* tp_traverse */
    (inquiry)NULL,                                    /* tp_clear */
    (richcmpfunc)NULL,                                /* tp_richcompare */
    0,                                                /* tp_weaklistoffset */
    (getiterfunc)NULL,                                /* tp_iter */
    (iternextfunc)NULL,                               /* tp_iternext */
    (struct PyMethodDef*)PyVGContext_methods,         /* tp_methods */
    (struct PyMemberDef*)0,                           /* tp_members */
    PyVGContext__getsets,                             /* tp_getset */
    NULL,                                             /* tp_base */
    NULL,                                             /* tp_dict */
    (descrgetfunc)NULL,                               /* tp_descr_get */
    (descrsetfunc)NULL,                               /* tp_descr_set */
    0,                                                /* tp_dictoffset */
    (initproc)PyVGContext__tp_init,                   /* tp_init */
    (allocfunc)PyType_GenericAlloc,                   /* tp_alloc */
    (newfunc)PyVGContext__tp_new,                     /* tp_new */
    (freefunc)0,                                      /* tp_free */
    (inquiry)NULL,                                    /* tp_is_gc */
    NULL,                                             /* tp_bases */
    NULL,                                             /* tp_mro */
    NULL,                                             /* tp_cache */
    NULL,                                             /* tp_subclasses */
    NULL,                                             /* tp_weaklist */
    (destructor) NULL                                 /* tp_del */
};


