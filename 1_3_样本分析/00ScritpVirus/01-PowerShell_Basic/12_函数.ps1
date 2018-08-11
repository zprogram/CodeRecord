# 函数定义

function simple(){
    return 1
}

## 调用函数
simple

# 带参数的函数

function printmsg
{
    param([int]$level=1 ,$message)
    Write-Output $level,$message
}

## 带参调用函数
printmsg 4 'this is the message'

# param语句
function printparam
{
   param([string]$level=1,[string]$message)
   Write-Output  $level,$message
}

## 指定参数
printparam -message 'this is the message' -level 10



