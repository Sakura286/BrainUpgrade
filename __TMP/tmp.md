
# some temp memo

发散记录
每天睡前收敛一次，归类、小标题、问题与想法
每周周末归类一次，移出本文件

## 6-12

### debian gnome的小问题



## 6-9

### RISC-V conference

李伟伟
QEMU RISC-V Simulator

V8 for RISC-V

史宁宁
OpenJDK for RISC-V

张宏斌
MLIR RISC-V Vector Dialect Proposal

韩柳彤
OpenCV for RISC-V vector（DNN？）

徐东
Arch Linux

于波


## 6-8

realpath basename dirname
注意用法

### 试试自定义

alias plz=sudo
alias hentai=su

### bridge

**问题**：啥是bridge啊
桥接模式 bridge 设计模式

### 拓展磁盘空间

装了fdisk但还是显示command not found

`whereis fdisk`看到fdisk在`/sbin/fdisk`

`echo $PATH`结果是`/usr/local/bin:/usr/bin:/bin:/usr/local/games:/usr/games`，没有上述的目录

然后想到现在是普通用户，`/sbin`是管理员使用的目录，那么`sudo fdisk`使用管理员权限运行就行了

### 关于configure和makefile的生成过程

博客园 - Linux下使用automake、autoconf生成configure文件
`https://www.cnblogs.com/bugutian/p/5560548.html`

src --autoscan--> configure.scan --edit--> configure.ac

configure.ac --aclocal--> aclocal.m4
configure.ac + aclocal.m4 --autoconf--> configure
configure.ac --autoheader--> config.h.in

Makefile.am --automake--> Makefile.in
Makefile.in + config.h.in + configure --configure--> Makefile

### 关于QEMU debian

通过
Debian-Ports `https://www.debian.org/ports/`
-->
Debian-Wiki `https://wiki.debian.org/RISC-V`
-->
Debian Quick Image Baker`https://people.debian.org/~gio/dqib/`
安装了 debian 12 riscv 版本（真几把难找）

**问题**：从哪里找一个*稳定*版本的镜像？

qemu跑前要装u-boot-qemu与opensbi
但arch linux想要跑qemu的debian还得从apt仓库里把u-boot-qemu与opensbi给拉出来，用debtap转一下才能用
AUR里找不到opensbi，里面有的u-boot-bin也不适合
**想法**：能不能给AUR里面添加opensbi与u-boot-qemu？反正已经会点makepkg打包了。

**想法**：写一个教程，教怎么找qemu镜像

说实话，磁盘IO速度真慢

**想法**：想看看chroot怎么搞，以及能不能跨架构使用
**想法**：要是能交叉编译的话，是不是性能可以大大提升？

### 关于Debian

**问题**：中文输入法设置不好
**问题**：桌面图标无法显示
**问题**：Grub炸了，得修一下
**想法**：能不能把Grub做得漂亮点？

### perl

chomp把回车\\n去掉

unshift(A,B,C)
把 B C 插入到A之前

A if(a)
if为操作语句的修饰符，这句话的意思是，如果a成立，那么执行A
一种倒装的语句形式

if条件为0或为空，则算false

Perl 子程序可以和其他编程一样接受多个参数，子程序参数使用特殊数组 @_ 标明。

因此子程序第一个参数为 $_[0], 第二个参数为 $_[1], 以此类推。

my定义局部变量
**问题**：儿子继承父亲不？

可以用local变量暂时将全局变量定义为局部变量，等局部变量失效后再还回去

使用static使变量离开函数后不销毁，等待下次调用的时候使用

### 复制时显示进度

`rsync --progress t01/demo.zip t02/`


apt --fix-missing可以跳过有问题的包

## 6-7

完成https://gitee.com/openeuler/RISC-V/blob/master/doc/tutorials/test_example_xfce.md

extra/qemu-common 7.0.0-10 [installed]
    A generic and open source machine emulator and virtualizer
extra/qemu-hw-display-virtio-gpu 7.0.0-10 [installed]
    QEMU virtio-gpu display device
extra/qemu-hw-display-virtio-gpu-gl 7.0.0-10 [installed]
    QEMU virtio-gpu-gl display device
extra/qemu-hw-display-virtio-gpu-pci 7.0.0-10 [installed]
    QEMU virtio-gpu-pci display device
extra/qemu-hw-display-virtio-gpu-pci-gl 7.0.0-10 [installed]
    QEMU virtio-gpu-pci-gl display device
