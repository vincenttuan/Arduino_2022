'''
+------+------+-----+
| 25.4 | 45.1 | off |
+------+------+-----+
'''
import tkinter
import firebase_admin
from tkinter import font
from PIL import Image, ImageTk  # 安裝 pillow
import threading
from firebase_admin import credentials
from firebase_admin import db

cred = credentials.Certificate('key.json')
firebase_admin.initialize_app(cred, {
    'databaseURL': 'https://d1mini-vincent-default-rtdb.firebaseio.com/'
})

def listener_temp(event):
    print("temp:", event.data)
    tempValue.set(event.data)

def listener_humi(event):
    print("humi:", event.data)
    humiValue.set(event.data)

def listener_led(event):
    print("led:", event.data)
    # 換圖片
    if event.data == 1:
        ledButton.config(image=led_on_img)
        ledButton.image = led_on_img
    elif event.data == 0:
        ledButton.config(image=led_off_img)
        ledButton.image = led_off_img


def listenerFirebase():
    firebase_admin.db.reference("/temp").listen(listener_temp)
    firebase_admin.db.reference("/humi").listen(listener_humi)
    firebase_admin.db.reference("/led").listen(listener_led)

def update_led():
    value = db.reference("/led").get()
    db.reference("/led").set(0 if value == 1 else 1)


if __name__ == '__main__':
    root = tkinter.Tk()
    root.geometry("1000x500")
    root.title("Firebase console")

    myfont36 = font.Font(family='Helvetica', size=36, weight='bold')
    myfont24 = font.Font(family='Helvetica', size=24)

    led_on_img = ImageTk.PhotoImage(Image.open('led_on.png'))
    led_off_img = ImageTk.PhotoImage(Image.open('led_off.png'))

    tempValue = tkinter.StringVar()
    tempValue.set("00.0 C")

    humiValue = tkinter.StringVar()
    humiValue.set("00.0 %")

    tempLabel = tkinter.Label(root, textvariable=tempValue, font=myfont36)
    humiLabel = tkinter.Label(root, textvariable=humiValue, font=myfont36)
    ledButton = tkinter.Button(root, image=led_off_img, font=myfont36, command=lambda: update_led())

    root.rowconfigure(0, weight=1)
    root.columnconfigure((0, 1, 2), weight=1)
    tempLabel.grid(row=0, column=0, sticky='EWNS')
    humiLabel.grid(row=0, column=1, sticky='EWNS')
    ledButton.grid(row=0, column=2, sticky='EWNS')

    t1 = threading.Thread(target=listenerFirebase)
    t1.start()

    root.mainloop()
