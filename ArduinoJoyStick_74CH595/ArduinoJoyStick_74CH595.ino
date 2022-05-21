#define ST 2  // 平台
#define SH 3  // 活塞
#define DS 4  // 資料

int data[9][8] = {
  {1, 0, 0, 0, 0, 0, 0, 0},
  {0, 1, 0, 0, 0, 0, 0, 0},
  {0, 0, 1, 0, 0, 0, 0, 0},
  {0, 0, 0, 1, 0, 0, 0, 0},
  {0, 0, 0, 0, 1, 0, 0, 0},
  {0, 0, 0, 0, 0, 1, 0, 0},
  {0, 0, 0, 0, 0, 0, 1, 0},
  {0, 0, 0, 0, 0, 0, 0, 1},
  {1, 1, 1, 1, 1, 1, 1, 1}
};

int k = 0;

void setup() {
  pinMode(ST, OUTPUT);
  pinMode(SH, OUTPUT);
  pinMode(DS, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int vrx, vry, sw;

  vrx = analogRead(A1);
  vry = analogRead(A2);
  sw  = analogRead(A3);

  char buf[100];
  sprintf(buf, "VRx=%d, VRy=%d, SW=%d", vrx, vry, sw);
  Serial.println(buf);

  // 判斷 sw
  if (sw < 10) {
    k = 8;
  } else {
    if (vrx > 1000) {
      k++;
    } else if (vrx < 10) {
      k--;
    }
    if (k > 7) {
      k = 7;
      k = 0;
    }
    if (k < 0) {
      k = 0;
      k = 7;
    }
  }

  digitalWrite(ST, LOW);  // 平台放下

  // 迴圈要反過來寫
  for (int i = 7; i >= 0; i--) {
    digitalWrite(SH, LOW);      // 拉回活塞
    digitalWrite(DS, data[k][i]);  // 放入資料
    digitalWrite(SH, HIGH);     // 活塞推入
  }

  digitalWrite(ST, HIGH); // 平台上推

  delay(200);

}
