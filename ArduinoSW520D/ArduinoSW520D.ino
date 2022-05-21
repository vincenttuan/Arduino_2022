void setup() {
  pinMode(3, INPUT);
  Serial.begin(9600);
}

void loop() {
  int val = digitalRead(3);
  Serial.println(val);
  delay(200);

}
