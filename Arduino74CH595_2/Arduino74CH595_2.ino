#define ST 2  // 平台
#define SH 3  // 活塞
#define DS 4  // 資料
//             0  1  2  3  4  5  6  7
int data[8][8] = {
  {1, 0, 0, 0, 0, 0, 0, 0},
  {0, 1, 0, 0, 0, 0, 0, 0},
  {0, 0, 1, 0, 0, 0, 0, 0},
  {0, 0, 0, 1, 0, 0, 0, 0},
  {0, 0, 0, 0, 1, 0, 0, 0},
  {0, 0, 0, 0, 0, 1, 0, 0},
  {0, 0, 0, 0, 0, 0, 1, 0},
  {0, 0, 0, 0, 0, 0, 0, 1}
};

void setup() {
  pinMode(ST, OUTPUT);
  pinMode(SH, OUTPUT);
  pinMode(DS, OUTPUT);
}

void loop() {
  
  for(int k=0;k<8;k++) {
    digitalWrite(ST, LOW);  // 平台放下
    // 迴圈要反過來寫
    for(int i=7;i>=0;i--) {
      digitalWrite(SH, LOW);      // 拉回活塞
      digitalWrite(DS, data[i][k]);  // 放入資料
      digitalWrite(SH, HIGH);     // 活塞推入
    }
    digitalWrite(ST, HIGH); // 平台上推
    delay(500);
  }

  for(int k=6;k>=1;k--) {
    digitalWrite(ST, LOW);  // 平台放下
    // 迴圈要反過來寫
    for(int i=7;i>=0;i--) {
      digitalWrite(SH, LOW);      // 拉回活塞
      digitalWrite(DS, data[i][k]);  // 放入資料
      digitalWrite(SH, HIGH);     // 活塞推入
    }
    digitalWrite(ST, HIGH); // 平台上推
    delay(500);
  }
  
}
