#!/usr/bin/python2

import sys
from distutils.core import setup

# version is last argument: fetch it and remove it from list, so distutils won't bother us with it
current_version = sys.argv[-1]
sys.argv = sys.argv[:-1]
setup(name="ftdiagnose", version=current_version, py_modules=["ftdiagnose", "ftdiagnose_ui", "ftdiagnose_open_ui"])
