// Arduino 模擬多執行緒
#include <Timer.h>

// 宣告 Timer 物件
Timer t;

void setup() {
  Serial.begin(9600);
  t.every(1000, oneJob);
  t.every(2000, twoJob);
  t.every(5000, fiveJob);
}

void loop() {
  t.update();
  delay(10);
}

void oneJob() {
  Serial.println("one 1");
}

void twoJob() {
  Serial.println("two 2");
}

void fiveJob() {
  Serial.println("five 5");
}
