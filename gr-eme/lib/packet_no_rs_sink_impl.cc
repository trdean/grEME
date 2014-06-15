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
#include <cstdio>
#include "packet_no_rs_sink_impl.h"

namespace gr {
  namespace eme {

    packet_no_rs_sink::sptr
    packet_no_rs_sink::make()
    {
      return gnuradio::get_initial_sptr
        (new packet_no_rs_sink_impl());
    }

    /*
     * The private constructor
     */
    packet_no_rs_sink_impl::packet_no_rs_sink_impl()
      : gr::sync_block("packet_no_rs_sink",
              gr::io_signature::make(1, 1, sizeof(eme_packet_no_rs)),
              gr::io_signature::make(0, 0, 0))
    {}

    /*
     * Our virtual destructor.
     */
    packet_no_rs_sink_impl::~packet_no_rs_sink_impl()
    {
    }

    int
    packet_no_rs_sink_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {
        const eme_packet_no_rs *in = (const eme_packet_no_rs *) input_items[0];

        // Do <+signal processing+>
	for (int i = 0; i < noutput_items; i++) {
		for (int j = 0; j < 12; j++) {
			printf ("%X ", in[i].data[j]);
		}
		printf ("\n\n");
	}

        // Tell runtime system how many output items we produced.
        return noutput_items;
    }

  } /* namespace eme */
} /* namespace gr */

