#encoding: utf-8

from flask import Flask,redirect,url_for

app = Flask(__name__)


@app.route('/')
def index():
    login_url = url_for('login')
    return redirect(login_url)
    return u'这是首页'

@app.route('/login/')
def login():
    return u'这是登录页面'

@app.route('/question/<is_login>/')
def question(is_login):
    if is_login == '1':
        return u'这是发布问答页面'
    else:
        return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)
