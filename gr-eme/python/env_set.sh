#!/bin/sh
export GR_DONT_LOAD_PREFS=1
export srcdir=/home/tom/gnuradio-3.7.2.1/gr-eme/python
export PATH=/home/tom/gnuradio-3.7.2.1/gr-eme/build/python:$PATH
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$DYLD_LIBRARY_PATH
export DYLD_LIBRARY_PATH=$LD_LIBRARY_PATH:$DYLD_LIBRARY_PATH
export PYTHONPATH=/home/tom/gnuradio-3.7.2.1/gr-eme/build/swig:$PYTHONPATH

