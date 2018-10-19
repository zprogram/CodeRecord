#encoding: utf-8

from flask import Flask
import config

# 载入配置文件
app = Flask(__name__)
app.config.from_object(config)

@app.route('/')
def hello_world():
    return 'Debug 模式'

if __name__ == '__main__':
    app.run()
    # 或者直接写在run中
    # app.run(DEBUG = True)