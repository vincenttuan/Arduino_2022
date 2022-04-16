const int FLAME_PIN = 11;
const int BUZEER_PIN = 10;

void setup() {
  Serial.begin(9600);
  pinMode(FLAME_PIN, INPUT);
  pinMode(BUZEER_PIN, OUTPUT);
  
}

void loop() {
  boolean isFlame = digitalRead(FLAME_PIN);
  Serial.println(isFlame);
  if(isFlame == 0) { // 0 表示有火焰
      digitalWrite(BUZEER_PIN, HIGH);
  } else {
    digitalWrite(BUZEER_PIN, LOW);
  }
  delay(200);
}
