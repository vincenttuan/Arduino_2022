// 呼吸燈
#define LED_PIN 11
void setup() {
  pinMode(LED_PIN, OUTPUT);

}

void loop() {
  for(int i=0;i<=255;i++) {
    analogWrite(LED_PIN, i);
    delay(5);  
  }

  for(int i=255;i>=0;i--) {
    analogWrite(LED_PIN, i);
    delay(5);  
  }
  
}
