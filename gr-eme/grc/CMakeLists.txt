# Copyright 2011 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
install(FILES
    eme_source_code_ss.xml
    eme_encode_rs_int.xml
    eme_decode_rs_int.xml
    eme_interleave_ii.xml
    eme_graycode_ii.xml
    eme_fsk_modulate_if.xml
    eme_add_sync_ii.xml
    eme_deinterleave_ii.xml
    eme_ungraycode_ii.xml
    eme_packet_no_rs_source.xml
    eme_packet_rs_source.xml
    eme_packet_no_rs_sink.xml
    eme_packet_rs_sink.xml DESTINATION share/gnuradio/grc/blocks
)
