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
#include "decode_rs_int_impl.h"
#include "reed-solomon/rs.h"

namespace gr {
  namespace eme {

    static void *rs; //pointer to encoder in Karn library

    decode_rs_int::sptr
    decode_rs_int::make(unsigned int symsize,unsigned int gfpoly,unsigned fcr,unsigned prim,
		unsigned int nroots)
    {
      return gnuradio::get_initial_sptr
        (new decode_rs_int_impl(symsize, gfpoly, fcr, prim, nroots));
    }

    /*
     * The private constructor
     */
    decode_rs_int_impl::decode_rs_int_impl()
      : gr::block("decode_rs_int",
              gr::io_signature::make(1, 1, sizeof(eme_packet_rs_encoded)),
              gr::io_signature::make(1, 1, sizeof(eme_packet_no_rs)))
    {
      rs = init_rs_int(6, 0x43, 3, 1, 51); 
    }

    /*
     * Our virtual destructor.
     */
    decode_rs_int_impl::~decode_rs_int_impl()
    {
    }

    void
    decode_rs_int_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
        ninput_items_required[0] = noutput_items;
    }

    int
    decode_rs_int_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
        const int *in = (const int *) input_items[0];
        int *out = (int *) output_items[0];

        // Do <+signal processing+>:
	int err_index;
	int err_pos[50];
	int rec_flip[63];
	for (int i = 0; i < noutput_items; i++) {
		for (int k = 0; k < 12; k++) rec_flip[k] = in[i].data[62-k];
		for (int k = 0; k < 51; k++) rec_flip[12+k] = in[i].data[50-k];

		decode_rs_int_work(rs, rec_flip, err_pos, err_index);

		for (int k = 0; k < 12; k++) out[i].data[k] = rec_flip[11-k]
	}
	
        // Tell runtime system how many input items we consumed on
        // each input stream.
        consume_each (noutput_items);

        // Tell runtime system how many output items we produced.
        return noutput_items;
    }

  } /* namespace eme */
} /* namespace gr */
