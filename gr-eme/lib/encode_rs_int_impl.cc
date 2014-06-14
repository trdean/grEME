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
#include "encode_rs_int_impl.h"
#include "reed-solomon/rs.h"

namespace gr {
  namespace eme {

   static void *rs; //pointer to encoder in Karn library

    encode_rs_int::sptr
    encode_rs_int::make()
    {
      return gnuradio::get_initial_sptr
        (new encode_rs_int_impl());
    }

    /*
     * The private constructor
     */
    encode_rs_int_impl::encode_rs_int_impl()
      : gr::block("encode_rs_int",
              gr::io_signature::make( 1, 1, sizeof(eme_packet_no_rs)),
              gr::io_signature::make( 1, 1, sizeof(eme_packet_rs_encoded)))
    { 
      rs = init_rs_int(6, 0x43, 3, 1, 51); 
    }
    

    /*
     * Our virtual destructor.
     */
    encode_rs_int_impl::~encode_rs_int_impl()
    {
      if(rs)
        free_rs_int(rs);
    }

    void
    encode_rs_int_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
        ninput_items_required[0] = noutput_items;
    }

    int
    encode_rs_int_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
        const eme_packet_no_rs *in = (const eme_packet_no_rs *) input_items[0];
        eme_packet_rs_encoded *out = (eme_packet_rs_encoded *) output_items[0];

        // Do <+signal processing+>
        int raw_parity[51];
        int tmp_data[12];
	for(int i = 0; i < noutput_items; i++) {

          // Reverse data order because ???
          for(int j=0; j<12; j++) {
            tmp_data[j]=in[i].data[11-j];
          }    
  
          encode_rs_int_work(rs, tmp_data, raw_parity); 

          // Move parity symbols and data into output - backwards because ???
          for (int j = 0; j < 51; j++) out[i].data[50-j] = raw_parity[j];
          for (int j = 0; j < 12; j++) out[i].data[j+51] = tmp_data[11-j];
        }
        // Tell runtime system how many input items we consumed on
        // each input stream.
        consume_each (noutput_items);

        // Tell runtime system how many output items we produced.
        return noutput_items;
    }

  } /* namespace eme */
} /* namespace gr */

