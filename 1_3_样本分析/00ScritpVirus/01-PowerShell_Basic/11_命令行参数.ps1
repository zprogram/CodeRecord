# 参数传值,返回所有参数

Write-Host "Hello,$args"

# PS C:\WINDOWS\system32> .11_命令行参数.ps1  "C++" "Powershell"

# 访问数组参数

For($i=0;$i -lt $args.Count; $i++)
{
    Write-Host "parameter $i : $($args[$i])"
}
