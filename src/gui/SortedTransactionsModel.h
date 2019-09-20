// Copyright (c) 2012-2017, The CryptoNote developers
// Copyleft (c) 2016-2018, Prosus Corp RTD
// Distributed under the MIT/X11 software license

#pragma once

#include <QDateTime>
#include <QSortFilterProxyModel>

namespace WalletGui {

class SortedTransactionsModel : public QSortFilterProxyModel {
  Q_OBJECT
  Q_DISABLE_COPY(SortedTransactionsModel)

public:
    /** Earliest date that can be represented (far in the past) */
    static const QDateTime MIN_DATE; // = QDateTime::fromTime_t(0);
    /** Last date that can be represented (far in the future) */
    static const QDateTime MAX_DATE; // = QDateTime::fromTime_t(0xFFFFFFFF);

  static SortedTransactionsModel& instance();
  void setDateRange(const QDateTime &from, const QDateTime &to);
  void setTxType(const int type);
  void setSearchFor(const QString &searchstring);

protected:
  bool lessThan(const QModelIndex& _left, const QModelIndex& _right) const Q_DECL_OVERRIDE;
  bool filterAcceptsRow(int _row, const QModelIndex &_parent) const Q_DECL_OVERRIDE;

private:
  SortedTransactionsModel();
  ~SortedTransactionsModel();

  bool dateInRange(const QDate &date) const;

  QDateTime dateFrom = MIN_DATE;
  QDateTime dateTo = MAX_DATE;
  QString searchstring;
  int selectedtxtype = 4;

};

}
