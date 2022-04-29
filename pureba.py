from codecs import utf_16_be_decode
import struct

def formated_data(data):
    smsMessage = ""
    for i in data:
        smsMessage += chr(i)
    clean_data = struct.unpack('<f',smsMessage.encode())
    return clean_data

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

value = 24.5
data = [102,102,90,65]
test = struct.pack('f',value)
smsMessage = ""
""" for i in data:
    smsMessage += chr(i) """

ieee_number = '11000010100100000100110011001101'
ieee_num_function = get_ieee(data)
print('Este es el valor real',ieee_number)
print('Este es el del codigo de nosotros',ieee_num_function)
print('El intento',ieee745ToFloat(ieee_num_function))
print('La respuesta',ieee745ToFloat(ieee_number))


#clean_data = struct.unpack('f',test)

