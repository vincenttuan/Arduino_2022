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

void checkLed() {
  int value = firebase.getInt("led");
  digitalWrite(LED_PIN, value);
}

void uploadDHT11() {
  float h = dht.readHumidity();
  // 攝式溫度
  float t = dht.readTemperature();
  // 華式溫度
  float f = dht.readTemperature(true);
  // 若讀取失敗則重讀
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  // 華式體感溫度
  float hif = dht.computeHeatIndex(f, h);
  // 攝式體感溫度
  float hic = dht.computeHeatIndex(t, h, false);
  // 印出資料
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
  // 上傳到 Firebase
  firebase.setFloat("humi", h);
  firebase.setFloat("temp", t);
  firebase.setFloat("temp_hic", hic);
  
}

void setup() {
  Serial.begin(9600);
  delay(1);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  connectWifi();
  t.every(1000, checkLed);
  t.every(2000, uploadDHT11);
}

void loop() {
  t.update();
}

void test() {

  firebase.setInt("led", 1);
  delay(1000);
  firebase.setInt("led", 0);
  delay(1000);
  firebase.pushInt("logs", random());
  delay(1000);
  float humi = firebase.getFloat("humi");
  Serial.print("humi = ");
  Serial.println(humi);
  delay(1000);
}
