# 尝试修复iavf

第一次错误

```bash
[root@openEuler-RISCV-rare SPECS]# rpmbuild -ba iavf.spec
Executing(%prep): /bin/sh -e /var/tmp/rpm-tmp.lqOEbV
+ umask 022
+ cd /root/rpmbuild/BUILD
+ cd /root/rpmbuild/BUILD
+ rm -rf iavf-4.0.1
+ /usr/bin/gzip -dc /root/rpmbuild/SOURCES/iavf-4.0.1.tar.gz
+ /usr/bin/tar -xof -
+ STATUS=0
+ '[' 0 -ne 0 ']'
+ cd iavf-4.0.1
+ /usr/bin/chmod -Rf a+rX,u+w,g-w,o-w .
+ /usr/bin/cat /root/rpmbuild/SOURCES/fix-build-error-with-Linux-5.10.patch
+ /usr/bin/patch -p1 -s --fuzz=0 --no-backup-if-mismatch
+ /usr/bin/cat /root/rpmbuild/SOURCES/backport-extend-coalesce-setting-uAPI-with-CQE-mode.patch
+ /usr/bin/patch -p1 -s --fuzz=0 --no-backup-if-mismatch
+ RPM_EC=0
++ jobs -p
+ exit 0
Executing(%build): /bin/sh -e /var/tmp/rpm-tmp.gLPszU
+ umask 022
+ cd /root/rpmbuild/BUILD
+ cd iavf-4.0.1
+ make -C src clean
make: Entering directory '/root/rpmbuild/BUILD/iavf-4.0.1/src'
make[1]: Entering directory '/usr/src/kernels/5.5.19-3.oe1.riscv64'
make[1]: Leaving directory '/usr/src/kernels/5.5.19-3.oe1.riscv64'
make: Leaving directory '/root/rpmbuild/BUILD/iavf-4.0.1/src'
+ make -C src
make: Entering directory '/root/rpmbuild/BUILD/iavf-4.0.1/src'
make[1]: Entering directory '/usr/src/kernels/5.5.19-3.oe1.riscv64'
  CC [M]  /root/rpmbuild/BUILD/iavf-4.0.1/src/iavf_main.o
In file included from ./include/linux/types.h:6,
                 from ./include/linux/list.h:5,
                 from ./include/linux/module.h:12,
                 from /root/rpmbuild/BUILD/iavf-4.0.1/src/iavf.h:7,
                 from /root/rpmbuild/BUILD/iavf-4.0.1/src/iavf_main.c:4:
./include/uapi/linux/types.h:5:10: fatal error: asm/types.h: No such file or directory
    5 | #include <asm/types.h>
      |          ^~~~~~~~~~~~~
compilation terminated.
make[2]: *** [scripts/Makefile.build:266: /root/rpmbuild/BUILD/iavf-4.0.1/src/iavf_main.o] Error 1
make[1]: *** [Makefile:1694: /root/rpmbuild/BUILD/iavf-4.0.1/src] Error 2
make[1]: Leaving directory '/usr/src/kernels/5.5.19-3.oe1.riscv64'
make: *** [Makefile:60: default] Error 2
make: Leaving directory '/root/rpmbuild/BUILD/iavf-4.0.1/src'
error: Bad exit status from /var/tmp/rpm-tmp.gLPszU (%build)


RPM build errors:
    Bad exit status from /var/tmp/rpm-tmp.gLPszU (%build)
```

要做的

错误1：

```bash
./include/uapi/linux/types.h:5:10: fatal error: asm/types.h: No such file or directory
    5 | #include <asm/types.h>
      |          ^~~~~~~~~~~~~
compilation terminated.
```

- 定位究竟是哪个asm/types.h文件

```bash
$ find / -name uapi
/usr/src/kernels/5.5.19-3.oe1.riscv64/include/uapi
/usr/src/kernels/5.5.19-3.oe1.riscv64/include/generated/uapi
```

应该是`/usr/src/kernels/5.5.19-3.oe1.riscv64/include/uapi`目录下的`asm-generic/types.h`，但 log 中显示的是 `asm/types.h`

