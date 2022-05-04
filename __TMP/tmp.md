
# 碎东西

临时记一些笔记

## cmake

https://www.jianshu.com/p/c2c71d5a09e9

set(A B C D)
结果是A=B;C;D

https://zhuanlan.zhihu.com/p/60479441

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

/usr/lib/rpm
find-debuginfo.sh
debugedit
gdb-add-index
