// Arduino 模擬多執行緒
// BH 1750, LCD, BT_APP, LED
#include <Timer.h>
#include <Wire.h>
#include <BH1750.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#define LED_PIN 12

BH1750 lightMeter;
float lux = 0;
LiquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial BT(10, 11);
char val; // BT 儲存接收到的資料

// 宣告 Timer 物件
Timer t;

void setup() {
  Serial.begin(9600);
  delay(2);
  
  Wire.begin();
  lightMeter.begin();
  
  lcd.begin();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("lux:");

  pinMode(LED_PIN, OUTPUT);
  
  BT.begin(9600);
  
  t.every(500, bt1750);
  t.every(1000, lcd_print);
  t.every(10, bt_app_led);

  Serial.println("Ready ...");
}

void loop() {
  t.update();
  delay(10);
}

void bt1750() {
  lux = lightMeter.readLightLevel();
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx");
}

void lcd_print() {
  lcd.setCursor(4, 0); // 指向第一列
  lcd.print("            "); // 14 個空白
  lcd.setCursor(4, 0); // 指向第一列
  lcd.print(lux);
}

void bt_app_led() {
  // 從主控台傳指令給 BT
  if(Serial.available()) {
    val = Serial.read(); // 接到指令
    BT.print(val); // 將指令給 BT
  }

  // BT 回應資料給主控台
  if(BT.available()) {
    val = BT.read(); // 讀取 BT 的回應資料
    Serial.print(val); // 將回應資料給主控台
    if(val == '1') {
      digitalWrite(LED_PIN, HIGH);  
    } else if(val == '0') {
      digitalWrite(LED_PIN, LOW);  
    }
  }
}
