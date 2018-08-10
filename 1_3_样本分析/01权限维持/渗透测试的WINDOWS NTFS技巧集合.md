**译者：**zzzhhh



这篇文章是来自[SEC Consult Vulnerability Lab](https://www.sec-consult.com/en/vulnerability-lab/)的ReneFreingruber ([@ReneFreingruber](https://twitter.com/ReneFreingruber))，分享了过去几年从各种博客文章中收集的或者是他自己发现的文件系统技巧，这些技巧不可以直接被利用。但是它们会在特殊情况下间接地产生可以被攻击者利用的漏洞。

请注意，这篇文章只说明有关于如何利用这些问题以及影响的信息(没有关于Windows API的技术底层细节)，因为这样会超出本篇文章的技术范围。

第一个文件系统技巧(技巧1 - [CVE-2018-1036](https://portal.msrc.microsoft.com/en-us/security-guidance/advisory/CVE-2018-1036))被微软修补了，其他技巧还有没有安全补丁。 



## 技巧1:创建没有权限的文件夹(CVE-2018-1036/NTFS EOP)

在Windows上，可以为文件夹分配“特殊权限”，例如允许用户在文件夹中创建文件但不允许创建文件夹的权限。

此类文件夹的一个示例是C:\Windows\Tasks\，用户可以在其中创建文件，但不允许创建文件夹：

![](https://images2018.cnblogs.com/blog/549050/201808/549050-20180803181309890-807196161.jpg)

图1：Windows10，Win7界面不一样。示例为Windows10



而管理员或程序可能会配置这样的权限，并假设用户不允许在其中创建文件夹。



这个ACL策略可以在用户创建文件时被绕过。如果在文件名的末尾添加```“::$INDEX_ALLOCATION”```将创建一个文件夹而不是一个文件。Windows当前不包含对该类情况的检查。

![](https://images2018.cnblogs.com/blog/549050/201808/549050-20180803181313944-1596937537.jpg)

图2：创建test文件夹



如上图所示，已成功创建了一个文件夹，用户可以在这个文件夹中创建任意的文件或文件夹（如果管理员/程序认为缺少权限而无法执行创建文件夹的操作，这个技巧可能会导致特权提升 ）。 

附注：如果应用程序只允许删除文件，```:: $ INDEX_ALLOCATION```技巧也可用于删除文件夹。

**译者注：**使用以下命令即可删除文件夹。

```
rd test::$INDEX_ALLOCATION
```

**微软漏洞联系时间表：**

```
2018年3月1日：	通过secure@microsoft.com进行初步联系。发送PGP加密的博客帖子。
2018年3月1日：	Microsoft分配了MSRC Case 43968 CRM：0461039882
2018年3月5日：	微软要求延长披露期限。
2018年3月5日：	同意延长90天的截止日期。
2018年3月27日：	询问微软是否可以重现漏洞以及何时可以获得补丁。
2018年3月28日：	微软证实，“技巧1”漏洞已成功重现并分配给了编号CVE-2018-1036。该漏洞将由5B（5月补丁星期二）修复。
2018年4月27日：	微软与我们联系，提议的修复方案导致回退。微软要求将修补的最后期限延长至2018-06-12(6月补丁周二)。
2018年4月30日：	了解微软的情况，截止日期延长至2018-06-12。询问微软是否还会修补其他技巧。
2018年4月30日：	微软回应称其他技巧“不会收到低级安全更新”。
2018年6月12日：	Microsoft发布补丁（请参阅此处的发布
               https://portal.msrc.microsoft.com/en-us/security-guidance/advisory/CVE-2018-1036
2018年6月13日：	博客发布。
```

## 技巧2：使用供选数据流绕过路径限制

你可能想知道为什么上面的方法有效。

> <文件名>:<数据流名称>:<类型>

如果我们创建一个名为test的文件。它将在内部存储为```test.test::$DATA```，因为数据流名为空，且```$DATA```是默认类型。第一个技巧的原理是将数据流类型更改为INDEX_ALLOCATION，而INDEX_ALLOCATION对应于文件夹类型，所以创建了一个文件夹。

但是，也可以将数据存储在不同的流中。(这就是所谓的Alternate Data Stream – ADS)。如果我们写的例子是“test.txt”，我们在实际写入的是```“test.txt::$DATA”```(数据流名称为空)。我们也可以写入“test.txt:foo” 或```“test.txt:foo:$DATA”```（两者都相同，因为```$DATA```是默认类型）。也可以使用不同的流名称用于存储文件的信息。如果你从互联网下载文件(或通过电子邮件接收)，Windows系统会通过流名称悄悄地添加区域标识符（如果你想执行会显示出一个附加的警告对话框）例如，如果我们下载“putty.exe”，Windows也会创建```”putty.exe:Zone.Identifier:$DATA“```。使用dir /r命令可以看到这些流名称：

![](https://images2018.cnblogs.com/blog/549050/201808/549050-20180804010453918-1657003301.jpg)

图3：将zone.identifier放到putty.exe中，然后尝试读取出来。



正如我们所看到的，带有数据流的文件是不能通过type命令直接读取的(使用更多的命令就可以了)，如果我们使用notepad读取文件，那么可以忽略冒号最末尾的```$DATA```类型。我们还可以把重要的信息(包括应用程序!)在ADS中存储。例如putty.exe就可以复制到ADS中，然后通过wmic调用(不可以用start直接调用)：

![](https://images2018.cnblogs.com/blog/549050/201808/549050-20180804013347901-844258305.png)

图4：运行test:Putty.exe



附注:本文撰写于2018-03-01，并报告给微软。与此同时，微软的Windows Defender被更新以检测WMIC进程调用。



你可能会问为什么有人会这样做?首先，ADS可以用来隐藏数据（dir没有使用/r开关不会显示文件中的ADS;explorer.exe也不会显示ADS;稍后介绍如何能够隐藏dir /r开关的内容…）而ADS还有一个很好的特性——我们可以在文件夹中添加ADS。这样做的前提是在文件夹里拥有“创建文件夹”的权限(而且文件夹名称不能是数字)。这样做可以使文件夹上的ADS看起来像是来自父文件夹的文件!



在Windows上一个普通用户无法在C:\Windows创建文件\(只有管理员可以写这个文件夹)。因为只有管理员可以创建这些文件,所以应用有可能认为文件在C:\Windows\是可以受信任的。可是普通用户在C:\Windows\Tracing文件夹中是可以创建文件和文件夹的，因此普通用户可以创建一个ADS在这个文件夹中。



假设用户写入文件C:\Windows\Tracing:test.dll。如果这个路径现在被传递给一个遍历文件夹的Windows API，这个API将从路径的末尾开始，直到找到第一个“\\”。将“\\”中剩下的所有内容作为文件夹返回。而C:\Windows\Tracing:test.dll 将返回C:\Windows\作为文件夹。正如前面提到的,一个普通用户不允许使用这个技巧创建文件在Windows文件夹。但是我们可以通过这个方法创建了一个文件，而且是存储在C:\ Windows文件夹内 !



这里是不同Windows函数遍历文件夹的输出(我们可以看到它总是C:\ Windows):

![](https://images2018.cnblogs.com/blog/549050/201808/549050-20180804015403436-171589036.jpg)

图5：遍历文件夹



注:上述存储dll可以开始与Windows内置的control.exe应用程序启动，命令为:

> control.exe C:\Windows\tracing:foobar.dll 



此行为可用于绕过某些应用程序白名单解决方案，也可以在各种情况下绕过安全检查。例如程序员认为检查文件是否存储在特定的文件文件夹中就足够了并且假设当管理员通过设置ACL后写入这个文件夹。



考虑应用程序允许上传数据，上传的数据存储在applicationFolder \\ uploadedData \\中。而应用程序允许从applicationFolder\启动脚本/应用程序，而不允许从applicationFolder \uploadedData\(使用黑名单方法)启动脚本/应用程序。如果用户上传一个名为“:foo.ps1”的文件，系统将创建一个类似于applicationFolder\uploadedData:foo.ps1的ADS。此文件似乎存储在applicationFolder\中，因此绕过安全检查。



另一个有趣的事情是ADS可以包含通常文件名禁止使用的“或*符号(必须使用本机Windows API创建这些文件;cmd.exe会过滤这些字符):

![](https://images2018.cnblogs.com/blog/549050/201808/549050-20180804154937598-4385899.jpg)

图6：特殊符号



 这本身就可能导致几个问题。 （例如，如果文件名以“开头和路径被”包围结尾，正如James Forshaw在他的博客中提到的方法;请参见参考资料部分）。另一个有趣的攻击向量可以是XSS(或命令注入)。假设一个网站在IIS上运行并允许上传文件，并且很容易出现CSRF。上传文件后，将显示包含文件名的成功对话框。如果文件名未被处理，这可能会导致XSS，但是如果文件名不允许包含像<或>之类的符号(因此我们不能用它来执行JavaScript代码)。如果允许ADS文件包含这些符号，那么攻击者可以尝试使用ADS文件名发送上传请求:

![](https://images2018.cnblogs.com/blog/549050/201808/549050-20180804163845570-1858649171.jpg)

图7：ADS的XSS利用

## 技巧3:创建无法通过“…”文件夹找到的文件

每个文件夹都包含默认的两个特殊条目，也就是指当前文件夹“.”文件夹和指向父文件夹（父目录）“..”文件夹。在Windows上不能用名称中的点创建文件/文件夹，最有可能防止将解析器与点混淆的攻击。

![](https://images2018.cnblogs.com/blog/549050/201808/549050-20180804164341263-2068877625.jpg)

图8：创建...文件夹测试



上面的截图显示,不能创建一个“…”或“....”的文件夹。但是可以使用上面提到的:$INDEX_ALLOCATION技巧来绕过:

![](https://images2018.cnblogs.com/blog/549050/201808/549050-20180804164854187-2001987519.jpg)

图9：ADS创建....文件夹



“…”文件夹是用上面提到的技巧创建的，但是这样的文件夹也可以将名称传递两次来创建，如“…”示例中所示。(mkdir “....\ ....\“ 创建文件夹”....”,但里面还有一个文件夹“….”。仅仅通过mkdir ”....\xyz\“不起作用。)。



使用第二个技巧，我们还可以输入这些文件夹，在那里存储文件，甚至从这个位置执行程序:

![](https://images2018.cnblogs.com/blog/549050/201808/549050-20180804171401514-1711514541.jpg)

图10：向...文件夹写入文件的方法

如图所示，无法仅使用名称进入文件夹(例如:“cd …”或“cd …\”或“cd …\…”不起作用)，必须使用“cd …\…\”的语法。进入文件夹之后可以在这个文件夹里创建文件。(有趣的是:如果你在这个文件夹里输入“cd .”，你又会回到这个文件夹，因为路径是混乱的)。



此外，也不可能从GUI (explorer.exe)打开这个文件夹。我遇到了两种不同的情况。在某些情况下，双击这样的文件夹没有影响(保持在当前文件夹中，路径保持不变)，在其他情况下，我们将保持在文件夹中，但是资源管理器中的路径发生了更改。例如，在“打开”文件夹17次之后(注意路径中的“…” ):

![](https://images2018.cnblogs.com/blog/549050/201808/549050-20180804183922184-978321928.jpg)

图11：...文件夹显示在地址栏的情况



可以尝试根据需要随时进入该文件夹 ，可无法在GUI中的文件夹中看到这些文件 。也无法通过在上图中的路径输入字段传递“C:\test\…\\…\”来打开文件夹。



(附注:如果试图从GUI中删除该文件夹，explorer.exe会崩溃;我们将看到一个对话框，其中Windows正在计算文件夹中的文件以及它所在的位置“很多文件” ；**不要在工作系统上试试这个... **)



通过GUI (explorer.exe)搜索这个文件夹中的文件也不起作用，例如GUI搜索“123.txt”文件，图形用户界面实际上是被挂起/搜索，而不会查找文件 。



请注意， 通过cmd进行搜索是没有问题的:

![](https://images2018.cnblogs.com/blog/549050/201808/549050-20180804184545301-714233317.jpg)

图12：命令行下搜索文件



但是大多数人现在都使用Powershell，而使用Powershell又找不到这个文件，因为它会陷入无限循环:

![](https://images2018.cnblogs.com/blog/549050/201808/549050-20180804184815620-661557924.jpg)

图13：Powershell搜索

(输出被截断，因为命令总是循环打印这两个文件夹...)

搜索“123.txt”(例如:“Get-ChildItem -Path C:\test -Filter 123.txt -Recurse -ErrorAction SilentlyContinue -Force”)将永远不会找到该文件(并且永远不会结束)。



我还用不同的AntiVirus产品进行了测试，这些产品似乎都可以正常工作(我将恶意软件样本放在这个...的特殊文件夹中，经过测试AntiVirus产品可以找到它们)。有些人仍然对这条路径感到困惑，例如在“C:\test\…\”中搜索病毒时，他们会在“C:\test\”中搜索。使用os.walk()的python代码似乎也能正常工作。



请注意，只是创建一个目录连接指向它自己的父文件夹不会在cmd或Powershell中导致无限循环 。



## 技巧4：“隐藏”目录连接的指向目标

目录连接是一个非常有用的NTFS功能，可以为攻击者找到安全漏洞。使用它可以创建(使用普通用户权限)到目标文件夹的符号链接。



解释目录连接的最佳安全漏洞是AVGater，攻击者将一个文件放在x文件夹中，然后将该文件标记为病毒，并且已安装的AntiVirus解决方案将其移至隔离区。之后攻击者删除文件夹x，并用一个名为“x”的目录连接替换它，该连接指向C:\windows\System32\。如果攻击者现在单击“恢复”按钮，AntiVirus解决方案会将把文件复制到x文件夹，该文件夹现在指向具有SYSTEM权限的system32(直接导致EoP)。



如果目标应用程序包含竞争条件类型漏洞(TOCTOU漏洞——检查使用时间)，则目录连接会被滥用。



使用mklink实用程序和/J参数创建一个目录连接。可以将它与::$INDEX_ALLOCATION技巧结合使用，创建一个名为“…”的目录连接:

![](https://images2018.cnblogs.com/blog/549050/201808/549050-20180804205113642-135205194.jpg)

图14：创建目录连接



第一个目录连接“test1”是用一个普通的名称创建的，因此目标在“dir”输出中被正确地显示。但是，在“…”目录连接的情况下，不再显示目标(而是显示[…];见红框)。还请注意，你可以让连接点1指向连接点2，指向连接点3，以此类推，直到最后一个指向真正的目的地。



由于路径混淆，您可以使用上面提到的“cd…\…\”技巧(在system32文件夹中)进入结点，但 “.”会指向“C:\test8”:

![](https://images2018.cnblogs.com/blog/549050/201808/549050-20180804210212488-789283586.jpg)

图15：在...目录执行dir命令



dir命令从system32文件夹打印文件（红色标记;请注意，第一个命令在C:\test8\创建了hello.bat文件）

![](https://images2018.cnblogs.com/blog/549050/201808/549050-20180804210623259-154312512.jpg)

图16：执行hello.bat结果



红色标记的文件是system32文件夹中的最后一个文件(dir命令的最后一个输出)。在蓝色中我们可以看到执行的是当前目录 (“.\”)中的“hello.bat” ，由于路径混淆，执行了C:\test8\hello.bat(绿色方块)而不是C:\windows\system32\hello.bat。我不确定这是否对安全性产生直接影响。因为我们可以在任何文件夹中启动文件。但是它可能会被用来绕过应用程序使用白名单脚本文件的白名单解决方案。



## 技巧5:隐藏供选数据流

如前所述，可以通过dir命令中的/r开关查看ADS。而streams.exe是Sysinternals里的一个工具，它也可以查看数据流:

![](https://images2018.cnblogs.com/blog/549050/201808/549050-20180804211610809-345655486.jpg)

图17：streams.exe查看ADS



在旧版本的Windows中，可以使用保留名作为基本名称来隐藏ADS (例如: CON, NUL, COM1, COM2, LPT1, …)。而在Windows 10上就做不到了，但“…”仍然有效:

![](https://images2018.cnblogs.com/blog/549050/201808/549050-20180804211851568-1297157583.jpg)

图18：测试保留名隐藏ADS



“…”上的ADS是成功创建的，但是没有被streams.exe工具列出。在COM1上创建ADS会导致错误，在NUL上创建ADS没有任何提示(ADS没被创建)。



请注意，还可以在驱动器上创建一个ADS，比如“echo 123 > C:\\:abc.txt”。将隐藏在C:\ 中的“dir /r” 命令中。但是，它将在“..”目录的C：\子文件夹中显示ADS。例如：  

![](https://images2018.cnblogs.com/blog/549050/201808/549050-20180804220359614-110225192.jpg)

图19：在C:创建ADS的效果

红色标记的部分ADS是由 C:\\:abc.txt 创建。如果直接在C:\上调用 ,那么通过Sysinternals工具流也看到ADS。因此，为了避开这两种工具，应该使用“…”技巧。



所以还存在可用于隐藏工具的第二技巧。在Windows上可以添加“.<空格>.”在文件的末尾，Windows将会自动删除它(规范化将其删除)。

![](https://images2018.cnblogs.com/blog/549050/201808/549050-20180804221725248-1834819653.jpg)

图20：添加...的技巧，echo 123  > "abc. ."



但是我们可以用ADS创建这样的文件！用工具不能打开这个文件，因为像“xyz. .”这样的路径会自动地更改为“xyz”，而这个文件不存在。



这是证明:

![](https://images2018.cnblogs.com/blog/549050/201808/549050-20180804232744890-90800243.jpg)

图21：“xyz. .”文件被创建



创建的ADS foobar.txt通过工具是无法找到的:

![](https://images2018.cnblogs.com/blog/549050/201808/549050-20180805133933856-1801378691.jpg)

图22：foobar.txt



附注1:此类文件也可以通过以下方式创建： echo test > “test. .::$DATA” 

附注2:请注意“..:abc.txt”是在“C:\\:abc.txt”上创建的ADS。

我们还可以创建一个名为“. .” 的目录，如下所示:

![](https://images2018.cnblogs.com/blog/549050/201808/549050-20180805134918844-1958516912.jpg)

图23：创建一个名为“. .” 的目录



这个文件夹是不可以进入的:

![](https://images2018.cnblogs.com/blog/549050/201808/549050-20180805135045716-126498026.jpg)

图24：不可以进入名为“. .” 的目录



前面提到过(像cd . .\\. .\\ 无法正常使用)，但是cd “. .::$INDEX_ALLOCATION”  是可以使用的(双引号很重要)。

如果我们可以在文件夹名之间添加空格，那我们也可以在末尾添加空格，如 “b ” 或“.. ”  或“. “。

![](https://images2018.cnblogs.com/blog/549050/201808/549050-20180805171021770-958751431.jpg)

图25：文件夹末尾添加空格

说明:有一个“b”和一个“b ”文件夹，一个名为“a”的文件，一个名为“a ”的文件，两个默认的目录“.”和“..”和“. ”和“. .”。

名称为“.. ”的目录可以使用我们已经讨论过的技术进行写入文件:

![](https://images2018.cnblogs.com/blog/549050/201808/549050-20180805173213441-328868993.jpg)

图26：写入文件到“. . ”目录中



附注1:如果在文件夹上单击两次，可以通过文件管理器打开该文件夹。也会正确显示文件夹的内容。但是由于路径错误，无法打开其中的文件（explorer.exe  使用 C:\test22\\.. \\.. \123.txt 而不是 C:\test22\\.. \123.txt）。在搜索这样的文件夹时，Powershell将再次陷入无限循环。

附注2:还可以在一个名为“abc”的文件夹上创建ADS。然后可以将文件夹重命名为仅包含数字的名称(如“1”)。之后你仍然可以看到ADS，但是你不能打开它。(用数字作为名称的文件夹上的ADS不起作用)。要打开ADS数据，必须首先将文件夹重命名为“abc”。



### 文件系统与反病毒产品/取证软件:



我快速验证了上述针对AntiVirus产品的技巧，以验证它们是否可以捕获滥用技巧的恶意软件。最值得关注之处是文件/文件夹以 “. .”结尾产生的变化。例如我将eicar(测试病毒)储存在一个文件夹中，并用以下命令复制：

```
copy eicar.com > "123. .::$DATA"
copy eicar.com > tester 
echo 123 > "foo. .::INDEX_ALLOCATION" 
cd "foo. .::$INDEX_ALLOCATION" 
copy ..\eicar.com . 
copy ..\eicar.com .\eicar
```

之后，我重新启用了AntiVirus解决方案并扫描了该文件夹，所有AntiVirus解决方案都在此文件夹中找到了“eicar.com”和“tester”，而不是“123. .”  中的eicar病毒或“foo. .” 文件夹中的两个文件。但是进入该文件夹并启动文件时，AntiVirus产品会找到它们(因为内容是从文件系统加载到内存的)。Windows Defender的“删除”操作无法删除文件，因此没有影响。但是Emsisoft的“删除”操作可以删除文件夹中的tester病毒（译者注：Emsisoft是来自澳大利亚的杀毒软件）。Emsisoft删除了 “foo. .”  文件夹中的 “eicar.com” 文件，“eicar”文件没有被删除，内容可以毫无问题地读取（Emsisoft回应我们，只有映射为可执行文件的文件才会被扫描，有些特定的文件扩展名如.com除外）。这种行为可以在文件保护设置中通过切换到“彻底扫描”来读取就可以进行查杀；另一方面，Windows Defender也阻止了将“eicar”作为文本文件读取)。



我还对Autopsy 4.6.0（免费取证软件）进行了一个简短的测试。通过将“logical files ”模式加载到工具中（从正在运行的系统;不是一个磁盘映像），可以输入“…” 文件夹，但是不能输入“foo. .” 文件夹。我创建了两个文件，一个命名为“valid”，内容为“valid”，还有一个文件命名为“valid.”，内容为“secret”。Autopsy 显示了两个文件的内容“valid”(而不是“secret”的内容)。在“logical files ”模式下双击“.. ”文件夹(末尾有空格)后被转化为“..” 。在磁盘镜像(raw)模式下，一切都显示正确(在live模式中，Autopsy使用Windows API访问数据，才会出现问题。）



## 技巧6:隐藏进程二进制

正如上面已经讨论过的:Windows会在文件的末尾自动删除“. .” 。如果我们可以以“file1. .” 这样的名称来启动一个进程呢?好吧，那就会在“file1”执行的情况发生检查(例如:来自AntiVirus产品的签名检查)。让我们试试以下命令:

![](https://images2018.cnblogs.com/blog/549050/201808/549050-20180806003933721-766027268.jpg)

图27：复制了三个文件



我们创建了3个文件:

- 来自taskmgr具有微软签名的文件“file”
- “file. .”这是我们的"假恶意软件"，应该隐藏但执行
- “filex x”包含WinSCP的签名，此文件稍后将变得重要。



我们现在需要一种方法来从 “file. .” 二进制文件启动进程，这不是一项简单的任务，因为所有Microsoft Windows API调用都会自动从文件名中删除“. .”，然后启动“file”(taskmgr)。为了解决这个问题，我们使用以下代码:

![](https://images2018.cnblogs.com/blog/549050/201808/549050-20180806005016053-1103564461.jpg)

图28：解决自动从文件名中删除“. .”的代码



上面的代码只是调用CreateProcessA来从“filex x”(WinSCP)创建一个进程。如果我们编译这个应用程序并启动它，最终将执行的是WinSCP。可我们不能正常启动这个文件。相反，我们在调试器内启动应用程序（例如：WinDbg）。现在我们在函数中设置一个断点，它将产生相关的系统函数调用，调用:“bp ntdll!NtCreateUserProcess”。我们可以使用 “g” (go)  命令在调试器中启动程序并命中断点。在断点处，可以dump当前堆栈 (“dq rsp”) 。堆栈上的第12个指针很重要，应该被dump。这个地址的第四个值是指向文件名的指针。![](https://images2018.cnblogs.com/blog/549050/201808/549050-20180806005531814-1878579620.jpg)

图29：windbg



文件名(绿色框)现在是标准化显示(以\??\C:\… 开头)。这种标准化还需要从文件名末尾删除 “. .”  ——这就是为什么上面的C代码不使用“file. .” 作为进程名的原因。但是由于文件已经被改变为标准化，现在可以修改这个值。让我们用“.” 覆盖 “x”  字符。(命令“eb”用于编辑字节):

![](https://images2018.cnblogs.com/blog/549050/201808/549050-20180806010649104-818584853.jpg)

图30：编辑字节为"."



然后继续执行“g”。猜猜会发生什么?

“file. .” (恶意软件)被执行。但如果用户右键单击任务管理器中的进程并选择“属性”，则显示“file” (taskmgr) 的Microsoft签名。

 ![](https://images2018.cnblogs.com/blog/549050/201808/549050-20180806011119024-1538520684.jpg)

图31：显示“file” (taskmgr) 的Microsoft签名。



但是“filex x” （WiSCP）是什么呢？是的，这个文件也显示为正在运行的进程，即进程资源管理器(因为路径是在调用NtCreateUserProcess之前设置的)。![](https://images2018.cnblogs.com/blog/549050/201808/549050-20180806011401968-421709753.jpg)

图32："filex x"运行情况



与PowerShell有什么关系？是的，也是错误的二进制文件：

![](https://images2018.cnblogs.com/blog/549050/201808/549050-20180806011530025-117093294.jpg)

图33：Powershell显示情况



这是不是安全问题得视情况而定。首先，攻击者可以启动一个进程(恶意软件)，重命名/删除它，然后将一个有效的文件重命名为相同的名称。在taskmanager和process explorer中也会出现上述效果。但是不同之处在于，使用上述技巧，得在进程启动的同时发生。



例如，如果在云中已知二进制哈希，请考虑已经安装的端点保护检查每个已启动的进程。通过此技巧，端点保护可能会使用错误的二进制文件来验证哈希是否为白名单。另外还要注意创建此类进程并不需要调试器，应用程序可以挂钩 NtCreateUserProcess函数并在钩子中就可以实现修改。



WINDOWS CMD的技巧:

这些技巧与文件系统技巧没有任何关系，但是我认为它们很适合这篇博文。在Windows cmd中，可以在命令中的任何位置写入^符号，CMD将完全忽略掉这个符号。例如,“calc.exe” 和“ca^l^c”效果相同。^是不是最后一个符号不重要，并且两个^符号在相邻时无法使用。使用双引号"隔开就没有限制了（它可以是最后一个字符或多次使用）。例如，^ca^“^”^lc^“将启动计算器。 



这同样适用于零长度环境变量。可以通过％name％访问环境变量。如果环境变量的长度为零，则“cal％name％c”将与“calc”相同。由于环境变量的默认值长度不为零，因此不能直接使用。但是，可以使用特殊语法（:~start,end）在环境变量上调用substring。下图显示了“windir”环境变量以及子字符串如何与negativ值一起使用以获取返回的零长度变量：

 ![](https://images2018.cnblogs.com/blog/549050/201808/549050-20180806031026164-635483423.jpg)

图34：环境变量取字符



下图显示了这些技术的组合，以隐藏Powershell在版本2中启动（这些技巧在之前很有用，但在最新的Windows 10系统上应该是实现不了）：

![](https://images2018.cnblogs.com/blog/549050/201808/549050-20180806160516942-2098099394.jpg)

图35：运行Powershell技巧



可以看到使用^和环境变量技巧（%os:~0,-56%），还使用版本“00000000002.0000”（而不仅仅是2）并且参数是“?ver ”不是“-ver”（注意，这不是正常的？符号，它是U+2015 ;光使用?不起作用）。 



在Windows上除了“\” 也可以把“/”作为路径使用。例如，C:\Windows/\//\system32\calc.exe 与C:\Windows\system32\calc.exe 相同。 而且还可以通过UNC路径访问二进制文件不用``` “C:\” ``` 模式： ```\\\127.0.0.1\C$\windows\system32\calc.exe ```



通常可以使用类似的技巧来打破使用黑名单的方法（例如，如果禁止使用Powershell.exe，则攻击者可以调用Power^shell.exe来绕过限制。或者如果禁止使用calc，则可以执行：

^"%LOCALAPPDATA:~-3%^%SYSTEMROOT:~0,1%^" 

启动calc.exe等）。



这篇博客文章由RenéFreingruber *(@ReneFreingruber)* 代表SEC Consult Vulnerability Lab撰写。James Forshaw*(@tiraniddo)将一系列的技术列表文档化。*Alex Inführ (@insertScript) 在他的博客文章中记录了一些ADS隐藏技巧。有关ADS之前的参考文献，请参阅以下参考资料部分。



## 参考文献

<https://msdn.microsoft.com/en-us/library/dn393272.aspx>

<https://tyranidslair.blogspot.co.at/2014/05/abusive-directory-syndrome.html>

<https://tyranidslair.blogspot.co.at/2014/06/addictive-double-quoting-sickness.html>

<https://googleprojectzero.blogspot.co.at/2016/02/the-definitive-guide-on-win32-to-nt.html>

<https://googleprojectzero.blogspot.co.at/2015/12/between-rock-and-hard-link.html>

<https://googleprojectzero.blogspot.co.at/2015/08/windows-10hh-symbolic-link-mitigations.html>

<http://insert-script.blogspot.co.at/2012/11/hidden-alternative-data-streams.html>

<https://bogner.sh/2017/11/avgater-getting-local-admin-by-abusing-the-anti-virus-quarantine/>

编辑历史：

2018-06-13：Soroush Dalili在Twitter上指出，他已经在2010年使用了INDEX_ALLOCATION技巧来绕过IIS5.1中的身份验证检查以及类似“..”文件夹的技巧。 更多信息可在以下两个参考资料中找到：

<https://soroush.secproject.com/blog/2010/07/iis5-1-directory-authentication-bypass-by-using-i30index_allocation/>

<https://soroush.secproject.com/blog/2010/12/a-dotty-salty-directory-a-secret-place-in-ntfs-for-secret-files/>

2018-06-14：Daniel Bohannon（@danielhbohannon）开发了Invoke-DOSfucation，这是一个可用于cmd.exe中混淆的工具。

<https://github.com/danielbohannon/Invoke-DOSfuscation>

<https://www.fireeye.com/blog/threat-research/2018/03/dosfuscation-exploring-obfuscation-and-detection-techniques.html>

2018-06-14：Oddvar Moe（@Oddvarmoe）列出了更多从ADS执行应用程序/脚本的技术：

<https://gist.github.com/api0cradle/cdd2d0d0ec9abb686f0e89306e277b8f>

<https://oddvar.moe/2018/01/14/putting-data-in-alternate-data-streams-and-how-to-execute-it/>

<https://oddvar.moe/2018/04/11/putting-data-in-alternate-data-streams-and-how-to-execute-it-part-2/>



## 附录

**译者注：**经过测试Windows XP后微软就禁止用户从ADS里执行程序了。不允许执行，但是写入，读出操作都可以。其实只是禁用了OWASP中提到的start命令，文章中用WMIC运行就很巧妙的绕过封堵，测试方法如下（需要使用绝对路径）。

```
wmic process call create "C:\ProjectCode\test\test:putty.exe"
```



文中的zone.identifier是一个文本文件，然后作为数据流存放到了putty.exe里。ADS并不是一个新的话题了，在翻译过程中发现国内有许多相关资料写得都不错，国人很棒棒。根据目前知识量的储备在WinDBG调试部分翻译的词汇翻译不够准确，根据需求请参考原文。

  

**文章来源**

https://www.sec-consult.com/en/blog/2018/06/pentesters-windows-ntfs-tricks-collection/

**OWASP alternate_data_stream**

https://www.owasp.org/index.php/Windows_::DATA_alternate_data_stream

**一个用ADS（供选数据流）隐藏Windows后门的方法**

http://www.freebuf.com/articles/73270.html

**文件流-MSDN说明**

https://msdn.microsoft.com/en-us/library/dn410405.aspx

https://docs.microsoft.com/zh-cn/windows/desktop/FileIO/file-streams

**Hidden Alternative Data Streams的进阶利用技巧**

http://www.4hou.com/technology/4783.html