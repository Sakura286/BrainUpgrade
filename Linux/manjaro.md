
# Manjaro Problems

## Start Menu freezed

use `ctrl`+`alt`+`esc` to kill a graphic process

```console
kstart plasmashell #to restart it
```

Refference:
[Can I restart the KDE Plasma Desktop without logging out?](https://askubuntu.com/questions/481329/can-i-restart-the-kde-plasma-desktop-without-logging-out)

## Add Desktop Widget

```console
plasmapkg2 -u widget-file-name.plasmoid
```

```console
kpackagetool5 -i file-name.tar.gz
```

## Locale fault

```log
man: can't set the locale; make sure $LC_* and $LANG are correct
```

Adjust Format from default to a specific region in system settings, and it works.

## yay & pacman

## desktop crash

After running 3d program, the desktop crashed.

It's not KDE's fault. Just latte crashed. So what I need to do is **kill latte and restart it**.

```console
$ ps -Al | grep latte
$ kill xxxx
$ latte-dock
```
