
# Debian

## 新安装Debian需要解决的问题

基于 Debian 11.3 Bullseye

### 无法使用 sudo

先使用su切换到管理员，然后编辑`/etc/sudoers`文件（有`nano`），在`root    ALL=(ALL:ALL) ALL`之后一行添加`<user> ALL=(ALL:ALL) ALL`，其中`<user>`需要替换为当前用户名

### 无法呼起 Terminal

启动 Settings -> Keyboard Shortcuts -> 拉到最下面点+打开`Add Custom Shortcut`窗口

Command 一栏填写 `gnome-terminal`
Shortcut 使用`ctrl`+`alt`+`t`

### 未使用暗色主题

启动 Tweaks -> Apparance -> Themes -> Applications

选择`Adwaita-dark`

### 没有最大化最小化按钮

启动 Tweaks -> Windows Titlebars -> Titlebar Buttons

### 任务栏显示秒数、电池电量等

启动 Tweaks -> Top Bar

### 桌面图标显示

#### 安装 Extension

`sudo apt install gnome-shell-extension-desktop-icons`

如果 apt 仓库里没有这个，可以先`apt search desktop-icons`搜索一下看看到底叫什么

#### 注销账户

#### 启用桌面图标显示

启动 Extensions -> Desktop Icons 打开
