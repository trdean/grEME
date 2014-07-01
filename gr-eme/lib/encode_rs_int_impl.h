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

#ifndef INCLUDED_EME_ENCODE_RS_INT_IMPL_H
#define INCLUDED_EME_ENCODE_RS_INT_IMPL_H

#include <eme/encode_rs_int.h>

namespace gr {
  namespace eme {

    class encode_rs_int_impl : public encode_rs_int
    {
     private:
	//None?
     public:
      encode_rs_int_impl();
      ~encode_rs_int_impl();

      // Where all the action really happens
      void forecast (int noutput_items, gr_vector_int &ninput_items_required);

      int general_work(int noutput_items,
		       gr_vector_int &ninput_items,
		       gr_vector_const_void_star &input_items,
		       gr_vector_void_star &output_items);

      void encode_rs_int_work(void *p, int *data, int *bb);
      void *init_rs_int(unsigned int symsize, unsigned int gfpoly, unsigned fcr,
                  unsigned prim, unsigned int nroots);
      void free_rs_int(void *p);

    };

   struct rs {
     unsigned int mm;   /* Bits per symbol */
     unsigned int nn;   /* Symbols per block (= (1<<mm)-1) */
     int *alpha_to;      /* log lookup table */
     int *index_of;      /* Antilog lookup table */
     int *genpoly;       /* Generator polynomial */
     unsigned int nroots;     /* Number of generator roots = number of parity symbols */
     unsigned int fcr;        /* First consecutive root, index form */
     unsigned int prim;       /* Primitive element, index form */
     unsigned int iprim;      /* prim-th root of 1, index form */
   };

   static inline int modnn(struct rs *rs, int x) {
     while (x >= rs->nn) {
       x -= rs->nn;
       x = (x >> rs->mm) + (x & rs->nn);
     }
     return x;
   }

  } // namespace eme
} // namespace gr

#define MODNN(x) modnn(rs,x)

#define MM (rs->mm)
#define NN (rs->nn)
#define ALPHA_TO (rs->alpha_to)
#define INDEX_OF (rs->index_of)
#define GENPOLY (rs->genpoly)
#define NROOTS (rs->nroots)
#define FCR (rs->fcr)
#define PRIM (rs->prim)
#define IPRIM (rs->iprim)
#define A0 (NN)

#endif /* INCLUDED_EME_ENCODE_RS_INT_IMPL_H */

