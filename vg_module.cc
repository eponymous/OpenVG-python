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

VGErrorCode check_error(void) {
    VGErrorCode error = vgGetError();

    switch (error) {
        case VG_NO_ERROR:
            break;
        case VG_BAD_HANDLE_ERROR:
            PyErr_SetString(PyExc_TypeError, "VG_BAD_HANDLE_ERROR");
            break;
        case VG_ILLEGAL_ARGUMENT_ERROR:
            PyErr_SetString(PyExc_TypeError, "VG_ILLEGAL_ARGUMENT_ERROR");
            break;
        case VG_OUT_OF_MEMORY_ERROR:
            PyErr_SetString(PyExc_MemoryError, "VG_OUT_OF_MEMORY_ERROR");
            break;
        case VG_PATH_CAPABILITY_ERROR:
            PyErr_SetString(PyExc_ValueError, "VG_PATH_CAPABILITY_ERROR");
            break;
        case VG_UNSUPPORTED_IMAGE_FORMAT_ERROR:
            PyErr_SetString(PyExc_ValueError, "VG_UNSUPPORTED_IMAGE_FORMAT_ERROR");
            break;
        case VG_UNSUPPORTED_PATH_FORMAT_ERROR:
            PyErr_SetString(PyExc_ValueError, "VG_UNSUPPORTED_PATH_FORMAT_ERROR");
            break;
        case VG_IMAGE_IN_USE_ERROR:
            PyErr_SetString(PyExc_RuntimeError, "VG_IMAGE_IN_USE_ERROR");
            break;
        case VG_NO_CONTEXT_ERROR:
            PyErr_SetString(PyExc_RuntimeError, "VG_NO_CONTEXT_ERROR");
            break;
    }
    return error;
}

#if PY_VERSION_HEX >= 0x03000000
static struct PyModuleDef VGRenderingQuality_moduledef = {
    PyModuleDef_HEAD_INIT,
    "VG.VGRenderingQuality",
    NULL,
    -1,
    NULL,
};
#endif

static PyObject *
initOpenVG_VGRenderingQuality(void)
{
    PyObject *m;
    #if PY_VERSION_HEX >= 0x03000000
    m = PyModule_Create(&VGRenderingQuality_moduledef);
    #else
    m = Py_InitModule3((char *) "VG.VGRenderingQuality", NULL, NULL);
    #endif
    if (m == NULL) {
        return NULL;
    }
    PyModule_AddIntConstant(m, (char *) "VG_RENDERING_QUALITY_NONANTIALIASED", VG_RENDERING_QUALITY_NONANTIALIASED);
    PyModule_AddIntConstant(m, (char *) "VG_RENDERING_QUALITY_FASTER", VG_RENDERING_QUALITY_FASTER);
    PyModule_AddIntConstant(m, (char *) "VG_RENDERING_QUALITY_BETTER", VG_RENDERING_QUALITY_BETTER);
    return m;
}

/*****************************************************************************/
#if PY_VERSION_HEX >= 0x03000000
static struct PyModuleDef VGTilingMode_moduledef = {
    PyModuleDef_HEAD_INIT,
    "VG.VGTilingMode",
    NULL,
    -1,
    NULL,
};
#endif

static PyObject *
initOpenVG_VGTilingMode(void)
{
    PyObject *m;
    #if PY_VERSION_HEX >= 0x03000000
    m = PyModule_Create(&VGTilingMode_moduledef);
    #else
    m = Py_InitModule3((char *) "VG.VGTilingMode", NULL, NULL);
    #endif
    if (m == NULL) {
        return NULL;
    }
    PyModule_AddIntConstant(m, (char *) "VG_TILE_FILL", VG_TILE_FILL);
    PyModule_AddIntConstant(m, (char *) "VG_TILE_PAD", VG_TILE_PAD);
    PyModule_AddIntConstant(m, (char *) "VG_TILE_REPEAT", VG_TILE_REPEAT);
    PyModule_AddIntConstant(m, (char *) "VG_TILE_REFLECT", VG_TILE_REFLECT);
    return m;
}

/*****************************************************************************/
#if PY_VERSION_HEX >= 0x03000000
static struct PyModuleDef VGMaskOperation_moduledef = {
    PyModuleDef_HEAD_INIT,
    "VG.VGMaskOperation",
    NULL,
    -1,
    NULL,
};
#endif

static PyObject *
initOpenVG_VGMaskOperation(void)
{
    PyObject *m;
    #if PY_VERSION_HEX >= 0x03000000
    m = PyModule_Create(&VGMaskOperation_moduledef);
    #else
    m = Py_InitModule3((char *) "VG.VGMaskOperation", NULL, NULL);
    #endif
    if (m == NULL) {
        return NULL;
    }
    PyModule_AddIntConstant(m, (char *) "VG_CLEAR_MASK", VG_CLEAR_MASK);
    PyModule_AddIntConstant(m, (char *) "VG_FILL_MASK", VG_FILL_MASK);
    PyModule_AddIntConstant(m, (char *) "VG_SET_MASK", VG_SET_MASK);
    PyModule_AddIntConstant(m, (char *) "VG_UNION_MASK", VG_UNION_MASK);
    PyModule_AddIntConstant(m, (char *) "VG_INTERSECT_MASK", VG_INTERSECT_MASK);
    PyModule_AddIntConstant(m, (char *) "VG_SUBTRACT_MASK", VG_SUBTRACT_MASK);
    return m;
}

/*****************************************************************************/
#if PY_VERSION_HEX >= 0x03000000
static struct PyModuleDef VGPaintType_moduledef = {
    PyModuleDef_HEAD_INIT,
    "VG.VGPaintType",
    NULL,
    -1,
    NULL,
};
#endif

static PyObject *
initOpenVG_VGPaintType(void)
{
    PyObject *m;
    #if PY_VERSION_HEX >= 0x03000000
    m = PyModule_Create(&VGPaintType_moduledef);
    #else
    m = Py_InitModule3((char *) "VG.VGPaintType", NULL, NULL);
    #endif
    if (m == NULL) {
        return NULL;
    }
    PyModule_AddIntConstant(m, (char *) "VG_PAINT_TYPE_COLOR", VG_PAINT_TYPE_COLOR);
    PyModule_AddIntConstant(m, (char *) "VG_PAINT_TYPE_LINEAR_GRADIENT", VG_PAINT_TYPE_LINEAR_GRADIENT);
    PyModule_AddIntConstant(m, (char *) "VG_PAINT_TYPE_RADIAL_GRADIENT", VG_PAINT_TYPE_RADIAL_GRADIENT);
    PyModule_AddIntConstant(m, (char *) "VG_PAINT_TYPE_PATTERN", VG_PAINT_TYPE_PATTERN);
    return m;
}


/*****************************************************************************/
#if PY_VERSION_HEX >= 0x03000000
static struct PyModuleDef VGPathCapabilities_moduledef = {
    PyModuleDef_HEAD_INIT,
    "VG.VGPathCapabilities",
    NULL,
    -1,
    NULL,
};
#endif

