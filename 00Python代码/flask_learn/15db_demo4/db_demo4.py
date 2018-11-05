#encoding: utf-8

from flask import Flask
import config
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)
app.config.from_object(config)

db = SQLAlchemy(app)

# create table article (
#     id int primary key autoincrement,
#     title varchar(100) not null,
# )
#
# create table tag (
#     id int primary key autoincrement,
#     name varchar(50) not null,
# )
#
# create table article_tag (
#     article_id int,
#     tag_id int,
#     primary key('article_id','tag_id'),
#     foreign key `article_id` references `article.id`,
#     foreign key `tag_id` references `tag.id`,
# )

article_tag = db.Table('article_tag',
        db.Column('article_id',db.Integer,db.ForeignKey('article.id'),primary_key=True),
        db.Column('tag_id',db.Integer,db.ForeignKey('tag.id'),primary_key=True)
    )

class Article(db.Model):
    __tablename__ = 'article'
    id = db.Column(db.Integer,primary_key=True,autoincrement=True)
    title = db.Column(db.String(100),nullable=False)

    tags = db.relationship('Tag',secondary=article_tag,backref=db.backref('articles'))

class Tag(db.Model):
    __tablename__ = 'tag'
    id = db.Column(db.Integer, primary_key=True, autoincrement=True)
    name = db.Column(db.String(100), nullable=False)

db.create_all()


@app.route('/')
def hello_world():

    article1 = Article(title='aaa')
    article2 = Article(title='bbb')

    tag1 = Tag(name='111')
    tag2 = Tag(name='222')

    article1.tags.append(tag1)
    article1.tags.append(tag2)

    article2.tags.append(tag1)
    article2.tags.append(tag2)

    db.session.add(article1)
    db.session.add(article2)

    db.session.add(tag1)
    db.session.add(tag2)

    db.session.commit()

    article1 = Article.query.filter(Article.title == 'aaa').first()
    tags = article1.tags
    for tag in tags:
        print tag.name

    return 'Hello World!'


if __name__ == '__main__':
    app.run(debug=True)
