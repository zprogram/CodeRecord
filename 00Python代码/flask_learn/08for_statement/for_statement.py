#encoding: utf-8

from flask import Flask,render_template

app = Flask(__name__)


# for遍历字典

@app.route('/')
def index():
    books = [
        {
            'name': u'西游记',
            'author': u'吴承恩',
            'price': 109
        },
        {
            'name': u'红楼梦',
            'author': u'曹雪芹',
            'price': 200
        },
        {
            'name': u'三国演义',
            'author': u'罗贯中',
            'price': 120
        },
        {
            'name': u'水浒传',
            'author': u'施耐庵',
            'price': 130
        }
    ]
    return render_template('index.html',books=books)


if __name__ == '__main__':
    app.run(debug=True)
