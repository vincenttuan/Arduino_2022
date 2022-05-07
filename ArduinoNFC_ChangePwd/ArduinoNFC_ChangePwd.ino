// 變更 Password
#include <SPI.h>
#include <RFID.h>

#define RST_PIN 9
#define SDA_PIN 10
#define BUZEER_PIN 8

RFID rfid (SDA_PIN, RST_PIN);
String cardId = "";

// 驗證資料(block id: 11)
// 舊密碼
unsigned char keyA[16] {0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xff, 0x07, 0x80, 0x69, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
// 新密碼
unsigned char newKeyA[16] {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xff, 0x07, 0x80, 0x69, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

int data_blockId = 9;
int key_blockId = 11;

void setup() {
  Serial.begin(9600);
  delay(2);
  SPI.begin();
  rfid.init();
  Serial.println("Change password");
}

void loop() {
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
  // 寫入 100
  // 授權驗證
  unsigned char status = rfid.auth(PICC_AUTHENT1A, key_blockId, keyA, rfid.serNum);
  if (status == MI_OK) {
    Serial.println("Auth pass");
    // 變更密碼
    status = rfid.write(key_blockId, newKeyA);
    if (status == MI_OK) {
      Serial.print("Old password: ");
      printKey(keyA);
      Serial.print("New password: ");
      printKey(newKeyA);
    } else {
      Serial.println("Update password error");
    }
    Serial.println("-------------------------------");
  }
  rfid.halt(); // 進入休眠
  delay(500);
}

void printKey(char key[] ) {
  for (int i = 0; i < 6; i++) {
    Serial.print(key[i], HEX);
    Serial.print(" ");
  }
  Serial.println();
}
