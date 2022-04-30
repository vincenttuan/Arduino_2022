// 4 x 4 keypad 薄膜鍵盤
#include "Adafruit_Keypad.h" 
// 在鍵盤上按下 2+3=5 <-- 自動算出 5

// 定義鍵盤的行列
const byte ROWS = 4; // 定義列(橫向)
const byte COLS = 4; // 定義行(縱向)

// 定義鍵盤上每一個按鈕名稱
// C 表示清除
char keys[ROWS][COLS] = {
  {'1', '2', '3', '/'},
  {'4', '5', '6', '*'},
  {'7', '8', '9', '-'},
  {'C', '0', '=', '+'},
};

// 定義腳位
byte rowPins[ROWS] = {11, 10, 9, 8}; // 定義列腳位
byte colPins[COLS] = {7, 6, 5, 4}; // 定義行腳位

// 鍵盤自製初始化
Adafruit_Keypad customKeypad = Adafruit_Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

int pos = 0; // 按下順序
int x = 0;
int y = 0;
char opt = ' '; // 運算符(+, -, *, /)

void setup() {
  Serial.begin(9600);
  delay(2);
  customKeypad.begin();
  Serial.println("Keypad ready ...");
}

void loop() {
  // 開始偵測使用者的按鍵狀態
  customKeypad.tick(); // 判斷按下哪一個鍵
  while(customKeypad.available()) {
    keypadEvent e = customKeypad.read(); // 讀取
    // 按下事件 KEY_JUST_PRESSED, 放開事件 KEY_JUST_RELEASED
    if(e.bit.EVENT == KEY_JUST_PRESSED){
      char key = (char)e.bit.KEY;
      Serial.print(key);
      switch(pos) {
        case 0:
          x = key - 48;
          ++pos;
          break;
        case 1:
          opt = key;
          ++pos;
          break;
        case 2:
          y = key - 48;
          ++pos;
          break;
        case 3:
          if(key == '=') {
            int result = getResult();
            Serial.println(result);
            pos=0;
          }
          break;  
      }
      
    }
  }
  delay(10);
}

int getResult() {
    switch(opt) {
      case '+':
        return x + y;
      case '-':
        return x - y;
      case '*':
        return x * y;
      case '/':
        return x / y;
    }
    return 0;
}
