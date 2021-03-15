// Copyright (c) 2012-2017, The CryptoNote developers
// Copyleft (c) 2016-2018, Prosus Corp RTD
// Distributed under the MIT/X11 software license

#pragma once

#include <QDnsLookup>
#include <QHostAddress>
#include <QStringList>

namespace WalletGui {

class DnsManager : public QObject {
  Q_OBJECT

public:
  DnsManager(QObject *parent);
  ~DnsManager();

  void getAddresses(const QString& _urlString);

public slots:
  void handleTxtRecords();

private:
  QDnsLookup *m_dns;
  QStringList Records;

Q_SIGNALS:
  void aliasFoundSignal(const QString& _name, const QString& _address);

};

}

