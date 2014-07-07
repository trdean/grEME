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


#ifndef INCLUDED_EME_PACKET_RS_SOURCE_H
#define INCLUDED_EME_PACKET_RS_SOURCE_H

#include <eme/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace eme {

    /*!
     * \brief <+description of block+>
     * \ingroup eme
     *
     */
    class EME_API packet_rs_source : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<packet_rs_source> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of eme::packet_rs_source.
       *
       * To avoid accidental use of raw pointers, eme::packet_rs_source's
       * constructor is in a private implementation
       * class. eme::packet_rs_source::make is the public interface for
       * creating new instances.
       */
      static sptr make(std::vector <int> data, bool repeat);
    };

  } // namespace eme
} // namespace gr

#endif /* INCLUDED_EME_PACKET_RS_SOURCE_H */

