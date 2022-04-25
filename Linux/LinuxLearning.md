
# Linux学习

## 待分类

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
