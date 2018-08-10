#!/usr/bin/env python
#coding:utf-8

import urllib
import urllib2

def loadPage(url, filename):
    """
        作用：根据url发送请求，获取服务器响应文件
        url: 需要爬取的url地址
        filename : 处理的文件名
    """
    filename = '下载 ' + filename
    print filename.decode("utf-8")
    headers = {"User-Agent" : "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_7_0) AppleWebKit/535.11 (KHTML, like Gecko) Chrome/17.0.963.56 Safari/535.11"}

    request = urllib2.Request(url, headers = headers)
    return urllib2.urlopen(request).read()

def writePage(html, filename):
    """
        作用：将html内容写入到本地
        html：服务器相应文件内容
    """
    tips =  "正在保存 " + filename
    print tips.decode("utf-8")

    # 文件写入
    with open(filename.decode("utf-8"), "w") as f:
        f.write(html)
    print "-" * 30

def tiebaSpider(url, beginPage, endPage):
    """
        作用：贴吧爬虫调度器，负责组合处理每个页面的url
        url : 贴吧url的前部分
        beginPage : 起始页
        endPage : 结束页
    """
    for page in range(beginPage, endPage + 1):
        pn = (page - 1) * 50
        filename = "第" + str(page) + "页.html"

        fullurl = url + "&pn=" + str(pn)

        html = loadPage(fullurl, filename)
        #print html
        writePage(html,filename)

    tips = "谢谢使用"
    print tips.decode("utf-8")

if __name__ == "__main__":
    # kw = raw_input("请输入需要爬取的贴吧名:")
    # beginPage = int(raw_input("请输入起始页："))
    # endPage = int(raw_input("请输入结束页："))
    kw = "python"
    beginPage = 1
    endPage = 3

    url = "http://tieba.baidu.com/f?"
    key = urllib.urlencode({"kw": kw})
    fullurl = url + key
    tiebaSpider(fullurl, beginPage, endPage)





