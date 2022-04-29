import sys
from smbus2 import SMBus, i2c_msg
import time
import struct 
import smbus2

bus = smbus2.SMBus(1)
I2C_SLAVE_ADDR = 0x04

def get_data():
    with SMBus(1) as bus:
        msg = i2c_msg.read(I2C_SLAVE_ADDR, 4)
        bus.i2c_rdwr(msg)
        data1 = list(msg)
    return data1

def get_ieee(data):
    ieee = ''
    data.reverse()
    for d in data:
        byte = str(format(d,'b'))
        if(len(byte)<8):
            byte = '0'*(8-len(byte)) + byte
        ieee+= byte    
    return ieee

def ieee745ToFloat(N): # ieee-745 bits (max 32 bit)
    a = int(N[0])        # sign,     1 bit
    b = int(N[1:9],2)    # exponent, 8 bits
    c = int("1"+N[9:], 2)# fraction, len(N)-9 bits

    return (-1)**a * c /( 1<<( len(N)-9 - (b-127) ))


def main():
    print("1: Voltaje \n2: Corriente\n3: Potencia")
    number = input("Digite el valor asociado al comando: ")
    bus.write_byte(I2C_SLAVE_ADDR, int(number))
    print("\n")
    print("Arduino answer to RPI: ", get_data())
    ieee_data = get_ieee(get_data())
    data = ieee745ToFloat(ieee_data)
    print("\n")
    print(f'Arduino ansewer: {formated_data(data)}')
    time.sleep(1)

try:
    while True:
        main()
except KeyboardInterrupt:
    print("\n")
    print("Exiting...")
    sys.exit(0)
