 # 获取运行脚本目录

$x = $MyInvocation.MyCommand.Definition
$x = Split-Path -Parent $MyInvocation.MyCommand.Definition
echo "当前路径为: $X\"

# # - (3) 交互式SHELL # # #

 # - 01 获取帮助命令

Get-Help

 # - 02 查找实现指定任务的命令
 
Get-Command 

Get-command pwd  # 查看pwd对应的Powershell命令
  
Get-command ls   # 查看ls对应的Powershell命令  

Get-command cd   # 查看cd对应的Powershell命令

 # - 03 将管道输出的结果保存到文件中


 # 通过Out-File命令或者重定向操作符命令输出的结果保存到文件中
 
Get-Command  | Out-File $X\unicodefile.txt


 # - 04 获取进程信息
 
Get-Process 
Get-Process | Export-CSV $X\procs.csv      # 导出csv
Get-Process | Export-Clixml $X\procs.xml   # 导出xml

 # - 05 环境变量

dir ENV:                # 查看所有环境变量
$ENV:COMPUTERNAME       # 查看计算机名

 # - 06 获取历史命令
 
Get-History


 # - 07 向文件的结尾处加入信息,管道也可以追加文件
 
Get-Process >> $X\files.txt

Get-Process | Out-File -Append $X\files.txt

"Hello zzzhhh" >> $X\files.txt


