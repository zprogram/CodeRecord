#encoding: utf-8

from flask import Flask
from flask_sqlalchemy import SQLAlchemy
import config

app = Flask(__name__)
app.config.from_object(config)
db = SQLAlchemy(app)

# # 用户表
# create table users (
#     id int primary key autoincrement,
#     username varchar(100) not null
# )
# # 文章表
# create table article (
#     id int primary key autoincrement,
#     title varchar(100) not null,
#     content text not null
#     author_id int,
#     foreign key `author_id` references `users.id`
# )

class User(db.Model):
    __tablename__ = 'user'
    id = db.Column(db.Integer,primary_key=True,autoincrement=True)
    username = db.Column(db.String(100),nullable=False)



class Article(db.Model):
    __tablename__ = 'article'
    id = db.Column(db.Integer, primary_key=True, autoincrement=True)
    title = db.Column(db.String(100),nullable=False)
    content = db.Column(db.Text,nullable=False)
    author_id = db.Column(db.Integer,db.ForeignKey('user.id'))
    # 给`Article`这个模型添加一个 `author`属性，可以访问这篇文章的作者的数据，像访问普通模型一样。
    # `backref`是定义反向引用，可以通过`User.articles`访问这个模型所写的所有文章。
    author = db.relationship('User',backref=db.backref('articles'))

db.create_all()


@app.route('/')
def index():
    # 想要添加一篇文章，因为文章必须依赖用户而存在，所以首先的话，先添加一个用户
    # 添加一个用户
    # user1 = User(username='admin')
    # db.session.add(user1)
    # db.session.commit()

    # 添加一篇文章
    # article = Article(title='aaa',content='bbb',author_id=1)
    # db.session.add(article)
    # db.session.commit()

    # 我要找文章标题为aaa的这个作者 方法1
    # article = Article.query.filter(Article.title == 'aaa').first()
    # author_id = article.author_id
    # user = User.query.filter(User.id == author_id).first()
    # print 'username:%s' % user.username

    # 方法2
    # article = Article.query.filter(Article.title == 'aaa').first()
    # article.author

    # 查询作者写过的文章
    # author = User.query.filter(User.username=='admin').first()
    # author.articles

    # 作者创建文章
    # article = Article(title='aaac',content='bbbc')
    # article.author = User.query.filter(User.id == 1).first()
    # db.session.add(article)
    # db.session.commit()

    # 我要找文章标题为aaa的这个作者
    # artile = Article.query.filter(Article.title == 'aaa').first()
    # print 'username:%s' % artile.author.username

    # 我要找到zhiliao 这个用户写过的所有文章
    # 添加文章
    # article = Article(title='111',content='222',author_id=1)
    # db.session.add(article)
    # db.session.commit()
    # # 查询用户写的文章
    # user = User.query.filter(User.username == 'admin').first()
    # result = user.articles
    # for article in result:
    #     print '-'*10
    #     print article.title

    return 'index'


if __name__ == '__main__':
    app.run(debug=True)