extra/qemu-system-riscv 7.0.0-10 [installed]
    QEMU system emulator for RISC-V
extra/qemu-ui-sdl 7.0.0-10 [installed]
    QEMU SDL UI driver
extra/vde2 2.3.3-1 [installed]
    Virtual Distributed Ethernet for emulators like qemu

  -display sdl,gl=on \
  -kernel "$fw" \
  -bios none \
  -drive file="$drive",format=raw,id=hd0 \
  -object rng-random,filename=/dev/urandom,id=rng0 \
  -device virtio-gpu-gl \
  -device virtio-rng-device,rng=rng0 \
  -device virtio-blk-device,drive=hd0 \
  -device virtio-net-device,netdev=usernet \

lsb_release -a
LSB Version:    n/a
Distributor ID: ManjaroLinux
Description:    Manjaro Linux
Release:        21.2.6
Codename:       Qonos
又学到了一手

常见的错误提示用语：

ERROR
WARNING
not found

bleeding edge就是测试版，预览版的意思

BusyBox 就是那个1M的集成了一大堆功能的shell

## 6-6

不能在数组里用变量？

## 6-5

fakeinstall时，perl会报错，找不到destdir，先尝试把--enable-split-app-modules关掉再说
--> 不行
--> 但是找到了问题所在：特么的用了相对路径~

发现自己电脑的makeflag是j9……八个任务在做然后另外一个任务在外面等待？

可以从autogen.sh中学习怎么写帮助

TDF: the document foundation

下载的这些额外文件都是什么？

从哪里找校验的MD5？

GPG check是不是要学习一下？

创建软链接时出错也会使得makepkg停下来

了解makepkg的一些参数

patch -p1

p后面的参数可以忽略掉patch里面前x层的目录

## 6-4

[infinity-mi infinity]# update-grub
Generating grub configuration file ...
Found theme: /usr/share/grub/themes/manjaro/theme.txt
Found linux image: /boot/vmlinuz-5.15-x86_64
Found initrd image: /boot/intel-ucode.img /boot/initramfs-5.15-x86_64.img
Found initrd fallback image: /boot/initramfs-5.15-x86_64-fallback.img
Warning: os-prober will be executed to detect other bootable partitions.
Its output will be used to detect bootable binaries on them and create new boot entries.
Found Windows Boot Manager on /dev/nvme0n1p1@/EFI/Microsoft/Boot/bootmgfw.efi
Adding boot menu entry for UEFI Firmware Settings ...
Found memtest86+ image: /boot/memtest86+/memtest.bin
/usr/bin/grub-probe: warning: unknown device type nvme0n1.
done

ventoy真是个好东西……记得复制完ISO后sync一下

搞明白 tarsier 在搞哪些发行版

arise issue

解释了debian，debian port，debian port for RISC-V 这些明此款
`https://riscv.org/wp-content/uploads/2016/07/Wed1115_Working_Towards_a_Debian_RISC-V_Port.pdf`

Arch官方的PKGBUILD里把link time optimization禁用了，我不知道这是个什么东西，先把一些链接拿上来
`https://www.its203.com/article/qq_36287943/103681797`
`https://blog.csdn.net/qq_36287943/article/details/103930336`
`https://zhuanlan.zhihu.com/p/384160632`
`https://www.jianshu.com/p/58fef052291a`

`source=('directory::url#fragment?query')`

`directory` 要克隆下来的名字
`url` 格式其实是`vcs+url`其中vcs是版本控制器的名字，比如git
`fragment` 要采用哪个分支/提交/标签，例如`branch=master`

PGP（商业） GPG（开源）
`https://zh.wikipedia.org/zh-hans/PGP`

Arch Linux 打包的相关链接

`https://wiki.archlinux.org/title/Makepkg_(%E7%AE%80%E4%BD%93%E4%B8%AD%E6%96%87)`
`https://wiki.archlinux.org/title/PKGBUILD_(%E7%AE%80%E4%BD%93%E4%B8%AD%E6%96%87)`
`https://wiki.archlinux.org/title/Creating_packages_(%E7%AE%80%E4%BD%93%E4%B8%AD%E6%96%87)`
`https://man.archlinux.org/man/PKGBUILD.5`
`https://wiki.archlinux.org/title/VCS_package_guidelines`

