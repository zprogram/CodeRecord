# 注释

<# 

   多行注释

#>

# 字符串分割

$string2 = "192.168.14.20,192.168.14.21,192.168.14.22,192.168.14.23"

$string2 -split "," # ,号过滤出IP

# 字符串替换replace

$string = "Hello C++" 

$string -replace "c\+\+","World"   # 输出 $string的值为 Hello World

$string -replace ([Regex]::Escape("C++")),"Powershell Program"


# 字符串拼接 join

('a','b','c') -join '/'