
# 拓展QEMU虚拟机中硬盘容量

> 建立日期：2022-04-29

## 问题

宿主机：Ubuntu 22.04 LTS
虚拟机：openEuler 20.03 LTS

最近在用QEMU仿真RISC-V64机器，在一次编译的时候发现存储空间不足

```bash
[root@openEuler-RISCV-rare dev]# df -h
Filesystem      Size  Used Avail Use% Mounted on
/dev/root       9.8G  9.1G  199M  98% /
devtmpfs        3.9G     0  3.9G   0% /dev
tmpfs           3.9G     0  3.9G   0% /dev/shm
tmpfs           3.9G  1.3M  3.9G   1% /run
tmpfs           3.9G     0  3.9G   0% /sys/fs/cgroup
tmpfs           3.9G     0  3.9G   0% /tmp
tmpfs           798M     0  798M   0% /run/user/0
```

于是想着拓展根目录分区的容量

## 问题分析

需要在虚拟机**之外**扩容**磁盘**，进入虚拟机的系统后再扩容**分区**

## 问题解决

### 调整虚拟机磁盘容量

```bash
qemu-img resize vmdisk.img +10G
```

`vmdisk.img`替换为自己用的虚拟机镜像，我使用的是`.qcow2`类型的文件，此命令依然可用

### 拓展原有分区

可能需要安装的包：`lvm2`

参考1:[fdisk、parted无损调整普通分区大小 - 黄三每丘八 - 51CTO](https://blog.51cto.com/u_13497208/2044196)
参考2:[Changing a partition with fdisk shows a warning like "partition#x contains ext4-signature" - stack overflow](https://stackoverflow.com/questions/53743677/changing-a-partition-with-fdisk-shows-a-warning-like-partitionx-contains-ext4)
参考3:[How to increase available filesystem size in /dev/root in Linux Centos 7.7 (AltArch)? - stack overflow](https://stackoverflow.com/questions/61425988/how-to-increase-available-filesystem-size-in-dev-root-in-linux-centos-7-7-alta)

查看分区情况

```bash
[root@openEuler-RISCV-rare dev]# fdisk -l
Disk /dev/vda: 50 GiB, 53687091200 bytes, 104857600 sectors
Units: sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes
Disklabel type: dos
Disk identifier: 0xcd5292f1

Device     Boot Start      End  Sectors Size Id Type
/dev/vda1        2048 20971519 20969472  10G 83 Linux
```

拓展分区

```bash
# 省略了部分输出内容
[root@openEuler-RISCV-rare dev] # fdisk /dev/vda
Command (m for help): d # 先删除要扩展的分区，这里是根目录/分区
Partition number (1-4):1
Command (m for help): p

Device     Boot Start      End  Sectors Size Id Type
/dev/vda1        2048 20971519 20969472  10G 83 Linux

Command (m for help): n # 再把删除的分区重新添加
Command action
e extended
P primary partition (1-4)
P
Partition number (1-4):2
First cylinder (26-2048,default 2048):2048 这里一定要跟原先的对应
Last cylinder ,+cylinders or +size{K,M,G} (26-104857599,default 104857599):1048599
# 原先是到20971519，这里直接到最后一个扇区
Command (m for help): w
```

中间会有关于`signature`的提示，具体请查看上方的参考链接2

其实比起上面这一大串，有更为简单的处理方式

```bash
growpart /dev/vda 1
```

拓展后，`/dev/vda1`扩容成功，但是`/dev/root`的大小仍然不变，这时需要使用如下命令

```bash
resize2fs /dev/vda1 
```

需要这个命令的原因及这个命令做了什么，具体并不清楚，先**MARK**一下，日后如果有更深的理解了再来处理

/dev/root是什么？**MARK**

lvm2 提供 lvextended lvresize 等命令，探索该命令**MARK**
