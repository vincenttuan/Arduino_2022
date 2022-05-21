void setup() {
  pinMode(3, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int vrx, vry, sw;

  vrx = analogRead(A1);
  vry = analogRead(A2);
  sw  = analogRead(A3);

  char buf[100];
  sprintf(buf, "VRx=%d, VRy=%d, SW=%d", vrx, vry, sw);
  Serial.println(buf);
  
  int y = map(vry, 0, 1023, 0, 255);
  Serial.println(y);
  analogWrite(3, y);
  delay(100);
}
