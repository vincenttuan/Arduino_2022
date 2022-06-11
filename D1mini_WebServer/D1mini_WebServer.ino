#include "DHT.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Timer.h>
#define LED_PIN 2  // D1mini D4 腳位
#define DHT_PIN 4  // D1mini D2 腳位
#define DHTTYPE DHT11

WiFiServer server(80); // 建立 WebServer 與 port
Timer t;

// 初始化 DHT sensor.
DHT dht(DHT_PIN, DHTTYPE);

String led_off_url = "http://www.clker.com/cliparts/6/l/f/V/f/H/green-led-off-md.png";
String led_on_url = "http://www.clker.com/cliparts/1/n/o/R/x/K/greenled-md.png";
String led_url = led_off_url;
String next_led_url = "";

float humi = 0.0;
float temp = 0.0;
float temp_hic = 0.0;

void connectWifi() {
  WiFi.begin("Gjun207", "Gjun@3474878");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");  
  }
  Serial.println(WiFi.localIP()); // 印出 IP
}

void startWebServer() {
  server.begin();  
  Serial.println();
  Serial.println("Start Web Server");
  Serial.println("========================");
  Serial.print("http://");
  Serial.println(WiFi.localIP());
  Serial.println();
}

void run_web() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if(!client) {
    return;  
  }
  Serial.println("New client");
  
  // Wait util the client sends some data
  while(!client.available()) {
    delay(1);  
  }
  
  // Read the first line of th request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  // Match the request
  int value = LOW;
  if(request.indexOf("/led=1") != -1) {
    digitalWrite(LED_PIN, HIGH);
    value = HIGH;
    led_url = led_on_url;
    next_led_url = "/led=0";
  } else if(request.indexOf("/led=0") != -1) {
    digitalWrite(LED_PIN, LOW);
    value = LOW;
    led_url = led_off_url;
    next_led_url = "/led=1";
  } 
  
  // Return a response
  // HTTP Spec.
  client.println("HTTP/1.1 200 OK"); // init line
  client.println("Content-Type: text/html;charset=utf-8"); // headers
  client.println(); // blank (勿忘我)
  client.println("<html>");
  // 每數秒鐘更新網頁一次
  client.println("<head><script>");
  client.println("setTimeout(function(){window.location.reload(1);}, 3000)");
  client.println("</script></head>");
  client.println("<h1>Hello D1 mini</h1>");
  client.print("<img onclick='window.location.href=\"" + next_led_url + "\";' border=0 src='" + led_url + "' />");
  client.print("<p>");
  client.print("<div style='font-size: 100px'>");
  client.print("濕度: ");
  client.print(humi);
  client.print(" %");
  client.print("</div>");
  client.print("<div style='font-size: 100px'>");
  client.print("溫度: ");
  client.print(temp);
  client.print(" °C");
  client.print("</div>");
  client.print("<div style='font-size: 100px'>");
  client.print("體感: ");
  client.print(temp_hic);
  client.print(" °C");
  client.print("</div>");
  
  client.println("</html>");
}



void run_dht11() {
  float h = dht.readHumidity();
  humi = h;
  // 攝式溫度
  float t = dht.readTemperature();
  temp = t;
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
  temp_hic = hic;
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
}

void setup() {
  Serial.begin(9600);
  delay(1);
  pinMode(LED_PIN, OUTPUT);
  dht.begin();
  connectWifi();
  startWebServer();
  t.every(100, run_web);
  t.every(2000, run_dht11);
}

void loop() {
  t.update();
}