static PyObject *
initOpenVG_VGPathCapabilities(void)
{
    PyObject *m;
    #if PY_VERSION_HEX >= 0x03000000
    m = PyModule_Create(&VGPathCapabilities_moduledef);
    #else
    m = Py_InitModule3((char *) "VG.VGPathCapabilities", NULL, NULL);
    #endif
    if (m == NULL) {
        return NULL;
    }
    PyModule_AddIntConstant(m, (char *) "VG_PATH_CAPABILITY_APPEND_FROM", VG_PATH_CAPABILITY_APPEND_FROM);
    PyModule_AddIntConstant(m, (char *) "VG_PATH_CAPABILITY_APPEND_TO", VG_PATH_CAPABILITY_APPEND_TO);
    PyModule_AddIntConstant(m, (char *) "VG_PATH_CAPABILITY_MODIFY", VG_PATH_CAPABILITY_MODIFY);
    PyModule_AddIntConstant(m, (char *) "VG_PATH_CAPABILITY_TRANSFORM_FROM", VG_PATH_CAPABILITY_TRANSFORM_FROM);
    PyModule_AddIntConstant(m, (char *) "VG_PATH_CAPABILITY_TRANSFORM_TO", VG_PATH_CAPABILITY_TRANSFORM_TO);
    PyModule_AddIntConstant(m, (char *) "VG_PATH_CAPABILITY_INTERPOLATE_FROM", VG_PATH_CAPABILITY_INTERPOLATE_FROM);
    PyModule_AddIntConstant(m, (char *) "VG_PATH_CAPABILITY_INTERPOLATE_TO", VG_PATH_CAPABILITY_INTERPOLATE_TO);
    PyModule_AddIntConstant(m, (char *) "VG_PATH_CAPABILITY_PATH_LENGTH", VG_PATH_CAPABILITY_PATH_LENGTH);
    PyModule_AddIntConstant(m, (char *) "VG_PATH_CAPABILITY_POINT_ALONG_PATH", VG_PATH_CAPABILITY_POINT_ALONG_PATH);
    PyModule_AddIntConstant(m, (char *) "VG_PATH_CAPABILITY_TANGENT_ALONG_PATH", VG_PATH_CAPABILITY_TANGENT_ALONG_PATH);
    PyModule_AddIntConstant(m, (char *) "VG_PATH_CAPABILITY_PATH_BOUNDS", VG_PATH_CAPABILITY_PATH_BOUNDS);
    PyModule_AddIntConstant(m, (char *) "VG_PATH_CAPABILITY_PATH_TRANSFORMED_BOUNDS", VG_PATH_CAPABILITY_PATH_TRANSFORMED_BOUNDS);
    PyModule_AddIntConstant(m, (char *) "VG_PATH_CAPABILITY_ALL", VG_PATH_CAPABILITY_ALL);
    return m;
}


/*****************************************************************************/
#if PY_VERSION_HEX >= 0x03000000
static struct PyModuleDef VGStringID_moduledef = {
    PyModuleDef_HEAD_INIT,
    "VG.VGStringID",
    NULL,
    -1,
    NULL,
};
#endif

static PyObject *
initOpenVG_VGStringID(void)
{
    PyObject *m;
    #if PY_VERSION_HEX >= 0x03000000
    m = PyModule_Create(&VGStringID_moduledef);
    #else
    m = Py_InitModule3((char *) "VG.VGStringID", NULL, NULL);
    #endif
    if (m == NULL) {
        return NULL;
    }
    PyModule_AddIntConstant(m, (char *) "VG_VENDOR", VG_VENDOR);
    PyModule_AddIntConstant(m, (char *) "VG_RENDERER", VG_RENDERER);
    PyModule_AddIntConstant(m, (char *) "VG_VERSION", VG_VERSION);
    PyModule_AddIntConstant(m, (char *) "VG_EXTENSIONS", VG_EXTENSIONS);
    return m;
}


/*****************************************************************************/
#if PY_VERSION_HEX >= 0x03000000
static struct PyModuleDef VGImageChannel_moduledef = {
    PyModuleDef_HEAD_INIT,
    "VG.VGImageChannel",
    NULL,
    -1,
    NULL,
};
#endif

static PyObject *
initOpenVG_VGImageChannel(void)
{
    PyObject *m;
    #if PY_VERSION_HEX >= 0x03000000
    m = PyModule_Create(&VGImageChannel_moduledef);
    #else
    m = Py_InitModule3((char *) "VG.VGImageChannel", NULL, NULL);
    #endif
    if (m == NULL) {
        return NULL;
    }
    PyModule_AddIntConstant(m, (char *) "VG_RED", VG_RED);
    PyModule_AddIntConstant(m, (char *) "VG_GREEN", VG_GREEN);
    PyModule_AddIntConstant(m, (char *) "VG_BLUE", VG_BLUE);
    PyModule_AddIntConstant(m, (char *) "VG_ALPHA", VG_ALPHA);
    return m;
}


/*****************************************************************************/
#if PY_VERSION_HEX >= 0x03000000
static struct PyModuleDef VGParamType_moduledef = {
    PyModuleDef_HEAD_INIT,
    "VG.VGParamType",
    NULL,
    -1,
    NULL,
};
#endif

static PyObject *
initOpenVG_VGParamType(void)
{
    PyObject *m;
    #if PY_VERSION_HEX >= 0x03000000
    m = PyModule_Create(&VGParamType_moduledef);
    #else
    m = Py_InitModule3((char *) "VG.VGParamType", NULL, NULL);
    #endif
    if (m == NULL) {
        return NULL;
    }
    PyModule_AddIntConstant(m, (char *) "VG_MATRIX_MODE", VG_MATRIX_MODE);
    PyModule_AddIntConstant(m, (char *) "VG_FILL_RULE", VG_FILL_RULE);
    PyModule_AddIntConstant(m, (char *) "VG_IMAGE_QUALITY", VG_IMAGE_QUALITY);
    PyModule_AddIntConstant(m, (char *) "VG_RENDERING_QUALITY", VG_RENDERING_QUALITY);
    PyModule_AddIntConstant(m, (char *) "VG_BLEND_MODE", VG_BLEND_MODE);
    PyModule_AddIntConstant(m, (char *) "VG_IMAGE_MODE", VG_IMAGE_MODE);
    PyModule_AddIntConstant(m, (char *) "VG_SCISSOR_RECTS", VG_SCISSOR_RECTS);
    PyModule_AddIntConstant(m, (char *) "VG_STROKE_LINE_WIDTH", VG_STROKE_LINE_WIDTH);
    PyModule_AddIntConstant(m, (char *) "VG_STROKE_CAP_STYLE", VG_STROKE_CAP_STYLE);
    PyModule_AddIntConstant(m, (char *) "VG_STROKE_JOIN_STYLE", VG_STROKE_JOIN_STYLE);
    PyModule_AddIntConstant(m, (char *) "VG_STROKE_MITER_LIMIT", VG_STROKE_MITER_LIMIT);
    PyModule_AddIntConstant(m, (char *) "VG_STROKE_DASH_PATTERN", VG_STROKE_DASH_PATTERN);
    PyModule_AddIntConstant(m, (char *) "VG_STROKE_DASH_PHASE", VG_STROKE_DASH_PHASE);
    PyModule_AddIntConstant(m, (char *) "VG_STROKE_DASH_PHASE_RESET", VG_STROKE_DASH_PHASE_RESET);
    PyModule_AddIntConstant(m, (char *) "VG_TILE_FILL_COLOR", VG_TILE_FILL_COLOR);
    PyModule_AddIntConstant(m, (char *) "VG_CLEAR_COLOR", VG_CLEAR_COLOR);
    PyModule_AddIntConstant(m, (char *) "VG_MASKING", VG_MASKING);
    PyModule_AddIntConstant(m, (char *) "VG_SCISSORING", VG_SCISSORING);
    PyModule_AddIntConstant(m, (char *) "VG_PIXEL_LAYOUT", VG_PIXEL_LAYOUT);
    PyModule_AddIntConstant(m, (char *) "VG_SCREEN_LAYOUT", VG_SCREEN_LAYOUT);
    PyModule_AddIntConstant(m, (char *) "VG_FILTER_FORMAT_LINEAR", VG_FILTER_FORMAT_LINEAR);
    PyModule_AddIntConstant(m, (char *) "VG_FILTER_FORMAT_PREMULTIPLIED", VG_FILTER_FORMAT_PREMULTIPLIED);
    PyModule_AddIntConstant(m, (char *) "VG_FILTER_CHANNEL_MASK", VG_FILTER_CHANNEL_MASK);
    PyModule_AddIntConstant(m, (char *) "VG_MAX_SCISSOR_RECTS", VG_MAX_SCISSOR_RECTS);
    PyModule_AddIntConstant(m, (char *) "VG_MAX_DASH_COUNT", VG_MAX_DASH_COUNT);
    PyModule_AddIntConstant(m, (char *) "VG_MAX_KERNEL_SIZE", VG_MAX_KERNEL_SIZE);
    PyModule_AddIntConstant(m, (char *) "VG_MAX_SEPARABLE_KERNEL_SIZE", VG_MAX_SEPARABLE_KERNEL_SIZE);
    PyModule_AddIntConstant(m, (char *) "VG_MAX_COLOR_RAMP_STOPS", VG_MAX_COLOR_RAMP_STOPS);
    PyModule_AddIntConstant(m, (char *) "VG_MAX_IMAGE_WIDTH", VG_MAX_IMAGE_WIDTH);
    PyModule_AddIntConstant(m, (char *) "VG_MAX_IMAGE_HEIGHT", VG_MAX_IMAGE_HEIGHT);
    PyModule_AddIntConstant(m, (char *) "VG_MAX_IMAGE_PIXELS", VG_MAX_IMAGE_PIXELS);
    PyModule_AddIntConstant(m, (char *) "VG_MAX_IMAGE_BYTES", VG_MAX_IMAGE_BYTES);
    PyModule_AddIntConstant(m, (char *) "VG_MAX_FLOAT", VG_MAX_FLOAT);
    PyModule_AddIntConstant(m, (char *) "VG_MAX_GAUSSIAN_STD_DEVIATION", VG_MAX_GAUSSIAN_STD_DEVIATION);
    return m;
}


