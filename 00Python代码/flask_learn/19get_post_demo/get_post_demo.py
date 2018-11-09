#encoding: utf-8

from flask import Flask,render_template,request

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/search/')
def search():
    # arguments
    q = request.args.get('q')
    return u'用户提交的查询参数是：%s' % q


# 默认的视图函数，只能采用get请求
# 如果你想采用post请求，那么要写明
@app.route('/login/',methods=['GET','POST'])
def login():
    if request.method == 'GET':
        return render_template('login.html')
    else:
        # 获取from表单的值
        username = request.form.get('username')
        password = request.form.get('password')
        print 'username:',username
        print 'password:',password
        return 'post request'



if __name__ == '__main__':
    app.run(debug=True)
