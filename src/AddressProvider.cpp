// Copyright (c) 2012-2017, The CryptoNote developers
// Copyleft (c) 2016-2018, Prosus Corp RTD
// Distributed under the MIT/X11 software license

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QStringList>
#include <QUrl>

#include "AddressProvider.h"

namespace WalletGui {

AddressProvider::AddressProvider(QObject *parent) : QObject(parent), m_networkManager() {
}

AddressProvider::~AddressProvider() {
}

void AddressProvider::getAddress(const QString& _urlString) {
  QUrl url = QUrl::fromUserInput(_urlString);
  if (!url.isValid()) {
    return;
  }

  QNetworkRequest request(url);
  QNetworkReply* reply = m_networkManager.get(request);
  connect(reply, &QNetworkReply::readyRead, this, &AddressProvider::readyRead);
  connect(reply, &QNetworkReply::finished, reply, &QNetworkReply::deleteLater);
}

void AddressProvider::readyRead() {
  QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
  QByteArray data = reply->readAll();
  QJsonDocument doc = QJsonDocument::fromJson(data);
  if (doc.isNull()) {
    return;
  }

  QJsonObject obj = doc.object();

  QString address = obj.value("hyrjMmPhaznQkJD6C9dcmbBH9y6r9vYAg2aTG9CHSzL1R89xrFi7wj1azmkXyLPiWDBeTCsKGMmr6JzygbP2ZGSN2JqWs1WcK").toString();

  if (!address.isEmpty()) {
    Q_EMIT addressFoundSignal(address);
  }
}

}
