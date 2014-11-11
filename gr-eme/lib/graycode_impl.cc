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

#include <stdio.h>

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "graycode_impl.h"

namespace gr {
  namespace eme {

    graycode::sptr
    graycode::make(int direction)
    {
      return gnuradio::get_initial_sptr
        (new graycode_impl(direction));
    }

    /*
     * The private constructor
     */
    graycode_impl::graycode_impl(int direction)
      : gr::sync_block("graycode",
              gr::io_signature::make(1, 1, sizeof(char)),
              gr::io_signature::make(1, 1, sizeof(char))),
              d_direction(direction)
    {
        if (d_direction != DECODE && d_direction != ENCODE)  {
            throw std::invalid_argument("eme::interleave::direction");
        }
    }

    /*
     * Our virtual destructor.
     */
    graycode_impl::~graycode_impl()
    {
    }

    int
    graycode_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {
        unsigned char symbol, shift, tmp;

        const unsigned char *in = (const unsigned char *) input_items[0];
        char unsigned *out = (unsigned char *) output_items[0];

        for ( int i = 0; i < noutput_items; i++ ) {            
            // Do <+signal processing+>
            if (d_direction == ENCODE) {
                out[i] = in[i] ^ (in[i] >> 1);
            } else if (d_direction == DECODE) {
                	symbol = in[i];

			shift = 1;
		        tmp = (symbol >> shift);
			while (tmp > 0) {
				symbol ^= tmp;
				shift = shift << 1;
				tmp = symbol >> shift;
			}
			
			out[i] = symbol;
            }
        }
        // Tell runtime system how many output items we produced.
        return noutput_items;
    }

  } /* namespace eme */
} /* namespace gr */

