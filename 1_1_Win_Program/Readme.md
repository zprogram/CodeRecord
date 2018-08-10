# 1、学习思路

熟悉恶意代码的编写原理，熟悉恶意代码常用的编程套路。

# 2、学习目标

- 熟悉WindowsAPI
- 熟悉恶意代码基础原理

# 3、Windows程序基础

## 3.1 消息机制

- FindWindow():通过指定的窗口类名或窗口标题查找匹配的窗口并返回最上层的窗口句柄
- SendMessage()：根据窗口句柄将消息发送给指定的窗口。
- RegisterClassEx()：注册窗口类
- GetMessage()：获取消息
- DispathMessage()：分发消息

### 窗口流程

RegisterClassEx注册窗口类->GetGetMessage()获取消息->DispathMessage()分发消息

### 发送消息

FindWindow()通过指定的窗口类名或窗口标题获取句柄->SendMessage()根据窗口句柄将操作消息发送给指定的窗口

## 3.2 通过消息实现进程间通信


### 通过自定义消息进行进程通信

- ON_MESSAGE(xx1,xx2): 自定义消息的消息映射。
- - xx1:消息宏定义
- - xx2:消息响应的回调函数

### 通过WM_COPYDATA消息进行进程通信

- 通过WM_COPYDATA消息进行进程通信消息需要使用SendMessage()函数进行发送。

# 4、恶意代码是怎么进行网络连接的？

恶意代码如何进行网络连接的原理。

## 4.1 网络编程基础

### 面向连接的协议-TCP

TCP协议，类似于打电话。必须对方接听之后建立链接才可以通信。

- 服务器端

socket()->bind()->listen()->accept()->send()/recv()->closesocket()

- 客户端

socket()->connet()->send()/recv()->closesocket()

### 非面向连接的协议-UDP

UDP协议，类似于发邮件。发送端只要直接将要发送的数据传出即可，不需要理会接收端是否能接收到数据。
而接收端在接收到数据时也不会响应信息通知发送给发送端。

- 服务器端

socket()->bind()->sendto()/recvfrom()->closesocket()

- 客户端

socket()->sendto()/recvfrom()->closesocket()

### 字节顺序

- 字节序基础

数值在内存中存储的方式有两种，一种是大尾方式（网络字节序），一种是小尾方式。

例如：0x01020304，用大尾方式存储，其存储格式为：01 02 03 04，用小尾方式存储：04 03 02 01

- -  大尾存储方式：内存高位地址存放数据低位字节数据，内存低位地址存放数据高位字节数据；

- - 小尾存储方式：内存高位地址存放数据高位字节数据，内存低位地址存放数据低位字节数据；

- 主机字节序与网络字节序

- - 主机字节序：指主机在存储数据时的字节顺序，Windows操作系统兼容的CPU为小尾方式，Unix操作系统多为大尾方式。主机字节序并非固定字节序，需要根据不同的操作系统架构确定。

- - 网络字节序：网络传输相关协议所规定的字节传输顺序，TCP/IP协议所使用的字节序为大尾方式。

- 编程实现

- - 方法1：取内存中低位地址的值

以下代码中，定义了0x01020304这个十六进制数，其在小尾方式内存中的存储顺序为 04 03 02 01 。*(BYTE*)&dwSmallNum 是取内存中低地址位的值，如果小尾方式存储，那么低地址位存储的值为0x04，如果是大尾方式则为0x01。

```
#include "stdafx.h"
#include <windows.h>


int main()
{
    DWORD dwSmallNum = 0x01020304;
    if (*(BYTE*)&dwSmallNum = 0x04) 
    {
        printf("small sequence");
    }

    return 0;
}
```
- - 方法2：直接转换比较法

利用字节序转换函数将所定义的值进行转换，然后用转换后的值和原值进行比较。如果原值与转换后的值相同，说明为大尾方式，否则为小尾方式。

```
htonl()：转换后的结果是网络字节序。
```

## 4.2 非阻塞模式开发

Windows套接字的工作模式有两种，分别为阻塞模式（同步模式）和非阻塞模式（异步模式）。

- 阻塞模式下的Winsock函数会将程序的某个线程处于“等待状态”。
- 非阻塞模式下的Winsock函数不会发生需要等待的情况。

### 设置Winsock的工作模式

- WSAAsyncSelect()函数会把套接字设置成阻塞模式
- - FD_READ:套接字收到对端发来的数据包
- - FD_ACCEPT:监听中的套接字有连接请求
- - FD_CONNECT:套接字成功连接到对方
- - FD_CLOSE:套接字对应的连接被关闭

### 非阻塞模式下的简单远程控制开发

远程控制分为控制端和被控端，控制端为客户端，被控端通常为服务器端。
客户端：FD_READ、FD_CONNECT、FD_CLOSE
服务器端：FD_READ、FD_ACCEPT、FD_CLOSE

### 原始套接字开发

调用socket()函数时为它的第2个参数指定相应的类型。

- TCP：SOCK_STREAM
- UDP：SOCK_DGRAM
- 原始套接字：SOCK_RAW

# 5、恶意代码是怎么在系统运行的？

搞清楚恶意代码如何利用Windows API对进程、线程、文件、注册表、服务进行操作。

## 5.1 文件编程

- CreateFile：打开文件函数，既可以打开文件也可以创建文件。

