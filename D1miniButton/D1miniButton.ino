// 接線方式
// DATA 接 D2 -> 4
const int buttonPin = 4;
int buttonState = 1;
void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
}

void loop() {
  if (digitalRead(buttonPin) == HIGH) {
    buttonState = !buttonState;
    Serial.println(!buttonState);
  }
  delay(200);
}
