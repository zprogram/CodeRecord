  # ��ȡ���нű�Ŀ¼
 
 $x = $MyInvocation.MyCommand.Definition
 $x = Split-Path -Parent $MyInvocation.MyCommand.Definition
 echo "��ǰ·��Ϊ: $X\"
 
 # �鿴�ļ��Ƿ����1
 
 $fobj = new-object System.IO.FileInfo "C:\hsrv.txt"
 if ($fobj.Exists){'the file does exist'}
 
 # �鿴�ļ��Ƿ����2
 if (Test-Path "C:\hsrv.txt") {'the file does exist'}
 
 # ���ļ���ȡ�ı�
 # $fobj = get-item "D:\filename.txt"
 $fobj = get-item "D:\20171111-test_bin2hex.txt"
 $strm = $fobj.OpenText()           # ���ļ�
 $n = 0
 while(!$strm.EndOfStream){        
     $txt = $strm.ReadLine()        # ��ȡ�ļ�
     $n++
     "$n : $txt"
 
 }
 $strm.Dispose()                    # �ر��ļ�
 
 
 echo "������һ����ȡ�ļ��Ĳ���"
 pause
 
 # ʹ�� get-contentִ�ж�ȡ�ı�����
 
 $n = 0
 #Get-Content "D:\filename.txt"
 Get-Content "D:\20171111-test_bin2hex.txt" | foreach { $n++;"$n ; $_"}
 

  echo "����ִ��д���ļ��Ĳ���"
 pause
 
# ���ļ�д���ı�

$fobj =  New-Object System.IO.FileInfo "D:\testfilename.txt"
$strm =  $fobj.CreateText()
$strm.WriteLine("this is the first line")
for($i=1;$i -le 10; $i++)
{
    $i
    $strm.Write("$i ")
}
$strm.WriteLine()
$strm.Dispose()