import firebase_admin
from firebase_admin import credentials
from firebase_admin import db

cred = credentials.Certificate('key.json')
firebase_admin.initialize_app(cred, {
    'databaseURL': 'https://d1mini-vincent-default-rtdb.firebaseio.com/'
})

if __name__ == '__main__':
    while True:
        value = int(input('是否要開燈/關燈(開:1 關:0): '))
        db.reference("/led").set(value)

