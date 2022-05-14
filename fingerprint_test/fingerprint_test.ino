/*
 * 本範程式為指紋辨識系統-驗証指紋的範例程式，由傑森創工提供
 * 本程式由Aadfruit Fingerprint Sensor Libray函式庫範例進行改寫。
 * 
 * 1，請先安裝Aadfruit Fingerprint Sensor Library
 * 2，請先安裝LiquidCrystal_PCF8574，LCD函式庫
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
#include <Servo.h>
#define LED_PIN 12
#define SERVO_PIN 13

LiquidCrystal_PCF8574 lcd(0x27);  // 設定LCD的i2c位址，一般情況就是0x27和0x3F兩種

//用Software Serial的方式，設定RX，TX
SoftwareSerial mySerial(2, 3);   //PIN2是RX，接到AS608的TX；PIN3是TX，接到AS608的RX

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

// 驗証通過的璇律
int melody[] = {
  262, 233, 415
};

// 璇律對映的節拍
int noteDurations[] = {
  8,4,2
};

// 採集指紋失敗的璇律
int melodyFail[] = {
  110, 55
};

// 璇律對映的節拍
int noteDurationsFail[] = {
  12, 2
};

// 建立 Servo 物件
Servo myServo;
int initDegree = 90; // 初始角度
int maxDegree = 0; // 最大角度

void setup()  
{
  Serial.begin(9600);
  delay(100);
  
  pinMode(LED_PIN, OUTPUT);
  myServo.attach(SERVO_PIN); // 設定 Servo 訊號腳位
  myServo.write(initDegree); // 設定初始角度位置
  
  Serial.println("Fingerprint detect test");

  // 設定AS608的Baud Rate
  finger.begin(57600);
  delay(5);

  //判斷是否可以使用指紋模組
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) { delay(1); }
  }

  //偵測目前有幾組已記錄的指紋
  finger.getTemplateCount();
  Serial.print("Sensor contains "); Serial.print(finger.templateCount); Serial.println(" templates");

  //等待指紋
  Serial.println("Waiting for valid finger...");

  //讓LCD顯示等待指紋中
  lcd.begin(16, 2); // 初始化LCD
  lcd.setBacklight(255);
  lcd.clear();
  lcd.setCursor(0, 0);  //設定游標位置 (字,行)
  lcd.print("Put your finger");
  lcd.setCursor(0, 1); 
  lcd.print("for indentify..");
  lcd.setCursor(15, 1); //第二行最後一個字閃動
  lcd.blink();
}

void loop()                     
{
  // 接收來自主機端的訊息
  while(Serial.available()>0) {
    char data = Serial.read();
    Serial.println(data);
    switch(data) {
      case '1':
        digitalWrite(LED_PIN, HIGH);
        openTheDoor();
        break;
      case '0':
        digitalWrite(LED_PIN, LOW);
        break;
    }
    
  }
  //進行比對指紋
  getFingerprintIDez();
  delay(50);            
}

// 如果回傳-1，則是沒有比對到已紀錄的指紋；比對成功則回傳對映的ID
int getFingerprintIDez() {
  
  uint8_t p = finger.getImage();  //取得指紋
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK){
    lcd.noBlink();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ACCESS DENIED!");
    playMusicFail();
    delay(3000);
    lcd.clear();
    lcd.setCursor(0, 0);  //設定游標位置 (字,行)
    lcd.print("Put your finger");
    lcd.setCursor(0, 1); 
    lcd.print("for indentify..");
    lcd.setCursor(15, 1); //第二行最後一個字閃動
    lcd.blink();
    return -1;
  }

  //以下是成功取得配對後才會進行的程序
  //finger.fingerID就是當初該指紋記錄的ID
  //finger.confidence則是比對的分數，0~255
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence);

  //如果finger.confidence分數大於100，表示驗証通過。
  //就在LCD顯示通過的訊息，並播放音效
  if(finger.confidence > 100){

    //設定ID所對映的人名，這部份要自行修改;ID沒有0，所以第一個隨意取
    char idname[][16]={"Nobody","Peter Chen","Amy Wang","Kelly Lee","Jessica Wu"};
    //在LCD顯示通過的人名
    lcd.noBlink();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(idname[finger.fingerID]);
    lcd.setCursor(0, 1);
    lcd.print("ACCESS GRANTED!");
    playMusic();
    delay(3000);
    lcd.clear();
    lcd.setCursor(0, 0);  //設定游標位置 (字,行)
    lcd.print("Put your finger");
    lcd.setCursor(0, 1); 
    lcd.print("for indentify..");
    lcd.setCursor(15, 1); //第二行最後一個字閃動
    lcd.blink();
  }
  
  return finger.fingerID; 
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
//播放失敗音效的副程式
void playMusicFail(){
  for (int thisNote = 0; thisNote < 2; thisNote++) {
    int noteDuration = 1000 / noteDurationsFail[thisNote];
    tone(4, melodyFail[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(4);
  }
}

void openTheDoor() {
  // 啟動 open 柵欄中 ...
  for(int i=initDegree;i>=maxDegree;i-=5) {
    myServo.write(i);
    delay(100);
  }
  delay(5000); // 柵欄全部開啟
  // 關閉 close 柵欄中 ...
  for(int i=maxDegree;i<=initDegree;i+=5) {
    myServo.write(i);
    delay(100);
  }
}
