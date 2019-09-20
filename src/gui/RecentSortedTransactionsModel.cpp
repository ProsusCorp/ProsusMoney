// Copyright (c) 2012-2017, The CryptoNote developers
// Copyleft (c) 2016-2018, Prosus Corp RTD
// Distributed under the MIT/X11 software license

#include <QDateTime>

#include "RecentSortedTransactionsModel.h"
#include "TransactionsModel.h"

namespace WalletGui {

RecentSortedTransactionsModel& RecentSortedTransactionsModel::instance() {
  static RecentSortedTransactionsModel inst;
  return inst;
}

RecentSortedTransactionsModel::RecentSortedTransactionsModel() : QSortFilterProxyModel() {
  setSourceModel(&TransactionsModel::instance());
  setDynamicSortFilter(true);
  sort(TransactionsModel::COLUMN_DATE, Qt::DescendingOrder);
}

RecentSortedTransactionsModel::~RecentSortedTransactionsModel() {
}

bool RecentSortedTransactionsModel::lessThan(const QModelIndex& _left, const QModelIndex& _right) const {
  QDateTime leftDate = _left.data(TransactionsModel::ROLE_DATE).toDateTime();
  QDateTime rightDate = _right.data(TransactionsModel::ROLE_DATE).toDateTime();
  if((rightDate.isNull() || !rightDate.isValid()) && (leftDate.isNull() || !leftDate.isValid())) {
    return _left.row() < _right.row();
  }

  if(leftDate.isNull() || !leftDate.isValid()) {
    return false;
  }

  if(rightDate.isNull() || !rightDate.isValid()) {
    return true;
  }

  return leftDate < rightDate;
}

}
