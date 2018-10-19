#encoding: utf-8
from flask import Flask,render_template

app = Flask(__name__)


@app.route('/')
def index():
    # 类
    class Person(object):
        name = u'p17bdw'
        age = 18

    p = Person()

    context = {
        'username': u'c17bdw',
        'gender': u'男',
        'age': 17,
        'person': p,    # 声明
        'websites': {
            'baidu': 'www.baidu.com',
            'google': 'www.google.com'
        }
    }
    return render_template('anthoer/index.html',**context)


if __name__ == '__main__':
    app.run(debug=True)
