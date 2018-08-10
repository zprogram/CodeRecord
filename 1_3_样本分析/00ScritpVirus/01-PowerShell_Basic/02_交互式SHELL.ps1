 # ��ȡ���нű�Ŀ¼

$x = $MyInvocation.MyCommand.Definition
$x = Split-Path -Parent $MyInvocation.MyCommand.Definition
echo "��ǰ·��Ϊ: $X\"

# # - (3) ����ʽSHELL # # #

 # - 01 ��ȡ��������

Get-Help

 # - 02 ����ʵ��ָ�����������
 
Get-Command 

Get-command pwd  # �鿴pwd��Ӧ��Powershell����
  
Get-command ls   # �鿴ls��Ӧ��Powershell����  

Get-command cd   # �鿴cd��Ӧ��Powershell����

 # - 03 ���ܵ�����Ľ�����浽�ļ���


 # ͨ��Out-File��������ض����������������Ľ�����浽�ļ���
 
Get-Command  | Out-File $X\unicodefile.txt


 # - 04 ��ȡ������Ϣ
 
Get-Process 
Get-Process | Export-CSV $X\procs.csv      # ����csv
Get-Process | Export-Clixml $X\procs.xml   # ����xml

 # - 05 ��������

dir ENV:                # �鿴���л�������
$ENV:COMPUTERNAME       # �鿴�������

 # - 06 ��ȡ��ʷ����
 
Get-History


 # - 07 ���ļ��Ľ�β��������Ϣ,�ܵ�Ҳ����׷���ļ�
 
Get-Process >> $X\files.txt

Get-Process | Out-File -Append $X\files.txt

"Hello zzzhhh" >> $X\files.txt


