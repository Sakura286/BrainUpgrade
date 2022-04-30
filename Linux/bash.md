
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
