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
#define REMOTEXY_MODE__ESP32CORE_BLUETOOTH
#include <BluetoothSerial.h>

#include <RemoteXY.h>

// RemoteXY connection settings
#define REMOTEXY_BLUETOOTH_NAME "RemoteXY"


// RemoteXY configurate
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =   // 28 bytes
{ 255, 1, 0, 1, 0, 21, 0, 16, 126, 1, 70, 16, 23, 17, 18, 18, 26, 37, 0, 1,
  0, 23, 50, 19, 19, 2, 31, 0
};

// this structure defines all the variables and events of your control interface
struct {

  // input variables
  uint8_t button_1; // =1 if button pressed, else =0

  // output variables
  uint8_t led_1; // led state 0 .. 1

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

  pinMode(LEDB, OUTPUT);
  pinMode(SW, INPUT);
  RemoteXY_Init ();
  Serial.begin(115200);
  // TODO you setup code

}

void loop()
{
  RemoteXY_Handler ();
  Serial.print (RemoteXY.led_1);
  Serial.print(" ");
  Serial.print (RemoteXY.button_1);
  Serial.print(" ");

  if (RemoteXY.button_1 == 1) {
    digitalWrite(LEDB, HIGH);
    RemoteXY.led_1 = HIGH;
  } else {
    digitalWrite(LEDB, LOW);
    RemoteXY.led_1 = LOW;
  }

}
