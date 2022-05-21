#include <ESP8266WiFi.h>
#define WIFI_SSID "Gjun207"
#define WIFI_PASSWORD "Gjun@3474878"

void setup() {
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting ");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);  
  }
  Serial.println();
  Serial.print("Connected OK! IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:

}