/*****************************************************************************/
#if PY_VERSION_HEX >= 0x03000000
static struct PyModuleDef VGMatrixMode_moduledef = {
    PyModuleDef_HEAD_INIT,
    "VG.VGMatrixMode",
    NULL,
    -1,
    NULL,
};
#endif

static PyObject *
initOpenVG_VGMatrixMode(void)
{
    PyObject *m;
    #if PY_VERSION_HEX >= 0x03000000
    m = PyModule_Create(&VGMatrixMode_moduledef);
    #else
    m = Py_InitModule3((char *) "VG.VGMatrixMode", NULL, NULL);
    #endif
    if (m == NULL) {
        return NULL;
    }
    PyModule_AddIntConstant(m, (char *) "VG_MATRIX_PATH_USER_TO_SURFACE", VG_MATRIX_PATH_USER_TO_SURFACE);
    PyModule_AddIntConstant(m, (char *) "VG_MATRIX_IMAGE_USER_TO_SURFACE", VG_MATRIX_IMAGE_USER_TO_SURFACE);
    PyModule_AddIntConstant(m, (char *) "VG_MATRIX_FILL_PAINT_TO_USER", VG_MATRIX_FILL_PAINT_TO_USER);
    PyModule_AddIntConstant(m, (char *) "VG_MATRIX_STROKE_PAINT_TO_USER", VG_MATRIX_STROKE_PAINT_TO_USER);
    return m;
}


/*****************************************************************************/
#if PY_VERSION_HEX >= 0x03000000
static struct PyModuleDef VGImageQuality_moduledef = {
    PyModuleDef_HEAD_INIT,
    "VG.VGImageQuality",
    NULL,
    -1,
    NULL,
};
#endif

static PyObject *
initOpenVG_VGImageQuality(void)
{
    PyObject *m;
    #if PY_VERSION_HEX >= 0x03000000
    m = PyModule_Create(&VGImageQuality_moduledef);
    #else
    m = Py_InitModule3((char *) "VG.VGImageQuality", NULL, NULL);
    #endif
    if (m == NULL) {
        return NULL;
    }
    PyModule_AddIntConstant(m, (char *) "VG_IMAGE_QUALITY_NONANTIALIASED", VG_IMAGE_QUALITY_NONANTIALIASED);
    PyModule_AddIntConstant(m, (char *) "VG_IMAGE_QUALITY_FASTER", VG_IMAGE_QUALITY_FASTER);
    PyModule_AddIntConstant(m, (char *) "VG_IMAGE_QUALITY_BETTER", VG_IMAGE_QUALITY_BETTER);
    return m;
}


/*****************************************************************************/
#if PY_VERSION_HEX >= 0x03000000
static struct PyModuleDef VGPathAbsRel_moduledef = {
    PyModuleDef_HEAD_INIT,
    "VG.VGPathAbsRel",
    NULL,
    -1,
    NULL,
};
#endif

static PyObject *
initOpenVG_VGPathAbsRel(void)
{
    PyObject *m;
    #if PY_VERSION_HEX >= 0x03000000
    m = PyModule_Create(&VGPathAbsRel_moduledef);
    #else
    m = Py_InitModule3((char *) "VG.VGPathAbsRel", NULL, NULL);
    #endif
    if (m == NULL) {
        return NULL;
    }
    PyModule_AddIntConstant(m, (char *) "VG_ABSOLUTE", VG_ABSOLUTE);
    PyModule_AddIntConstant(m, (char *) "VG_RELATIVE", VG_RELATIVE);
    return m;
}


/*****************************************************************************/
#if PY_VERSION_HEX >= 0x03000000
static struct PyModuleDef VGFillRule_moduledef = {
    PyModuleDef_HEAD_INIT,
    "VG.VGFillRule",
    NULL,
    -1,
    NULL,
};
#endif

static PyObject *
initOpenVG_VGFillRule(void)
{
    PyObject *m;
    #if PY_VERSION_HEX >= 0x03000000
    m = PyModule_Create(&VGFillRule_moduledef);
    #else
    m = Py_InitModule3((char *) "VG.VGFillRule", NULL, NULL);
    #endif
    if (m == NULL) {
        return NULL;
    }
    PyModule_AddIntConstant(m, (char *) "VG_EVEN_ODD", VG_EVEN_ODD);
    PyModule_AddIntConstant(m, (char *) "VG_NON_ZERO", VG_NON_ZERO);
    return m;
}


/*****************************************************************************/
#if PY_VERSION_HEX >= 0x03000000
static struct PyModuleDef VGPaintParamType_moduledef = {
    PyModuleDef_HEAD_INIT,
    "VG.VGPaintParamType",
    NULL,
    -1,
    NULL,
};
#endif

static PyObject *
initOpenVG_VGPaintParamType(void)
{
    PyObject *m;
    #if PY_VERSION_HEX >= 0x03000000
    m = PyModule_Create(&VGPaintParamType_moduledef);
    #else
    m = Py_InitModule3((char *) "VG.VGPaintParamType", NULL, NULL);
    #endif
    if (m == NULL) {
        return NULL;
    }
    PyModule_AddIntConstant(m, (char *) "VG_PAINT_TYPE", VG_PAINT_TYPE);
    PyModule_AddIntConstant(m, (char *) "VG_PAINT_COLOR", VG_PAINT_COLOR);
    PyModule_AddIntConstant(m, (char *) "VG_PAINT_COLOR_RAMP_SPREAD_MODE", VG_PAINT_COLOR_RAMP_SPREAD_MODE);
    PyModule_AddIntConstant(m, (char *) "VG_PAINT_COLOR_RAMP_PREMULTIPLIED", VG_PAINT_COLOR_RAMP_PREMULTIPLIED);
    PyModule_AddIntConstant(m, (char *) "VG_PAINT_COLOR_RAMP_STOPS", VG_PAINT_COLOR_RAMP_STOPS);
    PyModule_AddIntConstant(m, (char *) "VG_PAINT_LINEAR_GRADIENT", VG_PAINT_LINEAR_GRADIENT);
    PyModule_AddIntConstant(m, (char *) "VG_PAINT_RADIAL_GRADIENT", VG_PAINT_RADIAL_GRADIENT);
    PyModule_AddIntConstant(m, (char *) "VG_PAINT_PATTERN_TILING_MODE", VG_PAINT_PATTERN_TILING_MODE);
    return m;
}


