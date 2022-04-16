// 使用 9, 10, 11 ~PWM
#define RED 9
#define GREEN 10
#define BLUE 11


void setup() {
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
}

void loop() {
  analogWrite(RED, 255); // 0~255
  analogWrite(GREEN, 0); // 0~255
  analogWrite(BLUE, 0); // 0~255
  delay(1000);
  analogWrite(RED, 0); // 0~255
  analogWrite(GREEN, 255); // 0~255
  analogWrite(BLUE, 0); // 0~255
  delay(1000);
  analogWrite(RED, 0); // 0~255
  analogWrite(GREEN, 0); // 0~255
  analogWrite(BLUE, 255); // 0~255
  delay(1000);
  

}
