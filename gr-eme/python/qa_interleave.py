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

class qa_interleave (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_01 (self):
        data = tuple([i for i in range(63)])
        src = blocks.vector_source_b (data,repeat=False,vlen=63)
        interleaver = eme.interleave(1)
        deinterleaver = eme.interleave(0)
        dst = blocks.vector_sink_b(vlen=63)
        self.tb.connect(src, interleaver)
        #self.tb.connect(interleaver, dst)
        self.tb.connect(interleaver, deinterleaver)
        self.tb.connect(deinterleaver, dst)
        
        self.tb.run ()

        result = dst.data()
        self.assertEqual(data, result)

if __name__ == '__main__':
    gr_unittest.run(qa_interleave, "qa_interleave.xml")
