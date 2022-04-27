from smbus2 import SMBus
import time
import sys

def main(args):
    direccion = 31
    while True:
        with SMBus(1) as bus:
            comando = input("Ingresar comando: ")
            comandoString = comando
            comando = comando + "\n"
            comando = comando.encode()
            print(f"Comando {comandoString} enviado")
            bus.write_i2c_block_data(direccion, 0, comando) 
            time.sleep(0.5)
            while True:
                try:
                    data=bus.read_i2c_block_data(direccion,0,16)
                    print("Respuesta:")
                    print(data)
                except:
                    break
        time.sleep(0.1)

if __name__ == '__main__':
    try:
        main(sys.argv)
    except KeyboardInterrupt:
        print("program was stopped manually")
        input()