/*****************************************************************************/
#if PY_VERSION_HEX >= 0x03000000
static struct PyModuleDef VGImageFormat_moduledef = {
    PyModuleDef_HEAD_INIT,
    "VG.VGImageFormat",
    NULL,
    -1,
    NULL,
};
#endif

static PyObject *
initOpenVG_VGImageFormat(void)
{
    PyObject *m;
    #if PY_VERSION_HEX >= 0x03000000
    m = PyModule_Create(&VGImageFormat_moduledef);
    #else
    m = Py_InitModule3((char *) "VG.VGImageFormat", NULL, NULL);
    #endif
    if (m == NULL) {
        return NULL;
    }
    PyModule_AddIntConstant(m, (char *) "VG_sRGBX_8888", VG_sRGBX_8888);
    PyModule_AddIntConstant(m, (char *) "VG_sRGBA_8888", VG_sRGBA_8888);
    PyModule_AddIntConstant(m, (char *) "VG_sRGBA_8888_PRE", VG_sRGBA_8888_PRE);
    PyModule_AddIntConstant(m, (char *) "VG_sRGB_565", VG_sRGB_565);
    PyModule_AddIntConstant(m, (char *) "VG_sRGBA_5551", VG_sRGBA_5551);
    PyModule_AddIntConstant(m, (char *) "VG_sRGBA_4444", VG_sRGBA_4444);
    PyModule_AddIntConstant(m, (char *) "VG_sL_8", VG_sL_8);
    PyModule_AddIntConstant(m, (char *) "VG_lRGBX_8888", VG_lRGBX_8888);
    PyModule_AddIntConstant(m, (char *) "VG_lRGBA_8888", VG_lRGBA_8888);
    PyModule_AddIntConstant(m, (char *) "VG_lRGBA_8888_PRE", VG_lRGBA_8888_PRE);
    PyModule_AddIntConstant(m, (char *) "VG_lL_8", VG_lL_8);
    PyModule_AddIntConstant(m, (char *) "VG_A_8", VG_A_8);
    PyModule_AddIntConstant(m, (char *) "VG_BW_1", VG_BW_1);
    PyModule_AddIntConstant(m, (char *) "VG_sXRGB_8888", VG_sXRGB_8888);
    PyModule_AddIntConstant(m, (char *) "VG_sARGB_8888", VG_sARGB_8888);
    PyModule_AddIntConstant(m, (char *) "VG_sARGB_8888_PRE", VG_sARGB_8888_PRE);
    PyModule_AddIntConstant(m, (char *) "VG_sARGB_1555", VG_sARGB_1555);
    PyModule_AddIntConstant(m, (char *) "VG_sARGB_4444", VG_sARGB_4444);
    PyModule_AddIntConstant(m, (char *) "VG_lXRGB_8888", VG_lXRGB_8888);
    PyModule_AddIntConstant(m, (char *) "VG_lARGB_8888", VG_lARGB_8888);
    PyModule_AddIntConstant(m, (char *) "VG_lARGB_8888_PRE", VG_lARGB_8888_PRE);
    PyModule_AddIntConstant(m, (char *) "VG_sBGRX_8888", VG_sBGRX_8888);
    PyModule_AddIntConstant(m, (char *) "VG_sBGRA_8888", VG_sBGRA_8888);
    PyModule_AddIntConstant(m, (char *) "VG_sBGRA_8888_PRE", VG_sBGRA_8888_PRE);
    PyModule_AddIntConstant(m, (char *) "VG_sBGR_565", VG_sBGR_565);
    PyModule_AddIntConstant(m, (char *) "VG_sBGRA_5551", VG_sBGRA_5551);
    PyModule_AddIntConstant(m, (char *) "VG_sBGRA_4444", VG_sBGRA_4444);
    PyModule_AddIntConstant(m, (char *) "VG_lBGRX_8888", VG_lBGRX_8888);
    PyModule_AddIntConstant(m, (char *) "VG_lBGRA_8888", VG_lBGRA_8888);
    PyModule_AddIntConstant(m, (char *) "VG_lBGRA_8888_PRE", VG_lBGRA_8888_PRE);
    PyModule_AddIntConstant(m, (char *) "VG_sXBGR_8888", VG_sXBGR_8888);
    PyModule_AddIntConstant(m, (char *) "VG_sABGR_8888", VG_sABGR_8888);
    PyModule_AddIntConstant(m, (char *) "VG_sABGR_8888_PRE", VG_sABGR_8888_PRE);
    PyModule_AddIntConstant(m, (char *) "VG_sABGR_1555", VG_sABGR_1555);
    PyModule_AddIntConstant(m, (char *) "VG_sABGR_4444", VG_sABGR_4444);
    PyModule_AddIntConstant(m, (char *) "VG_lXBGR_8888", VG_lXBGR_8888);
    PyModule_AddIntConstant(m, (char *) "VG_lABGR_8888", VG_lABGR_8888);
    PyModule_AddIntConstant(m, (char *) "VG_lABGR_8888_PRE", VG_lABGR_8888_PRE);
    return m;
}


/*****************************************************************************/
#if PY_VERSION_HEX >= 0x03000000
static struct PyModuleDef VGImageParamType_moduledef = {
    PyModuleDef_HEAD_INIT,
    "VG.VGImageParamType",
    NULL,
    -1,
    NULL,
};
#endif

static PyObject *
initOpenVG_VGImageParamType(void)
{
    PyObject *m;
    #if PY_VERSION_HEX >= 0x03000000
    m = PyModule_Create(&VGImageParamType_moduledef);
    #else
    m = Py_InitModule3((char *) "VG.VGImageParamType", NULL, NULL);
    #endif
    if (m == NULL) {
        return NULL;
    }
    PyModule_AddIntConstant(m, (char *) "VG_IMAGE_FORMAT", VG_IMAGE_FORMAT);
    PyModule_AddIntConstant(m, (char *) "VG_IMAGE_WIDTH", VG_IMAGE_WIDTH);
    PyModule_AddIntConstant(m, (char *) "VG_IMAGE_HEIGHT", VG_IMAGE_HEIGHT);
    return m;
}


/*****************************************************************************/
#if PY_VERSION_HEX >= 0x03000000
static struct PyModuleDef VGCapStyle_moduledef = {
    PyModuleDef_HEAD_INIT,
    "VG.VGCapStyle",
    NULL,
    -1,
    NULL,
};
#endif

static PyObject *
initOpenVG_VGCapStyle(void)
{
    PyObject *m;
    #if PY_VERSION_HEX >= 0x03000000
    m = PyModule_Create(&VGCapStyle_moduledef);
    #else
    m = Py_InitModule3((char *) "VG.VGCapStyle", NULL, NULL);
    #endif
    if (m == NULL) {
        return NULL;
    }
    PyModule_AddIntConstant(m, (char *) "VG_CAP_BUTT", VG_CAP_BUTT);
    PyModule_AddIntConstant(m, (char *) "VG_CAP_ROUND", VG_CAP_ROUND);
    PyModule_AddIntConstant(m, (char *) "VG_CAP_SQUARE", VG_CAP_SQUARE);
    return m;
}


/*****************************************************************************/
#if PY_VERSION_HEX >= 0x03000000
static struct PyModuleDef VGPathCommand_moduledef = {
    PyModuleDef_HEAD_INIT,
    "VG.VGPathCommand",
    NULL,
    -1,
    NULL,
};
#endif

