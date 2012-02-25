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
PyVGImage__tp_init(PyVGImage *self, PyObject *args, PyObject *kwargs)
{
    VGImageFormat format;
    VGint width;
    VGint height;
    unsigned int allowedQuality;
    const char *keywords[] = {"format", "width", "height", "allowedQuality", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "iiiI", (char **) keywords, &format, &width, &height, &allowedQuality)) {
        return -1;
    }

    self->obj = vgCreateImage(format, width, height, allowedQuality);

    return check_error() ? -1 : 0;
}


PyDoc_STRVAR(OpenVG_vgChildImage__doc__,
".. function:: child(x, y, width, height)\n"
"\n"
"   Create a child image from the given dimensions.\n"
"\n"
"   :arg x: Start position x.\n"
"   :type x: int\n"
"   :arg y: Start position y.\n"
"   :type y: int\n"
"   :arg width: Width of the sub-region.\n"
"   :type width: int\n"
"   :arg height: Height of the sub-region.\n"
"   :type height: int\n"
"   :return: The child image.\n"
"   :rtype: VGImage\n"
"\n"
"   :error: VG_BAD_HANDLE_ERROR.\n"
"   :error: VG_IMAGE_IN_USE_ERROR.\n"
"   :error: VG_ILLEGAL_ARGUMENT_ERROR.\n"
);

static PyObject *
OpenVG_vgChildImage(PyVGImage *self, PyObject *args, PyObject *kwargs)
{
    PyObject *py_retval;
    VGint x;
    VGint y;
    VGint width;
    VGint height;
    const char *keywords[] = {"x", "y", "width", "height", NULL};
    PyVGImage *py_VGImage;
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "iiii", (char **) keywords, &x, &y, &width, &height)) {
        return NULL;
    }

    VGImage retval = vgChildImage(self->obj, x, y, width, height);

    if (check_error()) {
        return NULL;
    }

    py_VGImage = PyObject_New(PyVGImage, &PyVGImage_Type);
    py_VGImage->obj = retval;

    py_retval = Py_BuildValue((char *) "N", py_VGImage);
    return py_retval;
}


PyDoc_STRVAR(OpenVG_vgClearImage__doc__,
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
"   :error: VG_BAD_HANDLE_ERROR.\n"
"   :error: VG_IMAGE_IN_USE_ERROR.\n"
"   :error: VG_ILLEGAL_ARGUMENT_ERROR.\n"
);

static PyObject *
OpenVG_vgClearImage(PyVGImage *self, PyObject *args, PyObject *kwargs)
{
    VGint x;
    VGint y;
    VGint width;
    VGint height;
    const char *keywords[] = {"x", "y", "width", "height", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "iiii", (char **) keywords, &x, &y, &width, &height)) {
        return NULL;
    }

    vgClearImage(self->obj, x, y, width, height);

    if (check_error()) {
        return NULL;
    }

    Py_RETURN_NONE;
}


PyDoc_STRVAR(OpenVG_vgColorMatrix__doc__,
".. function:: color_matrix(x, y, width, height)\n"
"\n"
"   Computes a linear combination of color and alpha values from the normalized source image src at each pixel.\n"
"\n"
"   :arg src: Source image.\n"
"   :type src: VGImage\n"
"   :arg matrix: Color Matrix.\n"
"   :type matrix: float[16]\n"
"\n"
"   :error: VG_BAD_HANDLE_ERROR.\n"
"   :error: VG_IMAGE_IN_USE_ERROR.\n"
"   :error: VG_ILLEGAL_ARGUMENT_ERROR.\n"
);

