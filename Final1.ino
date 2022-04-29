#include <Wire.h>
#define SLAVE_ADDRESS 0x04
//Declaro las variables donde almacenar los datos de campo
float voltaje =13.65;
float corriente =-54.3;
float potencia =24.5;
byte number;
bool charcomplete = false;
//Declaro los arrays de datos
byte Datos_recibir;
byte Datos_enviar[4];

//Declaro las variables volatiles
volatile byte* voltajeFloatPtr;
volatile byte* corrienteFloatPtr;
volatile byte* potenciaFloatPtr;

void setup(){
  Serial.begin(9600);
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);

  Serial.println("PowerMeter is Ready!" );
  }

void requestEvent(){ //Cuando el maestro solicite datos llamo a esta funcion
//Descompongo dichas variables
if (charcomplete)
  { if (number==1) {
      voltajeFloatPtr=(byte*)&voltaje;  
      Datos_enviar[0]=voltajeFloatPtr[0];
      Datos_enviar[1]=voltajeFloatPtr[1];
      Datos_enviar[2]=voltajeFloatPtr[2];
      Datos_enviar[3]=voltajeFloatPtr[3];
  }
    else{
      if(number==2){
        corrienteFloatPtr=(byte*)&corriente;  
        Datos_enviar[0]=corrienteFloatPtr[0];
        Datos_enviar[1]=corrienteFloatPtr[1];
        Datos_enviar[2]=corrienteFloatPtr[2];
        Datos_enviar[3]=corrienteFloatPtr[3];
      
        } 
      else {
        potenciaFloatPtr=(byte*)&potencia;  
        Datos_enviar[0]=potenciaFloatPtr[0];
        Datos_enviar[1]=potenciaFloatPtr[1];
        Datos_enviar[2]=potenciaFloatPtr[2];
        Datos_enviar[3]=potenciaFloatPtr[3];
      
        }
    }
   }
  //envio el array de datos
  for(int i=0;i<4;i++){
    Serial.print(Datos_enviar[i]);
    }
  //Wire.write(1);
  Wire.write(Datos_enviar,4);
  }
  
  void receiveEvent(int datos_recibir){//cuando el maestro envie datos se llama a esta funcion
  
  //Iniciamos la recepción de los datos
  
  while (Wire.available()>0) {
    number = (byte)Wire.read();
    
    if (number != 0) {
      charcomplete = true;
   
    }
    else{
      break;
    }
    Serial.print("data received: ");
    Serial.println(number);
   }
  }
  
void loop() {
  
      
    
 }
  
