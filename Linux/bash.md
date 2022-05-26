
# bash笔记

## 待归类

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

## Shell 反引号、$() 和 ${} 的区别

### 反引号`` ` ``与`$()`的区别

都起到命令替换（command substitution）的作用，即将其作为子命令包括在命令里，优先执行该子命令

但是用反引号，里面的特殊符号都需要转义，包括嵌套的反引号

### `${}`

用于变量替换

对于

```bash
file="/dir1/dir2/dir3/myfile.txt"
```

#### `${:}`与`${::}`

eg1.

```bash
$ echo ${file:1}
dir1/dir2/dir3/myfile.txt
$ echo ${file: -3} # 注意空格
txt
$ echo ${file:(-3)}
txt
```

eg2.

```bash
$ echo ${file:0:5}
/dir1
$ echo ${file:5:5}
/dir2
```

#### `${/}`与`${//}`

匹配替换

eg.

```bash
$ echo ${file/dir/path}     # 替换第一个 dir 为 path
/path/dir2/dir3/my.file.txt
$ echo ${file//dir/path}    # 替换所有的 dir 为 path
/path/path2/path3/my.file.txt
```

#### `${#}` `${##}` `${%}` `${%%}`

取前缀与后缀

```bash
$ echo ${file#*/}
dir/dir2/dir3/my.file.txt
$ echo ${file##*/}      # 两个符号，贪心算法
my.file.txt
$ echo ${file%/*}
/dir/dir2/dir3
$ echo ${file%%/*}      # 两个符号，贪心算法

```