static PyObject *
OpenVG_vgColorMatrix(PyVGImage *self, PyObject *args, PyObject *kwargs)
{
    PyVGImage *src;
    VGfloat matrix[MATRIX_SIZE];
    PyObject *py_list;
    int idx;
    PyObject *element;
    const char *keywords[] = {"src", "matrix", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!O!", (char **) keywords, &PyVGImage_Type, &src, &PyList_Type, &py_list)) {
        return NULL;
    }

    if (PyList_Size(py_list) != 16) {
        PyErr_SetString(PyExc_TypeError, "Parameter `matrix' must be a list of 16 floats");
        return NULL;
    }

    for (idx = 0; idx < 16; idx++) {
        element = PyList_GET_ITEM(py_list, idx);
        if (!PyFloat_Check(element)) {
            PyErr_SetString(PyExc_TypeError, "Parameter `matrix' must be a list of 16 floats");
            return NULL;
        }
        matrix[idx] = (float) PyFloat_AsDouble(element);
    }

    vgColorMatrix(self->obj, src->obj, matrix);

    if (check_error()) {
        return NULL;
    }

    Py_RETURN_NONE;
}


PyDoc_STRVAR(OpenVG_vgConvolve__doc__,
".. function:: convolve(src, kernelWidth, kernelHeight, shiftX, shiftY,\n"
"                       kernel, scale, bias, tilingMode)\n"
"\n"
"   Computes a linear combination of color and alpha values\n"
"   from the normalized source image `src' at each pixel.\n"
"\n"
"   :arg src: Source image.\n"
"   :type src: VGImage\n"
"   :arg kernelWidth: Kernel Width.\n"
"   :type kernelWidth: int\n"
"   :arg kernelHeight: Kernel Height.\n"
"   :type kernelHeight: int\n"
"   :arg shiftX: X shift from source image.\n"
"   :type shiftX: int\n"
"   :arg shiftY: Y shift from source image.\n"
"   :type shiftY: int\n"
"   :arg kernel: Convolution kernel.\n"
"   :type kernel: int[kernelWidth*kernelHeight]\n"
"   :arg scale: Scale.\n"
"   :type scale: float\n"
"   :arg bias: Bias.\n"
"   :type bias: float\n"
"   :arg tilingMode: Tiling Mode.\n"
"   :type tilingMode: VGTilingMode\n"
"\n"
"   :error: VG_BAD_HANDLE_ERROR.\n"
"   :error: VG_IMAGE_IN_USE_ERROR.\n"
"   :error: VG_ILLEGAL_ARGUMENT_ERROR.\n"
);

static PyObject *
OpenVG_vgConvolve(PyVGImage *self, PyObject *args, PyObject *kwargs)
{
    PyVGImage *src;
    VGint kernelWidth, kernelHeight;
    VGint shiftX, shiftY;
    VGshort *kernel;
    PyObject *py_list;
    VGfloat scale, bias;
    VGTilingMode tilingMode;
    int count, idx;

    const char *keywords[] = {"src", "kernelWidth", "kernelHeight", "shiftX", "shiftY", "kernel", "scale", "bias", "tilingMode", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!iiii0!ffi", (char **) keywords, &PyVGImage_Type, &src, &kernelWidth, &kernelHeight, &shiftX, &shiftY, &PyList_Type, &py_list, &scale, &bias, &tilingMode)) {
        return NULL;
    }

    count = PyList_Size(py_list);

    if (count != kernelWidth*kernelHeight) {
        PyErr_SetString(PyExc_ValueError,
                        "VGImage.convolve(): kernel != kernelWidth * kernelHeight");
        return NULL;
    }

    kernel = (VGshort *)malloc(sizeof(VGshort) * count);
    for (idx = 0; idx < count; idx++) {
        PyObject *element = PyList_GET_ITEM(py_list, idx);
        kernel[idx] = (VGshort) PyLong_AsLong(element);
    }

    vgConvolve(self->obj, src->obj, kernelWidth, kernelHeight,
               shiftX, shiftY, kernel, scale, bias, (VGTilingMode)tilingMode);

    free(kernel);

    if (check_error()) {
        return NULL;
    }

    Py_RETURN_NONE;
}


