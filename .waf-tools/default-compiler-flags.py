# -*- Mode: python; py-indent-offset: 4; indent-tabs-mode: nil; coding: utf-8; -*-

from waflib import Logs, Configure

def options(opt):
    opt.add_option('--debug', '--with-debug', action='store_true', default=False, dest='debug',
                   help='''Compile in debugging mode without all optimizations (-O0)''')
    opt.add_option('--with-c++11', action='store_true', default=False, dest='use_cxx11',
                   help='''Use C++ 11 features if available in the compiler''')

def configure(conf):
    areCustomCxxflagsPresent = (len(conf.env.CXXFLAGS) > 0)
    defaultFlags = []

    if conf.options.use_cxx11:
        defaultFlags += ['-std=c++0x', '-std=c++11']
    else:
        defaultFlags += ['-std=c++03']

    defaultFlags += ['-pedantic', '-Wall', '-Wno-long-long']

    if conf.options.debug:
        conf.define('_DEBUG', 1)
        defaultFlags += ['-O0',
                         '-Og', # gcc >= 4.8
                         '-g3',
                         '-fcolor-diagnostics', # clang
                         '-fdiagnostics-color', # gcc >= 4.9
                         '-Werror',
                         '-Wno-error=deprecated-register',
                         '-Wno-error=maybe-uninitialized', # Bug #1615
                        ]
        if areCustomCxxflagsPresent:
            missingFlags = [x for x in defaultFlags if x not in conf.env.CXXFLAGS]
            if len(missingFlags) > 0:
                Logs.warn("Selected debug mode, but CXXFLAGS is set to a custom value '%s'"
                          % " ".join(conf.env.CXXFLAGS))
                Logs.warn("Default flags '%s' are not activated" % " ".join(missingFlags))
        else:
            conf.add_supported_cxxflags(defaultFlags)
    else:
        defaultFlags += ['-O2', '-g']
        if not areCustomCxxflagsPresent:
            conf.add_supported_cxxflags(defaultFlags)

@Configure.conf
def add_supported_cxxflags(self, cxxflags):
    """
    Check which cxxflags are supported by compiler and add them to env.CXXFLAGS variable
    """
    self.start_msg('Checking allowed flags for c++ compiler')

    supportedFlags = []
    for flag in cxxflags:
        if self.check_cxx(cxxflags=['-Werror', flag], mandatory=False):
            supportedFlags += [flag]

    self.end_msg(' '.join(supportedFlags))
    self.env.CXXFLAGS = supportedFlags + self.env.CXXFLAGS
