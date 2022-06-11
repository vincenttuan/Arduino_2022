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
ledLabel = tkinter.Label(root, image=led_off_img, font=myfont36)

root.rowconfigure(0, weight=1)
root.columnconfigure((0, 1, 2), weight=1)
tempLabel.grid(row=0, column=0, sticky='EWNS')
humiLabel.grid(row=0, column=1, sticky='EWNS')
ledLabel.grid(row=0, column=2, sticky='EWNS')

root.mainloop()
