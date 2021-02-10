#include <LiquidCrystal_I2C.h>
#define LiquidCrystal_I2C lcd(0x27, 16, 2);

void setupEcran() {
  lcd.init();
}

void loopEcran() {
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Hello World ! ");
  delay(1000);
}
