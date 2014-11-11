/* -*- c++ -*- */

#define EME_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "eme_swig_doc.i"

%{
#include "eme/rs_encode_cc.h"
#include "eme/interleave.h"
#include "eme/graycode.h"
#include "eme/add_sync.h"
#include "eme/fsk_modulate.h"
%}


%include "eme/rs_encode_cc.h"
GR_SWIG_BLOCK_MAGIC2(eme, rs_encode_cc);
%include "eme/interleave.h"
GR_SWIG_BLOCK_MAGIC2(eme, interleave);
%include "eme/graycode.h"
GR_SWIG_BLOCK_MAGIC2(eme, graycode);
%include "eme/add_sync.h"
GR_SWIG_BLOCK_MAGIC2(eme, add_sync);
%include "eme/fsk_modulate.h"
GR_SWIG_BLOCK_MAGIC2(eme, fsk_modulate);
