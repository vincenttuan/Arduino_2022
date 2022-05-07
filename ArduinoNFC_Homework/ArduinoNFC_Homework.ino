/*
  RFID, LCD, Button, Buzeer
  LCD 畫面
  (M:0 查看餘額) 按下 button
  +----------------+
  |           M:0  |
  |Bal:$0          |
  +----------------+

  (M:0 查看餘額) 刷卡
  +----------------+
  |A1B2C3D4E5 M:0  |
  |Bal:$180        |
  +----------------+

  (M:1 消費) 按下 button
  +----------------+
  |           M:1  |
  |Msg:      Fee:30| (30元固定)
  +----------------+

  (M:1 消費) 刷卡
  +----------------+
  |A1B2C3D4E5 M:1  |
  |Msg:OK    Fee:30| Msg:OK/Fail
  +----------------+

  (M:2 儲值) 按下 button
  +----------------+
  |           M:2  |
  |Msg:     Add:0  | (0 初始資料或前一次的資料)
  +----------------+

  (M:2 儲值) 從主控台輸入數字
  +----------------+
  |           M:2  |
  |Msg:     Add:50 | (不超過200)
  +----------------+

  (M:3 儲值) 刷卡
  +----------------+
  |A1B2C3D4E5 M:2  |
  |Msg:OK   Add:50 | Msg:OK/Fail
  +----------------+
*/
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
