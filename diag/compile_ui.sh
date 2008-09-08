#!/bin/sh

pyuic4 diag.ui > ftdiagnose_ui.py
pyuic4 open.ui > ftdiagnose_open_ui.py
./ftdiagnose.py

