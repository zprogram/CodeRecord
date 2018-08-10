# ע��

<# 

   ����ע��

#>

# �ַ����ָ�

$string2 = "192.168.14.20,192.168.14.21,192.168.14.22,192.168.14.23"

$string2 -split "," # ,�Ź��˳�IP

# �ַ����滻replace

$string = "Hello C++" 

$string -replace "c\+\+","World"   # ��� $string��ֵΪ Hello World

$string -replace ([Regex]::Escape("C++")),"Powershell Program"


# �ַ���ƴ�� join

('a','b','c') -join '/'