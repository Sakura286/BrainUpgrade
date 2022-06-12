
```log
~/Desktop ❯ sudo sbuild-createchroot --arch=riscv64 --foreign  --keyring="" --include=debian-ports-archive-keyring --make-sbuild-tarball=/srv/sid-riscv64-sbuild.tgz sid /tmp/chroots/sid-riscv64-sbuild1/  http://ftp.ports.debian.org/debian-ports/

mkdir /tmp/chroots
mkdir /tmp/chroots/sid-riscv64-sbuild1/
I: SUITE: sid
I: TARGET: /tmp/chroots/sid-riscv64-sbuild1
I: MIRROR: http://ftp.ports.debian.org/debian-ports/
I: Running debootstrap --arch=riscv64 --variant=buildd --verbose --foreign --include=fakeroot,build-essential,debian-ports-archive-keyring --components=main --no-check-gpg --resolve-deps --no-merged-usr sid /tmp/chroots/sid-riscv64-sbuild1 http://ftp.ports.debian.org/debian-ports/
I: Retrieving InRelease 
I: Retrieving Packages 
I: Validating Packages 
I: Resolving dependencies of required packages...
I: Resolving dependencies of base packages...
I: Checking component main on http://ftp.ports.debian.org/debian-ports...
I: Retrieving adduser 3.121
I: Validating adduser 3.121
I: Retrieving debconf 1.5.79
I: Validating debconf 1.5.79
I: Retrieving debian-archive-keyring 2021.1.1
I: Validating debian-archive-keyring 2021.1.1
I: Retrieving debian-ports-archive-keyring 2022.02.15
I: Validating debian-ports-archive-keyring 2022.02.15
I: Retrieving dpkg-dev 1.21.8
I: Validating dpkg-dev 1.21.8
I: Retrieving init-system-helpers 1.63
I: Validating init-system-helpers 1.63
I: Retrieving libaudit-common 1:3.0.7-1
I: Validating libaudit-common 1:3.0.7-1
I: Retrieving libdpkg-perl 1.21.8
I: Validating libdpkg-perl 1.21.8
I: Retrieving libpam-runtime 1.4.0-13
I: Validating libpam-runtime 1.4.0-13
I: Retrieving libsemanage-common 3.4-1
I: Validating libsemanage-common 3.4-1
I: Retrieving libtirpc-common 1.3.2-2
I: Validating libtirpc-common 1.3.2-2
I: Retrieving lsb-base 11.2
I: Validating lsb-base 11.2
I: Retrieving ncurses-base 6.3+20220423-2
I: Validating ncurses-base 6.3+20220423-2
I: Retrieving perl-modules-5.34 5.34.0-4
I: Validating perl-modules-5.34 5.34.0-4
I: Retrieving tzdata 2022a-1
I: Validating tzdata 2022a-1
I: Retrieving apt 2.5.0
I: Validating apt 2.5.0
I: Retrieving base-files 12.2
I: Validating base-files 12.2
I: Retrieving base-passwd 3.5.52
I: Validating base-passwd 3.5.52
I: Retrieving bash 5.1-6.1
I: Validating bash 5.1-6.1
I: Retrieving binutils-common 2.38-4
I: Validating binutils-common 2.38-4
I: Retrieving binutils-riscv64-linux-gnu 2.38-4
I: Validating binutils-riscv64-linux-gnu 2.38-4
I: Retrieving binutils 2.38-4
I: Validating binutils 2.38-4
I: Retrieving bsdutils 1:2.38-4
I: Validating bsdutils 1:2.38-4
I: Retrieving build-essential 12.9
I: Validating build-essential 12.9
I: Retrieving bzip2 1.0.8-5
I: Validating bzip2 1.0.8-5
I: Retrieving coreutils 8.32-4.1
I: Validating coreutils 8.32-4.1
I: Retrieving cpp-11 11.3.0-3
I: Validating cpp-11 11.3.0-3
I: Retrieving cpp 4:11.2.0-2
I: Validating cpp 4:11.2.0-2
I: Retrieving dash 0.5.11+git20210903+057cd650a4ed-8
I: Validating dash 0.5.11+git20210903+057cd650a4ed-8
I: Retrieving debianutils 5.7-0.2
I: Validating debianutils 5.7-0.2
I: Retrieving diffutils 1:3.7-5
I: Validating diffutils 1:3.7-5
I: Retrieving dpkg 1.21.8
I: Validating dpkg 1.21.8
I: Retrieving e2fsprogs 1.46.5-2
I: Validating e2fsprogs 1.46.5-2
I: Retrieving fakeroot 1.29-1
I: Validating fakeroot 1.29-1
I: Retrieving findutils 4.9.0-3
I: Validating findutils 4.9.0-3
I: Retrieving g++-11 11.3.0-3
I: Validating g++-11 11.3.0-3
I: Retrieving g++ 4:11.2.0-2
I: Validating g++ 4:11.2.0-2
I: Retrieving gcc-11-base 11.3.0-3
I: Validating gcc-11-base 11.3.0-3
I: Retrieving gcc-11 11.3.0-3
I: Validating gcc-11 11.3.0-3
I: Retrieving gcc-12-base 12.1.0-2
I: Validating gcc-12-base 12.1.0-2
I: Retrieving gcc-9-base 9.5.0-1
I: Validating gcc-9-base 9.5.0-1
I: Retrieving gcc 4:11.2.0-2
I: Validating gcc 4:11.2.0-2
I: Retrieving gpgv 2.2.35-2
I: Validating gpgv 2.2.35-2
I: Retrieving grep 3.7-1
I: Validating grep 3.7-1
I: Retrieving gzip 1.12-1
I: Validating gzip 1.12-1
I: Retrieving hostname 3.23
I: Validating hostname 3.23
I: Retrieving libacl1 2.3.1-1
I: Validating libacl1 2.3.1-1
I: Retrieving libapt-pkg6.0 2.5.0
I: Validating libapt-pkg6.0 2.5.0
I: Retrieving libasan6 11.3.0-3
I: Validating libasan6 11.3.0-3
I: Retrieving libatomic1 12.1.0-2
I: Validating libatomic1 12.1.0-2
I: Retrieving libattr1 1:2.5.1-1
I: Validating libattr1 1:2.5.1-1
I: Retrieving libaudit1 1:3.0.7-1+b1
I: Validating libaudit1 1:3.0.7-1+b1
I: Retrieving libbinutils 2.38-4
I: Validating libbinutils 2.38-4
I: Retrieving libblkid1 2.38-4
I: Validating libblkid1 2.38-4
I: Retrieving libbz2-1.0 1.0.8-5
I: Validating libbz2-1.0 1.0.8-5
I: Retrieving libc-bin 2.33-7
I: Validating libc-bin 2.33-7
I: Retrieving libc-dev-bin 2.33-7
I: Validating libc-dev-bin 2.33-7
I: Retrieving libc6-dev 2.33-7
I: Validating libc6-dev 2.33-7
I: Retrieving libc6 2.33-7
I: Validating libc6 2.33-7
I: Retrieving libcap-ng0 0.7.9-2.2+b2
I: Validating libcap-ng0 0.7.9-2.2+b2
I: Retrieving libcap2 1:2.44-1
I: Validating libcap2 1:2.44-1
I: Retrieving libcc1-0 12.1.0-2
I: Validating libcc1-0 12.1.0-2
I: Retrieving libcom-err2 1.46.5-2
I: Validating libcom-err2 1.46.5-2
I: Retrieving libcrypt-dev 1:4.4.27-1.1
I: Validating libcrypt-dev 1:4.4.27-1.1
I: Retrieving libcrypt1 1:4.4.27-1.1
I: Validating libcrypt1 1:4.4.27-1.1
I: Retrieving libctf-nobfd0 2.38-4
I: Validating libctf-nobfd0 2.38-4
I: Retrieving libctf0 2.38-4
I: Validating libctf0 2.38-4
I: Retrieving libdb5.3 5.3.28+dfsg1-0.9
I: Validating libdb5.3 5.3.28+dfsg1-0.9
I: Retrieving libdebconfclient0 0.262
I: Validating libdebconfclient0 0.262
I: Retrieving libext2fs2 1.46.5-2
I: Validating libext2fs2 1.46.5-2
I: Retrieving libfakeroot 1.29-1
I: Validating libfakeroot 1.29-1
I: Retrieving libffi8 3.4.2-4
I: Validating libffi8 3.4.2-4
I: Retrieving libgcc-11-dev 11.3.0-3
I: Validating libgcc-11-dev 11.3.0-3
I: Retrieving libgcc-s1 12.1.0-2
I: Validating libgcc-s1 12.1.0-2
I: Retrieving libgcrypt20 1.10.1-2
I: Validating libgcrypt20 1.10.1-2
I: Retrieving libgdbm-compat4 1.23-1
I: Validating libgdbm-compat4 1.23-1
I: Retrieving libgdbm6 1.23-1
I: Validating libgdbm6 1.23-1
I: Retrieving libgmp10 2:6.2.1+dfsg-3
I: Validating libgmp10 2:6.2.1+dfsg-3
I: Retrieving libgnutls30 3.7.4-2
I: Validating libgnutls30 3.7.4-2
I: Retrieving libgomp1 12.1.0-2
I: Validating libgomp1 12.1.0-2
I: Retrieving libgpg-error0 1.45-2
I: Validating libgpg-error0 1.45-2
I: Retrieving libgssapi-krb5-2 1.19.2-2+b2
I: Validating libgssapi-krb5-2 1.19.2-2+b2
I: Retrieving libhogweed6 3.7.3-1
I: Validating libhogweed6 3.7.3-1
I: Retrieving libidn2-0 2.3.2-2
I: Validating libidn2-0 2.3.2-2
I: Retrieving libisl23 0.24-2
I: Validating libisl23 0.24-2
I: Retrieving libk5crypto3 1.19.2-2+b2
I: Validating libk5crypto3 1.19.2-2+b2
I: Retrieving libkeyutils1 1.6.1-3
I: Validating libkeyutils1 1.6.1-3
I: Retrieving libkrb5-3 1.19.2-2+b2
I: Validating libkrb5-3 1.19.2-2+b2
I: Retrieving libkrb5support0 1.19.2-2+b2
I: Validating libkrb5support0 1.19.2-2+b2
I: Retrieving liblz4-1 1.9.3-2
I: Validating liblz4-1 1.9.3-2
I: Retrieving liblzma5 5.2.5-2.1
I: Validating liblzma5 5.2.5-2.1
I: Retrieving libmount1 2.38-4
I: Validating libmount1 2.38-4
I: Retrieving libmpc3 1.2.1-2
I: Validating libmpc3 1.2.1-2
I: Retrieving libmpfr6 4.1.0-3
I: Validating libmpfr6 4.1.0-3
I: Retrieving libnettle8 3.7.3-1
I: Validating libnettle8 3.7.3-1
I: Retrieving libnsl-dev 1.3.0-2
I: Validating libnsl-dev 1.3.0-2
I: Retrieving libnsl2 1.3.0-2
I: Validating libnsl2 1.3.0-2
I: Retrieving libp11-kit0 0.24.1-1
I: Validating libp11-kit0 0.24.1-1
I: Retrieving libpam-modules-bin 1.4.0-13
I: Validating libpam-modules-bin 1.4.0-13
I: Retrieving libpam-modules 1.4.0-13
I: Validating libpam-modules 1.4.0-13
I: Retrieving libpam0g 1.4.0-13
I: Validating libpam0g 1.4.0-13
I: Retrieving libpcre2-8-0 10.40-1
I: Validating libpcre2-8-0 10.40-1
I: Retrieving libpcre3 2:8.39-14
I: Validating libpcre3 2:8.39-14
I: Retrieving libperl5.34 5.34.0-4
I: Validating libperl5.34 5.34.0-4
I: Retrieving libselinux1 3.4-1
I: Validating libselinux1 3.4-1
I: Retrieving libsemanage2 3.4-1
I: Validating libsemanage2 3.4-1
I: Retrieving libsepol2 3.4-1
I: Validating libsepol2 3.4-1
I: Retrieving libsmartcols1 2.38-4
I: Validating libsmartcols1 2.38-4
I: Retrieving libss2 1.46.5-2
I: Validating libss2 1.46.5-2
I: Retrieving libssl3 3.0.3-7
I: Validating libssl3 3.0.3-7
I: Retrieving libstdc++-11-dev 11.3.0-3
I: Validating libstdc++-11-dev 11.3.0-3
I: Retrieving libstdc++6 12.1.0-2
I: Validating libstdc++6 12.1.0-2
I: Retrieving libsystemd0 251.2-2
I: Validating libsystemd0 251.2-2
I: Retrieving libtasn1-6 4.18.0-4
I: Validating libtasn1-6 4.18.0-4
I: Retrieving libtinfo6 6.3+20220423-2
I: Validating libtinfo6 6.3+20220423-2
I: Retrieving libtirpc-dev 1.3.2-2
I: Validating libtirpc-dev 1.3.2-2
I: Retrieving libtirpc3 1.3.2-2
I: Validating libtirpc3 1.3.2-2
I: Retrieving libudev1 251.2-2
I: Validating libudev1 251.2-2
I: Retrieving libunistring2 1.0-1
I: Validating libunistring2 1.0-1
I: Retrieving libuuid1 2.38-4
I: Validating libuuid1 2.38-4
I: Retrieving libxxhash0 0.8.1-1
I: Validating libxxhash0 0.8.1-1
I: Retrieving libzstd1 1.5.2+dfsg-1
I: Validating libzstd1 1.5.2+dfsg-1
I: Retrieving linux-libc-dev 5.18.2-1
I: Validating linux-libc-dev 5.18.2-1
I: Retrieving login 1:4.11.1+dfsg1-2
I: Validating login 1:4.11.1+dfsg1-2
I: Retrieving logsave 1.46.5-2
I: Validating logsave 1.46.5-2
I: Retrieving make 4.3-4.1
I: Validating make 4.3-4.1
I: Retrieving mawk 1.3.4.20200120-3
I: Validating mawk 1.3.4.20200120-3
I: Retrieving mount 2.38-4
I: Validating mount 2.38-4
I: Retrieving ncurses-bin 6.3+20220423-2
I: Validating ncurses-bin 6.3+20220423-2
I: Retrieving passwd 1:4.11.1+dfsg1-2
I: Validating passwd 1:4.11.1+dfsg1-2
I: Retrieving patch 2.7.6-7
I: Validating patch 2.7.6-7
I: Retrieving perl-base 5.34.0-4
I: Validating perl-base 5.34.0-4
I: Retrieving perl 5.34.0-4
I: Validating perl 5.34.0-4
I: Retrieving rpcsvc-proto 1.4.2-4
I: Validating rpcsvc-proto 1.4.2-4
I: Retrieving sed 4.8-1
I: Validating sed 4.8-1
I: Retrieving sysvinit-utils 3.03-1
I: Validating sysvinit-utils 3.03-1
I: Retrieving tar 1.34+dfsg-1
I: Validating tar 1.34+dfsg-1
I: Retrieving util-linux-extra 2.38-4
I: Validating util-linux-extra 2.38-4
I: Retrieving util-linux 2.38-4
I: Validating util-linux 2.38-4
I: Retrieving xz-utils 5.2.5-2.1
I: Validating xz-utils 5.2.5-2.1
I: Retrieving zlib1g 1:1.2.11.dfsg-4
I: Validating zlib1g 1:1.2.11.dfsg-4
I: Chosen extractor for .deb packages: dpkg-deb
I: Extracting adduser...
I: Extracting debconf...
I: Extracting debian-archive-keyring...
I: Extracting init-system-helpers...
I: Extracting libaudit-common...
I: Extracting libpam-runtime...
I: Extracting libsemanage-common...
I: Extracting lsb-base...
I: Extracting ncurses-base...
I: Extracting tzdata...
I: Extracting apt...
I: Extracting base-files...
I: Extracting base-passwd...
I: Extracting bash...
I: Extracting bsdutils...
I: Extracting coreutils...
I: Extracting dash...
I: Extracting debianutils...
I: Extracting diffutils...
I: Extracting dpkg...
I: Extracting e2fsprogs...
I: Extracting findutils...
I: Extracting gcc-12-base...
I: Extracting gcc-9-base...
I: Extracting gpgv...
I: Extracting grep...
I: Extracting gzip...
I: Extracting hostname...
I: Extracting libacl1...
I: Extracting libapt-pkg6.0...
I: Extracting libattr1...
I: Extracting libaudit1...
I: Extracting libblkid1...
I: Extracting libbz2-1.0...
I: Extracting libc-bin...
I: Extracting libc6...
I: Extracting libcap-ng0...
I: Extracting libcap2...
I: Extracting libcom-err2...
I: Extracting libcrypt1...
I: Extracting libdb5.3...
I: Extracting libdebconfclient0...
I: Extracting libext2fs2...
I: Extracting libffi8...
I: Extracting libgcc-s1...
I: Extracting libgcrypt20...
I: Extracting libgmp10...
I: Extracting libgnutls30...
I: Extracting libgpg-error0...
I: Extracting libhogweed6...
I: Extracting libidn2-0...
I: Extracting liblz4-1...
I: Extracting liblzma5...
I: Extracting libmount1...
I: Extracting libnettle8...
I: Extracting libp11-kit0...
I: Extracting libpam-modules-bin...
I: Extracting libpam-modules...
I: Extracting libpam0g...
I: Extracting libpcre2-8-0...
I: Extracting libpcre3...
I: Extracting libselinux1...
I: Extracting libsemanage2...
I: Extracting libsepol2...
I: Extracting libsmartcols1...
I: Extracting libss2...
I: Extracting libstdc++6...
I: Extracting libsystemd0...
I: Extracting libtasn1-6...
I: Extracting libtinfo6...
I: Extracting libudev1...
I: Extracting libunistring2...
I: Extracting libuuid1...
I: Extracting libxxhash0...
I: Extracting libzstd1...
I: Extracting login...
I: Extracting logsave...
I: Extracting mawk...
I: Extracting mount...
I: Extracting ncurses-bin...
I: Extracting passwd...
I: Extracting perl-base...
I: Extracting sed...
I: Extracting sysvinit-utils...
I: Extracting tar...
I: Extracting util-linux-extra...
I: Extracting util-linux...
I: Extracting zlib1g...
I: Configured /etc/hosts:
   +------------------------------------------------------------------------
   |127.0.0.1   localhost
   |::1         localhost ip6-localhost ip6-loopback
   |ff02::1             ip6-allnodes
   |ff02::2             ip6-allrouters
   |
   +------------------------------------------------------------------------
I: Configured /usr/sbin/policy-rc.d:
   +------------------------------------------------------------------------
   |#!/bin/sh
   |echo "All runlevel operations denied by policy" >&2
   |exit 101
   +------------------------------------------------------------------------
I: Configured APT /etc/apt/sources.list:
   +------------------------------------------------------------------------
   |deb http://ftp.ports.debian.org/debian-ports sid main
   |deb-src http://ftp.ports.debian.org/debian-ports/ sid main
   |
   +------------------------------------------------------------------------
I: Please add any additional APT sources to /tmp/chroots/sid-riscv64-sbuild1/etc/apt/sources.list
I: schroot chroot configuration written to /etc/schroot/chroot.d/sid-riscv64-sbuild-eySkGs.
   +------------------------------------------------------------------------
   |[sid-riscv64-sbuild]
   |description=Debian sid/riscv64 autobuilder
   |groups=root,sbuild
   |root-groups=root,sbuild
   |profile=sbuild
   |type=file
   |file=/srv/sid-riscv64-sbuild.tgz
   +------------------------------------------------------------------------
    I: Please rename and modify this file as required.
    W: The selected architecture and the current architecture do not match
    W: (riscv64 versus amd64).
    I: You probably need to add a personality option (see schroot(1)).
    I: You may want to report your use case to the sbuild developers so that
    I: the appropriate option gets automatically added in the future.

    /usr/sbin/chroot: failed to run command ‘/bin/sh’: Exec format error
    /usr/sbin/chroot: failed to run command ‘/bin/sh’: Exec format error
    E: Failed to create group sbuild
    Failed to set up chroot
    E: Error creating chroot session: skipping apt update
    I: Creating tarball...
    I: Done creating /srv/sid-riscv64-sbuild.tgz
    I: chroot /tmp/chroots/sid-riscv64-sbuild1 has been removed.
    I: Successfully set up sid chroot.
    I: Run "sbuild-adduser" to add new sbuild users.
```

