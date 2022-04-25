
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

git好像就是ssh？

```bash
[root@openEuler-RISCV-rare zlib]# ls
_service
_service:tar_scm_kernel_repo:0001-Neon-Optimized-hash-chain-rebase.patch
_service:tar_scm_kernel_repo:0002-Porting-optimized-longest_match.patch
_service:tar_scm_kernel_repo:0003-arm64-specific-build-patch.patch
_service:tar_scm_kernel_repo:0004-zlib-Optimize-CRC32.patch
_service:tar_scm_kernel_repo:0005-Accelerate-Adler32-using-arm64-SVE-instructions.patch
_service:tar_scm_kernel_repo:backport-0001-CVE-2018-25032.patch
_service:tar_scm_kernel_repo:backport-0002-CVE-2018-25032.patch
_service:tar_scm_kernel_repo:fix-undefined-buffer-detected-by-oss-fuzz.patch
_service:tar_scm_kernel_repo:zlib-1.2.11-optimized-s390.patch
_service:tar_scm_kernel_repo:zlib-1.2.11-SIMD.patch
_service:tar_scm_kernel_repo:zlib-1.2.11.tar.xz
_service:tar_scm_kernel_repo:zlib-1.2.5-minizip-fixuncrypt.patch
_service:tar_scm_kernel_repo:zlib.spec
_service:tar_scm_kernel_repo:zlib.yaml
[root@openEuler-RISCV-rare zlib]#
rm -f _service;
for file in `ls | grep -v .osc`;
do new_file=${file##*:};
mv $file $new_file;
done
[root@openEuler-RISCV-rare zlib]# ls
0001-Neon-Optimized-hash-chain-rebase.patch
0002-Porting-optimized-longest_match.patch
0003-arm64-specific-build-patch.patch
0004-zlib-Optimize-CRC32.patch
0005-Accelerate-Adler32-using-arm64-SVE-instructions.patch
backport-0001-CVE-2018-25032.patch
backport-0002-CVE-2018-25032.patch
fix-undefined-buffer-detected-by-oss-fuzz.patch
zlib-1.2.11-optimized-s390.patch
zlib-1.2.11-SIMD.patch
zlib-1.2.11.tar.xz
zlib-1.2.5-minizip-fixuncrypt.patch
zlib.spec
zlib.yaml

```

```
[root@openEuler-RISCV-rare zlib]# ls -a
# 0001-Neon-Optimized-hash-chain-rebase.patch
# 0002-Porting-optimized-longest_match.patch
# 0003-arm64-specific-build-patch.patch
# 0004-zlib-Optimize-CRC32.patch
# 0005-Accelerate-Adler32-using-arm64-SVE-instructions.patch
# backport-0001-CVE-2018-25032.patch
# backport-0002-CVE-2018-25032.patch
# fix-undefined-buffer-detected-by-oss-fuzz.patch
# zlib-1.2.11-optimized-s390.patch
# zlib-1.2.11-SIMD.patch
# zlib-1.2.11.tar.xz
# zlib-1.2.5-minizip-fixuncrypt.patch
# zlib.spec
# zlib.yaml

[root@openEuler-RISCV-rare zlib]# ls grep .osc
ls: cannot access 'grep': No such file or directory
.osc:
# 0001-Neon-Optimized-hash-chain-rebase.patch
# 0002-Porting-optimized-longest_match.patch
# 0003-arm64-specific-build-patch.patch
# 0004-zlib-Optimize-CRC32.patch
# 0005-Accelerate-Adler32-using-arm64-SVE-instructions.patch
_apiurl
# backport-0001-CVE-2018-25032.patch
# backport-0002-CVE-2018-25032.patch
_files
# fix-undefined-buffer-detected-by-oss-fuzz.patch
_meta
_osclib_version
_package
_project
# zlib-1.2.11-optimized-s390.patch
# zlib-1.2.11-SIMD.patch
# zlib-1.2.11.tar.xz
# zlib-1.2.5-minizip-fixuncrypt.patch
# zlib.spec
# zlib.yaml

```

## 一些

反引号括起来的命令是优先执行的

ls 的 -R 指令递归地列出子文件夹中的文件

变量初始化时不应加$
变量名可以不加${}，只是防止引起歧义

## 去除前缀

例如现在目录下有两个文件`1:2:3:4:abc.txt`与`5:6:7:8:def.txt`，要想获得`abc.txt`与`def.txt`，可以这样写

```bash
for file in `ls`; do new_file=`echo ${file##*:}`; mv $file $new_file; done
```

这里需要注意的是`${file##*:}`意味着什么，我们可以先看去掉一个`#`的`$file#*:`，获得了`2:3:4:abc.txt`与`2:3:4:def.txt`文件，即`${var#prefix}`里去掉了`var`的`prefix`前缀，那么加两个`#`则可能使用贪心匹配

## 三种包管理方式

rpm、deb、pacman

台湾那边把谷歌叫酷狗
台湾那边的“阳春”是“质朴”的意思

读一读《提问的智慧》

也就是说sda是硬盘，sda1是分区
