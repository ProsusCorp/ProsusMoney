// Copyright (c) 2012-2017, The CryptoNote developers
// Copyleft (c) 2016-2018, Prosus Corp RTD
// Distributed under the MIT/X11 software license

#pragma once

#include <QDateTime>
#include <QSortFilterProxyModel>

namespace WalletGui {

class SortedAddressBookModel : public QSortFilterProxyModel {
  Q_OBJECT
  Q_DISABLE_COPY(SortedAddressBookModel)

public:
  static SortedAddressBookModel& instance();
  void setSearchFor(const QString &searchstring);

protected:
  bool filterAcceptsRow(int _row, const QModelIndex &_parent) const Q_DECL_OVERRIDE;

private:
  SortedAddressBookModel();
  ~SortedAddressBookModel();

  QString searchstring;
};

}
