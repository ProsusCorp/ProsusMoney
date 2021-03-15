// Copyright (c) 2012-2017, The CryptoNote developers
// Copyleft (c) 2016-2018, Prosus Corp RTD
// Distributed under the MIT/X11 software license

#pragma once

#include <QStringListModel>

namespace WalletGui {

class PoolModel : public QStringListModel {
  Q_OBJECT

public:
  enum Roles {
    ROLE_HOST = Qt::UserRole, ROLE_PORT
  };

  PoolModel(QObject* _parent);
  ~PoolModel();

  void addPool(const QString& _host, quint16 _port);

  QVariant data(const QModelIndex& _index, int _role) const Q_DECL_OVERRIDE;
  Qt::ItemFlags flags(const QModelIndex& _index) const Q_DECL_OVERRIDE;
  QVariant headerData(int _section, Qt::Orientation _orientation, int _role) const Q_DECL_OVERRIDE;
  bool setData(const QModelIndex& _index, const QVariant& _value, int _role = Qt::EditRole) Q_DECL_OVERRIDE;
};

}
