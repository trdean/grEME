/* -*- c++ -*- */

#define EME_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "eme_swig_doc.i"

%{
#include "eme/source_code_ss.h"
#include "eme/encode_rs_int.h"
#include "eme/decode_rs_int.h"
#include "eme/interleave_ii.h"
#include "eme/graycode_ii.h"
#include "eme/fsk_modulate_if.h"
#include "eme/add_sync_ii.h"
%}


%include "eme/source_code_ss.h"
GR_SWIG_BLOCK_MAGIC2(eme, source_code_ss);
%include "eme/encode_rs_int.h"
GR_SWIG_BLOCK_MAGIC2(eme, encode_rs_int);
%include "eme/decode_rs_int.h"
GR_SWIG_BLOCK_MAGIC2(eme, decode_rs_int);
%include "eme/interleave_ii.h"
GR_SWIG_BLOCK_MAGIC2(eme, interleave_ii);
%include "eme/graycode_ii.h"
GR_SWIG_BLOCK_MAGIC2(eme, graycode_ii);
%include "eme/fsk_modulate_if.h"
GR_SWIG_BLOCK_MAGIC2(eme, fsk_modulate_if);
%include "eme/add_sync_ii.h"
GR_SWIG_BLOCK_MAGIC2(eme, add_sync_ii);
