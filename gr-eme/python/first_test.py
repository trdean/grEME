from gnuradio import gr
from gnuradio import blocks
import eme_swig as eme

class top_block(gr.top_block):

    def __init__(self):
        gr.top_block.__init__(self)

        src = eme.packet_no_rs_source((0,1,2,3), True) 
        dst = eme.packet_no_rs_sink()
        self.connect(src, dst)

if __name__ == '__main__':
    try:
        top_block().run()
    except KeyboardInterrupt:
        pass
