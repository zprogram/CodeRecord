#!/usr/bin/python
#coding:utf-8

import socket
import sys,os
iplist = []

# author:zzzhh
#  使用方法
# ip地址排序.py D:\IP.txt
# 在同目录生成排序好的IP文件 D:\ip.txt_sort.txt


#读取文件函数
def read_file(file_path):
    # 判断文件路径是否存在，如果不存在直接退出，否则读取文件内容
    if not os.path.exists(file_path):
        print 'Please confirm correct filepath !'
        sys.exit(0)
    else:
        with open(file_path, 'r') as source:
            for line in source:
                iplist.append(line.rstrip('\r\n').rstrip('\n'))


				
				
if __name__ == '__main__':
    file_str = sys.argv[1]  # 读取参数列表
    read_file(file_str)     # 读取文件
    f1 = open(file_str+"_sort.txt", 'w')
    for i in sorted(iplist,key=socket.inet_aton):
        print i
        f1.writelines(i+"\n")
    f1.close()