PyDoc_STRVAR(OpenVG_vgCopyImage__doc__,
".. function:: copy(dx, dy, src, sx, sy, width, height, dither)\n"
"\n"
"   Copy pixels between images.\n"
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
"   :arg dither: Apply dithering to the copied pixels.\n"
"   :type dither: bool\n"
"\n"
"   :error: VG_BAD_HANDLE_ERROR.\n"
"   :error: VG_IMAGE_IN_USE_ERROR.\n"
"   :error: VG_ILLEGAL_ARGUMENT_ERROR.\n"
);

static PyObject *
OpenVG_vgCopyImage(PyVGImage *self, PyObject *args, PyObject *kwargs)
{
    VGint dx;
    VGint dy;
    PyVGImage *src;
    VGint sx;
    VGint sy;
    VGint width;
    VGint height;
    PyObject *dither;
    const char *keywords[] = {"dx", "dy", "src", "sx", "sy", "width", "height", "dither", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "iiO!iiiiO!", (char **) keywords, &dx, &dy, &PyVGImage_Type, &src, &sx, &sy, &width, &height, &PyBool_Type, &dither)) {
        return NULL;
    }

    vgCopyImage(self->obj, dx, dy, src->obj, sx, sy, width, height,
                (VGboolean)PyObject_IsTrue(dither));

    Py_RETURN_NONE;
}


PyDoc_STRVAR(OpenVG_vgDrawImage__doc__,
".. function:: draw()\n"
"\n"
"   Draw the image on the current drawing surface.\n"
"\n"
"   :error: VG_BAD_HANDLE_ERROR.\n"
"   :error: VG_IMAGE_IN_USE_ERROR.\n"
);

static PyObject *
OpenVG_vgDrawImage(PyVGImage *self, PyObject *args, PyObject *kwargs)
{
    vgDrawImage(self->obj);

    if (check_error())
        return NULL;

    Py_RETURN_NONE;
}


PyDoc_STRVAR(OpenVG_vgGaussianBlur__doc__,
".. function:: gaussian_blur(src, stdDeviationX, stdDeviationY, tilingMode)\n"
"\n"
"   Applies a Gaussian separable convolution\n"
"   kernel to a normalized source image `src'.\n"
"\n"
"   :arg src: Source image.\n"
"   :type src: VGImage\n"
"   :arg stdDeviationX: Standard deviations in the horizontal direction.\n"
"   :type stdDeviationX: float\n"
"   :arg stdDeviationY: Standard deviations in the vertical direction.\n"
"   :type stdDeviationY: float\n"
"   :arg tilingMode: Tiling Mode.\n"
"   :type tilingMode: VGTilingMode\n"
"\n"
"   :error: VG_BAD_HANDLE_ERROR.\n"
"   :error: VG_IMAGE_IN_USE_ERROR.\n"
"   :error: VG_ILLEGAL_ARGUMENT_ERROR.\n"
);

static PyObject *
OpenVG_vgGaussianBlur(PyVGImage *self, PyObject *args, PyObject *kwargs)
{
    PyVGImage *src;
    VGfloat stdDeviationX;
    VGfloat stdDeviationY;
    VGTilingMode tilingMode;
    const char *keywords[] = {"src", "stdDeviationX", "stdDeviationY", "tilingMode", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!ffi", (char **) keywords, &PyVGImage_Type, &src, &stdDeviationX, &stdDeviationY, &tilingMode)) {
        return NULL;
    }

    vgGaussianBlur(self->obj, src->obj, stdDeviationX, stdDeviationY, tilingMode);

    if (check_error()) {
        return NULL;
    }

    Py_RETURN_NONE;
}


PyDoc_STRVAR(OpenVG_vgGetParent__doc__,
".. function:: parent()\n"
"\n"
"   Get the parent of this VGImage.\n"
"\n"
"   :return: the closest valid ancestor or self.\n"
"   :rtype: VGImage\n"
"\n"
"   :error: VG_BAD_HANDLE_ERROR.\n"
"   :error: VG_IMAGE_IN_USE_ERROR.\n"
);

