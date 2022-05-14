import serial  # 引用 pySerial 模組

if __name__ == '__main__':
    COM_PORT = 'COM7'  # 指定通訊埠
    BAUD_RATE = 9600  # 設定傳輸速率(鮑率)
    ser = None
    try:
        ser = serial.Serial(COM_PORT, BAUD_RATE)  # 初始化
        # 循環接收資料
        while True:
            while ser.in_waiting:  # 若有收到資料
                data_row = ser.readline()  # 讀一行原始資料
                data = data_row.decode()  # 將原始資料轉碼, 預設編碼是 UTF-8
                data = data.strip("\r").strip("\n")  # 去除換行符號
                print(data)

    except serial.SerialException:
        print('通訊埠', COM_PORT, '無法建立')
        print('請確認 Arduino IDE 的序列埠通訊視窗是否有關閉')
    except KeyboardInterrupt:
        if ser is not None:
            ser.close()  # 關閉通訊埠


