// 控制 LED 燈
// 輸入: 1 LED_PIN_13 ON,  LED_PIN_12 OFF
// 輸入: 2 LED_PIN_13 OFF, LED_PIN_12 ON
// 輸入: 3 LED_PIN_13 ON,  LED_PIN_12 ON
// 輸入: 4 LED_PIN_13 OFF, LED_PIN_12 OFF
// 輸入: 5 LED_PIN_13 與 LED_PIN_12 交替閃爍 (delay(200);)
const int LED_PIN_13 = 13;
const int LED_PIN_12 = 12;
int n = 0;

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN_13, OUTPUT);
  pinMode(LED_PIN_12, OUTPUT);
}

void loop() {
  if(Serial.available() > 0) {
    n = Serial.read();
  }
  runLED();
  delay(10);
}
void runLED() {
    switch(n) {
      case 49: // 1
        digitalWrite(LED_PIN_13, HIGH);
        digitalWrite(LED_PIN_12, LOW);
        break;  
      case 50: // 2
        digitalWrite(LED_PIN_13, LOW);
        digitalWrite(LED_PIN_12, HIGH);
        break;  
      case 51: // 3
        digitalWrite(LED_PIN_13, HIGH);
        digitalWrite(LED_PIN_12, HIGH);
        break;  
      case 52: // 4
        digitalWrite(LED_PIN_13, LOW);
        digitalWrite(LED_PIN_12, LOW);
        break;  
      case 53: // 5
        int value = !digitalRead(LED_PIN_13);
        digitalWrite(LED_PIN_13, value);
        digitalWrite(LED_PIN_12, !value);
        delay(200);
        break;
    }
}
