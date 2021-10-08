#!/usr/bin/env python
# -*- coding: utf-8 -*- 

from start import db


class Role(db.Model):
    __tablename__ = 'ROLES'
    ROLE_ID = db.Column(db.Integer, primary_key = True)
    ROLE_NAME = db.Column(db.String(45), nullable = False)

class User(db.Model):
    __tablename__ = 'USERS'
    USER_ID = db.Column(db.Integer, primary_key = True)
    USER_LOGIN = db.Column(db.String(45), nullable = False, unique = True)
    USER_PASS = db.Column(db.String(120), nullable = False)
    USER_PHONE_NUMBER = db.Column(db.String(13), nullable = False)
    USER_EMAIL = db.Column(db.String(45), nullable = False)
    ROLES_ROLE_ID = db.Column(db.Integer, db.ForeignKey('ROLES.ROLE_ID'),nullable = False)

class Pet(db.Model):
    __tablename__ = 'PETS'
    PET_ID = db.Column(db.Integer, primary_key = True)
    PET_IMAGE_LINK = db.Column(db.String(350), nullable = False)
    PET_NAME = db.Column(db.String(45), nullable = False)
    PET_PRICE = db.Column(db.Integer, nullable = False)
    PET_DESCRIPTION = db.Column(db.Text, nullable = False)

class OrderStatus(db.Model):
    __tablename__ = 'ORDER_STATUS'
    STATUS_ID = db.Column(db.Integer, primary_key = True)
    STATUS_NAME = db.Column(db.String(45), nullable = False)

class Order(db.Model):
    __tablename__ = 'ORDERS'
    ORDER_ID = db.Column(db.Integer, primary_key = True)
    PETS_PET_ID = db.Column(db.Integer, db.ForeignKey('PETS.PET_ID'),nullable = False)
    USERS_USER_ID = db.Column(db.Integer, db.ForeignKey('USERS.USER_ID'),nullable = False)
    ORDER_PRICE = db.Column(db.Integer, nullable = False)
    ORDER_DATE = db.Column(db.DateTime, nullable = False)
    ORDER_STATUS_STATUS_ID = db.Column(db.Integer, db.ForeignKey('ORDER_STATUS.STATUS_ID'),nullable = False)