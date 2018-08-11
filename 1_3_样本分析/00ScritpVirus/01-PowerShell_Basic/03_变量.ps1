
# # - (4) 变量 # # #
# 变量示例代码1：

## 普通写法

$result = Get-Process  # 将进程信息存储到$result

$result

$Loc = Get-Location #定义变量Loc，得到当前路径

$Loc                #输出当前路径

## 花括号写法

${Hello Computer Name} = "I 'am string"

${Hello Computer Name}  # 输出变量内容



# 变量方法和属性示例代码2：

<# PowerShell变量有一些内置的方法和属性，可以很方便对字符串操作。

以及获取用户主目录、脚本相关的内置变量 #>

# 示例代码：

### 字符串长度

${Hello Computer Name}.Length

### 字符串大小写

${Hello Computer Name}.ToUpper()

## 内置变量

### 获取当前执行脚本的目录路径

$PSScriptRoot

### 获取用户主目录的路径

$HOME



