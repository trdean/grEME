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
#include "packet_rs_source_impl.h"

namespace gr {
  namespace eme {

    packet_rs_source::sptr
    packet_rs_source::make(std::vector <int> data, bool repeat)
    {
      return gnuradio::get_initial_sptr
        (new packet_rs_source_impl(data, repeat));
    }

    /*
     * The private constructor
     */
    packet_rs_source_impl::packet_rs_source_impl(std::vector <int> data, bool repeat)
      : gr::block("packet_rs_source",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(1, 1, sizeof(eme_packet_rs_encoded)))
    {
        for (int i = 0; i < 63; i++) d_data[i] = data[i];
	d_repeat = repeat;
	d_blocks_out = false;
    }

    /*
     * Our virtual destructor.
     */
    packet_rs_source_impl::~packet_rs_source_impl()
    {
    }

    void
    packet_rs_source_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
        ninput_items_required[0] = 0;
    }

    int
    packet_rs_source_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
        //const <+ITYPE*> *in = (const <+ITYPE*> *) input_items[0];
        eme_packet_rs_encoded *out = (eme_packet_rs_encoded *) output_items[0];

        // Do <+signal processing+>
        for (int i = 0; i < noutput_items; i++) {
		if (!d_repeat && d_blocks_out)
			return 0;

		for (int j = 0; j < 63; j++) 
			out[i].data[j] = d_data[j];
		
		d_blocks_out = true;
	}

	// No input?  Not really sure how to handle this 
        consume_each (0);

        // Tell runtime system how many output items we produced.
        return noutput_items;
    }

  } /* namespace eme */
} /* namespace gr */

