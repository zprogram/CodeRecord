

# 1、Linux程序

## 1.1、Linux程序开发方式

- Linux下平台编译
hello.c
```
#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Hello World\n");
    exit(0);
}
```
编译、链接和运行程序
```
gcc -o hello hello.c
```
- VS2017+kaillinux配置开发调试环境

将文件保存为UTF8编码可解决程序乱码问题。

```
1>------ 已启动全部重新生成: 项目: HelloLinux, 配置: Release x64 ------
1>Cleaning remote project directory
1>Validating architecture
1>Validating sources
1>Copying sources remotely to '192.168.25.130'
1>Starting remote build
1>Compiling sources:
1>main.cpp
1>Linking objects
1>HelloLinux.vcxproj -> C:\ProjectCode\C++Code\LinuxC\进程_线程测试\HelloLinux\bin\x64\Release\HelloLinux.out
========== 全部重新生成: 成功 1 个，失败 0 个，跳过 0 个 ==========
```

## 1.2、开发系统引导

- 头文件

头文件位于/usr/include目录及其子目录中。

- 库文件
```
.a 代表传统的静态函数库
.so代表共享函数库
```

- 静态库调用

(1)两个文件编译出.o文件
bill.c
```
#include <stdio.h>

void bill(char *arg)
{
    printf("bill: you passed %s\n", arg);
}
```
fred.c
```
#include <stdio.h>

void fred(int arg)
{
    printf("fred: you passed %d\n", arg);
}
```
(2)编译
```
gcc -c bill.c fred.c
ls *.o
```
(3)调用库中的一个函数
program.c 
```
#include <stdlib.h>
#include "lib.h"

int main()
{
    bill("Hello World");
    exit(0);
}
```
调用bill.o里的函数
```
root@kali:~/Desktop/ex# gcc -c program.c 
root@kali:~/Desktop/ex# gcc -o program program.o bill.o
root@kali:~/Desktop/ex# ./program 
bill: you passed Hello World
```
(4)建立静态库文件

- 创建库文件
```
root@kali:~/Desktop/ex# ar crv libfoo.a bill.o fred.o
a - bill.o
a - fred.o
```

- 生成函数库内容表

```
root@kali:~/Desktop/ex# ranlib libfoo.a 
```

- gcc使用静态函数库

```
root@kali:~/Desktop/ex# gcc -o program program.o libfoo.a 
root@kali:~/Desktop/ex# ./program 
bill: you passed Hello World
```

# 2、shell程序设计

## 2.1 重定向

#### 重定向输出

```
ls -l > out.txt 写入到文件
ls -l >>out.txt 追加到文件
```
标准输出和标准错误输出都重定向到同一个文件中。

- 文件描述符0代表程序标准输入

- 文件描述符1代表程序标准输出
- 文件描述符2代表标准错误输出

以下例子为将标准错误输出重定向到与标准输出相同的地方。

```
root@kali:~/Desktop/ex# kill -1 1234 > killouterr.txt 2>&1
```
因为可以通过返回码了解执行结果，所以通常不需要保存标准输出或标准错误输出的内容。Linux的通用回收站命令【/dev/null】可以有效地丢弃输出信息。

```
kill -1 1234 >/dev/null 2>&1
```

分解这个组合：“>/dev/null 2>&1” 为五部分。  

- 1：> 代表重定向到哪里，例如：echo "123" > /home/123.txt 

- 2：/dev/null 代表空设备文件 

- 3：2> 表示stderr标准错误 

- 4：& 表示等同于的意思，2>&1，表示2的输出重定向等同于1 

- 5：1 表示stdout标准输出，系统默认值是1，所以">/dev/null"等同于 "1>/dev/null"  

  **因此，>/dev/null 2>&1 也可以写成“1> /dev/null 2> &1”** 

  语句执行过程为： 

  - 1>/dev/null ：首先表示标准输出重定向到空设备文件，也就是不输出任何信息到终端，说白了就是不显示任何信息。 
  - 2>&1 ：接着，标准错误输出重定向 到 标准输出，因为之前标准输出已经重定向到了空设备文件，所以标准错误输出也重定向到空设备文件。  

#### 重定向输入

示例：文件输入

```
more < killout.txt
```

示例：上面两个例子的结果不同，同时替换输入和输出，执行command1，从文件infile读取内容，然后将输出写入到outfile中。 

```
command1 < infile > outfile
```

### 2.2 管道输出

如果不使用管道输出，语句会拆分为多条。
```
root@kali:~/Desktop/ex# ps > psout.txt
root@kali:~/Desktop/ex# sort psout.txt > psort.out
root@kali:~/Desktop/ex# cat psort.out 
  2738 pts/2    00:00:01 bash
  5839 pts/2    00:00:00 ps
   PID TTY          TIME CMD
```
使用管道，则更方便输出。
```
root@kali:~/Desktop/ex# ps | sort > pssort.out
root@kali:~/Desktop/ex# cat pssort.out 
  2738 pts/2    00:00:01 bash
  5859 pts/2    00:00:00 ps
  5860 pts/2    00:00:00 sort
   PID TTY          TIME CMD
```

### 2.4 创建脚本 

创建包含命令的文件，命名为first。
```
#!/bin/sh

# first
# This file looks through all the files in the current
# directory for the string POSIX, and then prints the name of
# those files to the standard output.

for file in *
do
  if grep -q POSIX $file 
  then
    echo $file 
  fi
done

exit 0

```
执行：
```
root@kali:~/Desktop# chmod 777 first
root@kali:~/Desktop# /bin/sh first
```
### 2.5 变量

- echo 显示变量
```
salutation=Hello
echo $salutation
```
- read 输入赋值给一个变量
```
read salutation
echo $salutation
```
- 引号
字符串放在双引号中，使用单引号和反斜线(\)就不进行变量的替换。

- 环境变量

```
$HOME 当前用户的Home目录
$PATH 以冒号分隔的用来搜索命令的目录列表
$0 shell脚本的名字
$# 传递给脚本的参数个数
$$ shell脚本的进程号，脚本程序通常会用它来
   生成一个惟一的临时文件，如/tmp/tmpfile_$$
```
- 参数变量

```
$1,$2,... 脚本程序的参数
$*        在一个变量中列出所有的参数，各个参数之间
          用环境遍历IPS中的第一个字符分隔开。
$@        它是$*的一种精巧的变体，不使用IFS环境变量
          即使IFS为空，参数也不会挤到一起。
```




# 进程、线程

## 1、进程

### 什么是进程

一个其中运行着一个或多个线程的地址空间和这些线程所需要的系统资源。

### 进程的结构


## 2、线程

### 创建线程

### 多线程互斥与同步机制

## 3、进程通信机制

- 共享内存mmap
- 共享内存posix
- 管道
- 信号量




