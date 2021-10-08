import sys
reload(sys)
sys.setdefaultencoding('utf-8')

from flask import Flask
from flask_sqlalchemy import SQLAlchemy
from flaskext.mysql import MySQL

app = Flask(__name__)
app.secret_key = 'secreeeeeeeeeeeeet'
app.config['SQLALCHEMY_DATABASE_URI'] = 'mysql+mysqlconnector://root:rootroot@localhost/PET_SHOP'
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
db = SQLAlchemy(app)


import models, routes