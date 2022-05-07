#include <SPI.h>
#include <RFID.h>
#define RST_PIN 9
#define SDA_PIN 10
#define BUZEER_PIN 8

RFID rfid (SDA_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  delay(2);
  SPI.begin();
  rfid.init();
  Serial.println("Ready");

}

void loop() {
  Serial.print(rfid.isCard());
  Serial.print(", ");
  Serial.println(rfid.readCardSerial());
  
  rfid.halt(); // 進入休眠, 等待下次的激活
  delay(1000);

}
