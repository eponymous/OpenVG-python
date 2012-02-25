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


#if PY_VERSION_HEX >= 0x03000000
static struct PyModuleDef OpenVG_moduledef = {
    PyModuleDef_HEAD_INIT,
    "OpenVG",
    NULL,
    -1,
    NULL,
};
#endif

#if PY_VERSION_HEX >= 0x03000000
    #define MOD_ERROR NULL
    #define MOD_INIT(name) PyInit_##name(void)
    #define MOD_RETURN(val) val
#else
    #define MOD_ERROR
    #define MOD_INIT(name) init##name(void)
    #define MOD_RETURN(val)
#endif
PyMODINIT_FUNC
MOD_INIT(OpenVG)
{
    PyObject *m;
    PyObject *submodule;

    #if PY_VERSION_HEX >= 0x03000000
    m = PyModule_Create(&OpenVG_moduledef);
    #else
    m = Py_InitModule3((char *) "OpenVG", NULL, NULL);
    #endif
    if (m == NULL) {
        return MOD_ERROR;
    }

    submodule = initVG();
    if (submodule == NULL) {
        return MOD_ERROR;
    }
    Py_INCREF(submodule);
    PyModule_AddObject(m, (char *) "VG", submodule);

    submodule = initVGU();
    if (submodule == NULL) {
        return MOD_ERROR;
    }
    Py_INCREF(submodule);
    PyModule_AddObject(m, (char *) "VGU", submodule);

    return MOD_RETURN(m);
}

