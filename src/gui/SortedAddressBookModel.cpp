// Copyright (c) 2012-2017, The CryptoNote developers
// Copyleft (c) 2016-2018, Prosus Corp RTD
// Distributed under the MIT/X11 software license

#include <QDateTime>

#include "SortedAddressBookModel.h"
#include "AddressBookModel.h"

namespace WalletGui {

SortedAddressBookModel& SortedAddressBookModel::instance() {
  static SortedAddressBookModel inst;
  return inst;
}

SortedAddressBookModel::SortedAddressBookModel() : QSortFilterProxyModel() {
  setSourceModel(&AddressBookModel::instance());
  setDynamicSortFilter(true);
  sort(AddressBookModel::COLUMN_LABEL, Qt::DescendingOrder);
}

SortedAddressBookModel::~SortedAddressBookModel() {
}

bool SortedAddressBookModel::filterAcceptsRow(int _row, const QModelIndex &_parent) const {
  QModelIndex index0 = sourceModel()->index(_row, 0, _parent);
  QModelIndex index1 = sourceModel()->index(_row, 1, _parent);
  QModelIndex index2 = sourceModel()->index(_row, 2, _parent);

  return (sourceModel()->data(index0).toString().contains(searchstring)
       || sourceModel()->data(index1).toString().contains(searchstring)
       || sourceModel()->data(index2).toString().contains(searchstring));

  return true;
 }

void SortedAddressBookModel::setSearchFor(const QString &searchstring) {
    this->searchstring = searchstring;
    invalidateFilter();
}

}
