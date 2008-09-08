#!/usr/bin/python

import sys
from distutils.core import setup

# version is last argument: fetch it and remove it from list, so distutils won't bother us with it
current_version = sys.argv[-1]
sys.argv = sys.argv[:-1]
setup(name="robointerface", version=current_version, py_modules=["robointerface"])

