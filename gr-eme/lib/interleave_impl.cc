/* -*- c++ -*- */
/* 
 * Copyright 2014 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published b
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
#include "interleave_impl.h"

namespace gr {
  namespace eme {

    interleave::sptr
    interleave::make(int direction)
    {
      return gnuradio::get_initial_sptr
        (new interleave_impl(direction));
    }

    /*
     * The private constructor
     */
    interleave_impl::interleave_impl(int direction)
      : gr::sync_block("interleave",
              gr::io_signature::make(1, 1, 63*sizeof(char)),
              gr::io_signature::make(1, 1, 63*sizeof(char))),
      d_direction(direction)
    {
        if (d_direction != DECODE && d_direction != ENCODE)  {
            printf("%d\n", d_direction);
            throw std::invalid_argument("eme::interleave::direction");
        }

        //d_direction = direction;
    }

    /*
     * Our virtual destructor.
     */
    interleave_impl::~interleave_impl()
    {
    }

    int
    interleave_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {
        for (int i = 0; i < noutput_items; i++) {
            const char *in = (const char *) input_items[i];
            char *out = (char *) output_items[i];
        
            // Do <+signal processing+>
            if (d_direction == ENCODE) {
	        	for(int j = 0; j < 9; j++) {
		        	for( int k = 0; k < 7; k++) {
                                        out[9*k+j] = in[7*j+k];
		   	        }
		       }
            } else if (d_direction == DECODE) {
		for (int j = 0; j < 9; j++) {
			for (int k = 0; k < 7; k++) {
                                out[7*j+k] = in[9*k+j];
			}
		}
            }
        }
        // Tell runtime system how many output items we produced.
        return noutput_items;
    }

  } /* namespace eme */
} /* namespace gr */

