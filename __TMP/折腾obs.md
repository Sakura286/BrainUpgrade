
# 折腾OBS

rpm系与deb系

deb：debian，ubuntu
rpm：redhat，centOS, openSUSE

rpm：Red Hat Package Manage
RPM package manager

这玩意儿默认不带sudo……

## 一个错误

```default
sudo dnf install rpmdevtools*
[sudo] password for infinity:
Last metadata expiration check: 0:07:21 ago on Sat 23 Apr 2022 07:55:29 AM CST.
Error:
 Problem: conflicting requests
  - nothing provides fakeroot needed by rpmdevtools-8.10-8.noarch
(try to add '--skip-broken' to skip uninstallable packages or '--nobest' to use not only best candidate packages)
```

```default
sudo dnf install rpmdevtools --skip-broken
Last metadata expiration check: 0:09:19 ago on Sat 23 Apr 2022 07:55:29 AM CST.
Dependencies resolved.
Nothing to do.
Complete!
```

AArch64 是 Armv8的一种64位的执行状态， Armv8 也可以兼容 AArch32 这种32位状态

## Xshell颜色

蓝色表示目录；绿色表示可执行文件；红色表示压缩文件；浅蓝色表示链接文件；白色表示其他文件；黄色是设备文件

## 关于清华大学的 yum 源（仅有x86）

请注意，CentOS 8 （非 Stream 版）已提前进入 EOL 停止服务阶段，因此镜像已被官方移动。如果您正在寻找关于这些系统的镜像，请参考 centos-vault 的帮助。

该文件夹只提供 CentOS 7 与 8，架构仅为 x86_64 ，如果需要较早版本的 CentOS，请参考 centos-vault 的帮助，若需要其他架构，请参考 centos-altarch 的帮助。

建议先备份 /etc/yum.repos.d/ 内的文件。

然后编辑 /etc/yum.repos.d/ 中的相应文件，在 mirrorlist= 开头行前面加 # 注释掉；并将 baseurl= 开头行取消注释（如果被注释的话）。 对于 CentOS 7 ，请把该行内的域名（例如mirror.centos.org）替换为 mirrors.tuna.tsinghua.edu.cn。 对于 CentOS 8 ，请把 mirror.centos.org/$contentdir 替换为 mirrors.tuna.tsinghua.edu.cn/centos。

## 小心vscode

vscode 的 tab 并不是 \\t ，而是四个空格，在写 makefile 的时候要小心

## make

正常的 $ 符号是被转义的，所以在 make 里要用 $$ 代替 $

## 查看文件树

tree 命令

## ll

ll 与 ls -l 的作用是一样的，都是每个文件单独一行

## 配置本地 yum 源

注意repo文件配置中，有如下配置：`baseurl=file://<PATH>`，`PATH`为仓库的文件路径，例如在`/home/privateRepo`，这样的话`file:`后面会有**三个**正斜杠

清空yum缓存目录：`yum clean all`

生成yum元数据：`yum makecache`