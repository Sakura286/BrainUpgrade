
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

```bash
ps -Al | grep latte
kill xxxx
latte-dock
```

## input method

### Japanese input method

#### Install

Reference from [Installing Japanese Input Method and Fonts - Manjaro Linux Forum](https://archived.forum.manjaro.org/t/installing-japanese-input-method-and-fonts/10020)

1.Install mozc

```shell
sudo pacman -S fcitx-mozc
```

2.open `~/.xprofile` and add following lines

```shell
 export LANG="ja_JP.UTF-8"
 export XMODIFIERS="@im=fcitx"
 export XMODIFIER="@im=fcitx"
 export GTK_IM_MODULE=fcitx
 export QT_IM_MODULE=fcitx
 export DefaultIMModule=fcitx[/code]
```

3.restart computer

#### Usage

Reference from [How do I toggle to katakana input from hiragana with fcitx-mozc text entry? (16.04) - AskUbuntu](https://askubuntu.com/questions/886426/how-do-i-toggle-to-katakana-input-from-hiragana-with-fcitx-mozc-text-entry-16)

`F6`: full-width Hirakana
`F7`: full-width Katagana
`F8`: half-width Katagana
`F9`: full-width English
`F10`:half-width English

`ctrl`+`shift`, switch between Chinese and Japanese IME
`ctrl`+`space`, switch between English and Japanese(maybe fcitx) IMe
