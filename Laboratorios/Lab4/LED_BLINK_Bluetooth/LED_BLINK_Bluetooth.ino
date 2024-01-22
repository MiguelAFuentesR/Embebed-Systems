/*
Sensores : 
1. humedad relativa (valor en %)
2. presión atmosférica (valor en mbar)

3. temperatura (valor en °C)
4. velocidad del viento (valor en m/s) 
5. cantidad de lluvia (valor en mm/h)
*/


//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// RemoteXY select connection mode and include library 
#define REMOTEXY_MODE__ESP32CORE_BLE
#include <BLEDevice.h>

#include <RemoteXY.h>

// RemoteXY connection settings 
#define REMOTEXY_BLUETOOTH_NAME "Lab4 Sistemas Embebidos"


// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =   // 558 bytes
  { 255,0,0,24,2,39,2,16,30,4,131,5,89,41,21,6,1,12,88,83,
  101,110,115,111,114,32,52,0,131,4,89,12,21,6,2,12,8,83,101,110,
  115,111,114,32,49,0,129,0,47,0,52,4,0,1,69,115,116,97,99,105,
  195,179,110,32,77,101,116,101,111,114,111,108,195,179,103,105,99,97,32,85,
  68,0,66,0,38,9,9,21,4,2,26,129,0,4,11,19,5,2,146,82,
  101,108,97,116,105,118,97,0,129,0,74,15,4,5,2,24,37,0,67,1,
  49,15,20,5,4,24,26,101,129,0,249,6,22,5,2,146,72,117,109,101,
  100,97,100,0,129,0,253,8,19,5,4,64,80,114,101,115,105,195,179,110,
  32,0,71,56,29,8,25,25,3,0,73,95,135,0,0,0,0,0,0,200,
  66,0,0,160,65,0,0,32,65,0,0,0,64,39,0,129,0,246,6,29,
  5,5,106,84,101,109,112,101,114,97,116,117,114,97,0,66,131,19,13,36,
  13,5,2,24,129,0,73,15,6,5,5,8,194,176,32,67,0,129,0,249,
  7,23,5,3,238,86,101,108,111,99,105,100,97,100,0,129,0,3,12,23,
  5,3,238,100,101,108,32,118,105,101,110,116,111,0,72,4,30,9,20,20,
  2,95,26,189,39,0,0,0,0,0,0,200,66,0,0,0,0,67,1,59,
  14,13,6,2,24,26,101,131,4,89,50,21,6,3,12,88,83,101,110,115,
  111,114,32,53,0,129,0,65,15,12,5,4,24,109,98,97,114,0,67,1,
  60,14,13,6,5,24,26,101,67,1,58,13,13,6,3,24,26,101,67,1,
  54,16,13,6,1,24,26,101,129,0,72,14,6,5,3,8,109,47,115,0,
  129,0,254,7,23,5,1,6,67,97,110,116,105,100,97,100,32,100,101,0,
  129,0,10,11,14,5,1,6,76,108,117,118,105,97,0,66,1,29,12,21,
  16,1,193,26,129,0,66,17,8,5,1,8,109,109,47,104,0,131,4,89,
  21,21,6,4,12,8,83,101,110,115,111,114,32,50,0,131,4,89,31,21,
  6,5,12,8,83,101,110,115,111,114,32,51,0,129,0,1,13,28,5,4,
  64,65,116,109,111,115,102,195,169,114,105,99,97,0,68,17,237,33,100,28,
  2,8,36,129,0,247,27,22,5,0,255,72,105,115,116,111,114,105,99,111,
  58,0,68,17,244,33,93,28,4,8,36,68,17,238,33,98,28,5,8,36,
  68,17,238,33,98,28,1,8,36,68,17,237,33,99,28,3,8,36 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // output variables
  int8_t Barra_Presion; // =0..100 level position 
  char Valor_Presion[101];  // string UTF8 end zero 
  float Barra_VelocidadViento;  // from 0 to 100 
  int8_t Barra_Temperatura; // =0..100 level position 
  float Barra_Humedad;  // from 0 to 100 
  char Valor_Humedad[101];  // string UTF8 end zero 
  char Valor_Temperatura[101];  // string UTF8 end zero 
  char Valor_Viento[101];  // string UTF8 end zero 
  char Valor_Lluvia[101];  // string UTF8 end zero 
  int8_t Barra_Lluvia; // =0..100 level position 
  float Graf_Humedad;
  float Graf_Atmosfera;
  float Graf_Temperatura;
  float Graf_LLuvia;
  float Graf_Viento;

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////


#define LEDB 2 //Define GPIO2
#define SW 14//Define GPIO14


void setup() 
{
  RemoteXY_Init (); 
  Serial.begin(115200);
  
  // TODO you setup code
  
}

void loop() 
{ 
  
  RemoteXY_Handler ();
  
  
  // TODO you loop code
  // use the RemoteXY structure for data transfer
  // do not call delay() 


}
