/*
 * 聲音感測器
* 接線方式
* A0 : A0
* G  : GND
* +  : 5V
* D0 : 不接
*/
#define RELAY_PIN 4
#define CONTROL_PIN 13
void setup() {
  Serial.begin(9600);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(CONTROL_PIN, OUTPUT);
  delay(2);
}

void loop() {
  digitalWrite(CONTROL_PIN, HIGH);
  // 讀取 A0 的值
  int sensorValue = analogRead(A0);
  if(sensorValue > 50) {
    Serial.println(sensorValue);
    digitalWrite(RELAY_PIN, !digitalRead(RELAY_PIN));
    digitalWrite(CONTROL_PIN, LOW);
    delay(5000);
  }
  delay(10);
}
