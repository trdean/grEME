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
#include "interleave_ii_impl.h"
#include <eme/types.h>

namespace gr {
  namespace eme {

    interleave_ii::sptr
    interleave_ii::make()
    {
      return gnuradio::get_initial_sptr
        (new interleave_ii_impl());
    }

    /*
     * The private constructor
     */
    interleave_ii_impl::interleave_ii_impl()
      : gr::block("interleave_ii",
              gr::io_signature::make(1, 1, sizeof(eme_packet_rs_encoded)),
              gr::io_signature::make(1, 1, sizeof(eme_packet_rs_encoded)))
    {}

    /*
     * Our virtual destructor.
     */
    interleave_ii_impl::~interleave_ii_impl()
    {
    }

    void
    interleave_ii_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
        ninput_items_required[0] = noutput_items;
    }

    int
    interleave_ii_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
        const eme_packet_rs_encoded *in = (const eme_packet_rs_encoded *) input_items[0];
        eme_packet_rs_encoded *out = (eme_packet_rs_encoded *) output_items[0];

        // Do <+signal processing+>
        for(int i = 0; i < noutput_items; i++) {
		for(int j = 0; j < 9; j++) {
			for( int k = 0; k < 7; k++) {
				out[i].data[9*k+j] = in[i].data[7*j+k];
			}
		}
	}
        // Tell runtime system how many input items we consumed on
        // each input stream.
        consume_each (noutput_items);

        // Tell runtime system how many output items we produced.
        return noutput_items;
    }

  } /* namespace eme */
} /* namespace gr */

