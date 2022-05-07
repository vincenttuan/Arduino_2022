/*
 * LCD 顯示
 * ----------------
 * Card ID:
 * Open / Closed
 * ----------------
 * 
*/
#include <SPI.h>
#include <RFID.h>
#include <Timer.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

#define SERVO_PIN 6
#define RST_PIN 9
#define SDA_PIN 10
#define BUZEER_PIN 8

Timer t;
LiquidCrystal_I2C lcd(0x27, 16, 2); // 0x27 or 0x3F
RFID rfid (SDA_PIN, RST_PIN);
Servo myServo;

int initDegree = 90; // 初始角度
int maxDegree = 0; // 最大角度
String cardId = "";

void setup() {
  Serial.begin(9600);
  delay(2);
  SPI.begin();
  rfid.init();
  lcd.begin();
  lcd.backlight();
  lcd.clear();
  myServo.attach(SERVO_PIN); // 設定 Servo 訊號腳位
  myServo.write(initDegree); // 設定初始角度位置
  
  Serial.println("Ready");
  lcd.setCursor(0, 1);
  lcd.print("Closed");
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
    openTheDoor();
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

void openTheDoor() {
  // 啟動 open 柵欄中 ...
  lcd.setCursor(0, 1);
  lcd.print("Open  ");
  for(int i=initDegree;i>=maxDegree;i-=5) {
    myServo.write(i);
    delay(100);
  }
  delay(5000); // 柵欄全部開啟
  // 關閉 close 柵欄中 ...
  for(int i=maxDegree;i<=initDegree;i+=5) {
    myServo.write(i);
    delay(100);
  }
  lcd.setCursor(0, 1);
  lcd.print("Closed");
}