static PyObject *
OpenVG_vgGetParent(PyVGImage *self, PyObject *args, PyObject *kwargs)
{
    PyObject *py_retval;
    PyVGImage *py_VGImage;
    
    VGImage retval = vgGetParent(self->obj);

    if (check_error()) {
        return NULL;
    }

    py_VGImage = PyObject_New(PyVGImage, &PyVGImage_Type);
    py_VGImage->obj = retval;

    py_retval = Py_BuildValue((char *) "N", py_VGImage);

    return py_retval;
}


PyDoc_STRVAR(OpenVG_vgSeparableConvolve__doc__,
".. function:: convolve(src, kernelWidth, kernelHeight, shiftX, shiftY,\n"
"                       kernel, scale, bias, tilingMode)\n"
"\n"
"   applies a user-supplied separable convolution\n"
"   kernel to a normalized source image `src'.\n"
"\n"
"   :arg src: Source image.\n"
"   :type src: VGImage\n"
"   :arg kernelWidth: Kernel Width.\n"
"   :type kernelWidth: int\n"
"   :arg kernelHeight: Kernel Height.\n"
"   :type kernelHeight: int\n"
"   :arg shiftX: X shift from source image.\n"
"   :type shiftX: int\n"
"   :arg shiftY: Y shift from source image.\n"
"   :type shiftY: int\n"
"   :arg kernelX: Kernel X.\n"
"   :type kernelX: int[kernelWidth]\n"
"   :arg kernelY: Kernel Y.\n"
"   :type kernelY: int[kernelHeight]\n"
"   :arg scale: Scale.\n"
"   :type scale: float\n"
"   :arg bias: Bias.\n"
"   :type bias: float\n"
"   :arg tilingMode: Tiling Mode.\n"
"   :type tilingMode: VGTilingMode\n"
"\n"
"   :error: VG_BAD_HANDLE_ERROR.\n"
"   :error: VG_IMAGE_IN_USE_ERROR.\n"
"   :error: VG_ILLEGAL_ARGUMENT_ERROR.\n"
);

static PyObject *
OpenVG_vgSeparableConvolve(PyVGImage *self, PyObject *args, PyObject *kwargs)
{
    PyVGImage *src;
    VGint kernelWidth;
    VGint kernelHeight;
    VGint shiftX;
    VGint shiftY;
    VGshort *kernelX;
    PyObject *py_listX;
    VGshort *kernelY;
    PyObject *py_listY;
    VGfloat scale;
    VGfloat bias;
    VGTilingMode tilingMode;
    int idx;

    const char *keywords[] = {"src", "kernelWidth", "kernelHeight", "shiftX", "shiftY", "kernelX", "kernelY", "scale", "bias", "tilingMode", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!iiiiO!O!ffi", (char **) keywords, &PyVGImage_Type, &src, &kernelWidth, &kernelHeight, &shiftX, &shiftY, &PyList_Type, &py_listX, &PyList_Type, &py_listY, &scale, &bias, &tilingMode)) {
        return NULL;
    }

    if (PyList_Size(py_listX) != kernelWidth || PyList_Size(py_listY) != kernelHeight) {
        PyErr_SetString(PyExc_ValueError,
                        "VGImage.separable_convolve(): kernel dimensions don't match kernel list size");
        return NULL;
    }

    kernelX = (VGshort *)malloc(sizeof(VGshort) * kernelWidth);
    for (idx = 0; idx < kernelWidth; idx++) {
        PyObject *element = PyList_GET_ITEM(py_listX, idx);
        kernelX[idx] = (VGshort) PyLong_AsLong(element);
    }

    kernelY = (VGshort *)malloc(sizeof(VGshort) * kernelHeight);
    for (idx = 0; idx < kernelHeight; idx++) {
        PyObject *element = PyList_GET_ITEM(py_listY, idx);
        kernelY[idx] = (VGshort) PyLong_AsLong(element);
    }

    vgSeparableConvolve(self->obj,src->obj, kernelWidth, kernelHeight, shiftX, shiftY, kernelX, kernelY, scale, bias, (VGTilingMode)tilingMode);

    free(kernelX);
    free(kernelY);

    if (check_error()) {
        return NULL;
    }

    Py_RETURN_NONE;
}


