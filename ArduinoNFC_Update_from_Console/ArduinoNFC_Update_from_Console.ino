// 讀取卡片餘額
#include <SPI.h>
#include <RFID.h>

#define RST_PIN 9
#define SDA_PIN 10
#define BUZEER_PIN 8

RFID rfid (SDA_PIN, RST_PIN);
String cardId = "";

// 驗證資料(block id: 11)
unsigned char keyA[16] {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xff, 0x07, 0x80, 0x69, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

int data_blockId = 9;
int key_blockId = 11;
int bonus = 0; // 加值

void setup() {
  Serial.begin(9600);
  delay(2);
  SPI.begin();
  rfid.init();
  Serial.println("Ready");
}

void loop() {
  // 檢查使用者是否有輸入加值內容
  while(Serial.available() > 0) {
    // 注意 ! 使用 readString() 會稍慢且有明顯的 delay 感
    String data = Serial.readString();
    bonus = data.toInt();
    Serial.print("bonus: ");
    Serial.println(bonus);
  }
  
  if (rfid.isCard() && rfid.readCardSerial()) {
    tone(BUZEER_PIN, 976, 200)  ;
    Serial.println("Card found");
    cardId = "";
    for (int i = 0; i < 5; i++) {
      cardId += String(rfid.serNum[i], HEX);
    }
    Serial.print("Card id: ");
    Serial.println(cardId);
    // 回傳卡片內容
    int card_size = rfid.SelectTag(rfid.serNum);
    Serial.print("Card size: ");
    Serial.print(card_size);
    Serial.println("K bits");
    Serial.println();
  }
  //--------------------------------------------------------
  // 授權驗證
  unsigned char status = rfid.auth(PICC_AUTHENT1A, key_blockId, keyA, rfid.serNum);
  if (status == MI_OK) {
    Serial.println("Auth pass");
    // 讀取餘額
    unsigned char readData[16];
    status = rfid.read(data_blockId, readData); // 將資料讀取到 readDate 陣列
    if (status == MI_OK) {
      int balance = readData[15];
      Serial.print("Read ok: $");
      Serial.println(balance, DEC);
      // 判斷餘額是否足夠 ?
      if(balance < 255) {
        balance += bonus;
        // 回寫資料
        readData[15] = balance;
        status = rfid.write(data_blockId, readData);
        if (status == MI_OK) {
            Serial.println("Update balance success");  
        } else {
            Serial.println("Update balance error");  
        }
        Serial.print("Read balance again: $");
        Serial.println(balance, DEC);
      } else {
        Serial.println("Balance overflow!");
        delay(500);
        tone(BUZEER_PIN, 1500, 200)  ;
        delay(200);
        tone(BUZEER_PIN, 1500, 200)  ;
        delay(200);
        tone(BUZEER_PIN, 1500, 200)  ;
      }
    } else {
      Serial.println("Read error");
    }
    Serial.println("-------------------------------");
  }
  rfid.halt(); // 進入休眠
  delay(500);
}
