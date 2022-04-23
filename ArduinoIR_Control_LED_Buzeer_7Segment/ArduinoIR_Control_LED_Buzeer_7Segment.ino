#include <IRremote.h>
#define IR_RECV_PIN 10
#define LED_BUZEER_PIN 9 // 使用 7 段顯示器 DP 的 PIN

// IR 設備宣告
IRrecv irrecv(IR_RECV_PIN);
// IR 解碼資訊
decode_results results;

// 七段顯示器設定
boolean po = 0; // 0: 共陰, 1: 共陽
byte l = !po;
byte o = po;
byte seven_seg_digits [10][7] = {
  { l, l, l, l, l, l, o }, // = 0
  { o, l, l, o, o, o, o }, // = 1
  { l, l, o, l, l, o, l }, // = 2
  { l, l, l, l, o, o, l }, // = 3
  { o, l, l, o, o, l, l }, // = 4
  { l, o, l, l, o, l, l }, // = 5
  { l, o, l, l, l, l, l }, // = 6
  { l, l, l, o, o, o, o }, // = 7
  { l, l, l, l, l, l, l }, // = 8
  { l, l, l, o, o, l, l } // = 9
};

void setup() {
  Serial.begin(9600);
  delay(2);
  Serial.println("Enabling IR");
  irrecv.enableIRIn(); // 啟動 IR 接收
  Serial.println("Enabled IR");
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(LED_BUZEER_PIN, OUTPUT);
}

void loop() {
  // 將IR所收到的內容進行解碼 (&變數記憶體位置)
  if(irrecv.decode(&results)) {
    int value = results.value;
    Serial.println(value, HEX); // HEX: 16進位, DEC: 10進位
    switch(value) {
      case 0x6897: // 按下 0
        sevenSegWrite(0);
        break;
      case 0x30CF: // 按下 1
        sevenSegWrite(1);
        break;  
      case 0x18E7: // 按下 2
        sevenSegWrite(2);
        break;  
      case 0xFF7A85: // 按下 3
        sevenSegWrite(3);
        break;  
      case 0xFF10EF: // 按下 4
        sevenSegWrite(4);
        break;  
      case 0xFF38C7: // 按下 5
        sevenSegWrite(5);
        break;  
      case 0xFF5AA5: // 按下 6
        sevenSegWrite(6);
        break;  
      case 0xFF42BD: // 按下 7
        sevenSegWrite(7);
        break;  
      case 0xFF4AB5: // 按下 8
        sevenSegWrite(8);
        break;  
      case 0xFF52AD: // 按下 9
        sevenSegWrite(9);
        break;  
    }
    irrecv.resume(); // 恢復 IR 狀態, 讓 IR 能繼續接收下一個訊號
  }
  
  
  delay(100);
}

// 在七段顯示器上顯示所指定的數字
void sevenSegWrite(byte digit) {
  byte pin = 2;
  for(byte seg = 0; seg < 7 ; seg++) {
    digitalWrite(pin, seven_seg_digits[digit][seg]);  
    ++pin;
  }
  
  digitalWrite(LED_BUZEER_PIN, HIGH);
  delay(100);
  digitalWrite(LED_BUZEER_PIN, LOW);
  delay(100);
}
