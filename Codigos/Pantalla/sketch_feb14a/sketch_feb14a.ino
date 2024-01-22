#include <LiquidCrystal_I2C.h>

cont uint8_t RS=15,EN=4,D4=26,D5=25,D6=33,D7=32;

//LiquidCrystal lcd(15, 4, 26, 25, 33,32);

LiquidCrystal lcd(RS,EN,D4,D5,D6,D7);

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("Hello World");

  // go to row 1 column 0, note that this is indexed at 0
  lcd.setCursor(0, 1);
  lcd.print ("LCD with ESP32");
}

void loop() {
  // put your main code here, to run repeatedly:

}