static PyObject *
initOpenVG_VGPathCommand(void)
{
    PyObject *m;
    #if PY_VERSION_HEX >= 0x03000000
    m = PyModule_Create(&VGPathCommand_moduledef);
    #else
    m = Py_InitModule3((char *) "VG.VGPathCommand", NULL, NULL);
    #endif
    if (m == NULL) {
        return NULL;
    }
    PyModule_AddIntConstant(m, (char *) "VG_MOVE_TO_ABS", VG_MOVE_TO_ABS);
    PyModule_AddIntConstant(m, (char *) "VG_MOVE_TO_REL", VG_MOVE_TO_REL);
    PyModule_AddIntConstant(m, (char *) "VG_LINE_TO_ABS", VG_LINE_TO_ABS);
    PyModule_AddIntConstant(m, (char *) "VG_LINE_TO_REL", VG_LINE_TO_REL);
    PyModule_AddIntConstant(m, (char *) "VG_HLINE_TO_ABS", VG_HLINE_TO_ABS);
    PyModule_AddIntConstant(m, (char *) "VG_HLINE_TO_REL", VG_HLINE_TO_REL);
    PyModule_AddIntConstant(m, (char *) "VG_VLINE_TO_ABS", VG_VLINE_TO_ABS);
    PyModule_AddIntConstant(m, (char *) "VG_VLINE_TO_REL", VG_VLINE_TO_REL);
    PyModule_AddIntConstant(m, (char *) "VG_QUAD_TO_ABS", VG_QUAD_TO_ABS);
    PyModule_AddIntConstant(m, (char *) "VG_QUAD_TO_REL", VG_QUAD_TO_REL);
    PyModule_AddIntConstant(m, (char *) "VG_CUBIC_TO_ABS", VG_CUBIC_TO_ABS);
    PyModule_AddIntConstant(m, (char *) "VG_CUBIC_TO_REL", VG_CUBIC_TO_REL);
    PyModule_AddIntConstant(m, (char *) "VG_SQUAD_TO_ABS", VG_SQUAD_TO_ABS);
    PyModule_AddIntConstant(m, (char *) "VG_SQUAD_TO_REL", VG_SQUAD_TO_REL);
    PyModule_AddIntConstant(m, (char *) "VG_SCUBIC_TO_ABS", VG_SCUBIC_TO_ABS);
    PyModule_AddIntConstant(m, (char *) "VG_SCUBIC_TO_REL", VG_SCUBIC_TO_REL);
    PyModule_AddIntConstant(m, (char *) "VG_SCCWARC_TO_ABS", VG_SCCWARC_TO_ABS);
    PyModule_AddIntConstant(m, (char *) "VG_SCCWARC_TO_REL", VG_SCCWARC_TO_REL);
    PyModule_AddIntConstant(m, (char *) "VG_SCWARC_TO_ABS", VG_SCWARC_TO_ABS);
    PyModule_AddIntConstant(m, (char *) "VG_SCWARC_TO_REL", VG_SCWARC_TO_REL);
    PyModule_AddIntConstant(m, (char *) "VG_LCCWARC_TO_ABS", VG_LCCWARC_TO_ABS);
    PyModule_AddIntConstant(m, (char *) "VG_LCCWARC_TO_REL", VG_LCCWARC_TO_REL);
    PyModule_AddIntConstant(m, (char *) "VG_LCWARC_TO_ABS", VG_LCWARC_TO_ABS);
    PyModule_AddIntConstant(m, (char *) "VG_LCWARC_TO_REL", VG_LCWARC_TO_REL);
    return m;
}


/*****************************************************************************/
#if PY_VERSION_HEX >= 0x03000000
static struct PyModuleDef VGHardwareQueryType_moduledef = {
    PyModuleDef_HEAD_INIT,
    "VG.VGHardwareQueryType",
    NULL,
    -1,
    NULL,
};
#endif

static PyObject *
initOpenVG_VGHardwareQueryType(void)
{
    PyObject *m;
    #if PY_VERSION_HEX >= 0x03000000
    m = PyModule_Create(&VGHardwareQueryType_moduledef);
    #else
    m = Py_InitModule3((char *) "VG.VGHardwareQueryType", NULL, NULL);
    #endif
    if (m == NULL) {
        return NULL;
    }
    PyModule_AddIntConstant(m, (char *) "VG_IMAGE_FORMAT_QUERY", VG_IMAGE_FORMAT_QUERY);
    PyModule_AddIntConstant(m, (char *) "VG_PATH_DATATYPE_QUERY", VG_PATH_DATATYPE_QUERY);
    return m;
}


/*****************************************************************************/
#if PY_VERSION_HEX >= 0x03000000
static struct PyModuleDef VGErrorCode_moduledef = {
    PyModuleDef_HEAD_INIT,
    "VG.VGErrorCode",
    NULL,
    -1,
    NULL,
};
#endif

static PyObject *
initOpenVG_VGErrorCode(void)
{
    PyObject *m;
    #if PY_VERSION_HEX >= 0x03000000
    m = PyModule_Create(&VGErrorCode_moduledef);
    #else
    m = Py_InitModule3((char *) "VG.VGErrorCode", NULL, NULL);
    #endif
    if (m == NULL) {
        return NULL;
    }
    PyModule_AddIntConstant(m, (char *) "VG_NO_ERROR", VG_NO_ERROR);
    PyModule_AddIntConstant(m, (char *) "VG_BAD_HANDLE_ERROR", VG_BAD_HANDLE_ERROR);
    PyModule_AddIntConstant(m, (char *) "VG_ILLEGAL_ARGUMENT_ERROR", VG_ILLEGAL_ARGUMENT_ERROR);
    PyModule_AddIntConstant(m, (char *) "VG_OUT_OF_MEMORY_ERROR", VG_OUT_OF_MEMORY_ERROR);
    PyModule_AddIntConstant(m, (char *) "VG_PATH_CAPABILITY_ERROR", VG_PATH_CAPABILITY_ERROR);
    PyModule_AddIntConstant(m, (char *) "VG_UNSUPPORTED_IMAGE_FORMAT_ERROR", VG_UNSUPPORTED_IMAGE_FORMAT_ERROR);
    PyModule_AddIntConstant(m, (char *) "VG_UNSUPPORTED_PATH_FORMAT_ERROR", VG_UNSUPPORTED_PATH_FORMAT_ERROR);
    PyModule_AddIntConstant(m, (char *) "VG_IMAGE_IN_USE_ERROR", VG_IMAGE_IN_USE_ERROR);
    PyModule_AddIntConstant(m, (char *) "VG_NO_CONTEXT_ERROR", VG_NO_CONTEXT_ERROR);
    return m;
}


/*****************************************************************************/
#if PY_VERSION_HEX >= 0x03000000
static struct PyModuleDef VGPixelLayout_moduledef = {
    PyModuleDef_HEAD_INIT,
    "VG.VGPixelLayout",
    NULL,
    -1,
    NULL,
};
#endif

static PyObject *
initOpenVG_VGPixelLayout(void)
{
    PyObject *m;
    #if PY_VERSION_HEX >= 0x03000000
    m = PyModule_Create(&VGPixelLayout_moduledef);
    #else
    m = Py_InitModule3((char *) "VG.VGPixelLayout", NULL, NULL);
    #endif
    if (m == NULL) {
        return NULL;
    }
    PyModule_AddIntConstant(m, (char *) "VG_PIXEL_LAYOUT_UNKNOWN", VG_PIXEL_LAYOUT_UNKNOWN);
    PyModule_AddIntConstant(m, (char *) "VG_PIXEL_LAYOUT_RGB_VERTICAL", VG_PIXEL_LAYOUT_RGB_VERTICAL);
    PyModule_AddIntConstant(m, (char *) "VG_PIXEL_LAYOUT_BGR_VERTICAL", VG_PIXEL_LAYOUT_BGR_VERTICAL);
    PyModule_AddIntConstant(m, (char *) "VG_PIXEL_LAYOUT_RGB_HORIZONTAL", VG_PIXEL_LAYOUT_RGB_HORIZONTAL);
    PyModule_AddIntConstant(m, (char *) "VG_PIXEL_LAYOUT_BGR_HORIZONTAL", VG_PIXEL_LAYOUT_BGR_HORIZONTAL);
    return m;
}


