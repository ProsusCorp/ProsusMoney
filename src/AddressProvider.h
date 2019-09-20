// Copyright (c) 2012-2017, The CryptoNote developers
// Copyleft (c) 2016-2018, Prosus Corp RTD
// Distributed under the MIT/X11 software license

#pragma once

#include <QObject>
#include <QNetworkAccessManager>

namespace WalletGui {

class AddressProvider : public QObject {
  Q_OBJECT

public:
  AddressProvider(QObject *parent);
  ~AddressProvider();

  void getAddress(const QString& _urlString);

private:
  QNetworkAccessManager m_networkManager;
  void readyRead();

Q_SIGNALS:
  void addressFoundSignal(const QString& _address);
};

}
