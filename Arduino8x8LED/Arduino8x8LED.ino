#define L4 2
#define C1 3

void setup() {
  Serial.begin(9600);
  delay(2);
  pinMode(L4, OUTPUT);
  pinMode(C1, OUTPUT);
}

void loop() {
  digitalWrite(L4, HIGH);
  digitalWrite(C1, LOW);
}
