// Copyright (c) 2012-2017, The CryptoNote developers
// Copyleft (c) 2016-2018, Prosus Corp RTD
// Distributed under the MIT/X11 software license

#pragma once

#include <QSortFilterProxyModel>

namespace WalletGui {

class RecentTransactionsModel : public QSortFilterProxyModel {
  Q_OBJECT
  Q_DISABLE_COPY(RecentTransactionsModel)

public:
  RecentTransactionsModel();
  ~RecentTransactionsModel();

  int columnCount(const QModelIndex& _parent = QModelIndex()) const Q_DECL_OVERRIDE;
  QVariant data(const QModelIndex& _index, int _role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
  bool filterAcceptsRow(int _source_row, const QModelIndex& _source_parent) const Q_DECL_OVERRIDE;
};

}
