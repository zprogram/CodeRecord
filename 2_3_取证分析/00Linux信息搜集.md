## 1、取证工具

- LiME 内存获取工具
- volatility 内存分析工具

## 2、机器信息收集
```
#sysinfo  16

# # 查看当前登录用户
who > who.txt
# # 显示目前登入系统的用户信息
w > w.txt
# # 显示时间
date > date.txt
# # 查看CPU信息
cat /proc/cpuinfo > cpuinfo.txt
# # 查询系统版本
lsb_release -a > lsb_release.txt
# # 当前系统相关信息(内核版本号、硬件架构、主机名称和操作系统类型等)
uname -a > uname.txt
# # Linux查看当前操作系统版本信息
cat /proc/version >  version.txt
# # 以批处理模式显示进程信息，更新1次后不再更新
top -b -n 1 > top.txt
# # 查看系统负载
uptime > uptime.txt
# # MB显示当前内存的使用
free -m > free_m.txt
# # 文件系统的磁盘空间占用情况
df -lhT > df_lhT.txt
# #  显示分区类型
fdisk -l > fdisk_l.txt
# # 挂载设备情况
mount > mount.txt
# # 显示系统中已存在的环境变量
env > env.txt
# # 查看自定义环境变量
cat ~/.bashrc > bashrc.txt
# # 读取内核信息
cat /proc/meminfo > meminfo.txt

#account check  7

# # 系统用户信息
cat /etc/passwd > etc_passwd.txt
# # 密文信息
cat /etc/shadow > etc_shadow.txt
# # 查看用户文件状态
stat /etc/passwd > etc_passwd_stat.txt
stat /etc/shadow > etc_shadow_stat.txt
# # 查看特权用户
awk -F: '$3==0 {print $1}' /etc/passwd > etc_passwd_special_usr.txt
grep “0” /etc/passwd > etc_passwd_new_user.txt
awk -F: 'length($2)==0 {print $1}' /etc/shadow > etc_shadow_no_password_user.txt

#process check  4

# # 全格式显示所有进程
ps -elf > ps_elf.txt
# # 显示所有进程，包括其他用户 
ps aux > ps_aux.txt
ps -ef | grep inted  >  ps_inted.txt
ls /proc |sort -n|uniq > proc.txt

#file check 11

# # 根据uid、执行权限来查找
find / -uid 0 -perm -4000 > uid0_perm4000.txt
# # 根据文件大小
find / -size +10000k > size10000.txt
find / -name "..." > 3point_name_file.txt
find / -name ".. " > 2point_name_file.txt
find / -name ". " > 1point_name_file.txt
find / -name " " > blankspace_name_file.txt
# # 查看隐藏文件
find / -name ".*" > hide_file.txt
find / -name "*" > all_file.txt
find / -name ".rhosts" > rhosts.txt
find / -name ".forward" > forward.txt
# # 列出当前系统打开文件
lsof > lsof.txt

#integrity check 5

# # 查询指定文件来自于哪个安装包
rpm -qf /bin/ls > rpm_ls.txt
rpm -Vf /bin/ls >> rpm_ls.txt
rpm -qf /bin/netstat > rpm_netstat.txt
rpm -Vf /bin/netstat >> rpm_netstat.txt
rpm -qf /bin/login > rpm_login.txt
rpm -Vf /bin/login >> rpm_login.txt
rpm -qf /bin/find > rpm_find.txt
rpm -Vf /bin/find >> rpm_find.txt
rpm -qf /usr/bin/top > rpm_top.txt
rpm -Vf /usr/bin/top >> rpm_top.txt


#network check 6

# # 查看路由表条目
ip link | grep PROMISC > ip_promisc.txt
# # 显示所有联网文件
lsof -i > lsof_i.txt
# # 显示TCP、UDP传输协议、Socket程序名称
netstat -ntulpa >  netstat_ntulpa.txt
# # 显示正在使用Socket的程序
netstat -anpo > netstat_anpo.txt
# # 显示arp缓冲区的所有条目
arp -a > arp_a.txt
# # 显示全部接口信息
ifconfig -a > ifconfig_a.txt

#schedule check 5

# # 显示root的crontab文件内容
crontab -l -u root > root_crontab.txt
crontab -l -u coremail > coremail_crontab.txt
# # 计划任务
cat /etc/crontab > etc_crontab.txt
# # 列出计划任务的脚本
ls /etc/cron.* -a > etc_cron.txt
# # 查看定时任务
ls /var/spool/cron/ -a > var_spool_cron.txt

#rc check 4

# # 启动项顺序
cat /etc/rc.d/rc.local > rc_local.txt
# # 该目录下存在各个运行级别的脚本文件
ls /etc/rc.d -a > rc_d.txt
ls /etc/rc*.d -a > rcV_d.txt
# # 搜索执行权限4000的普通类型文件
find / -type f -perm 4000 > type_f_perm_4000.txt

#log check 11

# # 日志进程
ps -ef | grep syslog > syslog.txt
# # 列出日志目录
ls -al /var/log > var_log.txt
# # 列出日志目录状态
stat /var/log/wtmp > stat_wtmp.txt
stat /var/run/utmp > stat_utmp.txt
cat /var/run/utmp > utmp.txt
cat /etc/rsyslog.conf > rsyslog_conf.txt
cat /etc/init.d/rsyslog > rsyslog.txt
# # 列出登入系统失败的用户相关信息
lastb > lastb.txt
# # :列出目前与过去登入系统的用户相关信息
last > last.txt
# # Shell历史命令记录文件
cat ~/.bash_history > history.txt
ls -l ~/.bash_history > bash_history.txt

#inetd sheck 1

# # 扩展互联网服务守护进程配置
cat /etc/xinetd.conf > xinetd_config.txt

#kernel check 2

# # 加载的模块信息
lsmod > lsmod.txt
find / -name core -exec ls -l {} \; > core_file.txt

#service check 2

# # 查看开机启动服务
chkconfig --list > chkconfig_lists.txt
# # 查看本地rpc进程
rpcinfo -p > rpcinfo.txt

#files get 5

# # 打包守护进程文件
tar -zcvf xinetd.tar.gz /etc/xinetd.d/*
# # 打包日志文件
tar -zcvf log.tar.gz /var/log/*
# # 打包自启动脚本
tar -zcvf rcd.tar.gz /etc/rc.d/* 
# # 打包计划任务
tar -zcvf cron.tar.gz /etc/cron.*
tar -zcvf at.tar.gz /var/spool/at/* 
```
