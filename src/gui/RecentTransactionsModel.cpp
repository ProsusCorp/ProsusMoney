// Copyright (c) 2012-2017, The CryptoNote developers
// Copyleft (c) 2016-2018, Prosus Corp RTD
// Distributed under the MIT/X11 software license

#include "RecentTransactionsModel.h"
#include "RecentSortedTransactionsModel.h"

namespace WalletGui {

RecentTransactionsModel::RecentTransactionsModel() : QSortFilterProxyModel() {
  setSourceModel(&RecentSortedTransactionsModel::instance());
  setDynamicSortFilter(true);
  connect(sourceModel(), &QAbstractItemModel::rowsInserted, this, &RecentTransactionsModel::invalidateFilter);
}

RecentTransactionsModel::~RecentTransactionsModel() {
}

int RecentTransactionsModel::columnCount(const QModelIndex& _parent) const {
  return 1;
}

QVariant RecentTransactionsModel::data(const QModelIndex& _index, int _role) const {
  if(_role == Qt::DecorationRole) {
    return QVariant();
  }

  return QSortFilterProxyModel::data(_index, _role);
}

bool RecentTransactionsModel::filterAcceptsRow(int _sourceRow, const QModelIndex& _sourceParent) const {
  return _sourceRow < 6;
}


}
