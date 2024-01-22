#include <LiquidCrystal.h>

//Define los pines utilizados del ESP32 de acuerdo a la sintaxis de la libreria
const uint8_t RS=15,EN=4,D4=26,D5=25,D6=33,D7=32; 

LiquidCrystal lcd(RS,EN,D4,D5,D6,D7); //Define el objeto "lcd"

void setup() {
  lcd.begin(16,2); //Configurar LCD de tamaño 16x2
  lcd.setCursor(4,0); //Ubicar cursor en la columna 4 fila 0
  lcd.print("uC ESP32"); //Imprimir mensaje en la LCD
  for(uint8_t i=0;i<4;i++){
    delay(500);
    lcd.noDisplay();
    delay(500);
    lcd.display();
  }
  delay(1000);
  for(uint8_t i=0;i<4;i++){
    lcd.scrollDisplayRight();
    delay(500);
  }
  for(uint8_t i=0;i<8;i++){
    lcd.scrollDisplayLeft();
    delay(500);
  }
  for(uint8_t i=0;i<4;i++){
    lcd.scrollDisplayRight();
    delay(500);
  }
  delay(1000);
}

void loop() {
  lcd.setCursor(0,1);
  lcd.print(millis()/1000); //Imprimir el número de segundos desde el reset del ESP32
}
