// 5011AS 共陰
// 5011BS 共陽
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

byte hello_seg_digits [5][7] = {
 // 2, 3, 4, 5, 6, 7, 8
  { o, l, l, o, l, l, l }, // = H
  { l, o, o, l, l, l, l }, // = E
  { o, o, o, l, l, l, o }, // = L
  { o, o, o, l, l, l, o }, // = L
  { l, l, l, l, l, l, o } //  = O
};

void setup() {
  Serial.begin(9600);
  delay(2);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
}

void loop() {
  //digitalWrite(9, HIGH);
  //digitalWrite(3, HIGH);
  //digitalWrite(4, HIGH);
  for(int i=0;i<10;i++) {
    sevenSegWrite(i);
    delay(500);
  }
  helloSegWrite();
  delay(2000);
}

// 在七段顯示器上顯示所指定的數字
void sevenSegWrite(byte digit) {
  byte pin = 2;
  for(byte seg = 0; seg < 7 ; seg++) {
    digitalWrite(pin, seven_seg_digits[digit][seg]);  
    ++pin;
  }
}

void helloSegWrite() {
  for(int digit=0;digit<5;digit++) {
    byte pin = 2;
    for(byte seg = 0; seg < 7 ; seg++) {
      digitalWrite(pin, hello_seg_digits[digit][seg]);  
      ++pin;
    }
    delay(500);
  }
}
