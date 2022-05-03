
# Linux学习

## 各项命令

### journalctl 命令

直接跳到最后一页`-e`

**MARK**一下

### watch 命令

时间间隔`-n [time]`

### man 命令

在 man 里搜索，直接打`/`后接需要的内容，看情况需要转义

### ping 命令

ping在`iputils`里

### nice 命令

nice 被用来调整进程优先级，默认0；最小值-20，优先级最大；最大值19，优先级最小（也就是说补码被用在这儿了吗，也不对啊……）

CPU密集型程序使用nice命令提高优先级会比较不错

参考：[Linux nice及renice命令使用 - persistent_db - CSDN](https://blog.csdn.net/XD_hebuters/article/details/79619213)

### find 命令

find查找的是精确的名字，如果查找内容是文件名字的一部分，用*等

### ls 命令

`ls -l`可以简写为`ll`，`-h`人类可阅读模式，`-a`显示隐藏文件

### tree 命令

查看文件树，`-a`显示隐藏文件

## 常用目录

### 各个`bin`的区别

出处：[Linux文件系统中/bin、/sbin、/usr/bin、/usr/sbin、/usr/local/bin、/usr/local/sbin文件夹的区别是什么？ - netcan - 知乎](https://www.zhihu.com/question/21265424/answer/94120935)

`/bin`      This  directory contains executable programs which are needed in single user mode and to bring the system up or repair it.
`/sbin`  Like  /bin, this directory holds commands needed to boot the system, but which are usually not executed by normal users.
`/usr/bin`  This  is  the  primary directory for executable programs.  Most programs executed by normal users which are not needed for booting or for repairing the system and which are not installed  locally  should  be placed in this directory.
`/usr/sbin` This directory contains program binaries for system administration which are not essential for the boot process, for mounting /usr, or for system repair.
`/usr/local/bin` Binaries for programs local to the site.
`/usr/local/sbin` Locally installed programs for system administration.

翻译：

`/bin` 包含了需要在单用户模式下运行的程序，例如

`/sbin` 类似于`/bin`，这个文件夹包含启动系统的命令，但是通常不会让普通用户运行

`/usr/bin` 存放可执行程序的主要文件夹。大多数不会用来启动或修复系统的，并且不会单独给某个用户安装的程序会放在这个文件夹

`/usr/sbin` 这个文件夹包括了与启动进程、修复系统没什么关系的，仅能由管理员使用的程序

`/usr/local/bin` 当前用户使用的二进制程序

`/usr/local/sbin` 当前管理员使用的程序

### `/usr`目录

`bin` 用户常用命令存放目录

`include` 程序头文件存放目录

`lib` `lib64` 库文件存放目录

`local` 用户自己安装的程序与编译完成的程序存放目录

`share` 帮助文档与共享文档存放路径

`src` 源码存放路径

### `/usr/share`目录

`doc`文档目录，软件的杂项文档说明

`man`帮助文档目录

### `/etc`目录

`hosts` host table，主机表

`resolv.conf` DNS配置文件

`services` 端口、网络服务配置文件

## 待分类

### 网卡重启

centos7的网卡重启方法：systemctl restart network

### 环境变量

修改环境变量之后要`source .`一下

`echo $PATH`或者`env`测试当前环境变量

### 各种命令的风格

GNU风格，\-字母，\-\-单词
Unix风格，\-字母，\-单词
BSD风格，没有\-

### Linux 自启动程序的设置

可以修改`/etc/rc.local`文件，也可以把bash文件放到`/etc/rc.d`中

记得要`chmod +x [file]`赋予执行权限，包括`/etc/rc.local`文件

### 分区建议

BIOS

|目录|建议大小|格式|描述|
|---|---|---|---|
|/|10G-20G|ext4|根目录|
|swap|<2048M|swap|交换空间|
|/boot|200M左右|ext4|Linux的内核及引导系统程序所需要的文件，比如 vmlinuz initrd.img文件都位于这个目录中。在一般情况下，GRUB或LILO系统引导管理器也位于这个目录；启动撞在文件存放位置，如kernels，initrd，grub。|
|/tmp|5G左右|ext4|系统的临时文件，一般系统重启不会被保存。（建立服务器需要？）|
|/home|尽量大些|ext4|用户工作目录；个人配置文件，如个人环境变量等；所有账号分配一个工作目录。|

EFI

|目录|建议大小|格式|描述|
|---|---|---|---|
|/boot/efi|>300M|fat32|efi分区，在有些系统上不能太小|
|swap|见备注|swap|根据内存大小决定，若内存1G以内，建议用两倍内存容量；否则，建议用与内存相等的容量|
|/|剩下的都是|懒人分区法，只要前两个没问题就行|

记得要在 vmware 的设置中开启 uefi 启动

### Linux 三种包管理方式

rpm、deb、pacman

deb：debian，ubuntu
rpm：redhat，centOS, openSUSE
pacman: archLinux

rpm：Red Hat Package Manage
RPM package manager

### 关机与重启

参考链接：

1. [ACPI与UEFI - 知乎 - 老狼](https://zhuanlan.zhihu.com/p/25893464)
2. [Linux 下 halt, poweroff, shutdown 有什么区别？ - 知乎](https://www.zhihu.com/question/22060662)
3. [Linux 关机与重启命令 - 菜鸟教程](https://www.runoob.com/w3cnote/linux-shutdown-reboot.html)

#### 直接关机

`shutdown`实际上是调用`init 0`，`init 0`会做一些 cleanup 工作然后调用`halt`或`poweroff`，所以 `shutdown`需要**管理员**权限方能使用

```bash
shutdown -h now
```

`halt`会关闭OS，在不支持 ACPI 的机器上不会关闭电源

```bash
halt
```

`poweroff`在`halt`的基础上关闭电源，与`halt -p`的作用类似

```bash
poweroff
```

还有一种关机方式

```bash
systemctl poweroff
```

#### 定时关机

10 **分钟**后自动关机

```bash
shutdown -h 10
```

100 **秒**后自动关机

```bash
shutdown -h -t 100
```

#### 重启

使用`reboot`命令，或者使用`shutdown -r now`命令

### grep 多个关键字“与”和“或”

#### 或操作

```bash
grep -E 'abc|123' filename
```

#### 与操作

```bash
grep 'abc' filename | grep '123' filename
```

### 普通用户使用sudo命令借用root权限

1. 在终端以超级管理员身份登录

2. 确保安装了 sudo ，在 root 下执行

    ```bash
    dnf -y install sudo
    ```

3. 给 /etc/sudoer 文件附加可写权限

    ```bash
    chmod 600 /etc/sudoers
    ```

4. 编辑 /etc/sudoer 文件

    ```bash
    vim /etc/sudoers
    #在 root ALL=(ALL) ALL 下面添加一行
    用户名 ALL=(ALL)  ALL
    ```

5. 收回 /etc/sudoer 的可写权限

    ```bash
    chmod 600 etc/sudoers
    ```

> 注：如果在 vim 退出时使用 ! ，那么可以不需要给这个文件附加可写权限

### glob模式

原文链接：[glob 模式匹配简明教程](https://github.com/whinc/whinc.github.io/issues/18)

在编程中匹配字符最常见的工具是正则表达式，此外还有一种 glob 模式经常用于匹配文件路径，glob 模式在某些方面与正则表达式功能相同，但是他们各自有着不同的语法和约定，今天就一起学习下 glob 模式。

#### 介绍

根据[维基百科](<https://en.wikipedia.org/wiki/Glob_(programming)>)的介绍，在计算机编程中 glob 模式表示带有通配符的路径名，例如在 bash 中查看文件列表：

\$ls src/\*.js
src/a.js src/b.js

它最初是贝尔实验室 Unix 系统上的一个名叫 glob 的命令（glob 是 global 的缩写），用于展开命令行中的通配符。后来系统提供了该功能的 C 语言库函数`glob()`，知名的 shell 解释器就使用了该接口，shell 脚本和命令行中使用的 glob 模式匹配功能便源自于此。

#### 基础语法

相比正则表达式大量的元字符，glob 模式中元字符极少，所以掌握起来也很快。glob 默认不匹配隐藏文件（以点`.`开头的文件或目录），下面是 glob 的语法：

| 通配符 | 描述 | 示例 | 匹配 | 不匹配 |
| --- | --- | --- | --- | --- |
| `*` | 匹配0个或多个字符，包含空串 | `Law*` | `Law`, `Laws`和`Lawer` | `La`, `aw` |
| `?` | 匹配1个字符 | `?at` | `cat`, `bat` | `at` |
| `[abc]` | 匹配括号内字符集合中的单个字符 | `[cb]at` | `cat`, `bat` | `at`, `bcat` |
| `[a-z]` | 匹配括号内字符范围中的单个字符 | `[a-z]at` | `aat`, `bat`, `zat` | `at`, `bcat`, `Bat` |
| `[^abc]`或`[!abc]` | 匹配括号内字符集合中的单个字符 | `[cb]at` | `cat`, `bat` | `at`, `bcat` |
| `[^a-z]`或`[!a-z]` | 匹配括号内字符范围中的单个字符 | `[a-z]at` | `aat`, `bat`, `zat` | `at`, `bcat`, `Bat` |

> 在 bash 命令行中`[!abc]`需要转义成`[\!abc]`

#### 扩展语法

除了基础语法外，bash 还支持 glob 的一些扩展语法，主要包含三种：

* Brace Expansion
* globstar
* extglob

三种扩展语法的定义和描述如下：

| 通配符 | 描述 | 示例 | 匹配 | 不匹配 |
| --- | --- | --- | --- | --- |
| `{x, y, ...}` | Brace Expansion，展开花括号内容，支持展开嵌套括号 | `a.{png,jp{,e}g}` | `a.png`, `a.jpg`, `a.jpeg` |  |
| `**` | globstar，匹配所有文件和任意层目录，如果`**`后面紧接着`/`则只匹配目录，不含隐藏目录 | `src/**` | `src/a.js`, `src/b/a.js`, `src/b/` | `src/.hide/a.js` |
| `?(pattern-list)` | 匹配0次或1次给定的模式 | `a.?(txt|bin)` | `a.`, `a.txt`, `a.bin` | `a` |
| `*(pattern-list)` | 匹配0次或多次给定的模式 | `a.*(txt|bin)` | `a.`, `a.txt`, `a.bin`, `a.txtbin` | `a` |
| `+(pattern-list)` | 匹配1次或多次给定的模式 | `a.+(txt|bin)` | `a.txt`, `a.bin`, `a.txtbin` | `a.`, `a` |
| `@(pattern-list)` | 匹配给定的模式 | `a.@(txt|bin)` | `a.txt`, `a.bin` | `a.`, `a.txtbin` |
| `!(pattern-list)` | 匹配非给定的模式 | `a.!(txt|bin)` | `a.`, `a.txtbin` | `a.txt`, `a.bin` |

> pattern-list 是一组以`|`作为分隔符的模式集合，例如`abc|a?c|ac*`

#### 与 regexp 的差异

glob 模式主要用于匹配文件路径，当然也可以用于匹配字符串，不过在匹配字符串的能力上比 regexp 要弱很多。由于 glob 模式和 regexp 存在相同的元字符，但是含义却不同，容易导致混淆，为了避免混淆，下面将 glob 模式转换成对应的 regexp 表示，以便区分他们的异同点。

| glob | regexp | 精确的 regexp |
| --- | --- | --- |
| `*` | `.*` | `^(?!\.)[^\/]*?$` |
| `?` | `.` | `^(?!\.)[^\/]$` |
| `[a-z]` | `[a-z]` | `^[a-z]$` |

> glob 匹配的是整个字符串，而 regexp 默认匹配的是子串，regexp 如果要匹配整个字符串需显式指定`^`和`$`。正则表达式中的`(?!\.)`，其表示不匹配隐藏文件

### 查看本机IP

1. 下载net-tools

    ```bash
    sudo apt-get install net-tools
    ```

2. 输入命令`ifconfig`

## 远程访问

### 开启telnet服务

注意：**本部分需要进一步验证**，待验证[链接](https://blog.csdn.net/weixin_40449300/article/details/86619227)

1. 在Ubuntu端安装ssh服务，见《开启SSH服务》一节
2. 在ubuntu端安装vsftpd

    ```bash
    infinity@ubuntu:~$ sudo apt-get install openssh-server  #安装
    infinity@ubuntu:~$ ps -e | grep ssh    #查看ssh服务，如果只有ssh-agent表示还没启动，需要下面这步
    infinity@ubuntu:~$ /etc/init.d/ssh start   #启动服务
    ```

3. 在ubuntu端安装openbsd-inetd与telnetd

    ```bash
    infinity@ubuntu:~$ sudo apt-get install openbsd-inetd
    infinity@ubuntu:~$ sudo apt-get install telnetd
    infinity@ubuntu:~$ sudo /etc/init.d/openbsd-inetd restart   #重启openbsd-inetd
    infinity@ubuntu:~$ netstat -a | grep telnet    #查看telnet运行状态
    ```

### 开启SSH服务

```bash
infinity@ubuntu:~$ sudo apt-get install openssh-server  #安装
infinity@ubuntu:~$ ps -e | grep ssh    #查看ssh服务，如果只有ssh-agent表示还没启动，需要下面这步
infinity@ubuntu:~$ /etc/init.d/ssh start   #启动服务
```

## Bash的一些问题

### ls中不同颜色

[出处](https://askubuntu.com/questions/17299/what-do-the-different-colors-mean-in-ls)

* Blue: Directory
* Green: Executable or recognized data file
* Cyan (Sky Blue): Symbolic link file
* Yellow with black background: Device
* Magenta (Pink): Graphic image file
* Red: Archive file
* Red with black background: Broken link

### apt-get

`-y`可以在需要确认场景中自动回复yes

### 复制和粘贴文字

`ctrl`+`shift`+`c`复制
`ctrl`+`shitt`+`v`粘贴

如果必须要使用`ctrl`+`c`和`ctrl`+`v`

```bash
infinity@ubuntu:~$ gconftool-2 -t str -s /apps/gnome-terminal/keybindings/copy "c"
infinity@ubuntu:~$ gconftool-2 -t str -s /apps/gnome-terminal/keybindings/paste "v"
```
