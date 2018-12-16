#encoding: utf-8

# dialect+driver://username:password@host:port/database
HOST = '127.0.0.1'
PORT = '3306'
DATABASE = 'db_demo1'
USERNAME = 'root'
PASSWORD = 'root'
DIALECT = 'mysql'
DRIVER = 'mysqldb'


SQLALCHEMY_DATABASE_URI = "{}+{}://{}:{}@{}:{}/{}?charset=utf8".format(DIALECT,DRIVER,USERNAME,PASSWORD,HOST
                                             ,PORT,DATABASE)

SQLALCHEMY_TRACK_MODIFICATIONS = False