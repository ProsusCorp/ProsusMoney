// Copyright (c) 2012-2017, The CryptoNote developers
// Copyleft (c) 2016-2018, Prosus Corp RTD
// Distributed under the MIT/X11 software license

#pragma once

#include <QSortFilterProxyModel>

namespace WalletGui {

class TransactionsListModel : public QSortFilterProxyModel {
  Q_OBJECT

public:
  TransactionsListModel();
  ~TransactionsListModel();

protected:
  bool filterAcceptsColumn(int _sourceColumn, const QModelIndex& _sourceParent) const Q_DECL_OVERRIDE;
};

}
