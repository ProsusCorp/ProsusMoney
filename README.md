
# PROSUS MONEY

<img src="http://prosus.money/wp-content/uploads/2018/03/Prosus-header.jpg">

Cryptocurrency created in Chile (2016) as a means of payment, focused on training users without technical knowledge. Low hardware requirement. This project promote a future resource-based economy.

Mnemotechnic for Prosus Money is **xPR**.


## 💾 Install on Ubuntu

If you don't have the Source repositories (Which is the Ubuntu Default) installed, you should execute:

This is the repository for the C libboost libraries, needed to compile.

```
sudo add-apt-repository -s 'deb http://us.archive.ubuntu.com/ubuntu/ focal universe'
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
git clone https://github.com/ProsusCorp/prosus
```

#### GUI version (graphic user interface)
```
cd prosus
mkdir build && cd build
cmake ..
make
```

#### CLI version (console)
```
cd prosus && cd cryptonote
mkdir build && cd build
cmake ..
make
```


## 💾 other OS
[Windows](http://wiki.prosus.money) (Compilation instructions coming shortly)

[macOS](http://wiki.prosus.money) (Compilation instructions coming shortly)


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
