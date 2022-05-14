/*
  水位偵測
  - : GND
  + : 5v
  S : A0
*/
void setup() {
  Serial.begin(9600);
  delay(2);
  Serial.println("Water Sensor:");
}

void loop() {
  // 從 A0 中讀取資料
  int value = analogRead(A0);
  Serial.print(value);
  if(value <= 100) {
      Serial.println(" No Water");
  } else if(value > 100 && value <= 350) {
    Serial.println(" Low Water");    
  } else if(value > 350 && value <= 480) {
    Serial.println(" Middle Water");    
  } else {
    Serial.println(" High Water");    
  }
  delay(1000);
}
