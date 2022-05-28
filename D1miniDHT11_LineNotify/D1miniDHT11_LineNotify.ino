#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

WiFiClientSecure secure_client;

// 接線方式
// DATA 接 D4 -> 2
#include "DHT.h"
#define DHTPIN 2 
#define DHTTYPE DHT11

// 初始化 DHT sensor.
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println("DHT11 test!");
  dht.begin();

  // 連接 WiFi
  WiFi.begin("Gjun207", "Gjun@3474878");
  // 等待 WiFi 的連接(每隔500ms檢查一次)
  while(WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  // 連線建立成功, 取得 IP
  Serial.println(WiFi.localIP());
}

void loop() {
  delay(2000);
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
  // 上傳到 LineNotify
  if(secure_client.connect("notify-api.line.me", 443)) {
    Serial.println("Send to Line");
    String data = "message=" + String("\n我的溫溼度:\n");
    // HTTP lint line (Part 1)
    secure_client.println("POST /api/notify HTTP/1.1");
    // HTTP header area (Part 2)
    secure_client.println("Host: notify-api.line.me");
    secure_client.println("Authorization: Bearer <TOKEN>");
    secure_client.println("Content-type: application/x-www-form-urlencoded");
    secure_client.print("Content-Length: ");
    secure_client.println(data.length());
    // HTTP 分隔 line (Part 3)
    secure_client.println();
    // HTTP Body area (Part 4)
    secure_client.println(data);
    // Close
    secure_client.stop();
    Serial.println("Send to Line OK");
  } else {
    Serial.println("Send to Line Error");
  }
  delay(5000);
}
