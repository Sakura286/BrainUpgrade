
# some temp memo

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
