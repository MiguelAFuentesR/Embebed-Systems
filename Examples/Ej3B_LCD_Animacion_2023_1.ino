#include <LiquidCrystal.h>

//Define los pines utilizados del ESP32 de acuerdo a la sintaxis de la libreria
const uint8_t RS=15,EN=4,D4=26,D5=25,D6=33,D7=32; 

LiquidCrystal lcd(RS,EN,D4,D5,D6,D7); //Define el objeto "lcd"

//Genera tabla de 8 bytes por cada caracter a crear
byte corazon[8]={0x00,0x0A,0x1F,0x1F,0x1F,0x0E,0x04,0x00};
byte smile[8]={0x00,0x00,0x0A,0x00,0x00,0x11,0x0E,0x00};
byte brazoArriba[8]={0x04,0x0A,0x04,0x04,0x0E,0x15,0x04,0x0A};
byte brazoAbajo[8]={0x04,0x0A,0x04,0x15,0x0E,0x04,0x04,0x0A};

void setup() {
  lcd.begin(16,2); //Configurar LCD de tamaño 16x2
  lcd.createChar(0,corazon);
  lcd.createChar(1,smile);
  lcd.createChar(2,brazoArriba);
  lcd.createChar(3,brazoAbajo);
  lcd.setCursor(0,0);
  lcd.write(byte(0));
  lcd.print(" uC ESP32 ");
  lcd.write(1);
  delay(2000);
}

void loop() {
  lcd.setCursor(4,1);
  lcd.write(2);
  delay(500);
  lcd.setCursor(4,1);
  lcd.write(3);
  delay(500);
}
