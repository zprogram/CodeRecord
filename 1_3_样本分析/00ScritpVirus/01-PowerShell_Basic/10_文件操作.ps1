  # 获取运行脚本目录
 
 $x = $MyInvocation.MyCommand.Definition
 $x = Split-Path -Parent $MyInvocation.MyCommand.Definition
 echo "当前路径为: $X\"
 
 # 查看文件是否存在1
 
 $fobj = new-object System.IO.FileInfo "C:\hsrv.txt"
 if ($fobj.Exists){'the file does exist'}
 
 # 查看文件是否存在2
 if (Test-Path "C:\hsrv.txt") {'the file does exist'}
 
 # 从文件读取文本
 # $fobj = get-item "D:\filename.txt"
 $fobj = get-item "D:\20171111-test_bin2hex.txt"
 $strm = $fobj.OpenText()           # 打开文件
 $n = 0
 while(!$strm.EndOfStream){        
     $txt = $strm.ReadLine()        # 读取文件
     $n++
     "$n : $txt"
 
 }
 $strm.Dispose()                    # 关闭文件
 
 
 echo "即将下一个读取文件的操作"
 pause
 
 # 使用 get-content执行读取文本操作
 
 $n = 0
 #Get-Content "D:\filename.txt"
 Get-Content "D:\20171111-test_bin2hex.txt" | foreach { $n++;"$n ; $_"}
 

  echo "即将执行写入文件的操作"
 pause
 
# 向文件写入文本

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