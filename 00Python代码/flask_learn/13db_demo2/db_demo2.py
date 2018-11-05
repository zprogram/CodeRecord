#encoding: utf-8

from flask import Flask
from flask_sqlalchemy import SQLAlchemy
import config

app = Flask(__name__)
app.config.from_object(config)

db = SQLAlchemy(app)

# article表：
# create table article (
#     id int primary key autoincrement,
#     title varchar(100) not null,
#     content text not null,
# )

class Article(db.Model):
    __tablename__ = 'article'
    id = db.Column(db.Integer,primary_key=True,autoincrement=True)
    title = db.Column(db.String(100),nullable=False)
    content = db.Column(db.Text,nullable=False)

# 创建数据库
db.create_all()

@app.route('/')
def hello_world():
    # # 增加：
    # article1 = Article(title='aaa',content='bbb')
    # db.session.add(article1)
    # # 事务
    # db.session.commit()

    # # 查
    # select * from article where article.title='aaa';
    # 查询所有数据
    # article1 = Article.query.filter(Article.title == 'aaa').all()
    # for v in article1:
    #     print v.id
    # 查询第一条记录
    # article1 = Article.query.filter(Article.title == 'aaa').first()
    # print 'title:%s' % article1.title
    # print 'content:%s' % article1.content

    # # 改：
    # # 1. 先把要更改的数据查找出来
    # article1 = Article.query.filter(Article.title == 'aaa').first()
    # # 2. 把这条数据，需要修改的地方进行修改
    # article1.title = 'new title'
    # # 3. 做事务的提交
    # db.session.commit()

    # # 删
    # # 1. 把需要删除的数据查找出来
    # article1 = Article.query.filter(Article.content == 'bbb').first()
    # # 2. 把这条数据删除掉
    # db.session.delete(article1)
    # # 3. 做事务提交
    # db.session.commit()

    return 'Hello World!'


if __name__ == '__main__':
    app.run(debug=True)
