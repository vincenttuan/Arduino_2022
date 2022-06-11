#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Timer.h>
#define LED_PIN 2  // D1mini D4 腳位

WiFiServer server(80); // 建立 WebServer 與 port
Timer t;

String led_off_url = "http://www.clker.com/cliparts/6/l/f/V/f/H/green-led-off-md.png";
String led_on_url = "http://www.clker.com/cliparts/1/n/o/R/x/K/greenled-md.png";
String led_url = led_off_url;
String next_led_url = "";

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
  client.println("<h1>Hello D1 mini</h1>");
  client.print("<img onclick='window.location.href=\"" + next_led_url + "\";' border=0 src='" + led_url + "' />");
  client.println("</html>");
}

void setup() {
  Serial.begin(9600);
  delay(1);
  pinMode(LED_PIN, OUTPUT);
  
  connectWifi();
  startWebServer();
  t.every(100, run_web);
}

void loop() {
  t.update();
}
