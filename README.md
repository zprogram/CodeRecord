## 说明

 为了将自己调试过的代码做一个记录保存下来。把基础知识和项目也聚集起来，梳理知识框架。


## 目标

 Github单个仓库1G空间，单个文件不超过1000M
 啥时候能堆满，就开新的仓库。

- 恶意代码分析
- 取证分析
- Web安全
- 信息安全工程理论

## 1、恶意代码分析

### 1.1、Windows编程基础

#### 1.1.1、C语言基础

#### 1.1.2、C++基础

#### 1.1.3、数据结构基础与算法

- 数组

- 链表
- 二叉树

#### 1.1.4、产出：C++程序基础项目

- C语言通讯录

- 课程管理系统



#### 1.1.5、Windows API编程

[](https://github.com/zprogram/CodeRecord/tree/master/03Win_Program)

- Windows数据类型
- 文件系统
- - 磁盘和驱动器管理
  - GetLogicalDriveStrings：获取主机中所有的逻辑驱动器
  - FindFirstVolume：查找主机的第一个驱动器，返回查找句柄
  - GetDriverType：获取驱动器类型
- - 文件和目录管理
  - DeleteFile：删除参数所指定的文件
  - CopyFile：复制指定文件为一个新文件
  - MoveFile：将指定文件或目录移动到指定位置
  - CreateFile：新建或打开一个文件，获取文件句柄
  - ReadFile：读取由文件句柄指定的文件中写入内容
  - WriteFile：向由文件句柄指定的文件中写入内容
  - GetFileSize：获取文件大小
  - CreateDirectory：创建一个目录
  - GetCurrentDirectory：获取当前程序所在目录
  - SetCurrentDirectory：设置当前程序所在目录
  - GetModuleFileName：获取当前模块路径
  - FindFirstFile：查找指定目录下第一个文件或目录，获得查找句柄
  - FindNextFile：根据FindFirstFile获得的句柄，循环查找文件和目录
  - GetFileAttributesEx：获取指定文件或目录属性
  - SetFileAttributes：将文件属性设定为指定值
  - FileTimeToLocalFileTime：将文件时间转换为本地时间
  - FileTimeToSystemTime：将文件时间转换为系统时间
- - 内存映射文件
  - GetSystemInfo：获取系统内存分配粒度
  - CreateFileMapping：创建mapping对象
  - MapViewOfFile：创建视图，将文件maping映射到当前进程内存虚拟地址空间。
  - FlushViewOfFile：将视图中的文件数据写入到磁盘上
  - FillMemory：填充内存
  - CopyMemory：复制内存
  - GetMappedFileName：从映射对象获取被映射文件的文件设备名
  - QueryDosDevice：获取MS_DOS设备名，例如将C:转换为设备名，"\\Device\\HarddiskVolume3"

- 内存管理
- - Windows内存管理原理
- - 堆管理
- - 全局（Global）和局部（Local）内存管理
- - 虚拟内存管理
- - 内存操作与内存信息管理

#####  网络通信编程

- OSI 7层模型
- 网络通信模型

#####  木马技术分析

- 注册表启动编程
- 服务木马编程
- 注入木马编程
- 下载者
- 关机程序
- 进程查杀程序
- 多线程DOS攻击程序

#### 1.1.6、界面编程

#####  SDK编程

#####  MFC编程

#### 1.1.7、RootKit基础

- 内核编程基础

- 钩子技术
- - SSDT钩子
- - SYSENETR钩子
- - 内联钩子
- - IRP钩子
- - IDT钩子
- - IOAPIC钩子
- - LADDR钩子
- Anti Rootkit
- - 检查SSDT钩子与IDT钩子
- - 检查IAT
- - 检查IRP钩子
- - 检查内联钩子

#### 1.1.8、产出：安全编程项目

- Windows安全卫士
- 远程控制

### 1.2、逆向基础

#### 1.2.1、x86汇编语言

- 栈
- 寄存器
- 指令

#### 1.2.2、Windows环境下32位汇编


#### 1.2.3、PE

- 32和64位区别
- PE字段中签名的位置

#### 1.2.4、加壳

#### 1.2.5、脱壳

##### 利用内存断点

##### 利用堆栈平衡
##### 利用编译语言特点
##### 利用跨区段跳转

##### 最后一次异常法

##### SFX法

##### DUMP及IAT重建

##### DLL文件脱壳

#### 1.2.6、反调试

#### 1.2.7、IDA使用

#### 1.2.8、移动平台分析

- JAVA基础
- Android开发基础
- Hook框架

#### 1.2.9、产出：安全编程相关项目

- PE文件解析器
- 壳
- 驱动加载
- CTF练习

### 1.3、恶意代码分析

#### 1.3.1、脚本类木马分析

- 文档类-office
- - 宏：Office Macor基础.md
- - Powershell：PowerShell基础.md
- - Javascript
- 恶意脚本对抗：一次红队之旅.md

#### 1.3.2、恶意代码持久化方式

- 服务
- 注册表
- DLL劫持
- 启动目录
- MBR
- PE感染（劫持插件）
- 快捷方式漏洞
- 磁盘固件
- 系统特性
- - NTFS：渗透测试的WINDOWS NTFS技巧集合.md

#### 1.3.3、APT样本

- 海莲花
- 摩诃草

#### 1.3.4、操作系统知识

- OPcode（硬编码）
- 保护模式

#### 1.3.5、漏洞知识

- office exp

### 1.4、快速分析思路

- Virustotal

- 沙箱收集行为

  - 网络行为
  - 后门行为

- 导入表信息

  - 注入类

    - CreateRemoteThread()：远程线程注入

    - SetWindowsHookEx()：钩子

  - 提升权限

    - AdjustTokenPrivileges()：修改权限操作

  - 遍历进程

    - CreateToolhelp32Snapshot()：遍历进程

  - 执行外部程序

    - ShellExecute()：执行文件
    - WinExec()：执行文件
    - CreateProcess()：打开一个文件进程

  - 注册表

    - RegOpenKeyEx()：打开注册表
    - RegCreateKeyEx()：创建注册表键值

  - 文件遍历

    - FindFirstFile()
    - FindNextFile()

  - 网络行为

    - bind()
    - listen()
    - socket()

- 字符串信息

  - APT

## 2、取证分析

### 2.1、Linux编程基础

#### 2.1.1、LinuxC程序设计
- Linux命令
- VIM命令
- shell
- 进程间通信
- ELF文件格式
- Linux操作系统内核

#### 2.1.2、Python

- Python语法
- 面向对象
- 常用库
#### 2.1.3、产出：渗透测试项目

- 众测平台
- 漏洞扫描
#### 2.1.4、Golang


### 2.2、取证分析

目标：操作系统中的恶意代码排查，怎么进来的，做了什么。

#### 2.2.1、内存分析

#### 2.2.2、流量分析

#### 2.2.3、入侵痕迹排查

- 漏洞分析
- 日志分析

#### 2.2.4、恶意代码分析

- 检测工具

## 3、Web安全

### 3.1、工具使用

- Burpsuite

### 3.2、代码审计分析

#### 3.2.1、Java

#### 3.2.2、php

### 3.3、应用层漏洞取证分析

#### 应用层

- Weblogic
- Tomcat
- Nignx

#### 数据库层

- ...

## 4、信息安全工程

### 4.1、法律知识

### 4.2、密码学

### 4.3、网络安全

### 4.4、系统安全

### 4.5、应用安全

### 4.6、信息系统安全

### 4.7、安全配置

- Windows基础
- Windows安全策略
- Linux基础
- Linux命令

## 5、软技能

### 5.1 英语

### 5.2 数学



## 6、参考书籍

- c语言程序设计
- C++程序设计300例
- 剑指offer
- 黑客免杀攻防
- https://ctf-wiki.github.io/ctf-wiki/reverse/unpack/packer-introduction/
- 精通windowsAPI函数接口编程实例




