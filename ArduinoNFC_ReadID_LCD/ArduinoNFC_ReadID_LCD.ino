#include <SPI.h>
#include <RFID.h>
#include <Timer.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define RST_PIN 9
#define SDA_PIN 10
#define BUZEER_PIN 8

Timer t;
LiquidCrystal_I2C lcd(0x27, 16, 2); // 0x27 or 0x3F
RFID rfid (SDA_PIN, RST_PIN);
String cardId = "";

void setup() {
  Serial.begin(9600);
  delay(2);
  SPI.begin();
  rfid.init();
  lcd.begin();
  lcd.backlight();
  lcd.clear();
  Serial.println("Ready");
  t.every(10, detectCard);
}


void loop() {
  t.update();
  delay(10);
}

void detectCard() {
  if (rfid.isCard() && rfid.readCardSerial()) {
    tone(BUZEER_PIN, 976, 200)  ;
    Serial.println("Card found");
    cardId = "";
    for (int i = 0; i < 5; i++) {
      cardId += String(rfid.serNum[i], HEX);
    }
    showID();
    Serial.print("CardId: ");
    Serial.println(cardId);
    Serial.println();
    delay(500);
  }
  rfid.halt(); // 進入休眠, 等待下次的激活
}

void showID() {
  lcd.setCursor(0, 0);
  lcd.print("                "); // 16 個空白
  lcd.setCursor(0, 0);
  lcd.print(cardId);
}
