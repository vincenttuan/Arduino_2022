import cv2

face_cascade = cv2.CascadeClassifier('./haarcascades/haarcascade_frontalface_alt.xml')
eyes_cascade = cv2.CascadeClassifier('./haarcascades/haarcascade_eye_tree_eyeglasses.xml')
smile_cascade = cv2.CascadeClassifier('./haarcascades/haarcascade_smile.xml')

# 設定 Webcam 位置
cap = cv2.VideoCapture(1)

# 設定捕捉區域
cap.set(cv2.CAP_PROP_FRAME_WIDTH, 1024)  # 800, 640
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 768)  # 600, 480

while True:
    # 捕捉 frame-by-frame
    # ret : 2唔到的 frame 若是正確的會回傳 true
    # frame : 捕捉到的區域資料
    ret, frame = cap.read()
    print(ret, frame)

    frame = cv2.flip(frame, 1) # 鏡像處理

    # 圖像灰階化
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    # 畫出每一個臉的範圍
    faces = face_cascade.detectMultiScale(
        gray,             # 待檢測圖片，一般來說設定成灰度圖像可以加快檢測速度
        scaleFactor=1.1,  # 檢測粒度。若粒度增加會加速檢測速度，但會影響準確率
        minNeighbors=5,   # 每個目標至少要檢測到幾次以上，才被認定是真數據
        minSize=(30, 30), # 數據搜尋的最小尺寸
        flags=cv2.CASCADE_SCALE_IMAGE
    )



    # 在臉部周圍畫矩形框
    for (x, y, w, h) in faces:
        cv2.rectangle(frame, (x, y), (x+w, y+h), (0, 0, 255), 5)

        # 獲取眼睛 (ROI(region of interest))
        roi_gray = gray[y:y+h, x:x+w]
        roi_frame = frame[y:y+h, x:x+w]
        eyes = eyes_cascade.detectMultiScale(
            roi_gray,  # 待檢測圖片，一般來說設定成灰度圖像可以加快檢測速度
            scaleFactor=1.1,  # 檢測粒度。若粒度增加會加速檢測速度，但會影響準確率
            minNeighbors=5,  # 每個目標至少要檢測到幾次以上，才被認定是真數據
            minSize=(30, 30),  # 數據搜尋的最小尺寸
            flags=cv2.CASCADE_SCALE_IMAGE
        )
        # 在眼部周圍畫矩形框
        eyes_y = 0
        for (x, y, w, h) in eyes:
            cv2.rectangle(roi_frame, (x, y), (x + w, y + h), (0, 255, 0), 5)
            eyes_y = y + h

        # 獲取Smile (ROI(region of interest))
        smile = smile_cascade.detectMultiScale(
            roi_gray,  # 待檢測圖片，一般來說設定成灰度圖像可以加快檢測速度
            scaleFactor=1.1,  # 檢測粒度。若粒度增加會加速檢測速度，但會影響準確率
            minNeighbors=100,  # 每個目標至少要檢測到幾次以上，才被認定是真數據
            minSize=(30, 30),  # 數據搜尋的最小尺寸
            flags=cv2.CASCADE_SCALE_IMAGE
        )

        for (x, y, w, h) in smile:
            if (y > eyes_y + 10): # 調整，Smile 在 Eyes 的下面
                cv2.rectangle(roi_frame, (x, y), (x + w, y + h), (255, 0, 0), 5)


    # 顯示在 frame UI 上面
    cv2.imshow('My Video', frame)
    # 按下 q 離開迴圈
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break;

# 釋放資源
cap.release()
cv2.destroyAllWindows()
