#!/usr/bin/env python
# -*- coding:utf-8 -*-

import json
import threading
import requests
import urllib2
import sys
import threading
from time import ctime,sleep
import threadpool

# 主要执行函数
def main():
    f = open("target.txt")
    line = f.readlines()
    global g_list
    g_list = []
    urllist = []
    for url in line:
        url = url.rstrip()                      #  读取文本
        urllist.append(url)                     #  保存url的列表
    thread_requestor(urllist)                   # 线程池函数
    f = open('vulurl.txt','w')
    for q in g_list:                            # 保存线程回调函数的值到vulurl.txt中
        f.write(q+"\n")
    f.close()

# 回调函数的结果保存到g_list数组中
def res_printer(res1,res2):
    if res2:
        #print ('"线程返回的地址 = " %s ')% res2
        g_list.append(res2)
    else:
        pass

# 线程池函数
def thread_requestor(urllist):
    pool =  threadpool.ThreadPool(200)                                    # 线程池数量
    reqs =  threadpool.makeRequests(getScan,urllist,res_printer)          # 使用线程池
    [pool.putRequest(req) for req in reqs]                                # 简写 for req in reqs pool.putRequest(req)
    pool.wait()

# 检测HTTP状态码函数
def getScan(url):
    try:
        requests.packages.urllib3.disable_warnings()                      # 忽略HTTPS连接错误的警告
        status = requests.get(url, proxies=None, timeout=3,verify=False)  # 获取HTTP状态码
        print "scanning " + url + "\n"                                    # 正在扫描的地址
        if status.status_code == 200:                                     # 访问成功的网站可以返回
            return url
        else:
            pass
    except:
        pass

if __name__ == "__main__":
    main()