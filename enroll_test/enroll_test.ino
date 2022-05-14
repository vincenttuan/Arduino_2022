/*
 * 本範程式為指紋辨識系統-採集指紋的範例程式，由傑森創工提供
 * 本程式由Aadfruit Fingerprint Sensor Libray函式庫範例進行改寫。
 * 
 * 1，請先安裝Aadfruit Fingerprint Sensor Library
 * 2，請先安裝LiquidCrystal_PCF8574，LCD函式庫
 * 3，請先安裝LiquidCrystal_PCF8574，LCD函式庫
 * 
 * 套件購買網址：
 * https://www.jmaker.com.tw/products/fingerprint-system
 * 
 * 粉絲團：https://www.facebook.com/jasonshow
 * 傑森創工購物網：https://www.jmaker.com.tw/
 * 傑森創工部落格：https://blog.jmaker.com.tw/
 */


#include <Adafruit_Fingerprint.h>
#include <LiquidCrystal_PCF8574.h>
#include "Adafruit_Keypad.h"

LiquidCrystal_PCF8574 lcd(0x27);  // 設定LCD的i2c位址，一般情況就是0x27和0x3F兩種

//用Software Serial的方式，設定RX，TX
SoftwareSerial mySerial(2, 3);   //PIN2是RX，接到AS608的TX；PIN3是TX，接到AS608的RX

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

// 採集指紋成功的璇律
int melody[] = {
  262, 233, 415
};

// 璇律對映的節拍
int noteDurations[] = {
  8,4,2
};


const byte ROWS = 4; // 列數(橫的)
const byte COLS = 3; // 行數(直的)
//鍵盤上每一個按鍵的名稱
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {11, 10, 9, 8}; //定義列的腳位
byte colPins[COLS] = {7, 6, 5}; //定義行的腳位

//初始化鍵盤
Adafruit_Keypad customKeypad = Adafruit_Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS);

uint8_t id=0;
int digits=0;
int inputOK=0;
char enterNumber[3];
//int realNumber=0;

void setup()  
{
  Serial.begin(9600);

  delay(100);
  Serial.println("Fingerprint sensor enrollment");

  lcd.begin(16, 2); // 初始化LCD
  lcd.setBacklight(255);
  lcd.setCursor(0, 0);  //設定游標位置 (字,行)
  lcd.print("Wait ...");
  delay(100);
  
  // 設定AS608的Baud Rate
  finger.begin(57600);
  
  //判斷是否可以使用指紋模組
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) { delay(1); }
  }

  lcd.clear();

  customKeypad.begin();
}

uint8_t readnumber(void) {
  uint8_t num = 0;
  
  while (num == 0) {
    while (! Serial.available());
    num = Serial.parseInt();
  }
  return num;
}

void loop()                     // run over and over again
{
  lcd.setCursor(0, 0);  //設定游標位置 (字,行)
  lcd.print("Enter ID Number:");
  lcd.setCursor(digits, 1); 
  lcd.cursor();
  lcd.blink();
  // 開始偵測使用者的按鍵狀態
  customKeypad.tick();

  //判斷按了哪一個鍵
  //ID只能1~127，*表示清除，#代表輸入完成

  
    while(customKeypad.available()){
      keypadEvent e = customKeypad.read();
      if(e.bit.EVENT == KEY_JUST_RELEASED) {
        if((char)e.bit.KEY=='#'){
          digits=3;
          if(id>0 && id<128){
            inputOK=1;
            Serial.println(id);
          }else{
            lcd.clear();
            lcd.setCursor(0, 0);  //設定游標位置 (字,行)
            lcd.print("Error Number!");
            lcd.setCursor(0, 1);  
            lcd.print("Try Again!");
            delay(2000);
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd.cursor();
            lcd.blink();
            memset(enterNumber, 0, sizeof(enterNumber));
            id = 0;
            digits=0;
          }
        }else if((char)e.bit.KEY=='*'){
          lcd.clear();
          lcd.setCursor(0, 1);
          lcd.cursor();
          lcd.blink();
          memset(enterNumber, 0, sizeof(enterNumber));
          id = 0;
          digits=0;
        }else{
          if(digits==0){
            lcd.setCursor(0, 1);
            lcd.cursor();
            lcd.blink();
            lcd.print((char)e.bit.KEY);
            enterNumber[0]=(char)e.bit.KEY;
            id = atoi(enterNumber);
            digits++;
          }else if(digits==1){
            lcd.setCursor(1, 1);
            lcd.cursor();
            lcd.blink();
            lcd.print((char)e.bit.KEY);  
            enterNumber[1]=(char)e.bit.KEY;
            id = atoi(enterNumber);
            digits++;
          }else if(digits==2){
            lcd.setCursor(2, 1);
            lcd.cursor();
            lcd.blink();
            lcd.print((char)e.bit.KEY);  
            enterNumber[2]=(char)e.bit.KEY;
            id = atoi(enterNumber);
            digits++;
          }else{
            
          }
        }
      }
    }
  
  delay(10);
  if(inputOK==1){
    inputOK = 0;
    //
    lcd.clear();
    lcd.setCursor(0, 0);  //設定游標位置 (字,行)
    lcd.cursor();
    lcd.blink();
    lcd.print("Place You Finger");
    lcd.noCursor();
    lcd.noBlink();
    while (!  getFingerprintEnroll() );
  }
}

uint8_t getFingerprintEnroll() {

  int p = -1;
  Serial.print("Waiting for valid finger to enroll as #"); Serial.println(id);
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      break;
    default:
      Serial.println("Unknown error");
      break;
    }
  }

  // OK success!

  p = finger.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  Serial.println("Remove finger");
  //成功完成取指紋
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Remove finger");

  delay(2000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }
  Serial.print("ID "); Serial.println(id);
  p = -1;
  Serial.println("Place same finger again");

  //第二次取指紋，比對和上一次是否相同
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Place the same");
  lcd.setCursor(0, 1);
  lcd.print("finger again");
  
  
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.print(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      break;
    default:
      Serial.println("Unknown error");
      break;
    }
  }

  // OK success!

  p = finger.image2Tz(2);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  // OK converted!
  Serial.print("Creating model for #");  Serial.println(id);
  
  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
    Serial.println("Prints matched!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
    Serial.println("Fingerprints did not match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
  
  Serial.print("ID "); Serial.println(id);
  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) {
    Serial.println("c");
    //成功完成取指紋
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Finger Stored!");
    digits=0;
    id=0;
    playMusic();
    delay(3000);
    
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("Could not store in that location");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Error writing to flash");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
}

//播放成功音效的副程式
void playMusic(){
  for (int thisNote = 0; thisNote < 3; thisNote++) {
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(4, melody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(4);
  }
}
