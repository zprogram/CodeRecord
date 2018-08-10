# ������ֵ,�������в���

Write-Host "Hello,$args"

# PS C:\WINDOWS\system32> .11_�����в���.ps1  "C++" "Powershell"

# �����������

For($i=0;$i -lt $args.Count; $i++)
{
    Write-Host "parameter $i : $($args[$i])"
}
