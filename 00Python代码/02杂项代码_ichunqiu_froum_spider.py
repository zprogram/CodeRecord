#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Date    : 2017-03-19 15:06:48
# @Author  : 江sir (qq:2461805286)
# @Link    : http://www.blogsir.com
# @Version : v1.0


import requests
from bs4 import BeautifulSoup as bs
import threading
import re
from Queue import Queue
from prettytable import PrettyTable

thread_count = 10 #修改线程
page = 5 #可修改抓取页数

x = PrettyTable(["page","url","热度",'title'])
x.align["title"] = "1" # Left align city names
x.padding_width = 1

# headers = {'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; WOW64; rv:50.0) Gecko/20100101 Firefox/50.0'}
# html = requests.get('https://bbs.ichunqiu.com/forum-59-1.html',headers=headers)
# soup = bs(html.text,"lxml")
# res = soup.find_all(name="img", attrs={'alt':'heatlevel'})
# for i in res:
#   for j in  i.parent.contents:
#       if str(j).startswith('<a'):
#           # print j['href'],j.text
#           title = j.text
#           link = 'https://bbs.ichunqiu.com/'+j['href']
#           break
#   level = i['title'].split(':')[-1]

#   x.add_row([link,level,title])

# print x


class ichunqiu(threading.Thread):
    def __init__(self,queue):
        threading.Thread.__init__(self)
        self.Q = queue
        self.headers = {'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; WOW64; rv:50.0) Gecko/20100101 Firefox/50.0'}

    def run(self):
        while 1:
            try:
                url = self.Q.get(True,1)
                # print url
                self.spider(url)
            except:break

    def spider(self,url):
        try:
            html = requests.get(url,headers=self.headers,timeout=3).text
        except:
            html = ''
        # print len(html)
        soup = bs(html,"lxml")
        res = soup.find_all(name="img",attrs={'alt':'heatlevel'})
        page_num = re.findall('\-(\d+)\.',url)[0]
        for i in res:
            for j in  i.parent.contents:
                if str(j).startswith('<a'):
                    print j['href'],j.text
                    title = j.text
                    link = 'https://bbs.ichunqiu.com/'+j['href']
                    break
            level = i['title'].split(':')[-1]
            title.decode("utf-8")
            x.add_row([page_num,link,level,title])



def Load_Thread(queue):
    return [ichunqiu(queue) for i in range(thread_count)]

def Start_Thread(threads):
    print 'thread is start...'
    for t in threads:
        t.setDaemon(True)
        t.start()
    for t in threads:
        t.join()
    print 'thread is end...'

def main():
    queue = Queue()
    for i in range(page,0,-1):
        target = 'https://bbs.ichunqiu.com/forum-59-%s.html'%i
        queue.put(target)

    thread_list = Load_Thread(queue)
    Start_Thread(thread_list)
    print x


if __name__ == '__main__':
    main()
