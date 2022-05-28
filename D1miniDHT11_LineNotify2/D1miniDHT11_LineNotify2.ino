#include <ESP8266WiFi.h>
#include <TridentTD_LineNotify.h>

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
  Serial.println(LINE.getVersion());
  LINE.setToken("TOKEN"); // 設定 Token
  String temp = "溫度:" + String(t) + "℃\n";
  String body = "體感:" + String(hic) + "℃\n";
  String humd = "濕度:" + String(h) + "％";
  LINE.notify("DHT11:\n" + temp + body + humd);
  delay(5000);
}