尝试1：创建软链接

错误2（with 尝试1）：

```bash
+ make -C src
make: Entering directory '/root/rpmbuild/BUILD/iavf-4.0.1/src'
make[1]: Entering directory '/usr/src/kernels/5.5.19-3.oe1.riscv64'
  CC [M]  /root/rpmbuild/BUILD/iavf-4.0.1/src/iavf_main.o
In file included from ./include/linux/kernel.h:8,
                 from ./include/linux/list.h:9,
                 from ./include/linux/module.h:12,
                 from /root/rpmbuild/BUILD/iavf-4.0.1/src/iavf.h:7,
                 from /root/rpmbuild/BUILD/iavf-4.0.1/src/iavf_main.c:4:
./include/linux/linkage.h:8:10: fatal error: asm/linkage.h: No such file or directory
    8 | #include <asm/linkage.h>
      |          ^~~~~~~~~~~~~~~
compilation terminated.
make[2]: *** [scripts/Makefile.build:266: /root/rpmbuild/BUILD/iavf-4.0.1/src/iavf_main.o] Error 1
make[1]: *** [Makefile:1694: /root/rpmbuild/BUILD/iavf-4.0.1/src] Error 2
make[1]: Leaving directory '/usr/src/kernels/5.5.19-3.oe1.riscv64'
make: *** [Makefile:60: default] Error 2
make: Leaving directory '/root/rpmbuild/BUILD/iavf-4.0.1/src'
error: Bad exit status from /var/tmp/rpm-tmp.b42kVo (%build)

```

定位问题：

```bash
$ find / -name linkage.h
/usr/src/kernels/5.5.19-3.oe1.riscv64/include/linux/linkage.h
/usr/src/kernels/5.5.19-3.oe1.riscv64/include/asm-generic/linkage.h
```

尝试2：

继续使用软链接解决

错误3：

