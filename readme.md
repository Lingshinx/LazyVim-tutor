## 介绍

我想给朋友推荐NeoVim, 但是每个人都要我亲自教实在太麻烦了  
让朋友自学的话, 网上又基本是 Vim 的教程, 一些细节的方面, 或者更好的做法也还是需要我去提醒  
最主要的还是**那位大人**说自己需要那种很多练习任务的教程才学得下去  
于是我就写了这么一个教程

第一次写这样的文章, 也是第一次上传仓库到Github上, 有做得不对的地方请多指正

## 依赖

起码得安装个nvim吧

## 安装 nvim

### Windows

呃...自己去[官网](https://neovim.io/)下吧

### MacOS

```sh
brew install neovim
```

### Linux

你都用`Linux`了, 这种简单问题相信你可以自己解决的

## 安装LazyVim

### MacOS 和 Linux

```sh
git clone https://github.com/LazyVim/starter ~/.config/nvim
```

### Windows

#### 安装git

[git for windows](https://gitforwindows.org/)

下载好之后一路next就行

#### 环境变量

首先你需要设置下`XDG_CONFIG_HOME`和`XDG_DATA_HOME`两个环境变量

分别是**配置文件**和**数据**所在的位置

##### CMD

```cmd
setx XDG_CONFIG_HOME "配置文件路径"
setx XDG_DATA_HOME "数据路径"
```

##### Powershell

```powershell
[Environment]::SetEnvironmentVariable('XDG_CONFIG_HOME','配置文件路径')
[Environment]::SetEnvironmentVariable('XDG_DATA_HOME','数据路径')
```

> [!IMPORTANT]
> 这不仅是nvim所独占的目录, 许多Windows下的开源软件也遵从目录规范

#### 安装

```sh
git clone https://github.com/LazyVim/starter ${XDG_CONFIG_HOME}/nvim
```

但愿你的网络没有问题

## Gui

推荐安装neovide, 提供像素级滚动和平滑光标, 最重要的是有默认**Nerd Font**字体
