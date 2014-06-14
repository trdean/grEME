/* -*- c++ -*- */
/*
 * Copyright 2001,2006 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#include <cstring>
#include <cassert>


class eme_packet_no_rs {
 public:
  unsigned int	data[12];	   

  // overload equality operator
  bool operator== (const eme_packet_no_rs &other) const {
    return std::memcmp (data, other.data, sizeof (data)) == 0;
  };

  bool operator!= (const eme_packet_no_rs &other) const {
    return !(std::memcmp (data, other.data, sizeof (data)) == 0);
  };
};

class eme_packet_rs_encoded {
 public:
  unsigned int	data[63];	   

  // overload equality operator
  bool operator== (const eme_packet_rs_encoded &other) const {
    return std::memcmp (data, other.data, sizeof (data)) == 0;
  };

  bool operator!= (const eme_packet_rs_encoded &other) const {
    return !(std::memcmp (data, other.data, sizeof (data)) == 0);
  };
};

class eme_packet_with_sync {
 public:
  unsigned int	data[189];	   

  // overload equality operator
  bool operator== (const eme_packet_with_sync &other) const {
    return std::memcmp (data, other.data, sizeof (data)) == 0;
  };

  bool operator!= (const eme_packet_with_sync &other) const {
    return !(std::memcmp (data, other.data, sizeof (data)) == 0);
  };
};
