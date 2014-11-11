from gnuradio import gr
from gnuradio import blocks
import eme_swig as eme

class top_block(gr.top_block):

    def __init__(self):
        gr.top_block.__init__(self)

        #src = eme.packet_no_rs_source((0x61, 0x37, 0x30, 0x28, 0x09, 0x27, 0x61, 0x58, 0x26, 0x3, 0x49, 0x16), True) 
	src = eme.packet_no_rs_source((61, 37, 30, 28, 9, 27, 61, 58, 26, 3, 49, 16), True) 
	rs  = eme.encode_rs_int()
	interleave = eme.interleave_ii()
        dst = eme.packet_rs_sink()
        self.connect(src, rs)
	self.connect(rs, interleave)
	self.connect(interleave, dst)

if __name__ == '__main__':
    try:
        top_block().run()
    except KeyboardInterrupt:
        pass
