#!/usr/bin/env python
# -*- coding: utf-8 -*- 

from flask import render_template, redirect, url_for, request, flash,session
from flask_login import login_user, login_required, logout_user
from werkzeug.security import check_password_hash, generate_password_hash
from sqlalchemy.sql import func

from start import app,db
from models import Pet,User,Role,OrderStatus,Order
from access_level import requires_access_level

@app.route('/', methods=['GET'])
def main_page():
    update_count_in_backet_and_orders()
    return render_template('index.html', pets = Pet.query.all(), session = session)

@app.route('/login', methods=['POST'])
def login():
    if request.method == 'POST':
        user_login = request.form['login']
        user_password = request.form['password']
        user = User.query.filter_by(USER_LOGIN = user_login).first()

        if user and check_password_hash(user.USER_PASS, user_password):
            user_role = Role.query.filter_by(ROLE_ID = user.ROLES_ROLE_ID).first()
            session['ACCEES_LEVEL'] = user_role.ROLE_NAME
            session['USER_ID'] = user.USER_ID
            flash('Вход успешно произведён !','success')
            return redirect(url_for('main_page'))
        else:
            flash('Неправильное имя пользователя или пароль !','error')
    return redirect(url_for('main_page'))

@app.route('/logout')
@requires_access_level(['User','Admin'])
def logout():
    session['USER ID'] = -1
    session['ACCEES_LEVEL'] = 'Anon'
    flash('Выход успешно произведён !','success')
    return redirect(url_for('main_page'))

@app.route('/register', methods=['POST'])
def register():
    if request.method == 'POST':
        user_login = request.form['login']
        user_password = request.form['password']
        user_password_confirm = request.form['passwordConfirm']
        user_phone_number = request.form['phoneNumber']
        user_email = request.form['email']
        if user_password != user_password_confirm:
            flash('Пароли не свопадают !','error')
        else:
            check_for_same_login = User.query.filter_by(USER_LOGIN = user_login).first()
            if check_for_same_login:
                flash('Пользователь с таким именем уже существует !','error')
                return redirect(url_for('main_page'))
            user_role = Role.query.filter_by(ROLE_NAME = 'User').first()
            hashed_password = generate_password_hash(user_password)
            new_user = User(USER_LOGIN = user_login, USER_PASS = hashed_password, USER_PHONE_NUMBER = user_phone_number, \
                            USER_EMAIL = user_email, ROLES_ROLE_ID = user_role.ROLE_ID)
            db.session.add(new_user)
            db.session.commit()
            flash('Аккаунт успешно зарегестрирован !','success')
    return redirect(url_for('main_page'))



@app.route('/account_management', methods=['POST'])
@requires_access_level(['User'])
def account_management():
    if request.method == 'POST':
        new_number = request.form['new_number']
        new_email = request.form['new_email']
        new_password = request.form['new_password']
        new_password_confirm = request.form['new_password_confirm']
        user_password = request.form['password']
        is_new_data_entered = new_number or new_email or (new_password and new_password_confirm)

        if is_new_data_entered:
            user = User.query.filter_by(USER_ID = session['USER_ID']).first()

            if check_password_hash(user.USER_PASS, user_password):
                if new_password:
                    if new_password == new_password_confirm:
                        hashed_password = generate_password_hash(new_password)
                        user.USER_PASS = hashed_password
                    else:
                        flash('Новые пароли не свопадают !','error')
                        return redirect(url_for('main_page'))

                if new_number:
                    user.USER_PHONE_NUMBER = new_number

                if new_email:
                    user.USER_EMAIL = new_email
                db.session.commit()
                flash('Данные успешно изменены !','success')
            else:
                flash('Введён неверный текущий пароль !','error')  
    return redirect(url_for('main_page'))

def update_count_in_backet_and_orders():
    if 'ACCEES_LEVEL' not in session:
        session['ACCEES_LEVEL'] = 'Anon'
        session['USER_ID'] = -1
    if session['ACCEES_LEVEL'] == 'User':
        in_backet_status = OrderStatus.query.filter_by(STATUS_NAME = 'In backet').first()
        in_stock_status = OrderStatus.query.filter_by(STATUS_NAME = 'In stock').first()
        if Order.query.filter_by(USERS_USER_ID = session['USER_ID'], ORDER_STATUS_STATUS_ID = in_stock_status.STATUS_ID).count() > 0:
            flash('У вас есть заказы, которые ожидают, когда вы их заберёте !', 'warning')
        session['ORDERS_COUNT'] = Order.query.filter_by(USERS_USER_ID = session['USER_ID']).count()
        session['BACKET_COUNT'] = Order.query.filter_by(USERS_USER_ID = session['USER_ID'], ORDER_STATUS_STATUS_ID = in_backet_status.STATUS_ID).count()
        session['ORDERS_COUNT'] = session['ORDERS_COUNT'] - session['BACKET_COUNT']


@app.route('/backet', methods=['GET'])
@requires_access_level(['User'])
def backet():
    in_backet_status = OrderStatus.query.filter_by(STATUS_NAME = 'In backet').first()
    backet_orders = db.session.query(Order, Pet).filter_by( USERS_USER_ID = session['USER_ID'],\
                                                            ORDER_STATUS_STATUS_ID = in_backet_status.STATUS_ID).join(Pet).all() 
    return render_template('backet.html', orders = backet_orders, session = session)


@app.route('/add_to_backet/<pet_id>', methods=['GET'])
@requires_access_level(['User'])
def add_to_backet(pet_id):
    new_order = Order(PETS_PET_ID = pet_id, USERS_USER_ID = session['USER_ID'], ORDER_PRICE = 0, ORDER_DATE = '2020-2-2', ORDER_STATUS_STATUS_ID = '0')
    db.session.add(new_order)
    db.session.commit()
    flash('Питомец добавлен в корзину !','success')
    return redirect(url_for('main_page'))

