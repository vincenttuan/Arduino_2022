#include <ESP8266Firebase.h>
#include <ESP8266WiFi.h>
#include <Timer.h>
#include "DHT.h"

#define LED_PIN 2  // D1mini D4 腳位
#define DHT_PIN 4  // D1mini D2 腳位
#define DHTTYPE DHT11

#define _SSID "Gjun207"
#define _PASSWORD "Gjun@3474878"
#define PROJECT_ID ""

Firebase firebase(PROJECT_ID);
DHT dht(DHT_PIN, DHTTYPE);
Timer t;

void connectWifi() {
  WiFi.mode(WIFI_STA); // 預設就是 WIFI_STA. 以工作站（Station）模式啟動
  WiFi.disconnect(); // 先關閉
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to: ");
  Serial.println(_SSID);
  WiFi.begin(_SSID, _PASSWORD); // 重啟連線設定

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("-");
  }

  Serial.println("");
  Serial.println("WiFi Connected");

  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  digitalWrite(LED_BUILTIN, LOW);
  
}

void setup() {
  Serial.begin(9600);
  delay(1);
  pinMode(LED_BUILTIN, OUTPUT);
  connectWifi();
  
}

void loop() {
  
}
