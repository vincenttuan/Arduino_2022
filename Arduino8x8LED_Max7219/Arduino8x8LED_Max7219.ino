#include <LedControl.h>

const int DIN_PIN = 7;
const int CS_PIN = 6;
const int CLK_PIN = 5;

const uint64_t IMAGES[] = {
  0x0000000001000000,
  0x0000000103010000,
  0x0000010307030100,
  0x000002070f070200,
  0x0000040f1f0f0400,
  0x0000081e3e1e0800,
  0x0000103c7c3c1000,
  0x00002078f8782000,
  0x000040f0f0f04000,
  0x000080e0e0e08000,
  0x000000c0c0c00000,
  0x0000008080800000,
  0x0000000000000000
};
const int IMAGES_LEN = sizeof(IMAGES)/8;

LedControl display = LedControl(DIN_PIN, CLK_PIN, CS_PIN);


void setup() {
  display.clearDisplay(0);
  display.shutdown(0, false);
  display.setIntensity(0, 10);
}

void displayImage(uint64_t image) {
  for (int i = 0; i < 8; i++) {
    byte row = (image >> i * 8) & 0xFF;
    for (int j = 0; j < 8; j++) {
      display.setLed(0, i, j, bitRead(row, j));
    }
  }
}

int i = 0;

void loop() {
  displayImage(IMAGES[i]);
  if (++i >= IMAGES_LEN ) {
    i = 0;
  }
  delay(100);
}
