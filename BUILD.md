
# 1 💾 ESPECIFIC BUILD PARAMETERS

## 1.1 💾 Build on Windows

Dependencies: MSVC 2013 or later, CMake 2.8.6 or later, and Boost 1.55. You may download them from:
* http://www.microsoft.com/
* http://www.cmake.org/
* http://www.boost.org/

Open command line (cmd.exe), change to a directory where CMakeList.txt file is located, and execute this:
```
mkdir build
cd build
cmake -G "Visual Studio 12 Win64" ..
make
```
----
## 1.2 💾 Build on Debian/Ubuntu

If you don't have the Source repositories (Which is the Ubuntu Default) installed, you should execute:

This is the repository for the C libboost libraries, needed to compile.

```
sudo add-apt-repository -s 'deb http://us.archive.ubuntu.com/ubuntu/ $(lsb_release -sc) universe'
```

Now we need like 300MB of the QT Graphical interface libraries

```
sudo apt install qtbase5-dev qt5-default qtdeclarative5-dev qml-module-qtquick-controls qml-module-qtquick-controls2 qml-module-qtquick-dialogs qml-module-qtquick-xmllistmodel qml-module-qt-labs-settings qml-module-qt-labs-folderlistmodel qttools5-dev-tools qml-module-qtquick-templates2 libqt5svg5-dev
```
Then, do the following:

```
(sudo)
apt-get update
apt-get upgrade
apt-get install build-essential git cmake libboost-all-dev
git clone https://github.com/ProsusCorp/prosus.money.git
```

Next step is to compile the software, depending on what you want to use, do the following:

#### GUI version (graphic user interface)
```
cd prosus
mkdir build && cd build
cmake .. -DBoost_NO_BOOST_CMAKE=BOOL:ON
make
```

#### CLI version (console)
```
cd prosus && cd cryptonote
mkdir build && cd build
cmake .. -DBoost_NO_BOOST_CMAKE=BOOL:ON
make
```
----
**NOTE 1: The "-DBoost_NO_BOOST_CMAKE=BOOL:ON" is to enable the use of libboost 1.71.0, otherwise it won't compile.**

**NOTE 2: For low disc space, install especific modules from Boost library **
```
apt-get install -y \
libboost-dev \
libboost-regex-dev \
libboost-serialization-dev \
libboost-program-options-dev \
libboost-coroutine-dev \
libboost-context-dev \
libboost-system-dev \
libboost-filesystem-dev \
libboost-thread-dev \
libboost-date-time-dev \
libboost-chrono-dev 
```

----
## 1.3 💾 Build on macOS

[macOS](http://wiki.prosus.money) (Compilation instructions coming shortly)


----
# 2 :snail: ESPECIFIC RUN PARAMETERS

## 2.1 :snail: DEBIAN: Downloading the daemon directly (without compiling)

____Download_____
```
wget http://prosus.money/wp-content/uploads/2019/10/Prosus_0.7.2-cli_Ubuntu16.zip
unzip Prosus_0.7.2-cli_Ubuntu16.zip
```

----
## 2.2 :snail: DEBIAN: Running the daemon

```
./prosus-daemon
```

___Create wallet___

```
./prosus-wallet
```


___Make it resident___
[How to run this as a service; ]

```
./prosus-daemon --add-exclusive-node 200.42.190.22
```

___How to run as a service in the background; so it keeps running when leaving the console___

```
nohup setsid ./prosus-daemon --add-exclusive-node 200.42.190.22
```

___List all system processes___

```
ps aux
```

___kill a prosus-daemon(closes the daemon process)___

```
pkill -9 prosus-daemon
```

___Block IPs with iptables ( Iptables are temporary.)___

```
sudo iptables -A INPUT -s 45.55.36.111 -j DROP
sudo iptables -A INPUT -s 35.231.66.169 -j DROP
sudo iptables -A INPUT -s 13.57.179.95 -j DROP
```
___SOLO MINING___

Run as a service in the background, mining directly from the daemon to an external wallet
```
nohup setsid ./prosus-daemon --start-mining ProsusxxxxxxxxADDRESS -t 2 &

