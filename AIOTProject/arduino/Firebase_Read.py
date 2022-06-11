import firebase_admin
from firebase_admin import credentials
from firebase_admin import db

cred = credentials.Certificate('key.json')
firebase_admin.initialize_app(cred, {
    'databaseURL': 'https://d1mini-vincent-default-rtdb.firebaseio.com/'
})

#temp = db.reference("/temp").get()
#print("temp:", temp)


def listener_temp(event):
    print("temp:", event.data)


# listener
firebase_admin.db.reference("/temp").listen(listener_temp)