- CloseHandle：对文件操作完成后，需要对打开文件的句柄进行关闭以释放资源。

- DeleteFile()：删除文件

- ReadFile()：读取文件

- WriteFile()：写入文件

- FlushFileBuffers()：指定文件句柄的缓冲区清空

- SetFilePointer()：移动文件指针，读写文件的某个部分

- GetLogicalDriveStrings()：获取本地所有逻辑驱动器函数

- GetDriveType()：获取驱动器类型函数

  ```
  #define DRIVE_UNKNOWN     0  // 无法识别此驱动器类型
  #define DRIVE_NO_ROOT_DIR 1  // 无效的驱动器路径
  #define DRIVE_REMOVABLE   2  // 可移动驱动器，如U盘、移动硬盘等
  #define DRIVE_FIXED       3  // 不可移动驱动器，指硬盘
  #define DRIVE_REMOTE      4  // 网络驱动器
  #define DRIVE_CDROM       5  // 光盘驱动器
  #define DRIVE_RAMDISK     6  // 虚拟驱动器
  ```

- CreateDirectory()：创建目录

- GetModuleFileName()：获取自身程序所在路径

- SetFileAttributes()：设置文件属性

### 5.1.1 示例：模拟U盘病毒

- 编程思路

  1、设定autorun.inf的内容

  2、获取当前完整路径及文件名

  3、获取当前盘符

  4、判断

  - - 如果在硬盘上，就感染移动U盘

  - - 如果在移动U盘上，就感染硬盘

  5、获取本地逻辑磁盘函数

  - 如果在U盘，拷贝自身到硬盘的位置。
  - 如果在硬盘，拷贝自身到U盘的位置。
  - 建立Autorun.inf文件
  - 设置Autorun.inf文件属性为隐藏属性

- 代码路径

[WindowsAPI_文件操作_模拟U盘病毒.cpp](https://github.com/zprogram/CodeRecord/blob/master/03Win_Program/Basic_Project/WindowsAPI_%E6%96%87%E4%BB%B6%E6%93%8D%E4%BD%9C_%E6%A8%A1%E6%8B%9FU%E7%9B%98%E7%97%85%E6%AF%92.cpp)

### 5.1.2 示例：免疫U盘病毒

- 编程思路

- 代码路径

[WindowsAPI_文件操作_U盘免疫_Autorun.inf](https://github.com/zprogram/CodeRecord/tree/master/03Win_Program/Basic_Project/U%E7%9B%98_%E5%85%8D%E7%96%ABAutorun.inf)


## 5.2 注册表编程

### 5.2.1 注册表结构

regedit:注册表是树状结构，由根键、子键、键项值组成。

- 根键：注册表树状结构的根节点。类似磁盘驱动器的盘符：C:、D:、E:、F:

  ```
  HKEY_CLASSES_ROOT
  HKEY_CURRENT_USER
  HKEY_LOCAL_MACHINE
  HKEY_USERS
  HKEY_CURRENT_CONFIG
  ```

- - 子键：根节点下的子节点。类似磁盘驱动器的文件夹。

  ```
  HKEY_USERS\.DEFAULT
  ```
- - - 键项值：不包括子键的子键就是键值项，相当于树状结构中的叶子节点。
- 注册表中的数据：根键、子键、键项都是注册表中的结构，注册表中具体的数据由3部分组成：值名称、值类型和值。也就是：名称、类型和数据。

### 5.2.2 操作注册表API

- RegOpenKeyEx：打开注册表句柄

- RegOpenKey：打开注册表句柄，Win16下函数，在Win32仍然可用，但是为了兼容而设置的。

- RegCloseKey：关闭释放注册表句柄。

- RegCreateKeyEx()：创建一个子健。

- RegDeleteKey()：删除子健。

- RegQueryValueEx()：读取键名称中的数据，查询键名称的属性。

- RegDeleteValue()：删除键值项。

- RegEnumKeyEx()：对指定键下面的子键进行逐一的获取。

- RegEnumValue()：枚举键值。
  
### 5.2.3 示例：注册表下启动项的管理




## 5.3 服务编程

- 查看系统服务

- 服务控制管理器

## 5.4 进程与线程

- 进程的创建
- 进程的结束
- 进程的枚举
- 调整当前进程权限
- 进程的暂停与恢复
- 多线程编程

## 5.5 DLL编程

- 导出函数
- 调用函数1
- 调用函数2
- 查看DLL程序导出函数
- 远程线程注入
- 卸载被注入的DLL文件


## 5.6 内核驱动开发基础

### 5.6.1 驱动入口
### 5.6.2 驱动程序编译
### 5.6.3 驱动文件的装载与输出
### 5.6.4 文件操作
### 5.6.5 注册表操作


#  6、恶意代码分析编程基础

## 6.1 汇编语言

## 6.2 PE文件结构

## 6.2 HOOK

## 6.3 后门手法剖析

### 自启动技术

### 配置生成

### 反弹端口

### 感染技术

### 自删除技术

### 隐藏DLL文件

### 端口复用技术

### 远程CMD通信技术

### 端口扫描技术

### 嗅探技术实现

### 驱动下的进程遍历

### HOOK SSDT

# 7、反病毒编程技术

## 7.1 病毒专杀开发

## 7.2 行为监控

## 7.3 U盘防御

## 7.4 目录监控