@app.route('/delete_from_backet/<order_id>', methods=['GET'])
@requires_access_level(['User'])
def delete_from_backet(order_id):
    in_backet_status = OrderStatus.query.filter_by(STATUS_NAME = 'In backet').first()
    Order.query.filter_by(ORDER_ID = order_id, USERS_USER_ID = session['USER_ID'], ORDER_STATUS_STATUS_ID = in_backet_status.STATUS_ID).delete()
    db.session.commit()
    flash('Питомец убран из корзины !','success')
    update_count_in_backet_and_orders()
    return redirect(url_for('backet'))

@app.route('/pay', methods=['GET'])
@requires_access_level(['User'])
def pay():
    in_backet_status = OrderStatus.query.filter_by(STATUS_NAME = 'In backet').first()
    paid_status = OrderStatus.query.filter_by(STATUS_NAME = 'Paid').first()
    orders = Order.query.filter_by(USERS_USER_ID = session['USER_ID'], ORDER_STATUS_STATUS_ID = in_backet_status.STATUS_ID)
    for order in orders:
        order.ORDER_STATUS_STATUS_ID = paid_status.STATUS_ID
        order.ORDER_DATE = func.now()
    db.session.commit()
    update_count_in_backet_and_orders()
    flash('Оплачено успешно!','success')
    return redirect(url_for('orders'))

@app.route('/orders', methods=['GET'])
@requires_access_level(['User','Admin'])
def orders():
    in_backet_status = OrderStatus.query.filter_by(STATUS_NAME = 'In backet').first()
    if session['ACCEES_LEVEL'] == 'User':
        backet_orders = db.session.query(Order, OrderStatus,Pet).filter( Order.USERS_USER_ID == session['USER_ID'],\
                                                                     Order.ORDER_STATUS_STATUS_ID != in_backet_status.STATUS_ID).join(OrderStatus).join(Pet).all() 
        return render_template('orders.html', orders = backet_orders)
    if session['ACCEES_LEVEL'] == 'Admin':
        backet_orders = db.session.query(Order, OrderStatus,Pet, User).filter( Order.ORDER_STATUS_STATUS_ID != in_backet_status.STATUS_ID)\
                                                                        .join(OrderStatus).join(Pet).join(User).all()
        return render_template('orders.html', orders = backet_orders)


@app.route('/pet_edit/<pet_id>', methods=['POST'])
@requires_access_level(['Admin'])
def pet_edit(pet_id):
    if request.method == 'POST':
        photo_url = request.form['photo_url']
        pet_name = request.form['pet_name']
        pet_price = request.form['pet_price']
        pet_description = request.form['pet_description']
        pet_to_edit = Pet.query.filter_by(PET_ID = pet_id).first()
        pet_to_edit.PET_IMAGE_LINK = photo_url
        pet_to_edit.PET_NAME = pet_name
        pet_to_edit.PET_PRICE = pet_price
        pet_to_edit.PET_DESCRIPTION = pet_description
        db.session.commit()
        flash('Данные успешно изменены!','success')
    return redirect(url_for('main_page'))

@app.route('/pet_delete/<pet_id>', methods=['GET'])
@requires_access_level(['Admin'])
def pet_delete(pet_id):
    Pet.query.filter_by(PET_ID = pet_id).delete()
    db.session.commit()
    flash('Данные успешно удалены!','success')
    return redirect(url_for('main_page'))

@app.route('/pet_add', methods=['POST'])
@requires_access_level(['Admin'])
def pet_add():
    if request.method == 'POST':
        photo_url = request.form['photo_url']
        pet_name = request.form['pet_name']
        pet_price = request.form['pet_price']
        pet_description = request.form['pet_description']
        new_pet = Pet(PET_IMAGE_LINK = photo_url, PET_NAME = pet_name, PET_PRICE = pet_price, PET_DESCRIPTION = pet_description)
        db.session.add(new_pet)
        db.session.commit()
        flash('Питомец успешно добавлен!','success')
    return redirect(url_for('main_page'))

@app.route('/order_confirm_give/<order_id>', methods=['GET'])
@requires_access_level(['Admin'])
def order_confirm_give(order_id):
    order_to_confirm = Order.query.filter_by(ORDER_ID = order_id).first()
    given_status = OrderStatus.query.filter_by(STATUS_NAME = 'Given').first()
    order_to_confirm.ORDER_STATUS_STATUS_ID = given_status.STATUS_ID
    db.session.commit()
    flash('Статус заказа успешно изменён!','success')
    return redirect(url_for('orders'))

@app.route('/order_confirm_in_stock/<order_id>', methods=['GET'])
@requires_access_level(['Admin'])
def order_confirm_in_stock(order_id):
    order_to_confirm = Order.query.filter_by(ORDER_ID = order_id).first()
    in_stock_status = OrderStatus.query.filter_by(STATUS_NAME = 'In stock').first()
    order_to_confirm.ORDER_STATUS_STATUS_ID = in_stock_status.STATUS_ID
    db.session.commit()
    flash('Статус заказа успешно изменён!','success')
    return redirect(url_for('orders'))

@app.route('/remove_order/<order_id>', methods=['GET'])
@requires_access_level(['Admin'])
def remove_order(order_id):
    Order.query.filter_by(ORDER_ID = order_id).delete()
    db.session.commit()
    flash('Заказ успешно удалён!','success')
    return redirect(url_for('orders'))