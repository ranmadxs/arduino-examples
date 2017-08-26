from exception import SmbusDummyException

class SMBus(object):
    def __init__(self, bus=None, force=False):
        pass
    
    def write_i2c_block_data(self, i2c_addr, register, data):
        raise SmbusDummyException("write_i2c_block_data Smbus Dummy not implemented")