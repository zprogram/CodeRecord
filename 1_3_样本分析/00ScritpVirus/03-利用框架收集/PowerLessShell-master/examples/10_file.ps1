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