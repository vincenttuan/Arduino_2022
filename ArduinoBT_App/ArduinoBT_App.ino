#include <SoftwareSerial.h> // 引用程式庫
// 透過手機 App 來控制藍芽
// 定義 BT 序列埠
/*
 * HC-05 接線方式
 * VCC - 5V  
 * GND - GND  
 * TXD - 10  
 * RXD - 11  
*/
SoftwareSerial BT(10, 11); // RX(對應 BT的TXD), TX(對應 BT的RXD)
char val; // 儲存接收到的資料

void setup() {
  Serial.begin(9600);
  delay(2);
  // 進入 BT - App (Android 手機) 連線設定 baund
  BT.begin(9600);
  Serial.println("BT App Ready ...");
}

void loop() {
  // 從主控台傳指令給 BT
  if(Serial.available()) {
    val = Serial.read(); // 接到指令
    BT.print(val); // 將指令給 BT
  }

  // BT 回應資料給主控台
  if(BT.available()) {
    val = BT.read(); // 讀取 BT 的回應資料
    Serial.print(val); // 將回應資料給主控台
  }

  delay(10);
}
