#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // 0x27 or 0x3F

void setup() {
  // initialize the LCD
  lcd.begin();
  // Turn on the blacklight and print a message.
  lcd.backlight();
  //lcd.setBacklight(false); // 關閉背光
  // 清空 lcd
  lcd.clear();
  // 設定 cursor
  lcd.setCursor(5, 1); // 欄(0-15), 列(0, 1)
  // 印字
  lcd.print("Hello");
  // 設定 cursor
  lcd.setCursor(2, 0); // 欄(0-15), 列(0, 1)
  // 印字
  lcd.print("World");
}

void loop() {
  // 跑馬燈
  for(int i=5;i<=10;i++) {
      // 第二列一整列清空
      lcd.setCursor(0, 1); // 指向第二列
      lcd.print("                "); // 16 個空白
      
      lcd.setCursor(i, 1);
      lcd.print("Hello");
      delay(500);
  }
  for(int i=10;i>=5;i--) {
      // 第二列一整列清空
      lcd.setCursor(0, 1); // 指向第二列
      lcd.print("                "); // 16 個空白
      
      lcd.setCursor(i, 1);
      lcd.print("Hello");
      delay(500);
  }

}
