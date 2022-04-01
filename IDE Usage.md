# IDE的一些用途

## CLion

多光标的使用快捷键是 `alt` + `shift` ;

如果调试莫名其妙出bug，可以去`CMakeLists.txt`里去看看有没有多余的文件

不包含`main()`的`.c`文件里如有需要也要好好引用`.h`头文件

## VSCode

一个比较不错的针对汇编语言高亮的插件ASM Code Lens


### Markdown

Markdown的[推荐插件](https://zhuanlan.zhihu.com/p/56943330)：

- Markdown All in One
- Markdown Preview Github Styling

在Markdown中突出显示bash代码

示例：

```bash
root@ubuntu:~$ sudo apt-get install openssh-server  #安装
root@ubuntu:~$ ps -e | grep ssh    #查看ssh服务，如果只有ssh-agent表示还没启动，需要下面这步
root@ubuntu:~$ /etc/init.d/ssh start   #启动服务
```

根据VSCode的[源码](https://github.com/Microsoft/vscode/commit/10927a864df60789a1ef7be382db856e867b58ab)，可用`bash`、`sh`、`zsh`等参数

