
# 折腾QEMU

[QEMU 网络配置](https://tomwei7.com/2021/10/09/qemu-network-config.html)

[Documentation/Networking](https://wiki.qemu.org/Documentation/Networking)

reboot 会卡住，暂时不要用这种命令

## QEMU被系统杀掉的问题

QEMU经常莫名其妙死掉

```log
systemd-journald[140]: File /var/log/journal/5752e0903cf6471ba6b18338c39992db/user-1000.journal corrupted or uncleanly shut down, renaming and replacing.
./r.sh: line 12: 21964 Killed                  qemu-system-riscv64 -nographic -machine virt -smp 4 -m 4G -kernel fw_payload_oe_docker.elf -drive file=openEuler-preview.riscv64.qcow2,format=qcow2,id=hd0 -object rng-random,filename=/dev/urandom,id=rng0 -device virtio-rng-device,rng=rng0 -device virtio-blk-device,drive=hd0 -device virtio-net-device,netdev=usernet -netdev user,id=usernet,hostfwd=tcp::10286-:22,hostfwd=tcp::10022-:10022,hostfwd=tcp::10023-:10023,hostfwd=tcp::10024-:10024,hostfwd=tcp::10025-:10025,hostfwd=tcp::10026-:10026,hostfwd=tcp::10027-:10027,hostfwd=tcp::10028-:10028,hostfwd=tcp::10029-:10029,hostfwd=tcp::10030-:10030 -append 'root=/dev/vda1 rw console=ttyS0 systemd.default_timeout_start_sec=600 selinux=0 highres=off mem=4096M earlycon' -bios none
```

```log
./r.sh: line 12:  2272 Killed qemu-system-riscv64 -nographic -machine virt -smp 4 -m 4G -kernel fw_payload_oe_docker.elf -drive file=openEuler-preview.riscv64.qcow2,format=qcow2,id=hd0 -object rng-random,filename=/dev/urandom,id=rng0 -device virtio-rng-device,rng=rng0 -device virtio-blk-device,drive=hd0 -device virtio-net-device,netdev=usernet -netdev user,id=usernet,hostfwd=tcp::10286-:22,hostfwd=tcp::10022-:10022,hostfwd=tcp::10023-:10023,hostfwd=tcp::10024-:10024,hostfwd=tcp::10025-:10025,hostfwd=tcp::10026-:10026,hostfwd=tcp::10027-:10027,hostfwd=tcp::10028-:10028,hostfwd=tcp::10029-:10029,hostfwd=tcp::10030-:10030 -append 'root=/dev/vda1 rw console=ttyS0 systemd.default_timeout_start_sec=600 selinux=0 highres=off mem=4096M earlycon' -bios none
```

查看 `/var/log/kern.log` ，发现是 oom 杀掉了 QEMU

```log
root@ubuntu:/var/log# cat kern.log | grep 2272
Apr 28 01:20:50 ubuntu kernel: [10765.786689] [   2272]  1000  2272  1906045   758812  9482240   100643             0 qemu-system-ris
Apr 28 01:20:50 ubuntu kernel: [10765.786695] oom-kill:constraint=CONSTRAINT_NONE,nodemask=(null),cpuset=/,mems_allowed=0,global_oom,task_memcg=/,task=qemu-system-ris,pid=2272,uid=1000
Apr 28 01:20:50 ubuntu kernel: [10765.786724] Out of memory: Killed process 2272 (qemu-system-ris) total-vm:7624180kB, anon-rss:3035248kB, file-rss:0kB, shmem-rss:0kB, UID:1000 pgtables:9260kB oom_score_adj:0
Apr 28 01:20:50 ubuntu kernel: [10765.874126] oom_reaper: reaped process 2272 (qemu-system-ris), now anon-rss:0kB, file-rss:0kB, shmem-rss:0kB
```

转移到新电脑上了，多分配点内存
