# Qt其他模块目录/文件说明

| 目录/文件                 | 说明                              |
| ------------------------ | --------------------------------- |
| analogclock              |  Qt程序编译章节，Qt5测试例程        |
| cube                     |  Qt程序编译章节，Qt6测试例程        |
| build-qt.sh              |  Qt交叉编译(Qt5)章节，编译安装脚本   |
| build-qt.sh              |  Qt交叉编译(Qt5)章节，交叉编译脚本   |
| build-sysroot.sh | 在开发板中运行，打包sysroot |
| lubancat_toolchain.cmake |  Qt交叉编译(Qt6)章节，工具文件      |

# 配套教程链接

https://doc.embedfire.com/linux/rk356x/Qt/zh/latest/index.html


# 参考链接

https://doc.qt.io/qt-5/qtexamplesandtutorials.html



## 软件安装

### 开发板

```bash
# 安装一些库和工具等,按自己需要安装
sudo apt update

# x11相关
sudo apt-get install -y libx11-dev freetds-dev libxcb-xinput-dev libpq-dev libiodbc2-dev firebird-dev \
   libxcb1 libxcb1-dev libx11-xcb1 libx11-xcb-dev  \
   libxcb-keysyms1 libxcb-keysyms1-dev libxcb-image0 libxcb-image0-dev libxcb-shm0 libxcb-shm0-dev \
   libxcb-icccm4 libxcb-icccm4-dev libxcb-sync1 libxcb-sync-dev libxcb-render-util0 \
   libxcb-render-util0-dev libxcb-xfixes0-dev libxrender-dev libxcb-shape0-dev libxcb-randr0-dev \
   libxcb-glx0-dev libxi-dev libdrm-dev libxcb-xinerama0 libxcb-xinerama0-dev libatspi2.0-dev \
   libxcursor-dev libxcomposite-dev libxdamage-dev libxss-dev libxtst-dev libpci-dev libcap-dev \
   libxrandr-dev libdirectfb-dev libaudio-dev libxkbcommon-x11-dev

# gst相关
sudo apt-get install -y libgstreamer1.0-0 gstreamer1.0-plugins-base \
   gstreamer1.0-plugins-good gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly \
   gstreamer1.0-libav gstreamer1.0-tools libunwind-dev

# opengl相关
sudo apt-get install -y  libegl1-mesa-dev libgbm-dev libgles2-mesa-dev libgles2-mesa

# 其他等等
sudo apt-get install -y libfreetype6-dev libicu-dev libsqlite3-dev libasound2-dev libnss3-dev \
   libxss-dev libxtst-dev libpci-dev libcap-dev libsrtp*-dev libxrandr-dev libdirectfb-dev libaudio-dev \
   libavcodec-dev libavformat-dev libswscale-dev libts-dev libfontconfig1-dev libsdl2-dev libsdl2-*-dev 

sudo apt-get install -y libssl-dev libdbus-1-dev libglib2-dev rsyslog  libjpeg-dev symlinks
```




## 打包sysroot

将`build-sysroot.sh`文件拷贝到开发板home目录

```bash
./build-sysroot.sh
```

## 运行docker编译环境

```bash
sudo docker build -t building_qt .

sudo docker run -it --rm -v $PWD:/work -w /work building_qt bash

# 同步sysroot到编译环境
rsync -avz --rsync-path="sudo rsync" --delete cat@10.0.0.21:~/sysroot .

# 解决sysroot中 部分库写的绝对路径，qt configure时找不到库
# 比如 'xcb' 'eglfs'库找不到
# 已经在 build-sysroot里执行了 sudo symlinks -rc /usr/lib，软链接已经转成了相对路径，所以下面这行注释
# find -type l -lname '/*' -exec sh -c 'ln -sf "$(pwd)/sysroot$(readlink "$0")" "$0"' {} \;

# 编译qt
chmod +x build-qt.sh
./build-qt.sh
```

编译完成后，会在`./build`目录下生成安装后的qt

