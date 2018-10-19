#encoding: utf-8

from flask import Flask

app = Flask(__name__)


@app.route('/')
def hello_world():
    return 'Hello World!'


@app.route('/article/<id>')
def article(id):
    return u'您请求的参数是：%s' % id


if __name__ == '__main__':
    app.run(debug=True)
