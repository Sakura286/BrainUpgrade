
# SPEC 学习

```bash
RPM build errors:
    Installed (but unpackaged) file(s) found:
   /usr/bin/hello
   /usr/share/info/dir
   /usr/share/info/hello.info.gz
   /usr/share/locale/bg/LC_MESSAGES/hello.mo
   /usr/share/locale/ca/LC_MESSAGES/hello.mo
    ...
   /usr/share/locale/zh_CN/LC_MESSAGES/hello.mo
   /usr/share/locale/zh_TW/LC_MESSAGES/hello.mo
   /usr/share/man/man1/hello.1.gz
```

## hello.spec

```bash
Name:     hello
Version:  2.10
Release:  1%{?dist}
Summary:  The "Hello World" program from GNU
Summary(zh_CN):  GNU "Hello World" 程序
License:  GPLv3+
URL:      http://ftp.gnu.org/gnu/hello
Source0:  http://ftp.gnu.org/gnu/hello/%{name}-%{version}.tar.gz

BuildRequires:  gettext
Requires(post): info
Requires(preun): info

%description
The "Hello World" program, done with all bells and whistles of a proper FOSS
project, including configuration, build, internationalization, help files, etc.

%description -l zh_CN
"Hello World" 程序, 包含 FOSS 项目所需的所有部分, 包括配置, 构建, 国际化, 帮助文件等.

%prep
%setup -q

%build
%configure
make %{?_smp_mflags}

%install
make install DESTDIR=%{buildroot}
%find_lang %{name}
rm -f %{buildroot}/%{_infodir}/dir

%post
/sbin/install-info %{_infodir}/%{name}.info %{_infodir}/dir || :

%preun
if [ $1 = 0 ] ; then
/sbin/install-info --delete %{_infodir}/%{name}.info %{_infodir}/dir || :
fi

%files -f %{name}.lang
%doc AUTHORS ChangeLog NEWS README THANKS TODO
%license COPYING
%{_mandir}/man1/hello.1.*
%{_infodir}/hello.info.*
%{_bindir}/hello

%changelog
* Sun Dec 4 2016 Your Name <youremail@xxx.xxx> - 2.10-1
- Update to 2.10
* Sat Dec 3 2016 Your Name <youremail@xxx.xxx> - 2.9-1
- Update to 2.9
```

rpm –showrc | grep _topdir
rpm –eval “%{_topdir}”

macrofiles: /usr/lib/rpm/macros:/etc/rpm/macros

_smp_mflags -->  -j%{_smp_build_ncpus}
_smp_build_ncpus -->  $RPM_BUILD_NCPUS

|| :   || :
|| 表明前面的指令执行失败后执行后面的，：与true一样

set -e set +e

## preun 与 post

preun -- pre uninstall 在卸载之前做什么

postun -- post uninstall 在卸载之后做什么

pre -- 在安装之前做什么

post -- 在安装之后做什么
