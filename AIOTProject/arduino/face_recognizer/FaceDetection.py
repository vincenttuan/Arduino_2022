import cv2

face_cascade = cv2.CascadeClassifier("./haarcascades/haarcascade_frontalface_alt.xml")
# 設定 Webcam
cap = cv2.VideoCapture(1)

# 設定捕捉區域
cap.set(cv2.CAP_PROP_FRAME_WIDTH, 1024)  # 800, 640
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 768)  # 600, 480

while True:
    # 捕捉 frame-by-frame
    # ret : 得到的 frame 若是正確的會回傳 true
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
        minNeighbors=10,   # 每個目標至少要檢測到幾次以上，才被認定是真數據
        minSize=(30, 30), # 數據搜尋的最小尺寸
        flags=cv2.CASCADE_SCALE_IMAGE
        # CASCADE_DO_CANNY_PRUNING=1 -> 利用canny邊緣檢測來排除一些邊緣很少或者很多的影象區域
        # CASCADE_SCALE_IMAGE=2 -> 正常比例檢測
        # CASCADE_FIND_BIGGEST_OBJECT=4 -> 只檢測最大的物體
        # CASCADE_DO_ROUGH_SEARCH=8 粗略的檢測
    )

    # 在臉部周圍畫矩形框訓練集資料已儲存
    for (x, y, w, h) in faces:
        # 繪文字 putText(來源, 文字, 左下座標, 字型, 字型大小, 文字顏色, 文字線條寬度)
        cv2.putText(frame, 'Vincent', (x, y-10), cv2.FONT_HERSHEY_COMPLEX, 1.2, (0, 255, 0), 2)
        cv2.rectangle(frame, (x, y), (x+w, y+h), (0, 0, 255), 5)

    # 顯示在 frame UI 上面
    cv2.imshow('My Video', frame)
    # 按下 q 離開迴圈
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break;

# 釋放資源
cap.release()
cv2.destroyAllWindows()