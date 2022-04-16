const int LED_PIN = 11;
const int CDS_PIN = 0;

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  int value = analogRead(CDS_PIN);
  Serial.println(value);
  if(value < 300) {
    analogWrite(LED_PIN, 255);
  } else if(value < 600) {
    analogWrite(LED_PIN, 50);
  } else {
    analogWrite(LED_PIN, 0);  
  }
  delay(200);
}