/*****************************************************************************/
#if PY_VERSION_HEX >= 0x03000000
static struct PyModuleDef VGPathDatatype_moduledef = {
    PyModuleDef_HEAD_INIT,
    "VG.VGPathDatatype",
    NULL,
    -1,
    NULL,
};
#endif

static PyObject *
initOpenVG_VGPathDatatype(void)
{
    PyObject *m;
    #if PY_VERSION_HEX >= 0x03000000
    m = PyModule_Create(&VGPathDatatype_moduledef);
    #else
    m = Py_InitModule3((char *) "VG.VGPathDatatype", NULL, NULL);
    #endif
    if (m == NULL) {
        return NULL;
    }
    PyModule_AddIntConstant(m, (char *) "VG_PATH_DATATYPE_S_8", VG_PATH_DATATYPE_S_8);
    PyModule_AddIntConstant(m, (char *) "VG_PATH_DATATYPE_S_16", VG_PATH_DATATYPE_S_16);
    PyModule_AddIntConstant(m, (char *) "VG_PATH_DATATYPE_S_32", VG_PATH_DATATYPE_S_32);
    PyModule_AddIntConstant(m, (char *) "VG_PATH_DATATYPE_F", VG_PATH_DATATYPE_F);
    return m;
}


/*****************************************************************************/
#if PY_VERSION_HEX >= 0x03000000
static struct PyModuleDef VGPathSegment_moduledef = {
    PyModuleDef_HEAD_INIT,
    "VG.VGPathSegment",
    NULL,
    -1,
    NULL,
};
#endif

static PyObject *
initOpenVG_VGPathSegment(void)
{
    PyObject *m;
    #if PY_VERSION_HEX >= 0x03000000
    m = PyModule_Create(&VGPathSegment_moduledef);
    #else
    m = Py_InitModule3((char *) "VG.VGPathSegment", NULL, NULL);
    #endif
    if (m == NULL) {
        return NULL;
    }
    PyModule_AddIntConstant(m, (char *) "VG_CLOSE_PATH", VG_CLOSE_PATH);
    PyModule_AddIntConstant(m, (char *) "VG_MOVE_TO", VG_MOVE_TO);
    PyModule_AddIntConstant(m, (char *) "VG_LINE_TO", VG_LINE_TO);
    PyModule_AddIntConstant(m, (char *) "VG_HLINE_TO", VG_HLINE_TO);
    PyModule_AddIntConstant(m, (char *) "VG_VLINE_TO", VG_VLINE_TO);
    PyModule_AddIntConstant(m, (char *) "VG_QUAD_TO", VG_QUAD_TO);
    PyModule_AddIntConstant(m, (char *) "VG_CUBIC_TO", VG_CUBIC_TO);
    PyModule_AddIntConstant(m, (char *) "VG_SQUAD_TO", VG_SQUAD_TO);
    PyModule_AddIntConstant(m, (char *) "VG_SCUBIC_TO", VG_SCUBIC_TO);
    PyModule_AddIntConstant(m, (char *) "VG_SCCWARC_TO", VG_SCCWARC_TO);
    PyModule_AddIntConstant(m, (char *) "VG_SCWARC_TO", VG_SCWARC_TO);
    PyModule_AddIntConstant(m, (char *) "VG_LCCWARC_TO", VG_LCCWARC_TO);
    PyModule_AddIntConstant(m, (char *) "VG_LCWARC_TO", VG_LCWARC_TO);
    return m;
}


/*****************************************************************************/
#if PY_VERSION_HEX >= 0x03000000
static struct PyModuleDef VGPathParamType_moduledef = {
    PyModuleDef_HEAD_INIT,
    "VG.VGPathParamType",
    NULL,
    -1,
    NULL,
};
#endif

static PyObject *
initOpenVG_VGPathParamType(void)
{
    PyObject *m;
    #if PY_VERSION_HEX >= 0x03000000
    m = PyModule_Create(&VGPathParamType_moduledef);
    #else
    m = Py_InitModule3((char *) "VG.VGPathParamType", NULL, NULL);
    #endif
    if (m == NULL) {
        return NULL;
    }
    PyModule_AddIntConstant(m, (char *) "VG_PATH_FORMAT", VG_PATH_FORMAT);
    PyModule_AddIntConstant(m, (char *) "VG_PATH_DATATYPE", VG_PATH_DATATYPE);
    PyModule_AddIntConstant(m, (char *) "VG_PATH_SCALE", VG_PATH_SCALE);
    PyModule_AddIntConstant(m, (char *) "VG_PATH_BIAS", VG_PATH_BIAS);
    PyModule_AddIntConstant(m, (char *) "VG_PATH_NUM_SEGMENTS", VG_PATH_NUM_SEGMENTS);
    PyModule_AddIntConstant(m, (char *) "VG_PATH_NUM_COORDS", VG_PATH_NUM_COORDS);
    return m;
}


/*****************************************************************************/
#if PY_VERSION_HEX >= 0x03000000
static struct PyModuleDef VGColorRampSpreadMode_moduledef = {
    PyModuleDef_HEAD_INIT,
    "VG.VGColorRampSpreadMode",
    NULL,
    -1,
    NULL,
};
#endif

static PyObject *
initOpenVG_VGColorRampSpreadMode(void)
{
    PyObject *m;
    #if PY_VERSION_HEX >= 0x03000000
    m = PyModule_Create(&VGColorRampSpreadMode_moduledef);
    #else
    m = Py_InitModule3((char *) "VG.VGColorRampSpreadMode", NULL, NULL);
    #endif
    if (m == NULL) {
        return NULL;
    }
    PyModule_AddIntConstant(m, (char *) "VG_COLOR_RAMP_SPREAD_PAD", VG_COLOR_RAMP_SPREAD_PAD);
    PyModule_AddIntConstant(m, (char *) "VG_COLOR_RAMP_SPREAD_REPEAT", VG_COLOR_RAMP_SPREAD_REPEAT);
    PyModule_AddIntConstant(m, (char *) "VG_COLOR_RAMP_SPREAD_REFLECT", VG_COLOR_RAMP_SPREAD_REFLECT);
    return m;
}


/*****************************************************************************/
#if PY_VERSION_HEX >= 0x03000000
static struct PyModuleDef VGPaintMode_moduledef = {
    PyModuleDef_HEAD_INIT,
    "VG.VGPaintMode",
    NULL,
    -1,
    NULL,
};
#endif

static PyObject *
initOpenVG_VGPaintMode(void)
{
    PyObject *m;
    #if PY_VERSION_HEX >= 0x03000000
    m = PyModule_Create(&VGPaintMode_moduledef);
    #else
    m = Py_InitModule3((char *) "VG.VGPaintMode", NULL, NULL);
    #endif
    if (m == NULL) {
        return NULL;
    }
    PyModule_AddIntConstant(m, (char *) "VG_STROKE_PATH", VG_STROKE_PATH);
    PyModule_AddIntConstant(m, (char *) "VG_FILL_PATH", VG_FILL_PATH);
    return m;
}


