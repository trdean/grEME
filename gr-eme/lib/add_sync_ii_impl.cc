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
#include <eme/types.h>
#include "add_sync_ii_impl.h"

namespace gr {
  namespace eme {

    int sync_vector [126] = {1,0,0,1,1,0,0,0,1,1,1,1,1,1,0,1,0,1,0,0,0,1,0,1,1,0,0,1,0,0,0,1,1,1,0,0,1,1,1,1,0,1,1,0,1,1,1,1,0,0,0,1,1,0,1,0,1,0,1,1,0,0,1,1,0,1,0,1,0,1,0,0,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1, 0,1,0,0,1,0,1,1,0,1,0,1,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,0,1,1,1,1,1,1,1,1};

    add_sync_ii::sptr
    add_sync_ii::make()
    {
      return gnuradio::get_initial_sptr
        (new add_sync_ii_impl());
    }

    /*
     * The private constructor
     */
    add_sync_ii_impl::add_sync_ii_impl()
      : gr::block("add_sync_ii",
              gr::io_signature::make(1, 1, sizeof(eme_packet_rs_encoded)),
              gr::io_signature::make(1, 1, sizeof(eme_packet_with_sync)))
    {}

    /*
     * Our virtual destructor.
     */
    add_sync_ii_impl::~add_sync_ii_impl()
    {
    }

    void
    add_sync_ii_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
    	ninput_items_required[0] = noutput_items;
    }

    int
    add_sync_ii_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
        const eme_packet_rs_encoded *in = (const eme_packet_rs_encoded *) input_items[0];
        eme_packet_with_sync *out = (eme_packet_with_sync *) output_items[0];

        // Do <+signal processing+>
	for(int i = 0; i < noutput_items; i++) {
		for( int j = 0; j < 126; j++ ) {
			out[i].data[j] = sync_vector[j];
		}
		for( int j = 126; j < 189; j++ ) {
			out[i].data[j] = in[i].data[j-126];
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

