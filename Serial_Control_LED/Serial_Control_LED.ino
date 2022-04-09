// 控制 LED 燈
// 輸入: 0 LED_PIN_13 關燈
// 輸入: 1 LED_PIN_13 開燈
const int LED_PIN_13 = 13;
void setup() {
  pinMode(LED_PIN_13, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if(Serial.available() > 0) {
    int n = Serial.read();
    Serial.print("arduino: ");
    Serial.println(n);
    switch(n) {
      case 48: // '0'
        digitalWrite(LED_PIN_13, LOW);
        break;
      case 49: // '1'
        digitalWrite(LED_PIN_13, HIGH);
        break;  
    }  
  }

}