PyDoc_STRVAR(OpenVG_vgImageSubData__doc__,
".. function:: set_sub_data(data, dataStride, dataFormat, x, y, width, height)\n"
"\n"
"   Fill region with `data'.\n"
"\n"
"   :arg data: Raw pixel data.\n"
"   :type data: bytes\n"
"   :arg dataStride: Stride between pixel rows.\n"
"   :type dataStride: int\n"
"   :arg dataFormat: Pixel data format.\n"
"   :type dataFormat: VGImageFormat\n"
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
"   :error: VG_UNSUPPORTED_IMAGE_FORMAT_ERROR.\n"
"   :error: VG_ILLEGAL_ARGUMENT_ERROR.\n"
);

static PyObject *
OpenVG_vgImageSubData(PyVGImage *self, PyObject *args, PyObject *kwargs)
{
    PyObject *data;
    VGint dataStride;
    VGImageFormat dataFormat;
    VGint x, y, width, height;

    const char *keywords[] = {"data", "dataStride", "dataFormat", "x", "y", "width", "height", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs,
                                     (char *) "O!iiiiii",
                                     (char **) keywords,
                                     &PyByteArray_Type, &data,
                                     &dataStride, &dataFormat,
                                     &x, &y, &width, &height)) {
        return NULL;
    }

    vgImageSubData(self->obj, PyByteArray_AsString(data),
                   dataStride, dataFormat, x, y, width, height);

    if (check_error()) {
        return NULL;
    }

    Py_RETURN_NONE;
}


PyDoc_STRVAR(OpenVG_vgGetImageSubData__doc__,
".. function:: get_sub_data(dataStride, dataFormat, x, y, width, height)\n"
"\n"
"   Copy pixel values to `data'.\n"
"\n"
"   :arg dataStride: Stride between pixel rows.\n"
"   :type dataStride: int\n"
"   :arg dataFormat: Pixel data format.\n"
"   :type dataFormat: VGImageFormat\n"
"   :arg x: Start position x.\n"
"   :type x: int\n"
"   :arg y: Start position y.\n"
"   :type y: int\n"
"   :arg width: Width of the sub-region.\n"
"   :type width: int\n"
"   :arg height: Height of the sub-region.\n"
"   :return: Raw pixel data.\n"
"   :rtype: bytearray\n"
"\n"
"   :error: VG_BAD_HANDLE_ERROR.\n"
"   :error: VG_IMAGE_IN_USE_ERROR.\n"
"   :error: VG_UNSUPPORTED_IMAGE_FORMAT_ERROR.\n"
"   :error: VG_ILLEGAL_ARGUMENT_ERROR.\n"
);

static PyObject *
OpenVG_vgGetImageSubData(PyVGImage *self, PyObject *args, PyObject *kwargs)
{
    PyObject *py_retval;
    char *data;
    VGint dataStride;
    VGImageFormat dataFormat;
    VGint x, y, width, height;
    int bytes;

    const char *keywords[] = {"dataStride", "dataFormat", "x", "y", "width", "height", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "iiiiii", (char **) keywords, &dataStride, &dataFormat, &x, &y, &width, &height)) {
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

    vgGetImageSubData(self->obj, data, dataStride, dataFormat, x, y, width, height);

    if (check_error()) {
        free(data);
        return NULL;
    }

    py_retval = Py_BuildValue((char *) "N", PyByteArray_FromStringAndSize(data, bytes));

    free(data);

    return py_retval;
}


