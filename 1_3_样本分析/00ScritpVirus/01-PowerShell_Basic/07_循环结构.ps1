# 9到0的循环写法

### while循环示例

$a = 10
while($a)
{
    $a = $a - 1
    $a
}


## do..while和dountil示例

echo "do..while"

#do...while重复该循环，如果表达式为False的话，循环退出。

$b = 10
do
{
    $b = $b - 1
    $b

}while($b)

echo "do..until"

# do...until重复该循环，如果表达式为True的话，循环退出。

$c = 10

do{
    $c = $c - 1
    $c
}until($c -eq 0)


## for循环

echo "for"

for($d =10 ; $d -ge 0;$d--)
{
    $d
}

## foreach循环

echo "foreach"

$array = 1,2,3,4

foreach($v in $array)
{
    Write-Output("Array value : " + $v)
}
