
# tmp

修改环境变量之后要`source .`一下

在当前bash环境下读取并执行FileName中的命令

`echo $PATH`或者`env`测试当前环境变量

centos7的网卡重启方法：systemctl restart network

```bash
chmod +x ./test.sh  #使脚本具有执行权限
./test.sh  #执行脚本
```

./configure --prefix=/usr/lcoal/test

[QEMU 网络配置](https://tomwei7.com/2021/10/09/qemu-network-config.html)

[Documentation/Networking](https://wiki.qemu.org/Documentation/Networking)

NIC

wget用来测试联网（docker）

[tes]
name=tes
baseurl=https://isrc.iscas.ac.cn/mirror/openeuler-sig-riscv/oe-RISCV-repo/

You have enabled checking of packages via GPG keys. This is a good thing.
However, you do not have any GPG public keys installed. You need to download
the keys for packages you wish to install and install them.
You can do that by running the command:
    rpm --import public.gpg.key

Alternatively you can specify the url to the key you would like to use
for a repository in the 'gpgkey' option in a repository section and YUM
will install it for you.

For more information contact your distribution or package provider.

SSL certificate problem: certificate is not yet valid
error: Curl error (60): SSL peer certificate or SSH remote key was not OK for https://isrc.iscas.ac.cn/mirror/openeuler-sig-riscv/oe-RISCV-repo/repodata/repomd.xml
系统时间不对啊亲！想用HTTPS得先把系统时间调对了！

clone

https://isrc.iscas.ac.cn/mirror/openeuler-sig-riscv/oe-RISCV-repo/

折腾个狗屁源，直接git clone然后make install了拉倒

https://docs.openeuler.org/zh/docs/20.03_LTS/docs/Administration/%E5%9F%BA%E7%A1%80%E9%85%8D%E7%BD%AE.html
OpenEuler 基础配置

gnome-terminal Ubuntu

rdma

ping在`iputils`里

不响应ICMP
