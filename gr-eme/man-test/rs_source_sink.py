#!/usr/bin/env python

from gnuradio import gr
from gnuradio import blocks
import eme_swig as eme

class top_block(gr.top_block):

	def __init__(selt):
		gr.top_block.__init__(self)

		source = 
		sink = 

		self.connect (source, sink)

if __name__ == '__main__':
	try:
		my_top_block().run()
	
	except KeyboardInterrupt:
		pass

