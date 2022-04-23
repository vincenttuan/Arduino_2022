// 超音波HC-SR04
#define TRIG_PIN 5
#define ECHO_PIN 6

void setup() {
  Serial.begin(9600);
  delay(2);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.println("Ready");
}

void loop() {
  // 發送: HIGH 持續 10ms
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10); // 延遲 10ms
  digitalWrite(TRIG_PIN, LOW);
  // 讀取 ECHO_PIN 的資料, 並透過 pulseIn 讀取 ECHO_PIN 腳針的脈衝時間
  int duration = pulseIn(ECHO_PIN, HIGH);
  // 在攝氏0~50度下音速每一公分需要29.1ms
  int cm = (duration/2)/29.1;
  Serial.print("duration: ");
  Serial.print(duration);
  Serial.print(", cm:");
  Serial.println(cm);
  delay(200);
  
}
