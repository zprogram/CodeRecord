#encoding: utf-8

# 导入模块
from flask import Flask
import config

# 声明Flask类实例
app = Flask(__name__)
# 导入配置文件
app.config.from_object(config)



# 建立路由
@app.route('/')
def hello_world():
    return 'hello world11'

# 主函数
if __name__ == '__main__':
    app.run()