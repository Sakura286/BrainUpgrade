# 工具软件的用法

## VMWare

### 从 VMWare 里的 Linux 里复制文件到主机上

#### 方法一： FileZilla

使用 sftp 方式连接，适合复制小文件

#### 方法二：共享文件夹

虚拟机设置 - 选项 - 共享文件夹 - 添加

在虚拟机里这样使用：

```shell
sudo vmhgfs-fuse .host:/<sourcedir> <targetdir>
```

其中，`<sourcedir>`为在虚拟机设置里设置的名称（不是目录），`<targetdir>`为 Linux 的指定目录

参考：[VMware 如何映射宿主机Windows 的目录到 虚拟机Linux？ - one312的博客](https://blog.csdn.net/one312/article/details/104604013)

### 关于虚拟机克隆

1. 有快照的不能直接克隆
2. 克隆快照需要该快照处于关机或挂起状态

## vim

### 替换

```plain
:<range>s/<pattern>/<string>/<flags>
```

`<range>`为空时，仅匹配光标所在行，为`%`时，匹配所有行
`<flags>`为空时，仅替换第一个匹配，为`g`是，替换所有匹配

`%`和`g`一起使用时，全文替换

## Tabby

A terminal emulator which is very beautiful.

## CLion

多光标的使用快捷键是 `alt` + `shift` ;

如果调试莫名其妙出bug，可以去`CMakeLists.txt`里去看看有没有多余的文件

不包含`main()`的`.c`文件里如有需要也要好好引用`.h`头文件

## VSCode

一个比较不错的针对汇编语言高亮的插件ASM Code Lens

### Markdown

#### 推荐插件

Markdown的[推荐插件](https://zhuanlan.zhihu.com/p/56943330)：

- Markdown All in One
- Markdown Preview Github Styling

#### 在Markdown中突出显示bash代码

示例：

```bash
root@ubuntu:~$ sudo apt-get install openssh-server  #安装
root@ubuntu:~$ ps -e | grep ssh    #查看ssh服务，如果只有ssh-agent表示还没启动，需要下面这步
root@ubuntu:~$ /etc/init.d/ssh start   #启动服务
```

根据VSCode的[源码](https://github.com/Microsoft/vscode/commit/10927a864df60789a1ef7be382db856e867b58ab)，可用`bash`、`sh`、`zsh`等参数

#### markdownlint plugin for VSCode

问题：[MD046/code-block-style: Code block style [Expected: indented; Actual: fenced]](https://stackoverflow.com/questions/67300416/md046-code-block-style-code-block-style-expected-indented-actual-fenced)

官方描述：[MD046 - Code block style](https://github.com/DavidAnson/markdownlint/blob/v0.25.1/doc/Rules.md#md046)

MD046 规则有四条：

- consistend（持续)，默认为此选项。文章必须在 fenced 与 indented 风格里选择一种，并保持在整篇文章内风格不变，否则报错。
- fenced(围住)，即用\`\`\`的方式围住代码。若启用，所有 indented 代码会报错。
- indented(缩进)，即每一行代码前都有缩进。若启用，所有 fenced 代码会报错。
- false。fenced 与 indented 类型随便用

#### 导出PDF

安装`princexml`后并把`<prince>/engine/bin`加到环境变量中

## Xshell

### Xshell颜色

蓝色表示目录；绿色表示可执行文件；红色表示压缩文件；浅蓝色表示链接文件；白色表示其他文件；黄色是设备文件
