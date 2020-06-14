
# PROSUS MONEY

<img src="http://prosus.money/wp-content/uploads/2018/03/Prosus-header.jpg">

Cryptocurrency created in Chile (2016) as a means of payment, focused on training users without technical knowledge. Low hardware requirement. This project promote a future resource-based economy.

Mnemotechnic for Prosus Money is **xPR**.


## 💾 Installation on Ubuntu

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
**NOTE: The "-DBoost_NO_BOOST_CMAKE=BOOL:ON" is to enable the use of libboost 1.71.0, otherwise it won't compile.**

## 💾 other OS
[Windows](http://wiki.prosus.money) (Compilation instructions coming shortly)

[macOS](http://wiki.prosus.money) (Compilation instructions coming shortly)

## Downloading the daemon directly (without compiling)

____Download_____
```
wget http://prosus.money/wp-content/uploads/2019/10/Prosus_0.7.2-cli_Ubuntu16.zip
unzip Prosus_0.7.2-cli_Ubuntu16.zip
```

## Running the daemon

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
```

## :star: Official web sites
* [Home](http://prosus.money)
* [Block Explorer](http://explorer.prosus.money)
* [Docs](http://wiki.prosus.money)
* [Smart Energy Project](http://prosus.energy)
* [Research and Technological Development](http://prosuscorp.com)

## :family: Community
* [Facebook](https://www.facebook.com/groups/prosus.money)
* [Telegram](https://t.me/prosus_money)
* [Telegram (español)](https://t.me/prosus)
* [Discord](https://discordapp.com/channels/477481402829635604)
* [Market](https://prosus.dinova.cl)
