#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();
}

void loop() {
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Hello World ! ");
  delay(1000);
}