/*****************************************************************************/
#if PY_VERSION_HEX >= 0x03000000
static struct PyModuleDef VGHardwareQueryResult_moduledef = {
    PyModuleDef_HEAD_INIT,
    "VG.VGHardwareQueryResult",
    NULL,
    -1,
    NULL,
};
#endif

static PyObject *
initOpenVG_VGHardwareQueryResult(void)
{
    PyObject *m;
    #if PY_VERSION_HEX >= 0x03000000
    m = PyModule_Create(&VGHardwareQueryResult_moduledef);
    #else
    m = Py_InitModule3((char *) "VG.VGHardwareQueryResult", NULL, NULL);
    #endif
    if (m == NULL) {
        return NULL;
    }
    PyModule_AddIntConstant(m, (char *) "VG_HARDWARE_ACCELERATED", VG_HARDWARE_ACCELERATED);
    PyModule_AddIntConstant(m, (char *) "VG_HARDWARE_UNACCELERATED", VG_HARDWARE_UNACCELERATED);
    return m;
}


/*****************************************************************************/
#if PY_VERSION_HEX >= 0x03000000
static struct PyModuleDef VGJoinStyle_moduledef = {
    PyModuleDef_HEAD_INIT,
    "VG.VGJoinStyle",
    NULL,
    -1,
    NULL,
};
#endif

static PyObject *
initOpenVG_VGJoinStyle(void)
{
    PyObject *m;
    #if PY_VERSION_HEX >= 0x03000000
    m = PyModule_Create(&VGJoinStyle_moduledef);
    #else
    m = Py_InitModule3((char *) "VG.VGJoinStyle", NULL, NULL);
    #endif
    if (m == NULL) {
        return NULL;
    }
    PyModule_AddIntConstant(m, (char *) "VG_JOIN_MITER", VG_JOIN_MITER);
    PyModule_AddIntConstant(m, (char *) "VG_JOIN_ROUND", VG_JOIN_ROUND);
    PyModule_AddIntConstant(m, (char *) "VG_JOIN_BEVEL", VG_JOIN_BEVEL);
    return m;
}


/*****************************************************************************/
#if PY_VERSION_HEX >= 0x03000000
static struct PyModuleDef VGImageMode_moduledef = {
    PyModuleDef_HEAD_INIT,
    "VG.VGImageMode",
    NULL,
    -1,
    NULL,
};
#endif

static PyObject *
initOpenVG_VGImageMode(void)
{
    PyObject *m;
    #if PY_VERSION_HEX >= 0x03000000
    m = PyModule_Create(&VGImageMode_moduledef);
    #else
    m = Py_InitModule3((char *) "VG.VGImageMode", NULL, NULL);
    #endif
    if (m == NULL) {
        return NULL;
    }
    PyModule_AddIntConstant(m, (char *) "VG_DRAW_IMAGE_NORMAL", VG_DRAW_IMAGE_NORMAL);
    PyModule_AddIntConstant(m, (char *) "VG_DRAW_IMAGE_MULTIPLY", VG_DRAW_IMAGE_MULTIPLY);
    PyModule_AddIntConstant(m, (char *) "VG_DRAW_IMAGE_STENCIL", VG_DRAW_IMAGE_STENCIL);
    return m;
}


/*****************************************************************************/
#if PY_VERSION_HEX >= 0x03000000
static struct PyModuleDef VGBlendMode_moduledef = {
    PyModuleDef_HEAD_INIT,
    "VG.VGBlendMode",
    NULL,
    -1,
    NULL,
};
#endif

static PyObject *
initOpenVG_VGBlendMode(void)
{
    PyObject *m;
    #if PY_VERSION_HEX >= 0x03000000
    m = PyModule_Create(&VGBlendMode_moduledef);
    #else
    m = Py_InitModule3((char *) "VG.VGBlendMode", NULL, NULL);
    #endif
    if (m == NULL) {
        return NULL;
    }
    PyModule_AddIntConstant(m, (char *) "VG_BLEND_SRC", VG_BLEND_SRC);
    PyModule_AddIntConstant(m, (char *) "VG_BLEND_SRC_OVER", VG_BLEND_SRC_OVER);
    PyModule_AddIntConstant(m, (char *) "VG_BLEND_DST_OVER", VG_BLEND_DST_OVER);
    PyModule_AddIntConstant(m, (char *) "VG_BLEND_SRC_IN", VG_BLEND_SRC_IN);
    PyModule_AddIntConstant(m, (char *) "VG_BLEND_DST_IN", VG_BLEND_DST_IN);
    PyModule_AddIntConstant(m, (char *) "VG_BLEND_MULTIPLY", VG_BLEND_MULTIPLY);
    PyModule_AddIntConstant(m, (char *) "VG_BLEND_SCREEN", VG_BLEND_SCREEN);
    PyModule_AddIntConstant(m, (char *) "VG_BLEND_DARKEN", VG_BLEND_DARKEN);
    PyModule_AddIntConstant(m, (char *) "VG_BLEND_LIGHTEN", VG_BLEND_LIGHTEN);
    PyModule_AddIntConstant(m, (char *) "VG_BLEND_ADDITIVE", VG_BLEND_ADDITIVE);
    PyModule_AddIntConstant(m, (char *) "VG_BLEND_SRC_OUT_SH", VG_BLEND_SRC_OUT_SH);
    PyModule_AddIntConstant(m, (char *) "VG_BLEND_DST_OUT_SH", VG_BLEND_DST_OUT_SH);
    PyModule_AddIntConstant(m, (char *) "VG_BLEND_SRC_ATOP_SH", VG_BLEND_SRC_ATOP_SH);
    PyModule_AddIntConstant(m, (char *) "VG_BLEND_DST_ATOP_SH", VG_BLEND_DST_ATOP_SH);
    return m;
}


/* --- module functions --- */

PyObject *
OpenVG_vgHardwareQuery(PyObject * UNUSED(dummy), PyObject *args, PyObject *kwargs)
{
    PyObject *py_retval;
    VGHardwareQueryResult retval;
    VGHardwareQueryType key;
    VGint setting;
    const char *keywords[] = {"key", "setting", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "ii", (char **) keywords, &key, &setting)) {
        return NULL;
    }
    retval = vgHardwareQuery(key, setting);
    py_retval = Py_BuildValue((char *) "i", retval);
    return py_retval;
}

PyObject *
OpenVG_vgGetString(PyObject * UNUSED(dummy), PyObject *args, PyObject *kwargs)
{
    PyObject *py_retval;
    const VGubyte *retval;
    VGStringID name;
    const char *keywords[] = {"name", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, (char *) "i", (char **) keywords, &name)) {
        return NULL;
    }
    retval = vgGetString(name);
    py_retval = Py_BuildValue((char *) "s", retval);
    return py_retval;
}

PyObject *
OpenVG_vgGetError()
{
    PyObject *py_retval;
    VGErrorCode retval;
    
    retval = vgGetError();
    py_retval = Py_BuildValue((char *) "i", retval);
    return py_retval;
}


static PyMethodDef OpenVG_functions[] = {
    {(char *) "hardware_query",
     (PyCFunction) OpenVG_vgHardwareQuery,
     METH_KEYWORDS|METH_VARARGS,
     NULL
    },
    {(char *) "get_string",
     (PyCFunction) OpenVG_vgGetString,
     METH_KEYWORDS|METH_VARARGS,
     NULL
    },
    {(char *) "get_error",
     (PyCFunction) OpenVG_vgGetError,
     METH_NOARGS,
     NULL
    },
    {NULL, NULL, 0, NULL}
};

#if PY_VERSION_HEX >= 0x03000000
static struct PyModuleDef OpenVG_moduledef = {
    PyModuleDef_HEAD_INIT,
    "VG",
    NULL,
    -1,
    OpenVG_functions,
};
#endif


