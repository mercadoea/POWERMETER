#include <Robojax_WCS.h>
#include <Wire.h>
#define SLAVE_ADDRESS 0x04
//Declaro las variables donde almacenar los datos de campo
float voltaje;
float corriente;
float potencia;
byte number;
bool charcomplete = false;
//Declaro los arrays de datos
byte Datos_recibir;
byte Datos_enviar[4];
//Declaro los pines asociados al sensor de corriente
float medicion;
float currentSensorVal;
#define MODEL 12 //see list above
#define SENSOR_PIN A0 //pin for reading sensor
#define SENSOR_VCC_PIN 8 //pin for powring up the sensor
#define ZERO_CURRENT_LED_PIN 2 //zero current LED pin

#define ZERO_CURRENT_WAIT_TIME 5000 //wait for 5 seconds to allow zero current measurement
#define CORRECTION_VLALUE 164 //mA
#define MEASUREMENT_ITERATION 20
#define VOLTAGE_REFERENCE  5000.0 //5000mv is for 5V
#define BIT_RESOLUTION 10
#define DEBUT_ONCE true
Robojax_WCS sensor(
          MODEL, SENSOR_PIN, SENSOR_VCC_PIN, 
          ZERO_CURRENT_WAIT_TIME, ZERO_CURRENT_LED_PIN,
          CORRECTION_VLALUE, MEASUREMENT_ITERATION, VOLTAGE_REFERENCE,
          BIT_RESOLUTION, DEBUT_ONCE           
          );
//Declaro los pines asociados al sensor de voltaje
const int voltageSensorPin = A1;          // sensor pin
float vIn;                                // measured voltage (3.3V = max. 16.5V, 5V = max 25V)
float vOut;
float voltageSensorVal;                   // value on pin A3 (0 - 1023)
const float factor = 10.2;               // reduction factor of the Voltage Sensor shield

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
  sensor.start();
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
   voltageSensorVal = analogRead(voltageSensorPin);    // read the current sensor value (0 - 1023) 
   vOut = (voltageSensorVal/1024 )*5;             // convert the value to the real voltage on the analog pin
   voltaje =  vOut * factor;
   corriente = sensor.getCurrent();
   potencia = voltaje*corriente;  
    
 }
  
