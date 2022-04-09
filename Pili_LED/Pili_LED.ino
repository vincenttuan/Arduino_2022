const int LED_PIN_8 = 8;
const int LED_PIN_9 = 9;
const int LED_PIN_10 = 10;
const int LED_PIN_11 = 11;

void setup() {
  // 初始腳位
  pinMode(LED_PIN_8, OUTPUT);
  pinMode(LED_PIN_9, OUTPUT);
  pinMode(LED_PIN_10, OUTPUT);
  pinMode(LED_PIN_11, OUTPUT);
}

void loop() {
  digitalWrite(LED_PIN_8, HIGH);
  digitalWrite(LED_PIN_9, LOW);
  digitalWrite(LED_PIN_10, LOW);
  digitalWrite(LED_PIN_11, LOW);
  delay(200);
  digitalWrite(LED_PIN_8, LOW);
  digitalWrite(LED_PIN_9, HIGH);
  digitalWrite(LED_PIN_10, LOW);
  digitalWrite(LED_PIN_11, LOW);
  delay(200);
  digitalWrite(LED_PIN_8, LOW);
  digitalWrite(LED_PIN_9, LOW);
  digitalWrite(LED_PIN_10, HIGH);
  digitalWrite(LED_PIN_11, LOW);
  delay(200);
  digitalWrite(LED_PIN_8, LOW);
  digitalWrite(LED_PIN_9, LOW);
  digitalWrite(LED_PIN_10, LOW);
  digitalWrite(LED_PIN_11, HIGH);
  delay(200);
  //-------------------------------
  digitalWrite(LED_PIN_8, LOW);
  digitalWrite(LED_PIN_9, LOW);
  digitalWrite(LED_PIN_10, HIGH);
  digitalWrite(LED_PIN_11, LOW);
  delay(200);
  digitalWrite(LED_PIN_8, LOW);
  digitalWrite(LED_PIN_9, HIGH);
  digitalWrite(LED_PIN_10, LOW);
  digitalWrite(LED_PIN_11, LOW);
  delay(200);
}
