import sys
from smbus2 import SMBus, i2c_msg
import time
import struct
import smbus2
I2C_SLAVE_ADDR = 0x04

def get_data():
    with SMBus(l) as bus:
        msg = i2c_msg.read(I2C_SLAVE_ADDR, 4)
        bus.i2c_rdwr(msg)
        data1 = list(msg)
        data = struct.unpack('f', data1[0:4])
    return data

def get_float(data, index):
    bytes = data[4*index:(index+1)*4]
    return struct.unpack('f', "".join(map(chr, bytes)))[0]

def main():
    print("1: Voltaje \n2: Corriente\n3: Potencia")
    number = input("Digite el valor asociado al comando: ")
    bus.write_byte(I2C_SLAVE_ADDR, int(number))
    print("\n")
    print("Arduino answer to RPI: ", get_data())
    print("\n")
    time.sleep(1)

try:
    while True:
        main()
except KeyboardInterrupt:
    print("\n")
    print("Exiting...")
    sys.exit(0)
