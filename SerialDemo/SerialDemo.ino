void setup() {
  Serial.begin(9600); // 設定傳輸速率

}

void loop() {
  int x = random(100);
  Serial.println(x);
  delay(1000);
}
