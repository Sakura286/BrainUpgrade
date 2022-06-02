
# 安装libreport时的错误

> configure: error: Package requirements (libarchive) were not met:
> Package 'libarchive', required by 'virtual:world', not found
> Consider adjusting the PKG_CONFIG_PATH environment variable if you installed software in a non-standard prefix.
> Alternatively, you may set the environment variables LIBARCHIVE_CFLAGS and LIBARCHIVE_LIBS to avoid the need to call pkg-config. See the pkg-config man page for more details.
> Configured for local debugging ...

## 可能原因

[简述configure、pkg-config、pkg_config_path三者的关系 - 博客园 - ArcherDev](https://www.cnblogs.com/cnland/archive/2013/02/08/2909273.html)

configure 需要通过 pkg-config 来检查依赖

程序为 pkg-config 提供一个`.pc`来告知库的头文件存放位置，这个文件一般放在 /usr/lib/pkgconfig/ 或者 /usr/local/lib/pkgconfig/ 里，这样， pkg-config 就可以为configure提供依赖检查了

## 解决方法

已经安装了 libarchive ，但是`pkg-config --list-all | grep libarchive`并没有出现 libarchive，安装 libarchive-devel 后解决

export GTK_IM_MODULE=fcitx
export QT_IM_MODULE=fcitx
export XMODIFIERS=@im=fcitxdfd发达发达