
# Linux学习

## 待分类

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

- Blue: Directory
- Green: Executable or recognized data file
- Cyan (Sky Blue): Symbolic link file
- Yellow with black background: Device
- Magenta (Pink): Graphic image file
- Red: Archive file
- Red with black background: Broken link

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
