#!/usr/bin/env python
# -*- coding: utf-8 -*-
# 
# Copyright 2014 <+YOU OR YOUR COMPANY+>.
# 
# This is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
# 
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this software; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
# 

from gnuradio import gr, gr_unittest
from gnuradio import blocks
import eme_swig as eme

class qa_graycode (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_01 (self):
        data = tuple([i for i in range(256)])
        src = blocks.vector_source_b(data, repeat=False, vlen=1)
        encode = eme.graycode(1)
        decode = eme.graycode(0)
        intblock = blocks.vector_sink_b()
        dst = blocks.vector_sink_b()

        self.tb.connect(src, encode)
        self.tb.connect(encode, intblock)
        self.tb.connect(encode,decode)
        self.tb.connect(decode, dst)

        self.tb.run ()
        
        enc_data = intblock.data()
        result = dst.data()

        #print(enc_data)
        #print(result)
        self.assertEqual(data, result)


if __name__ == '__main__':
    gr_unittest.run(qa_graycode, "qa_graycode.xml")
