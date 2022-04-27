import sys
import smbus2 as smbus
import time
import struct
bus = smbus.SMBus(1)
I2C_SLAVE_ADDR = 0x04

def get_data():
    data = bus.read_i2c_block_data(I2C_SLAVE_ADDR, 0, 4)
    #return get_float(data, 0) 
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