PyDoc_STRVAR(OpenVG_vgLookup__doc__,
".. function:: lookup(src, redLUT, greenLUT, blueLUT, alphaLUT,\n"
"                     outputLinear, outputPremultiplied)\n"
"\n"
"   Pass each image channel from `src' through a seperate lookup table.\n"
"\n"
"   :arg src: Source image.\n"
"   :type src: VGImage\n"
"   :arg redLUT: Lookup table for the red channel.\n"
"   :type redLUT: bytearray\n"
"   :arg greenLUT: Lookup table for the green channel.\n"
"   :type greenLUT: bytearray\n"
"   :arg blueLUT: Lookup table for the blue channel.\n"
"   :type blueLUT: bytearray\n"
"   :arg alphaLUT: Lookup table for the alpha channel.\n"
"   :type alphaLUT: bytearray\n"
"   :arg sourceChannel: Source channel.\n"
"   :type sourceChannel: VGImageChannel.\n"
"   :arg outputLinear: Output linear pixels.\n"
"   :type outputLinear: bool\n"
"   :arg outputPremultiplied: Output premultiplied pixels.\n"
"   :type outputPremultiplied: bool\n"
"\n"
"   :error: VG_BAD_HANDLE_ERROR.\n"
"   :error: VG_IMAGE_IN_USE_ERROR.\n"
"   :error: VG_ILLEGAL_ARGUMENT_ERROR.\n"
);

static PyObject *
OpenVG_vgLookup(PyVGImage *self, PyObject *args, PyObject *kwargs)
{
    PyVGImage *src;
    PyObject *redLUT, *greenLUT, *blueLUT, *alphaLUT;
    PyObject *outputLinear, *outputPremultiplied;

    const char *keywords[] = {"src", "redLUT", "greenLUT", "blueLUT",
                              "alphaLUT", "outputLinear", "outputPremultiplied",
                              NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs,(char *) "O!O!O!O!O!O!O!",
                                     
                                     (char **) keywords,
                                     &PyVGImage_Type, &src,
                                     &PyByteArray_Type, &redLUT,
                                     &PyByteArray_Type, &greenLUT,
                                     &PyByteArray_Type, &blueLUT,
                                     &PyByteArray_Type, &alphaLUT,
                                     &PyBool_Type, &outputLinear,
                                     &PyBool_Type, &outputPremultiplied)) {
        return NULL;
    }

    if (PyByteArray_Size(redLUT) != 256   ||
        PyByteArray_Size(greenLUT) != 256 ||
        PyByteArray_Size(blueLUT) != 256  ||
        PyByteArray_Size(alphaLUT) != 256) {
        PyErr_SetString(PyExc_TypeError,
                        "Lookup Tables must be a bytearray of length 256");
        return NULL;
    }

    vgLookup(self->obj, src->obj,
             (const VGubyte*)PyByteArray_AsString(redLUT),
             (const VGubyte*)PyByteArray_AsString(greenLUT),
             (const VGubyte*)PyByteArray_AsString(blueLUT),
             (const VGubyte*)PyByteArray_AsString(alphaLUT),
             (VGboolean)PyObject_IsTrue(outputLinear),
             (VGboolean)PyObject_IsTrue(outputPremultiplied));

    if (check_error()) {
        return NULL;
    }

    Py_RETURN_NONE;
}


PyDoc_STRVAR(OpenVG_vgLookupSingle__doc__,
".. function:: lookup_single(src, lookupTable, sourceChannel,\n"
"                            outputLinear, outputPremultiplied)\n"
"\n"
"   Pass a single image channel `sourceChannel' through a lookup table.\n"
"\n"
"   :arg src: Source image.\n"
"   :type src: VGImage\n"
"   :arg lookupTable: Lookup table.\n"
"   :type lookupTable: unsigned int[256]\n"
"   :arg sourceChannel: Source channel.\n"
"   :type sourceChannel: VGImageChannel.\n"
"   :arg outputLinear: Output linear pixels.\n"
"   :type outputLinear: bool\n"
"   :arg outputPremultiplied: Output premultiplied pixels.\n"
"   :type outputPremultiplied: bool\n"
"\n"
"   :error: VG_BAD_HANDLE_ERROR.\n"
"   :error: VG_IMAGE_IN_USE_ERROR.\n"
"   :error: VG_ILLEGAL_ARGUMENT_ERROR.\n"
);

