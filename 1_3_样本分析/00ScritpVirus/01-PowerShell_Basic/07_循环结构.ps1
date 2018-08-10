# 9��0��ѭ��д��

### whileѭ��ʾ��

$a = 10
while($a)
{
    $a = $a - 1
    $a
}


## do..while��dountilʾ��

echo "do..while"

#do...while�ظ���ѭ����������ʽΪFalse�Ļ���ѭ���˳���

$b = 10
do
{
    $b = $b - 1
    $b

}while($b)

echo "do..until"

# do...until�ظ���ѭ����������ʽΪTrue�Ļ���ѭ���˳���

$c = 10

do{
    $c = $c - 1
    $c
}until($c -eq 0)


## forѭ��

echo "for"

for($d =10 ; $d -ge 0;$d--)
{
    $d
}

## foreachѭ��

echo "foreach"

$array = 1,2,3,4

foreach($v in $array)
{
    Write-Output("Array value : " + $v)
}
