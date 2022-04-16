// 左邊玩家
const int LEFT_LED_PIN_1 = 8;
const int LEFT_LED_PIN_2 = 9;
const int LEFT_ANSWER_BUTTON_PIN = 7;
// 搶答燈
const int ANSWER_LED_PIN = 5;
// 右邊玩家
const int RIGHT_LED_PIN_1 = 3;
const int RIGHT_LED_PIN_2 = 4;
const int RIGHT_ANSWER_BUTTON_PIN = 6;
// 達標分數
int count = 2;
// 左邊玩家分數
int left_score = 0;
// 右邊玩家分數
int right_score = 0;
// 遊戲結束
boolean gameOver = false;
void setup() {
  Serial.begin(9600);
  // 初始資料
  pinMode(LEFT_LED_PIN_1, OUTPUT);
  pinMode(LEFT_LED_PIN_2, OUTPUT);
  pinMode(LEFT_ANSWER_BUTTON_PIN, INPUT);
  pinMode(ANSWER_LED_PIN, OUTPUT);
  pinMode(RIGHT_LED_PIN_1, OUTPUT);
  pinMode(RIGHT_LED_PIN_2, OUTPUT);
  pinMode(RIGHT_ANSWER_BUTTON_PIN, INPUT_PULLUP);
  // 所有玩家的燈先關閉
  digitalWrite(LEFT_LED_PIN_1, LOW);
  digitalWrite(LEFT_LED_PIN_2, LOW);
  digitalWrite(RIGHT_LED_PIN_1, LOW);
  digitalWrite(RIGHT_LED_PIN_2, LOW);
  // 遊戲開始
  gameOver = false;
}

void loop() {
  if(gameOver) {
    return;  
  }
  // 關閉搶答燈
  digitalWrite(ANSWER_LED_PIN, LOW);
  Serial.println("Ready...");
  delay(3000);
  Serial.println("GO");
  // 開始出題
  delay(random(3000, 10000));
  // 搶答燈亮
  digitalWrite(ANSWER_LED_PIN, HIGH);
  // 等待玩家按下按鈕
  while(true) {
    // 左邊玩家按下
    if(digitalRead(LEFT_ANSWER_BUTTON_PIN) == 0) {
      left_score++; // 分數加+1
      if(left_score == 1) { // 亮第一燈
        digitalWrite(LEFT_LED_PIN_1, HIGH);
      } else { // 亮第二燈
        digitalWrite(LEFT_LED_PIN_2, HIGH);    
      }
      break;
    }
    // 右邊玩家按下
    if(digitalRead(RIGHT_ANSWER_BUTTON_PIN) == 0) {
      right_score++; // 分數加+1
      if(left_score == 1) { // 亮第一燈
        digitalWrite(RIGHT_LED_PIN_1, HIGH);
      } else { // 亮第二燈
        digitalWrite(RIGHT_LED_PIN_2, HIGH);    
      }
      break;
    }
  }
  if(left_score == count) { // 驗證玩家分數是否 == 達標分數
      Serial.println("LEFT WIN !");
      gameOver = true;
  }
  if(right_score == count) {
      Serial.println("RIGHT WIN !");
      gameOver = true;
  }
  delay(1000);
}
