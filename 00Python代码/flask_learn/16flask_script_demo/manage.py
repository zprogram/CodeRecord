#encoding: utf-8

from flask_script import Manager
from flask_script_demo import app
from db_scripts import DBManager

manager = Manager(app)


# 自定义命令一：
# python manage.py runserver
@manager.command
def runserver():
    print '服务器跑起来了!!!!!'


# 和数据库相关的操作，都放在一起
# 自定义命令二：
# python manage.py db init
manager.add_command('db',DBManager)


if __name__ == '__main__':
    manager.run()

