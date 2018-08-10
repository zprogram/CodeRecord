# ��������

function simple(){
    return 1
}

## ���ú���
simple

# �������ĺ���

function printmsg
{
    param([int]$level=1 ,$message)
    Write-Output $level,$message
}

## ���ε��ú���
printmsg 4 'this is the message'

# param���
function printparam
{
   param([string]$level=1,[string]$message)
   Write-Output  $level,$message
}

## ָ������
printparam -message 'this is the message' -level 10