```log
~/Desktop ❯ sudo schroot -c sid-riscv64-sbuild                                            08:35:34
W: Failed to change to directory ‘/home/infinity/Desktop’: No such file or directory
I: The directory does not exist inside the chroot.  Use the --directory option to run the command in a different directory.
W: Falling back to directory ‘/root’
E: Failed to execute “/bin/bash”: Exec format error

 / ❯ sudo schroot -c sid-riscv64-sbuild                                                  08:37:52
E: Failed to execute “/bin/bash”: Exec format error
```

```bash
sudo sbuild-createchroot --arch=riscv64 \
                         --foreign \ 
                         --keyring="" \
                         --include=debian-ports-archive-keyring \
                         --make-sbuild-tarball=/srv/sid-riscv64-sbuild.tgz \ 
                         sid \ # SUITE
                         /tmp/chroots/sid-riscv64-sbuild1/  # TARGET-DIRECTORY
                         http://ftp.ports.debian.org/debian-ports/ # DEBIAN-MIRROR-URI
```

主板CPU套装
https://item.jd.com/100032834866.html
CPU散热器
https://item.jd.com/100012001257.html
内存（注：两套）
https://item.jd.com/100022451588.html
硬盘
https://item.jd.com/100015242141.html
https://item.jd.com/100027922632.html
显卡
https://item.jd.com/100019033224.html

电源
https://item.jd.com/225549.html
机箱
https://item.jd.com/1842778.html

显示器
https://item.jd.com/100021897578.html

鼠标
https://item.jd.com/2150706.html

什么叫他妈的“source-only”？看起来和local是相对的