static PyObject *
OpenVG_vgLookupSingle(PyVGImage *self, PyObject *args, PyObject *kwargs)
{
    PyVGImage *src;
    VGuint lookupTable[256];
    PyObject *py_list;
    VGImageChannel sourceChannel;
    PyObject *outputLinear, *outputPremultiplied;
    int idx;

    const char *keywords[] = {"src", "lookupTable", "sourceChannel",
                              "outputLinear", "outputPremultiplied", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "O!O!iO!O!",
                                    (char **) keywords,
                                    &PyVGImage_Type, &src,
                                    &PyList_Type, &py_list,
                                    &sourceChannel,
                                    &PyBool_Type, &outputLinear,
                                    &PyBool_Type, &outputPremultiplied)) {
        return NULL;
    }

    if (PyList_Size(py_list) != 256) {
        PyErr_SetString(PyExc_TypeError,
                        "Parameter `lookupTable' must be a list of 256 unsigned ints");
        return NULL;
    }

    for (idx = 0; idx < 256; idx++) {
        PyObject *element = PyList_GET_ITEM(py_list, idx);
        lookupTable[idx] = (VGubyte) PyLong_AsUnsignedLong(element);
    }

    vgLookupSingle(self->obj, src->obj, (const VGuint*)lookupTable, sourceChannel,
                   (VGboolean)PyObject_IsTrue(outputLinear),
                   (VGboolean)PyObject_IsTrue(outputPremultiplied));

    if (check_error()) {
        return NULL;
    }

    Py_RETURN_NONE;
}

static PyMethodDef PyVGImage_methods[] = {
    {(char *) "child",
     (PyCFunction) OpenVG_vgChildImage,
     METH_KEYWORDS|METH_VARARGS,
     OpenVG_vgChildImage__doc__
    },
    {(char *) "clear",
     (PyCFunction) OpenVG_vgClearImage,
     METH_KEYWORDS|METH_VARARGS,
     OpenVG_vgClearImage__doc__
    },
    {(char *) "color_matrix",
     (PyCFunction) OpenVG_vgColorMatrix,
     METH_KEYWORDS|METH_VARARGS,
     OpenVG_vgColorMatrix__doc__
    },
    {(char *) "convolve",
     (PyCFunction) OpenVG_vgConvolve,
     METH_KEYWORDS|METH_VARARGS,
     OpenVG_vgConvolve__doc__
    },
    {(char *) "copy",
     (PyCFunction) OpenVG_vgCopyImage,
     METH_KEYWORDS|METH_VARARGS,
     OpenVG_vgCopyImage__doc__
    },
    {(char *) "draw",
     (PyCFunction) OpenVG_vgDrawImage,
     METH_NOARGS,
     OpenVG_vgDrawImage__doc__
    },
    {(char *) "gaussian_blur",
     (PyCFunction) OpenVG_vgGaussianBlur,
     METH_KEYWORDS|METH_VARARGS,
     OpenVG_vgGaussianBlur__doc__
    },
    {(char *) "lookup",
     (PyCFunction) OpenVG_vgLookup,
     METH_KEYWORDS|METH_VARARGS,
     OpenVG_vgLookup__doc__
    },
    {(char *) "lookup_single",
     (PyCFunction) OpenVG_vgLookupSingle,
     METH_KEYWORDS|METH_VARARGS,
     OpenVG_vgLookupSingle__doc__
    },
    {(char *) "parent",
     (PyCFunction) OpenVG_vgGetParent,
     METH_NOARGS,
     OpenVG_vgGetParent__doc__
    },
    {(char *) "separable_convolve",
     (PyCFunction) OpenVG_vgSeparableConvolve,
     METH_KEYWORDS|METH_VARARGS,
     OpenVG_vgSeparableConvolve__doc__
    },
    {(char *) "get_sub_data",
     (PyCFunction) OpenVG_vgGetImageSubData,
     METH_KEYWORDS|METH_VARARGS,
     OpenVG_vgGetImageSubData__doc__
    },
    {(char *) "set_sub_data",
     (PyCFunction) OpenVG_vgImageSubData,
     METH_KEYWORDS|METH_VARARGS,
     OpenVG_vgImageSubData__doc__
    },
    {NULL, NULL, 0, NULL}
};