libreoffice除了主程序core（256M左右）之外，还有子模块字典（dictionaries 51M）、帮助（help 110M）、翻译（translations 196M）

每次更新的log可以在`https://dev-builds.libreoffice.org/pre-releases/src/`看

## 6-3

Refer:[lightlyshaders - aur](https://aur.archlinux.org/cgit/aur.git/tree/PKGBUILD?h=lightlyshaders-git)

TODO:

1. see how to use variable in sed
2. know more about the .desktop group of libreoffice

sudo rejects password that is correct when using yay to build

<!-- referrence:[sudo rejects password that is correct](https://serverfault.com/questions/424775/sudo-rejects-password-that-is-correct) -->

查看systemd-homed，发现这个进程死掉了

```console
$ systemctl status systemd-homed
○ systemd-homed.service - Home Area Manager
     Loaded: loaded (/usr/lib/systemd/system/systemd-homed.service; disabled; vendor preset: enabled)
     Active: inactive (dead)
       Docs: man:systemd-homed.service(8)
             man:org.freedesktop.home1(5)
```

重启该服务

```console
systemctl start systemd-homed
```

然后查看systemd-homed，没问题了

```console
$ systemctl status systemd-homed
● systemd-homed.service - Home Area Manager
     Loaded: loaded (/usr/lib/systemd/system/systemd-homed.service; disabled; vendor preset: enabled)
     Active: active (running) since Fri 2022-06-03 11:32:05 CST; 2s ago
       Docs: man:systemd-homed.service(8)
             man:org.freedesktop.home1(5)
   Main PID: 557487 (systemd-homed)
     Status: "Processing requests..."
      Tasks: 1 (limit: 19033)
     Memory: 1.3M
        CPU: 23ms
     CGroup: /system.slice/systemd-homed.service
             └─ 557487 /usr/lib/systemd/systemd-homed

6月 03 11:32:05 infinity-mi systemd[1]: Starting Home Area Manager...
6月 03 11:32:05 infinity-mi systemd-homed[557487]: Watching /home.
6月 03 11:32:05 infinity-mi systemd[1]: Started Home Area Manager.
```

## 6-2

base-devel还没加进去

我这边在x86 manjaro上编译通过了libreoffice，现在正在看怎么用makepkg编译打包

写一个脚本，可以将文件添加进我的github临时仓库，并返回该文件的链接

./external/tarballs

`wget -r --level=1 -nd -P ./external/tarballs https://go.suokunlong.cn:88/dl/libreoffice/external_tarballs/`

error: failed to init transaction (unable to lock database)
error: could not lock database: File exists
  if you're sure a package manager is not already
  running, you can remove /var/lib/pacman/db.lck

不能在pacman安装程序的时候运行另外一个pacman安装程序，否则会报这样的错误

## 5-12 Shell script: write an auto-backup shell script for Minecraft backup

usage: `local-backup.sh -p <preffix> <file1> <file2> <file3> ...`

output name: `<preffix>-<date>-<time>-<sha256preffix>.tar.xz`, such as `minecraft-20220526-0739-xxxxxxxxx.tar.xz`

todo:

- [x] get the preffix - default is the name of the parent folder
- [x] generate time and convert it to suitable format
- [x] choose a compress method/suffix
- [x] check whether the file exist
- [x] compress to a file - generate filename with 'mktemp'
- [x] calc sha256 and rename it
- [x] add `--help`, and usage prompt

optional:

- [x] backup regularly
- [ ] check whether the file updated, if not, stop archive
- [ ] upload the file to Telegram channel

## English

contact **with** sb.

## 测试岗位信息搜索

## 从零开始学测试

项目的一生

1. 编程阶段：单元（白盒）测试
2. 编程完成：开发联调（集成测试）
3. 提交测试：冒烟测试（自动化为主）
4. 测试阶段：黑盒测试，安全测试
5. 验收阶段：验收测试

### 软件测试

1

### 测试覆盖率

特点：

1. 通过覆盖率数据，可以检测我们的测试是否充分
2. 分析出测试的弱点在哪方面
3. 指导我们设计能够覆盖率的测试用例，有效提高测试质量。但是不能无休止地提升，因为提升需要成本。

测试覆盖率对于黑盒测试来说，有两个方面

#### 1. 需求覆盖

需求覆盖 = （被验证到的需求数量） / （总的需求数量）

第一次发布软件时，需求覆盖率需要达到100%

后续迭代时

#### 2. 用例覆盖

用例覆盖 = （验证通过的用例数量） / （总的用例总数）

一般要求达到80%的覆盖率

#### 测试覆盖率的运用

##### 简单测试覆盖率

本次用例数 / 所有用例数

要求总用例数编写全面，一般对于大型系统测试要求覆盖率100%

覆盖率的审核：抽样验收

考察**测试人员**，测试策略，抽样还是全覆盖，看一下测试用例的选用是否全面

##### 基于产品的测试覆盖率

已测试需求点/涉及所有需求数

无论大小项目或者小需求迭代，要求覆盖率达到100%

提交给**产品方**，使产品方判断产品是否有遗漏测试场景

**审核**：抽样

##### 基于白盒的覆盖率

单元测试代码覆盖代码行/总代码行

考察研发人员，更多时候要求覆盖率达到80%所有

**缺陷**：只能代表测试过哪些代码，不代表是否测试好。容易一楼逻辑、判断等场景。

使用**工具**来验证，tomcat，emma

既需要源码，也需要单元测试代码

##### 基于自动化覆盖率

自动化覆盖的测试用例/所有测试场景

二八原则，80%的时间在使用20%的核心功能上，测试用例选择上更着重与这20%核心功能的完善

#### 测试覆盖率的最终意义

应用最多的地方在**测试停止标准**

瀑布式开发中并不需要，因为需要100%

螺旋式、敏捷开发模型中难以确定哪些模块在开发过程中没有给予足够的测试

在短迭代、DevOps中，更强调用白盒覆盖率来评估不断增加的代码数量

### 测试团队组织架构

#### 金字塔式管理

有专门的测试部门

测试总监 - 产品线测试经理/主管 - 测试组长 - 测试人员

#### 矩阵化管理模式

**项目经理**、研发经理、测试经理分开管理测试人员

### 软件测试人员

#### 知识体系

- 软件测试基础知识
- 软件测试流程
- （黑盒）测试用例设计方法
- 兼容性测试/易用性测试
- 缺陷管理
- 测试工具使用
- 测试文档编写

#### 软件测试的原则

1. 所有的测试都应该追溯到用户的需求
2. 今早启动测试工作——修改错误的成本越晚越高
3. 帕累托法则应用于软件测试（二八定律）
   在分析设计阶段解决80%的问题，在系统测试阶段解决80%的问题，剩下的4%用户使用阶段发现
4. 穷尽测试是不可能的，需要合理利用风险分析
5. 杀虫剂怪事
   软件测试越多，其对测试的免疫力越强，因为开发人员知道怎么做才能更容易通过测试套路。测试人员应该不断编写不同新的测试程序
6. 前进两部，后退一步
   一个基本问题：缺陷修复总会以20~50%的几率引入新的缺陷
   每次修复之后必须重新运行之前的测试用例保证通过
7. 三心二意
   细心、信心、耐心
   团队合作的沟通意识，时刻保持怀疑的态度且有缺陷预防意识

#### 软件工程标准

国内通用的主要用 ISO9000 和 CMM

##### ISO9000

1. 控制的思想，对产品形成的全过程进行控制
2. 预防的思想：预防不合格，从根本上减少或消除不合格产品

### 软件测试环境搭建原则 - 测试环境必知必会

#### 搭建环境前

##### 确定测试目的

功能测试、稳定性测试还是性能测试

测试功能：不需要大量的数据，需要覆盖率高，测试数据要尽量真实

性能测试：可能需要大量存数据，模拟与实际硬件环境尽可能相似的硬件配置

##### 测试的软件环境尽可能地模拟真实环境

尽可能模拟用户使用环境，选用合适的操作系统和软件平台

了解符合测试软件运行的最低要求及用户使用的硬件配置

了解用户常用的软件，避免所有的配置所有操作系统下都要进行测试

产品化的测试需要考虑兼容性的方案

##### 营造独立的测试环境

保持测试环境独立，不会受到其他测试人员及项目研发人员的影响

##### 构建可复用的测试环境

通过备份或数据隔离的方式，重复运用一套测试环境进行多版本多时间段的测试

#### 搭建测试环境过程分析

##### 线下搭建

独立的测试服务器或虚拟机

测试环境配置

测试项目导入

example：

1. 配置java环境（下载jdk病配置环境变量）
2. 下载并安装中间件（tomcat、jetty或其他）
3. 安装数据库并导入初始化脚本

##### Docker模式

##### 依赖第三方平台

### 浅谈测试环境的建设落地

#### 环境建设思路

**考虑点**：用途、使用成本、维护成本

**基本架构**：

研发环境：用户研发自测、集成测试
测试环境：用于日常单系统或两两微服务之间测试，可同事集成自动化测试回归
联测环境：完备环境，用于大型联测
外联环境（如果有需求）：稳定环境版本，用于外部商户等联调
灰度/沙箱环境：用户生产数据测试，仿真测试

#### 测试过程

##### 测试过程划分

#### 测试策划

进行测试需求的分析

确定需要测试的内容和特征

明确测试的充分性要求

#### 3-1 需求测试

测试工程师参与需求分析，加深对需求的理解，减少了与开发人员的交互，节省时间

提早设计测试用例

可以获取一些测试数据，为测试用例提供帮助

发现需求不合理的地方，降低测试成本

明确测试覆盖范围

测试需求必须有一个可观察可评测的结果

无法核实的需求不是需求，不测试

明确哪些需求更重要

确保风险承担者尽早地对项目达成共识

对将来的产品有个清晰的认识

测试需求是制定计划的基本依据

设计测试用例的指导

##### 需求验证

**审查需求文档**：

对需求文档及相关模型进行仔细检查

在需求开发期间所做的非正式评审也是有裨益的

**以需求为一句编写测试用例**：

编写用户手册（浅显易懂的），来辅助需求分析过程

**确定合格的标准**：

让用户描述什么样的产品才算满足他们的要求

### 需求规格说明书

## vmware 错误

```log
VMware Workstation unrecoverable error: (mks)
ISBRendererComm: Lost connection to mksSandbox (2878)
A log file is available in "/home/infinity/VMware VMs/Windows XP/vmware.log".  
You can request support.  

To collect data to submit to VMware support, choose "Collect Support Data" from the Help menu.
You can also run the "vm-support" script in the Workstation folder directly.
We will respond on the basis of your support entitlement.
```

Maybe ran out of memory

VRAM or RAM?

是不是前台与后台的问题？

最小化后

## 一个 bash 错误

`usage: count <expected line count>`可能是因为count定义的时候中间加空格了

## 滚动发行

rolling release - Arc Linux
用的是最新的软件！
point release - Ubuntu
使用点发行的系统软件库不会有升级更新，只会有安全更新的推送

Manjaro 把二者结合起来了

## 几种虚拟机磁盘格式

VDI是VirtualBox的基本且独有的格式。目前应该还没有支持这种格式的其他软件。

VMDK是专门为VMWare开发，但其他虚机像Sun xVM，QEMU，VirtualBox，SUSE Studio和.NET DiscUtils也都支持这种格式。 (这种格式应该是最适合题主的，因为您希望在Ubuntu上正常运行虚拟机软件。)

VHD是Microsoft Virtual PC的基本格式。这是在Microsoft产品系中受欢迎的格式。

关于HDD，从这个站点来看，Parallels是Mac OS X产品，可能不太适合您，特别是考虑到VirtualBox仅支持旧版本的HDD格式。

## learn linux

Meta键（Mac键盘是一个四瓣的小花，Windows键盘是Windows键）

readlink

## gitee

轻量级PR

## sth wrong in log

```log
[  152s] [319/491] installing libnsl2-2.0.0-1.oe2203
[  152s] /sbin/ldconfig: /usr/lib64/libnsl.so.2 is not a symbolic link
```

```log
[  212s] [449/491] installing dnf-4.10.0-3.oe2203
[  213s] Failed to preset unit, unit dnf-automatic.timer does not exist.
[  213s] Failed to preset unit, unit dnf-automatic-notifyonly.timer does not exist.
[  213s] Failed to preset unit, unit dnf-automatic-download.timer does not exist.
[  213s] Failed to preset unit, unit dnf-automatic-install.timer does not exist.
```

```log
[  164s] [182/493] installing elfutils-0.185-5.oe2203
[  166s] /usr/lib/systemd/systemd-sysctl: error while loading shared libraries: libkmod.so.2: cannot open shared object file: No such file or directory
```

```log
[  544s] now finalizing build dir...
[  546s] SIOCSIFADDR: Permission denied
[  548s] Warning: spec file parser line 5: can't expand %(...)
```

Maybe there are some problems on `libswtpm_libtpms.la`.

I need to learn `Makefile` and `Spec` again.

> before userbuild

## to see the packing process

## add dnf-automatic to obs

[dnf-automatic – Install Security Updates Automatically in CentOS 8](https://www.tecmint.com/dnf-automatic-install-security-updates-automatically-in-centos-8/)

[12.5.6.3. 启用 DNF AUTOMATIC](https://access.redhat.com/documentation/zh-cn/red_hat_enterprise_linux/8/html/configuring_basic_system_settings/enabling-dnf-automatic_automating-software-updates)

[安装dnf-automatic以在CentOS 8/RHEL 8上启用自动软件更新](https://ywnz.com/linuxaq/6334.html)

For each timer file, a matching unit file must exist, describing the unit to activate when the timer elapses. By default, a service by the same name as the timer (except for the suffix) is activated. Example: a timer file `foo.timer` activates a matching service `foo.service`.

[孤儿进程，僵尸进程](https://www.cnblogs.com/anker/p/3271773.html)

## cmake

`https://www.jianshu.com/p/c2c71d5a09e9`

set(A B C D)
结果是A=B;C;D

`https://zhuanlan.zhihu.com/p/60479441`

find_package(git)
查找并载入一个外部包，**包**是什么？？

奇怪：
依赖里面有很多python3的包
但是整个项目里所有带print函数的.py文件都是python2的

ctrl + p 寻找

pre install
install
diff

core dumped

export k=v
子进程

whereis which type

`file <file>` 查看类型

bookmark

qa! 中的a是什么

elf文件

shebang

题目：在构造数据时，需要将数据对齐，每 4 个单位一组，不对齐就要补全。
输入的数据长度是无符号整数，最终得到的数据长度一定是 4 的倍数。

```c++
unsigned k = n + ((~n + 1) & 0x3);
unsigned l = n + (4 - n % 4) % 4;
unsigned m = n / 4 * 4 + 4 * ((n % 4) && (0x3));
```

都通过了

```log
[13084s] extracting debug info from /home/abuild/rpmbuild/BUILDROOT/mysql5-5.7.37-1.oe1.riscv64/usr/bin/myisamlog  ####TAG
[13085s] Could not find platform independent libraries <prefix>
[13085s] Could not find platform dependent libraries <exec_prefix>
[13085s] Consider setting $PYTHONHOME to <prefix>[:<exec_prefix>]
[13085s] Could not find platform independent libraries <prefix>
[13085s] Could not find platform dependent libraries <exec_prefix>
[13085s] Consider setting $PYTHONHOME to <prefix>[:<exec_prefix>]
[13085s] Fatal Python error: initfsencoding: unable to load the file system codec
[13085s] ModuleNotFoundError: No module named 'encodings'

[13086s] Current thread 0x0000003fd88cc020 (most recent call first):
[13087s] /usr/bin/gdb-add-index: line 106: 655022 Aborted                 (core dumped) $GDB --batch -nx -iex 'set auto-load no' -ex "file $file" -ex "save gdb-index $dwarf5 $dir"
[13087s] gdb-add-index: gdb error generating index for /home/abuild/rpmbuild/BUILDROOT/mysql5-5.7.37-1.oe1.riscv64/usr/bin/lz4_decompress
[13087s] /usr/bin/gdb-add-index: line 106: 655021 Aborted                 (core dumped) $GDB --batch -nx -iex 'set auto-load no' -ex "file $file" -ex "save gdb-index $dwarf5 $dir"
[13087s] gdb-add-index: gdb error generating index for /home/abuild/rpmbuild/BUILDROOT/mysql5-5.7.37-1.oe1.riscv64/usr/bin/my_safe_process
[13087s] /usr/bin/gdb-add-index: line 106: 655044 Aborted                 (core dumped) $GDB --batch -nx -iex 'set auto-load no' -ex "file $file" -ex "save gdb-index $dwarf5 $dir"
[13087s] gdb-add-index: gdb error generating index for /home/abuild/rpmbuild/BUILDROOT/mysql5-5.7.37-1.oe1.riscv64/usr/bin/innochecksum
[13087s] /usr/bin/gdb-add-index: line 106: 655043 Aborted                 (core dumped) $GDB --batch -nx -iex 'set auto-load no' -ex "file $file" -ex "save gdb-index $dwarf5 $dir"
```

/usr/lib/rpm
find-debuginfo.sh
debugedit
gdb-add-index
