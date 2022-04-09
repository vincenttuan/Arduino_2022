// 讀取 PC 傳來的指令
void setup() {
  Serial.begin(9600);

}

void loop() {
  // 判斷 Arduino 是否有收到傳來的資料 ?
  if(Serial.available() > 0) {
    //char c = Serial.read(); // 讀一個字
    String c = Serial.readString(); // 讀一字串
    Serial.print("arduino: ");
    Serial.println(c);
  }
  delay(10);
}
