#encoding: utf-8

from flask import Flask,render_template,request,session,redirect,url_for,g
import os

app = Flask(__name__)
app.config['SECRET_KEY'] = os.urandom(24)


@app.route('/')
def hello_world():
    print 'index'
    return render_template('index.html')

@app.route('/login/',methods=['GET','POST'])
def login():
    print 'login'
    if request.method == 'GET':
        return render_template('login.html')
    else:
        username = request.form.get('username')
        password = request.form.get('password')
        if username == 'admin' and password == '111111':
            session['username'] = 'admin'
            'user_id'
            return u'登录成功'
        else:
            return u'用户名或密码错误！'

@app.route('/edit/')
def edit():
    # user_id = session.get('user_id')
    # if user_id:
    #     user = User.query.filter(User.id == user_id).first()


    # if hasattr(g,'username'):
    #     return render_template('edit.html')
    # else:
    #     return redirect(url_for('login'))
    # 上下文处理器起作用的位置
    return render_template('edit.html')


# before_requst：在请求之前执行的
# before_request是在视图函数执行之前执行的
# before_request这个函数只是一个装饰器，他可以把需要设置为钩子函数的代码放到视图函数执行之前来执行

@app.before_request
def my_before_request():
    # user_id = session.get('user_id')
    # user = User.query.filter(User.id==user_id).first()
    # g.user = user
    print 'hello world'
    if session.get('username'):
        g.username = session.get('username',username='admin')

# 上下文处理器应该返回一个字典。字典中的`key`会被模板中当成变量来渲染。
@app.context_processor
def my_context_processor():
    # username = session.get('username')
    # if username:
    #     return {'username':username}
    return {'username':'111111'}


if __name__ == '__main__':
    app.run(debug=True)
