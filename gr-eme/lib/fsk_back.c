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
#include <math.h>
#include "fsk_modulate_if_impl.h"
#define PI 3.14159265

namespace gr {
  namespace eme {

    fsk_modulate_if::sptr
    fsk_modulate_if::make()
    {
      return gnuradio::get_initial_sptr
        (new fsk_modulate_if_impl());
    }

    /*
     * The private constructor
     */
    fsk_modulate_if_impl::fsk_modulate_if_impl()
      : sync_interpolator("fsk_modulate_if",
              gr::io_signature::make(1, 1, sizeof(eme_packet_with_sync)),
              gr::io_signature::make(1, 1, sizeof(float),
	      63*4096)  //63 symbols per packet * 4096 samples per symbol
    {}

    /*
     * Our virtual destructor.
     */
    fsk_modulate_if_impl::~fsk_modulate_if_impl()
    {
    }

/*
    void
    fsk_modulate_if_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
        ninput_items_required[0] = noutput_items / (4096*126);  //This is probably not going to work
    }
*/

    int
    fsk_modulate_if_impl::work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
        const eme_packet_rs_encoded *in = (const eme_packet_rs_encoded *) input_items[0];
        float *out = (float *) output_items[0];

        // Do <+signal processing+>
	int symbol_index;
	int input_index;
	float phase;
	float freq;
	float sample_rate = 11025;
	for( int i = 0; i < noutput_items; i++ ) {
		symbol_index = i / 2048;
		if (symbol_index > 125) {
			symbol_index = (symbol_index / 2) + 126;
		}
		input_index = i / (4096*126);
		if ( in[ input_index ].data[symbol_index] == 0 ) {
			out[i] = 0;
		} else {
			while ( phase > 2*PI ) {
				phase -= 2*PI;
			}
			freq = (1270.5 + 2.6917 * in[ input_index ].data[symbol_index]);
			phase += 2 * PI * freq / sample_rate;
			out[i] = sin (phase);
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

