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
#include "source_code_ss_impl.h"

namespace gr {
  namespace eme {

    source_code_ss::sptr
    source_code_ss::make()
    {
      return gnuradio::get_initial_sptr
        (new source_code_ss_impl());
    }

    /*
     * The private constructor
     */
    source_code_ss_impl::source_code_ss_impl()
      : gr::block("source_code_ss",
              gr::io_signature::make(1, 1, sizeof(int)),
              gr::io_signature::make(1, 1, sizeof(int)))
    {}

    /*
     * Our virtual destructor.
     */
    source_code_ss_impl::~source_code_ss_impl()
    {
    }

    void
    source_code_ss_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
        /* <+forecast+> e.g. ninput_items_required[0] = noutput_items */
    }

    int
    source_code_ss_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
        const int *in = (const int *) input_items[0];
        int *out = (int *) output_items[0];

        // Do <+signal processing+>
        // Tell runtime system how many input items we consumed on
        // each input stream.
        consume_each (noutput_items);

        // Tell runtime system how many output items we produced.
        return noutput_items;
    }

  } /* namespace eme */
} /* namespace gr */

