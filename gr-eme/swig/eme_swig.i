/* -*- c++ -*- */

#define EME_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "eme_swig_doc.i"

%{
#include "eme/source_code_ss.h"
%}


%include "eme/source_code_ss.h"
GR_SWIG_BLOCK_MAGIC2(eme, source_code_ss);
