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

#ifndef _OPENVG_MODULE_H
#define _OPENVG_MODULE_H

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <stddef.h>
#include "openvg.h"

#if PY_VERSION_HEX < 0x020400F0

#define PyEval_ThreadsInitialized() 1

#define Py_CLEAR(op)				\
        do {                            	\
                if (op) {			\
                        PyObject *tmp = (PyObject *)(op);	\
                        (op) = NULL;		\
                        Py_DECREF(tmp);		\
                }				\
        } while (0)


#define Py_VISIT(op)							\
        do { 								\
                if (op) {						\
                        int vret = visit((PyObject *)(op), arg);	\
                        if (vret)					\
                                return vret;				\
                }							\
        } while (0)

#endif



#if PY_VERSION_HEX < 0x020500F0

typedef int Py_ssize_t;
# define PY_SSIZE_T_MAX INT_MAX
# define PY_SSIZE_T_MIN INT_MIN
typedef inquiry lenfunc;
typedef intargfunc ssizeargfunc;
typedef intobjargproc ssizeobjargproc;

#endif


#ifndef PyVarObject_HEAD_INIT
#define PyVarObject_HEAD_INIT(type, size) \
        PyObject_HEAD_INIT(type) size,
#endif


#if PY_VERSION_HEX >= 0x03000000
typedef void* cmpfunc;
#endif


#if     __GNUC__ > 2
# define UNUSED(param) param __attribute__((__unused__))
#elif     __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ > 4)
# define UNUSED(param) __attribute__((__unused__)) param
#else
# define UNUSED(param) param
#endif  /* !__GNUC__ */

#define MATRIX_SIZE 9

typedef struct {
    PyObject_HEAD
    VGPath obj;
    unsigned int paint_modes;
    unsigned int capabilities;
} PyVGPath;


typedef struct {
    PyObject_HEAD
    VGPaint obj;
} PyVGPaint;

typedef struct {
    PyObject_HEAD
    VGImage obj;
} PyVGImage;

typedef struct {
    PyObject_HEAD
    bool init;
    int dimensions[2];
} PyVGContext;


extern PyTypeObject PyVGPath_Type;
extern PyTypeObject PyVGPaint_Type;
extern PyTypeObject PyVGImage_Type;
extern PyTypeObject PyVGContext_Type;

VGErrorCode check_error(void);

PyObject *initVG(void);
PyObject *initVGU(void);

#endif // _OPENVG_MODULE_H