```bash
+ make -C src
make: Entering directory '/root/rpmbuild/BUILD/iavf-4.0.1/src'
make[1]: Entering directory '/usr/src/kernels/5.5.19-3.oe1.riscv64'
  CC [M]  /root/rpmbuild/BUILD/iavf-4.0.1/src/iavf_main.o
In file included from ./include/asm/atomic.h:12,
                 from ./include/linux/atomic.h:7,
                 from ./include/asm-generic/bitops/lock.h:5,
                 from ./include/asm/bitops.h:31,
                 from ./include/linux/bitops.h:26,
                 from ./include/linux/kernel.h:12,
                 from ./include/linux/list.h:9,
                 from ./include/linux/module.h:12,
                 from /root/rpmbuild/BUILD/iavf-4.0.1/src/iavf.h:7,
                 from /root/rpmbuild/BUILD/iavf-4.0.1/src/iavf_main.c:4:
./include/asm/cmpxchg.h:11:2: error: #error "Cannot use generic cmpxchg on SMP"
   11 | #error "Cannot use generic cmpxchg on SMP"
      |  ^~~~~
In file included from ./include/linux/atomic.h:74,
                 from ./include/asm-generic/bitops/lock.h:5,
                 from ./include/asm/bitops.h:31,
                 from ./include/linux/bitops.h:26,
                 from ./include/linux/kernel.h:12,
                 from ./include/linux/list.h:9,
                 from ./include/linux/module.h:12,
                 from /root/rpmbuild/BUILD/iavf-4.0.1/src/iavf.h:7,
                 from /root/rpmbuild/BUILD/iavf-4.0.1/src/iavf_main.c:4:
./include/linux/atomic-fallback.h: In function 'atomic64_inc':
./include/linux/atomic-fallback.h:1378:2: error: implicit declaration of function 'atomic64_add'; did you mean 'atomic_add'? -Werror=implicit-function-declaration]
 1378 |  atomic64_add(1, v);
      |  ^~~~~~~~~~~~
      |  atomic_add
./include/linux/atomic-fallback.h: In function 'atomic64_inc_return':
./include/linux/atomic-fallback.h:1394:9: error: implicit declaration of function 'atomic64_add_return'; did you mean 'atomic_add_return'? [-Werror=implicit-function-declaration]
 1394 |  return atomic64_add_return(1, v);
      |         ^~~~~~~~~~~~~~~~~~~
      |         atomic_add_return
./include/linux/atomic-fallback.h: In function 'atomic64_fetch_inc':
./include/linux/atomic-fallback.h:1475:9: error: implicit declaration of function 'atomic64_fetch_add'; did you mean 'atomic_fetch_add'? [-Werror=implicit-function-declaration]
 1475 |  return atomic64_fetch_add(1, v);
      |         ^~~~~~~~~~~~~~~~~~
      |         atomic_fetch_add
./include/linux/atomic-fallback.h: In function 'atomic64_dec':
./include/linux/atomic-fallback.h:1549:2: error: implicit declaration of function 'atomic64_sub'; did you mean 'atomic_sub'? -Werror=implicit-function-declaration]
 1549 |  atomic64_sub(1, v);
      |  ^~~~~~~~~~~~
      |  atomic_sub
./include/linux/atomic-fallback.h: In function 'atomic64_dec_return':
./include/linux/atomic-fallback.h:1565:9: error: implicit declaration of function 'atomic64_sub_return'; did you mean 'atomic_sub_return'? [-Werror=implicit-function-declaration]
 1565 |  return atomic64_sub_return(1, v);
      |         ^~~~~~~~~~~~~~~~~~~
      |         atomic_sub_return
./include/linux/atomic-fallback.h: In function 'atomic64_fetch_dec':
./include/linux/atomic-fallback.h:1646:9: error: implicit declaration of function 'atomic64_fetch_sub'; did you mean 'atomic_fetch_sub'? [-Werror=implicit-function-declaration]
 1646 |  return atomic64_fetch_sub(1, v);
      |         ^~~~~~~~~~~~~~~~~~
      |         atomic_fetch_sub
./include/linux/atomic-fallback.h: In function 'atomic64_andnot':
./include/linux/atomic-fallback.h:1762:2: error: implicit declaration of function 'atomic64_and'; did you mean 'atomic64_inc'? [-Werror=implicit-function-declaration]
 1762 |  atomic64_and(~i, v);
      |  ^~~~~~~~~~~~
      |  atomic64_inc
./include/linux/atomic-fallback.h: In function 'atomic64_fetch_andnot':
./include/linux/atomic-fallback.h:1778:9: error: implicit declaration of function 'atomic64_fetch_and'; did you mean 'atomic64_fetch_inc'? [-Werror=implicit-function-declaration]
 1778 |  return atomic64_fetch_and(~i, v);
      |         ^~~~~~~~~~~~~~~~~~
      |         atomic64_fetch_inc
./include/linux/atomic-fallback.h: In function 'atomic64_try_cmpxchg':
./include/linux/atomic-fallback.h:2028:6: error: implicit declaration of function 'atomic64_cmpxchg'; did you mean 'atomic_cmpxchg'? [-Werror=implicit-function-declaration]
 2028 |  r = atomic64_cmpxchg(v, o, new);
      |      ^~~~~~~~~~~~~~~~
      |      atomic_cmpxchg
./include/linux/atomic-fallback.h: In function 'atomic64_fetch_add_unless':
./include/linux/atomic-fallback.h:2196:10: error: implicit declaration of function 'atomic64_read'; did you mean 'atomic_read'? [-Werror=implicit-function-declaration]
 2196 |  s64 c = atomic64_read(v);
      |          ^~~~~~~~~~~~~
      |          atomic_read
In file included from ./include/linux/atomic.h:76,
                 from ./include/asm-generic/bitops/lock.h:5,
                 from ./include/asm/bitops.h:31,
                 from ./include/linux/bitops.h:26,
                 from ./include/linux/kernel.h:12,
                 from ./include/linux/list.h:9,
                 from ./include/linux/module.h:12,
                 from /root/rpmbuild/BUILD/iavf-4.0.1/src/iavf.h:7,
                 from /root/rpmbuild/BUILD/iavf-4.0.1/src/iavf_main.c:4:
./include/asm-generic/atomic-long.h: In function 'atomic_long_set':
./include/asm-generic/atomic-long.h:40:2: error: implicit declaration of function 'atomic64_set'; did you mean 'atomic64_dec'? [-Werror=implicit-function-declaration]
   40 |  atomic64_set(v, i);
      |  ^~~~~~~~~~~~
      |  atomic64_dec
./include/asm-generic/atomic-long.h: In function 'atomic_long_or':
./include/asm-generic/atomic-long.h:328:2: error: implicit declaration of function 'atomic64_or'; did you mean 'atomic_or'? [-Werror=implicit-function-declaration]
  328 |  atomic64_or(i, v);
      |  ^~~~~~~~~~~
      |  atomic_or
./include/asm-generic/atomic-long.h: In function 'atomic_long_fetch_or':
./include/asm-generic/atomic-long.h:334:9: error: implicit declaration of function 'atomic64_fetch_or'; did you mean 'atomic_fetch_or'? [-Werror=implicit-function-declaration]
  334 |  return atomic64_fetch_or(i, v);
      |         ^~~~~~~~~~~~~~~~~
      |         atomic_fetch_or
./include/asm-generic/atomic-long.h: In function 'atomic_long_xor':
./include/asm-generic/atomic-long.h:358:2: error: implicit declaration of function 'atomic64_xor'; did you mean 'atomic_xor'? [-Werror=implicit-function-declaration]
  358 |  atomic64_xor(i, v);
      |  ^~~~~~~~~~~~
      |  atomic_xor
./include/asm-generic/atomic-long.h: In function 'atomic_long_fetch_xor':
./include/asm-generic/atomic-long.h:364:9: error: implicit declaration of function 'atomic64_fetch_xor'; did you mean 'atomic_fetch_xor'? [-Werror=implicit-function-declaration]
  364 |  return atomic64_fetch_xor(i, v);
      |         ^~~~~~~~~~~~~~~~~~
      |         atomic_fetch_xor
./include/asm-generic/atomic-long.h: In function 'atomic_long_xchg':
./include/asm-generic/atomic-long.h:388:9: error: implicit declaration of function 'atomic64_xchg'; did you mean 'atomic_xchg'? [-Werror=implicit-function-declaration]
  388 |  return atomic64_xchg(v, i);
      |         ^~~~~~~~~~~~~
      |         atomic_xchg
In file included from ./include/asm/bitops.h:35,
                 from ./include/linux/bitops.h:26,
                 from ./include/linux/kernel.h:12,
                 from ./include/linux/list.h:9,
                 from ./include/linux/module.h:12,
                 from /root/rpmbuild/BUILD/iavf-4.0.1/src/iavf.h:7,
                 from /root/rpmbuild/BUILD/iavf-4.0.1/src/iavf_main.c:4:
./include/asm-generic/bitops/le.h: At top level:
./include/asm-generic/bitops/le.h:6:10: fatal error: asm/byteorder.h: No such file or directory
    6 | #include <asm/byteorder.h>
      |          ^~~~~~~~~~~~~~~~~
cc1: some warnings being treated as errors
compilation terminated.
make[2]: *** [scripts/Makefile.build:266: /root/rpmbuild/BUILD/iavf-4.0.1/src/iavf_main.o] Error 1
make[1]: *** [Makefile:1694: /root/rpmbuild/BUILD/iavf-4.0.1/src] Error 2
make[1]: Leaving directory '/usr/src/kernels/5.5.19-3.oe1.riscv64'
make: *** [Makefile:60: default] Error 2
make: Leaving directory '/root/rpmbuild/BUILD/iavf-4.0.1/src'
error: Bad exit status from /var/tmp/rpm-tmp.GpRUa6 (%build)


RPM build errors:
    Bad exit status from /var/tmp/rpm-tmp.GpRUa6 (%build)
```

暂时停止修复
