# Partially stolen from https://bitbucket.org/mblum/libgp/src/2537ea7329ef/.ycm_extra_conf.py
import os
import ycm_core

# These are the compilation flags that will be used in case there's no
# compilation database set (by default, one is not set).
# CHANGE THIS LIST OF FLAGS. YES, THIS IS THE DROID YOU HAVE BEEN LOOKING FOR.
flags = [
    '-Wall',
    '-Wextra',
    '-Werror',
    '-Wmissing-declarations',
    '-Wconversion',
    '-Wfloat-equal',
    '-Wno-long-long',
    '-Wno-variadic-macros',
    '-fexceptions',
    '-fmessage-length=0',
    '-fsigned-char',
    # THIS IS IMPORTANT! Without a "-std=<something>" flag, clang won't know which
    # language to use when compiling headers. So it will guess. Badly. So C++
    # headers will be compiled as C headers. You don't want that so ALWAYS specify
    # a "-std=<something>".
    # For a C project, you would set this to something like 'c99' instead of
    # 'c++11'.
    # '-std=c++14',
    '-std=c++11',
    # ...and the same thing goes for the magic -x option which specifies the
    # language that the files to be compiled are written in. This is mostly
    # relevant for c++ headers.
    # For a C project, you would set this to 'c' instead of 'c++'.
    # '-x', 'c++',
    '-x', 'c++',
    # This path will only work on OS X, but extra paths that don't exist are not
    # harmful
    '-I', './CAN_Analyser_USB_Driver',
    '-I', './CAN_Analyser_USB_Driver/hidapi',
    '-I', './R_Visualizer',
    '-I', './R_Visualizer/ErrLogView',
    '-I', './R_Visualizer/MessageConfig',
    '-I', './R_Visualizer/Msg',
    '-I', './R_Visualizer/SendMessages',
    '-I', './R_Visualizer/SystemOverview',
    '-I', './R_Visualizer/SystemOverview/SysOvrvObj',
    '-I', './R_Visualizer/SystemOverview/SysOvrvTrigger',
    '-I', './R_Visualizer_Utilities',
    '-I', '.',
]


def FlagsForFile( filename, **kwargs ):
    return {
            'flags': flags,
            'do_cache': True
            }
