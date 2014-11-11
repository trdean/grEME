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
#include "fsk_modulate_impl.h"

namespace gr {
  namespace eme {

    fsk_modulate::sptr
    fsk_modulate::make(int samples_per_symbol)
    {
      return gnuradio::get_initial_sptr
        (new fsk_modulate_impl(samples_per_symbol));
    }

    /*
     * The private constructor
     */
    fsk_modulate_impl::fsk_modulate_impl(int samples_per_symbol)
      : gr::sync_interpolator("fsk_modulate",
              gr::io_signature::make(1, 1, sizeof(char)),
              gr::io_signature::make(1, 1, sizeof(gr_complex)), samples_per_symbol)
    {}

    /*
     * Our virtual destructor.
     */
    fsk_modulate_impl::~fsk_modulate_impl()
    {
    }

    int
    fsk_modulate_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {
        const char *in = (const char *) input_items[0];
        gr_complex *out = (gr_complex *) output_items[0];

        // Do <+signal processing+>

        // Tell runtime system how many output items we produced.
        return noutput_items;
    }

  } /* namespace eme */
} /* namespace gr */

