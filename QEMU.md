# QEMU

## 如何流畅运行一个GUI界面

我也不知道 **MARK**,[Invocation — QEMU documentation](https://www.qemu.org/docs/master/system/invocation.html#hxtool-3)

暂时知道的是，分别有`-display` `-vga` `-device`三个

其中 `-display` 可以用 `sdl` `gtk` `dbus` `egl-headless` 等，现在能用的只有`gtk`和`sdl`

`-vga`可以用`std` `qxl` `virtio`等，现在能用的只有`std`

`-device` 使用`VGA`，`virtio-vga-gl`不能用

附1：openEuler 启动 xfce 的脚本

```shell
qemu-system-riscv64 \
  -nographic -machine virt \
  -smp "$vcpu" -m "$memory"G \
  -vnc :0 \
  -display egl-headless,rendernode=/dev/dri/renderD128 \
  -audiodev pa,id=snd0 \
  -kernel "$fw" \
  -bios none \
  -drive file="$drive",format=raw,id=hd0 \
  -object rng-random,filename=/dev/urandom,id=rng0 \
  -device virtio-vga-gl \
  -device virtio-rng-device,rng=rng0 \
  -device virtio-blk-device,drive=hd0 \
  -device virtio-net-device,netdev=usernet \
  -netdev user,id=usernet,hostfwd=tcp::"$ssh_port"-:22 \
  -device qemu-xhci -usb -device usb-kbd -device usb-tablet -device usb-audio,audiodev=snd0 \
  -append 'root=/dev/vda1 rw console=ttyS0 swiotlb=1 loglevel=3 systemd.default_timeout_start_sec=600 selinux=0 highres=off mem="$memory_append"M earlycon' "
```

附2：现在的 Debian 启动脚本（VMWare）

```shell
#!/bin/bash

#<<'CLI'
qemu-system-riscv64 -nographic -machine virt -smp 8,cores=8,threads=1,sockets=1 -m 12G \
 -bios /usr/lib/riscv64-linux-gnu/opensbi/generic/fw_jump.elf \
 -kernel /usr/lib/u-boot/qemu-riscv64_smode/uboot.elf \
 -object rng-random,filename=/dev/urandom,id=rng0 -device virtio-rng-device,rng=rng0 \
 -append "console=ttyS0 rw root=/dev/vda1" \
 -device virtio-blk-device,drive=hd0 -drive file=rootfs.img,format=raw,id=hd0 \
 -device virtio-net-device,netdev=usernet -netdev user,id=usernet,hostfwd=tcp::22222-:22
#CLI

<<'VIDEO'
qemu-system-riscv64 \
  -nographic -machine virt \
  -smp 8,cores=8,threads=1,sockets=1 -m 8G \
  -display sdl -vga std \
  -kernel /usr/lib/u-boot/qemu-riscv64_smode/uboot.elf \
  -bios /usr/lib/riscv64-linux-gnu/opensbi/generic/fw_jump.elf \
  -drive file=rootfs.img,format=raw,id=hd0 \
  -object rng-random,filename=/dev/urandom,id=rng0 \
  -device virtio-vga \
  -device virtio-rng-device,rng=rng0 \
  -device virtio-blk-device,drive=hd0 \
  -device virtio-net-device,netdev=usernet \
  -netdev user,id=usernet,hostfwd=tcp::22222-:22 \
  -device qemu-xhci -usb -device usb-kbd -device usb-tablet \
  -append 'root=/dev/vda1 rw console=ttyS0 swiotlb=1 loglevel=3 systemd.default_timeout_start_sec=600 selinux=0 highres=off mem=8096M earlycon'
VIDEO
```

附3：现在的Debian启动脚本（MI-Laptop）

```shell
qemu-system-riscv64 \
  -nographic -machine virt \
  -smp 8,cores=8,threads=1,sockets=1 -m 8G \
  -display gtk -vga std -device VGA\
  -kernel /usr/lib/u-boot/qemu-riscv64_smode/uboot.elf \
  -bios /usr/lib/riscv64-linux-gnu/opensbi/generic/fw_jump.elf \
  -drive file=rootfs.img,format=raw,id=hd0 \
  -object rng-random,filename=/dev/urandom,id=rng0 \
  -device virtio-rng-device,rng=rng0 \
  -device virtio-blk-device,drive=hd0 \
  -device virtio-net-device,netdev=usernet \
  -netdev user,id=usernet,hostfwd=tcp::22222-:22 \
  -device qemu-xhci -usb -device usb-kbd -device usb-tablet \
  -append 'root=/dev/vda1 rw console=ttyS0 swiotlb=1 loglevel=3 systemd.default_timeout_start_sec=600 selinux=0 highres=off mem=8096M earlycon'
```

