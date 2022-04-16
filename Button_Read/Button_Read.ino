const int BUTTON_PIN_7 = 7;
const int BUTTON_PIN_6 = 6;

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN_7, INPUT); // 讀取模式
  pinMode(BUTTON_PIN_6, INPUT_PULLUP); // 讀取上拉電阻模式
}

void loop() {
  int value7 = digitalRead(BUTTON_PIN_7);
  Serial.print("PIN 7 = ");
  Serial.print(value7);
  int value6 = digitalRead(BUTTON_PIN_6);
  Serial.print(" PIN 6 = ");
  Serial.println(value6);
  
  delay(100); // 透過 delay 可讓 Arduino 穩定讀取
}
