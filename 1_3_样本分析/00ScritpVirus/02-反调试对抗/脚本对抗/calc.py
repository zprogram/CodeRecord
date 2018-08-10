#! /usr/bin/env python
# -*- coding: utf-8 -*-

import os
import sys

def payload(files):
    shellcode = ""
    ctr = 1
    maxlen = 15 #to create rows
    try:
        for b in open(files, "rb").read():
            shellcode +=b.encode("hex")
            if ctr == maxlen:
                ctr = 0
            ctr += 1
        print "Code length: " + str(len(shellcode))
        return shellcode
    except:
        print "ת��ʧ�ܣ�����!"

f = open('calc_hex.txt','w')
files = "calc.exe" 
a = payload(files)
f.write(a)
f.close()