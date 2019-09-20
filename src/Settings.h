// Copyright (c) 2012-2017, The CryptoNote developers
// Copyleft (c) 2016-2018, Prosus Corp RTD
// Distributed under the MIT/X11 software license

#pragma once

#include <QDir>
#include <QJsonObject>
#include <QObject>

namespace WalletGui {

class CommandLineParser;

class Settings : public QObject {
  Q_OBJECT
  Q_DISABLE_COPY(Settings)

public:
  static Settings& instance();

  void setCommandLineParser(CommandLineParser* _cmd_line_parser);
  void load();

  bool hasAllowLocalIpOption() const;
  bool hasHideMyPortOption() const;
  bool isTestnet() const;
  QDir getDataDir() const;
  QString getP2pBindIp() const;
  quint16 getLocalRpcPort() const;
  quint16 getP2pBindPort() const;
  quint16 getP2pExternalPort() const;
  QStringList getExclusiveNodes() const;
  QStringList getPeers() const;
  QStringList getPriorityNodes() const;
  QStringList getSeedNodes() const;

  QString getWalletFile() const;
  QStringList getRecentWalletsList() const;
  QString getAddressBookFile() const;
  QString getVersion() const;
  QStringList getMiningPoolList() const;
  QString getLanguage() const;
  QString getConnection() const;
  QStringList getRpcNodesList() const;
  quint16 getCurrentLocalDaemonPort() const;
  QString getCurrentRemoteNode() const;
  QString getCurrentPool() const;
  quint16 getMiningThreads() const;
  QString getCurrentTheme() const;

  bool isEncrypted() const;
  bool isStartOnLoginEnabled() const;
  bool isMiningOnLaunchEnabled() const;
  bool isTrackingMode() const;

#ifdef Q_OS_WIN
  bool isMinimizeToTrayEnabled() const;
  bool isCloseToTrayEnabled() const;
#endif

  void setWalletFile(const QString& _file);
  void setEncrypted(bool _encrypted);
  void setTrackingMode(bool _tracking);
  void setCurrentTheme(const QString& _theme);
  void setLanguage(const QString& _language);
  void setStartOnLoginEnabled(bool _enable);
  void setMiningOnLaunchEnabled(bool _enable);
  void setMiningPoolList(const QStringList& _miningPoolList);
  void setConnection(const QString& _connection);
  void setCurrentLocalDaemonPort(const quint16& _daemonPort);
  void setCurrentRemoteNode(const QString& _remoteNode);
  void setRpcNodesList(const QStringList& _RpcNodesList);
  void setCurrentPool(const QString& _pool);
  void setMiningThreads(const quint16& _threads);
#ifdef Q_OS_WIN
  void setMinimizeToTrayEnabled(bool _enable);
  void setCloseToTrayEnabled(bool _enable);
#endif

private:
  QJsonObject m_settings;
  QString m_addressBookFile;
  QString m_currentLang;
  QString m_connectionMode;
  quint16 m_daemonPort;
  CommandLineParser* m_cmdLineParser;

  Settings();
  ~Settings();

  void saveSettings() const;
};

}
