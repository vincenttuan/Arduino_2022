void setup() {
  Serial.begin(9600);

}

void loop() {
  int begin = 0;
  int end = 10;
  int value = random(begin, end); // begin <= value < end
  Serial.println(value);
  delay(500);
}