PyObject *
initVG(void)
{
    PyObject *m;
    PyObject *submodule;
    #if PY_VERSION_HEX >= 0x03000000
    m = PyModule_Create(&OpenVG_moduledef);
    #else
    m = Py_InitModule3((char *) "VG", OpenVG_functions, NULL);
    #endif
    if (m == NULL) {
        return NULL;
    }

    /* Register the 'VGPath' class */
    if (PyType_Ready(&PyVGPath_Type)) {
        return NULL;
    }
    PyModule_AddObject(m, (char *) "VGPath", (PyObject *) &PyVGPath_Type);

    /* Register the 'VGPaint' class */
    if (PyType_Ready(&PyVGPaint_Type)) {
        return NULL;
    }
    PyModule_AddObject(m, (char *) "VGPaint", (PyObject *) &PyVGPaint_Type);

    /* Register the 'VGImage' class */
    if (PyType_Ready(&PyVGImage_Type)) {
        return NULL;
    }
    PyModule_AddObject(m, (char *) "VGImage", (PyObject *) &PyVGImage_Type);

    /* Register the 'VGContext' class */
    if (PyType_Ready(&PyVGContext_Type)) {
        return NULL;
    }
    PyModule_AddObject(m, (char *) "VGContext", (PyObject *) &PyVGContext_Type);

    submodule = initOpenVG_VGRenderingQuality();
    if (submodule == NULL) {
        return NULL;
    }
    Py_INCREF(submodule);
    PyModule_AddObject(m, (char *) "VGRenderingQuality", submodule);

    submodule = initOpenVG_VGTilingMode();
    if (submodule == NULL) {
        return NULL;
    }
    Py_INCREF(submodule);
    PyModule_AddObject(m, (char *) "VGTilingMode", submodule);

    submodule = initOpenVG_VGMaskOperation();
    if (submodule == NULL) {
        return NULL;
    }
    Py_INCREF(submodule);
    PyModule_AddObject(m, (char *) "VGMaskOperation", submodule);

    submodule = initOpenVG_VGPaintType();
    if (submodule == NULL) {
        return NULL;
    }
    Py_INCREF(submodule);
    PyModule_AddObject(m, (char *) "VGPaintType", submodule);

    submodule = initOpenVG_VGPathCapabilities();
    if (submodule == NULL) {
        return NULL;
    }
    Py_INCREF(submodule);
    PyModule_AddObject(m, (char *) "VGPathCapabilities", submodule);

    submodule = initOpenVG_VGStringID();
    if (submodule == NULL) {
        return NULL;
    }
    Py_INCREF(submodule);
    PyModule_AddObject(m, (char *) "VGStringID", submodule);

    submodule = initOpenVG_VGImageChannel();
    if (submodule == NULL) {
        return NULL;
    }
    Py_INCREF(submodule);
    PyModule_AddObject(m, (char *) "VGImageChannel", submodule);

    submodule = initOpenVG_VGParamType();
    if (submodule == NULL) {
        return NULL;
    }
    Py_INCREF(submodule);
    PyModule_AddObject(m, (char *) "VGParamType", submodule);

    submodule = initOpenVG_VGMatrixMode();
    if (submodule == NULL) {
        return NULL;
    }
    Py_INCREF(submodule);
    PyModule_AddObject(m, (char *) "VGMatrixMode", submodule);

    submodule = initOpenVG_VGImageQuality();
    if (submodule == NULL) {
        return NULL;
    }
    Py_INCREF(submodule);
    PyModule_AddObject(m, (char *) "VGImageQuality", submodule);

    submodule = initOpenVG_VGPathAbsRel();
    if (submodule == NULL) {
        return NULL;
    }
    Py_INCREF(submodule);
    PyModule_AddObject(m, (char *) "VGPathAbsRel", submodule);

    submodule = initOpenVG_VGFillRule();
    if (submodule == NULL) {
        return NULL;
    }
    Py_INCREF(submodule);
    PyModule_AddObject(m, (char *) "VGFillRule", submodule);

    submodule = initOpenVG_VGPaintParamType();
    if (submodule == NULL) {
        return NULL;
    }
    Py_INCREF(submodule);
    PyModule_AddObject(m, (char *) "VGPaintParamType", submodule);

    submodule = initOpenVG_VGImageFormat();
    if (submodule == NULL) {
        return NULL;
    }
    Py_INCREF(submodule);
    PyModule_AddObject(m, (char *) "VGImageFormat", submodule);

    submodule = initOpenVG_VGImageParamType();
    if (submodule == NULL) {
        return NULL;
    }
    Py_INCREF(submodule);
    PyModule_AddObject(m, (char *) "VGImageParamType", submodule);

    submodule = initOpenVG_VGCapStyle();
    if (submodule == NULL) {
        return NULL;
    }
    Py_INCREF(submodule);
    PyModule_AddObject(m, (char *) "VGCapStyle", submodule);

    submodule = initOpenVG_VGPathCommand();
    if (submodule == NULL) {
        return NULL;
    }
    Py_INCREF(submodule);
    PyModule_AddObject(m, (char *) "VGPathCommand", submodule);

    submodule = initOpenVG_VGHardwareQueryType();
    if (submodule == NULL) {
        return NULL;
    }
    Py_INCREF(submodule);
    PyModule_AddObject(m, (char *) "VGHardwareQueryType", submodule);

    submodule = initOpenVG_VGErrorCode();
    if (submodule == NULL) {
        return NULL;
    }
    Py_INCREF(submodule);
    PyModule_AddObject(m, (char *) "VGErrorCode", submodule);

    submodule = initOpenVG_VGPixelLayout();
    if (submodule == NULL) {
        return NULL;
    }
    Py_INCREF(submodule);
    PyModule_AddObject(m, (char *) "VGPixelLayout", submodule);

    submodule = initOpenVG_VGPathDatatype();
    if (submodule == NULL) {
        return NULL;
    }
    Py_INCREF(submodule);
    PyModule_AddObject(m, (char *) "VGPathDatatype", submodule);

    submodule = initOpenVG_VGPathSegment();
    if (submodule == NULL) {
        return NULL;
    }
    Py_INCREF(submodule);
    PyModule_AddObject(m, (char *) "VGPathSegment", submodule);

    submodule = initOpenVG_VGPathParamType();
    if (submodule == NULL) {
        return NULL;
    }
    Py_INCREF(submodule);
    PyModule_AddObject(m, (char *) "VGPathParamType", submodule);

    submodule = initOpenVG_VGColorRampSpreadMode();
    if (submodule == NULL) {
        return NULL;
    }
    Py_INCREF(submodule);
    PyModule_AddObject(m, (char *) "VGColorRampSpreadMode", submodule);

    submodule = initOpenVG_VGPaintMode();
    if (submodule == NULL) {
        return NULL;
    }
    Py_INCREF(submodule);
    PyModule_AddObject(m, (char *) "VGPaintMode", submodule);

    submodule = initOpenVG_VGHardwareQueryResult();
    if (submodule == NULL) {
        return NULL;
    }
    Py_INCREF(submodule);
    PyModule_AddObject(m, (char *) "VGHardwareQueryResult", submodule);

    submodule = initOpenVG_VGJoinStyle();
    if (submodule == NULL) {
        return NULL;
    }
    Py_INCREF(submodule);
    PyModule_AddObject(m, (char *) "VGJoinStyle", submodule);

    submodule = initOpenVG_VGImageMode();
    if (submodule == NULL) {
        return NULL;
    }
    Py_INCREF(submodule);
    PyModule_AddObject(m, (char *) "VGImageMode", submodule);

    submodule = initOpenVG_VGBlendMode();
    if (submodule == NULL) {
        return NULL;
    }
    Py_INCREF(submodule);
    PyModule_AddObject(m, (char *) "VGBlendMode", submodule);

    return m;
}