static PyObject *
PyVGImage__mp_subscript(PyVGImage *self, PyObject *value)
{
    PyObject *py_retval;
    VGuint key = PyLong_AsUnsignedLong(value);

    switch (key) {
        case VG_IMAGE_FORMAT:
            py_retval = PyLong_FromUnsignedLong(vgGetParameteri(self->obj, key));
            break;
        case VG_MAX_IMAGE_WIDTH:
        case VG_MAX_IMAGE_HEIGHT:
            py_retval = PyLong_FromLong(vgGetParameteri(self->obj, key));
            break;
        default:
            PyErr_SetString(PyExc_IndexError,
                            "VGImage[key]: key must be a VGImageParamType");
            return NULL;
    }

    return Py_BuildValue((char *) "N", py_retval);
}

static int
PyVGImage__mp_ass_subscript(PyVGImage *self, PyObject *pykey, PyObject *value)
{
    VGuint key = (VGImageParamType)PyLong_AsUnsignedLong(pykey);
    
    switch (key) {
        case VG_IMAGE_FORMAT:
            vgSetParameteri(self->obj, key, PyLong_AsUnsignedLong(value));
            break;        
        case VG_MAX_IMAGE_WIDTH:
            PyErr_SetString(PyExc_KeyError,
                            "VGImage[VG_MAX_IMAGE_WIDTH]: value is read only");
            return -1;
        case VG_MAX_IMAGE_HEIGHT:
            PyErr_SetString(PyExc_KeyError,
                            "VGImage[VG_MAX_IMAGE_HEIGHT]: value is read only");
            return -1;
        default:
            PyErr_SetString(PyExc_IndexError,
                            "VGImage[key]: key must be a VGImageParamType");
            return -1;
    }

    return 0;
}

static PyMappingMethods PyVGImage__tp_as_mapping = {
	(lenfunc) NULL,	                                /* mp_length */
	(binaryfunc) PyVGImage__mp_subscript,	        /* mp_subscript */
	(objobjargproc) PyVGImage__mp_ass_subscript,  /* mp_ass_subscript */
};

static void
PyVGImage__tp_dealloc(PyVGImage *self)
{
    if (self->obj) {
        VGImage tmp = self->obj;
        self->obj = NULL;
        vgDestroyImage(tmp);
    }
    Py_TYPE(self)->tp_free((PyObject*)self);
}


PyTypeObject PyVGImage_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    (char *) "VG.VGImage",                     /* tp_name */
    sizeof(PyVGImage),                             /* tp_basicsize */
    0,                                             /* tp_itemsize */
    /* methods */
    (destructor)PyVGImage__tp_dealloc,             /* tp_dealloc */
    (printfunc)0,                                  /* tp_print */
    (getattrfunc)NULL,                             /* tp_getattr */
    (setattrfunc)NULL,                             /* tp_setattr */
    (cmpfunc)NULL,                                 /* tp_compare */
    (reprfunc)NULL,                                /* tp_repr */
    (PyNumberMethods*)NULL,                        /* tp_as_number */
    (PySequenceMethods*)NULL,                      /* tp_as_sequence */
    (PyMappingMethods*)&PyVGImage__tp_as_mapping,   /* tp_as_mapping */
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
    (struct PyMethodDef*)PyVGImage_methods,        /* tp_methods */
    (struct PyMemberDef*)0,                        /* tp_members */
    0,                                             /* tp_getset */
    NULL,                                          /* tp_base */
    NULL,                                          /* tp_dict */
    (descrgetfunc)NULL,                            /* tp_descr_get */
    (descrsetfunc)NULL,                            /* tp_descr_set */
    0,                                             /* tp_dictoffset */
    (initproc)PyVGImage__tp_init,                  /* tp_init */
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


