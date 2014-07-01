/* -*- c++ -*- */
/* 
 * Copyright 2014 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "encode_rs_int_impl.h"

namespace gr {
  namespace eme {

   static void *rs; //pointer to encoder in Karn library

    encode_rs_int::sptr
    encode_rs_int::make()
    {
      return gnuradio::get_initial_sptr
        (new encode_rs_int_impl());
    }

    /*
     * The private constructor
     */
    encode_rs_int_impl::encode_rs_int_impl()
      : gr::block("encode_rs_int",
              gr::io_signature::make( 1, 1, sizeof(eme_packet_no_rs)),
              gr::io_signature::make( 1, 1, sizeof(eme_packet_rs_encoded)))
    { 
      rs = init_rs_int(6, 0x43, 3, 1, 51); 
    }
    

    /*
     * Our virtual destructor.
     */
    encode_rs_int_impl::~encode_rs_int_impl()
    {
      //if(rs)
      //  free_rs_int(rs);
    }

    void
    encode_rs_int_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
        ninput_items_required[0] = noutput_items;
    }

    int
    encode_rs_int_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
        const eme_packet_no_rs *in = (const eme_packet_no_rs *) input_items[0];
        eme_packet_rs_encoded *out = (eme_packet_rs_encoded *) output_items[0];

        // Do <+signal processing+>
        int raw_parity[51];
        int tmp_data[12];
	for(int i = 0; i < noutput_items; i++) {

          // Reverse data order because ???
          for(int j=0; j<12; j++) {
            tmp_data[j]=in[i].data[11-j];
          }    
  
          encode_rs_int_work(rs, tmp_data, raw_parity); 

          // Move parity symbols and data into output - backwards because ???
          for (int j = 0; j < 51; j++) out[i].data[50-j] = raw_parity[j];
          for (int j = 0; j < 12; j++) out[i].data[j+51] = tmp_data[11-j];
        }
        // Tell runtime system how many input items we consumed on
        // each input stream.
        consume_each (noutput_items);

        // Tell runtime system how many output items we produced.
        return noutput_items;
    }

    //Reed-Solomon stuff
    void
    encode_rs_int_impl::encode_rs_int_work(void *p, int *data, int *bb) 
    {
      struct rs *rs = (struct rs *)p;

      unsigned int i, j;
      int feedback;

      memset(bb,0,NROOTS*sizeof(int));

      for(i=0;i<NN-NROOTS;i++){
        feedback = INDEX_OF[data[i] ^ bb[0]];
    	if(feedback != A0){      /* feedback term is non-zero */
#ifdef UNNORMALIZED
        /* This line is unnecessary when GENPOLY[NROOTS] is unity, as it must
         * always be for the polynomials constructed by init_rs()
         */
          feedback = MODNN(NN - GENPOLY[NROOTS] + feedback);
#endif
          for(j=1;j<NROOTS;j++)
            bb[j] ^= ALPHA_TO[MODNN(feedback + GENPOLY[NROOTS-j])];
        }
        /* Shift */
        memmove(&bb[0],&bb[1],sizeof(int)*(NROOTS-1));
        if(feedback != A0)
          bb[NROOTS-1] = ALPHA_TO[MODNN(feedback + GENPOLY[0])];
        else
          bb[NROOTS-1] = 0;
      }
    }

    void *
    encode_rs_int_impl::init_rs_int(unsigned int symsize, unsigned int gfpoly, unsigned fcr,
                  unsigned prim, unsigned int nroots) 
    {
      struct rs *rs;
      int sr,root,iprim;
      unsigned int i, j;

      if(symsize > 8*sizeof(int))
        return NULL; /* Need version with ints rather than chars */

      if(fcr >= (1u<<symsize))
        return NULL;
      if(prim == 0 || prim >= (1u<<symsize))
        return NULL;
      if(nroots >= (1u<<symsize))
        return NULL; /* Can't have more roots than symbol values! */

      rs = (struct rs *)calloc(1,sizeof(struct rs));
      rs->mm = symsize;
      rs->nn = (1<<symsize)-1;

      rs->alpha_to = (int *)malloc(sizeof(int)*(rs->nn+1));
      if(rs->alpha_to == NULL){
        free(rs);
        return NULL;
      }

      rs->index_of = (int *)malloc(sizeof(int)*(rs->nn+1));
      if(rs->index_of == NULL){
        free(rs->alpha_to);
        free(rs);
        return NULL;
      }

      /* Generate Galois field lookup tables */
      rs->index_of[0] = A0; /* log(zero) = -inf */
      rs->alpha_to[A0] = 0; /* alpha**-inf = 0 */
      sr = 1;
      for(i=0;i<rs->nn;i++){
        rs->index_of[sr] = i;
        rs->alpha_to[i] = sr;
        sr <<= 1;
        if(sr & (1<<symsize))
          sr ^= gfpoly;
        sr &= rs->nn;
      }
      if(sr != 1){
        /* field generator polynomial is not primitive! */
        free(rs->alpha_to);
        free(rs->index_of);
        free(rs);
        return NULL;
      }

      /* Form RS code generator polynomial from its roots */
      rs->genpoly = (int *)malloc(sizeof(int)*(nroots+1));
      if(rs->genpoly == NULL){
        free(rs->alpha_to);
        free(rs->index_of);
        free(rs);
        return NULL;
      }
      rs->fcr = fcr;
      rs->prim = prim;
      rs->nroots = nroots;

      /* Find prim-th root of 1, used in decoding */
      for(iprim=1;(iprim % prim) != 0;iprim += rs->nn)
        ;
      rs->iprim = iprim / prim;

      rs->genpoly[0] = 1;
      for (i = 0,root=fcr*prim; i < nroots; i++,root += prim) {
        rs->genpoly[i+1] = 1;

        /* Multiply rs->genpoly[] by  @**(root + x) */
        for (j = i; j > 0; j--){
          if (rs->genpoly[j] != 0)
            rs->genpoly[j] = rs->genpoly[j-1] ^ rs->alpha_to[modnn(rs,rs->index_of[rs->genpoly[j]] + root)];
          else
            rs->genpoly[j] = rs->genpoly[j-1];
        }
        /* rs->genpoly[0] can never be zero */
        rs->genpoly[0] = rs->alpha_to[modnn(rs,rs->index_of[rs->genpoly[0]] + root)];
      }
      /* convert rs->genpoly[] to index form for quicker encoding */
      for (i = 0; i <= nroots; i++)
        rs->genpoly[i] = rs->index_of[rs->genpoly[i]];

      return rs;
    }

    void 
    encode_rs_int_impl::free_rs_int(void *p) {
      struct rs *rs = (struct rs *)p;

      free(rs->alpha_to);
      free(rs->index_of);
      free(rs->genpoly);
      free(rs);
    }

  } /* namespace eme */
} /* namespace gr */

