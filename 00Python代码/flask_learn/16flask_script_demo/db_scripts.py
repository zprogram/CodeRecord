#encoding: utf-8

from flask_script import Manager


DBManager = Manager()

@DBManager.command
def init():
    print '数据库初始化完成'

@DBManager.command
def migrate():
    print '数据表迁移成功'