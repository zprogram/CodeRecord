# -*- coding=utf-8 -*-
import time
import itchat
import threading


# define the sign function , sign in daily 00:00 - 00:01
def sign():
    today = int(time.strftime('%y%m%d', time.localtime(time.time())))
    while True:
        print today
        mps = itchat.get_mps()
        #print mps
        mps = itchat.search_mps(name='T00ls')
        print mps
        userName = mps[0]['UserName']
        print userName
        itchat.send("3",toUserName = userName)
        time.sleep(40200)

        if today == int(time.strftime('%y%m%d', time.localtime(time.time()))):
            time.sleep(60)
        else:
            try:
                #itchat.send(msg='3',toUserName='T00lsNet')
                time.sleep(3)
                #itchat.send(msg='4',toUserName='T00lsNet')
                today = int(time.strftime('%y%m%d', time.localtime(time.time())))
            except Exception,e:
                print('Error : '+ str(e))


# login the wechat by scan QR code
itchat.auto_login(enableCmdQR=True)
t = threading.Thread(target=sign)
t.setDaemon(True)
t.start()
itchat.run()