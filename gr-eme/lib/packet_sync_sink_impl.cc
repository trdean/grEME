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
#include "packet_sync_sink_impl.h"

namespace gr {
  namespace eme {

    packet_sync_sink::sptr
    packet_sync_sink::make()
    {
      return gnuradio::get_initial_sptr
        (new packet_sync_sink_impl());
    }

    /*
     * The private constructor
     */
    packet_sync_sink_impl::packet_sync_sink_impl()
      : gr::sync_block("packet_sync_sink",
              gr::io_signature::make(1, 1, sizeof(eme_packet_with_sync)),
              gr::io_signature::make(0, 0, 0))
    {}

    /*
     * Our virtual destructor.
     */
    packet_sync_sink_impl::~packet_sync_sink_impl()
    {
    }

    int
    packet_sync_sink_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {
        const eme_packet_with_sync *in = (const eme_packet_with_sync *) input_items[0];

        // Do <+signal processing+>
        for (int i = 0; i < noutput_items; i++) {
                for (int j = 0; j < 189; j++) {
                        printf ("%X ", in[i].data[j]);
                }

                printf ("\n\n");
        }

        // Tell runtime system how many output items we produced.
        return noutput_items;
    }

  } /* namespace eme */
} /* namespace gr */

