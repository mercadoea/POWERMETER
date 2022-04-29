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

def formated_data(data):
    smsMessage = ""
    for i in data:
        smsMessage += chr(i)
    clean_data = struct.unpack('<f',smsMessage.encode())
    return clean_data


def get_float(data, index):
    bytes = data[4*index:(index+1)*4]
    return struct.unpack('f', "".join(map(chr, bytes)))[0]

def main():
    print("1: Voltaje \n2: Corriente\n3: Potencia")
    number = input("Digite el valor asociado al comando: ")
    bus.write_byte(I2C_SLAVE_ADDR, int(number))
    print("\n")
    print("Arduino answer to RPI: ", get_data())
    data = get_data()
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
