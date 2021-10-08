#!/usr/bin/env python
# -*- coding: utf-8 -*- 

from functools import wraps
from flask import url_for,redirect, flash,session

def requires_access_level(access_level):
    def decorator(f):
        @wraps(f)
        def decorated_function(*args, **kwargs):
            if 'ACCEES_LEVEL' not in session or session['ACCEES_LEVEL'] not in access_level:
                flash('Вы не можете выполнить этот запрос !','error')
                return redirect(url_for('main_page'))
            return f(*args, **kwargs)
        return decorated_function
    return decorator