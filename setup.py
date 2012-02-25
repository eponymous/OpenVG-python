from distutils.core import setup, Extension

module_openvg = Extension('OpenVG',
                          include_dirs = ['.', '/usr/include/vg'],
                          libraries = ['OpenVG', 'GL', 'GLU'],
                          library_dirs = ['/usr/lib'],
                          sources = ['vg_image.cc',
                                     'vg_path.cc',
                                     'vg_context.cc',
                                     'vg_paint.cc',
                                     'vg_module.cc',
                                     'vgu_module.cc',
                                     'openvg_module.cc'])

setup (name = 'OpenVG-python',
       version = '0.1.0',
       description = 'OpenVG Python Bindings',
       author = 'Dan Eicher',
       author_email = 'dan@trollwerks.org',
       license = 'GPLv2+',
       ext_modules = [module_openvg])

