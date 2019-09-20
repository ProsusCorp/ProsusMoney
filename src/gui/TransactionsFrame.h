// Copyright (c) 2012-2017, The CryptoNote developers
// Copyleft (c) 2016-2018, Prosus Corp RTD
// Distributed under the MIT/X11 software license

#pragma once

#include <QWidget>
#include <QFrame>
#include <QMenu>

#include <QStyledItemDelegate>

namespace Ui {
class TransactionsFrame;
}

QT_BEGIN_NAMESPACE
class QDateTimeEdit;
QT_END_NAMESPACE

namespace WalletGui {

class TransactionsListModel;

class TransactionsFrame : public QFrame {
  Q_OBJECT
  Q_DISABLE_COPY(TransactionsFrame)

public:
  TransactionsFrame(QWidget* _parent);
  ~TransactionsFrame();
  QModelIndex index;

  // Date ranges for filter
      enum DateEnum
      {
          Unconfirmed,
          All,
          Today,
          ThisWeek,
          ThisMonth,
          LastMonth,
          ThisYear,
          Range
      };

      enum TypeEnum
      {
          AllTypes,
          Incoming,
          Outgoing,
          Mining,
          InOut
      };

  void scrollToTransaction(const QModelIndex& _index);

public slots:
  void onCustomContextMenu(const QPoint &point);
  void chooseDate(int idx);
  void chooseType(int idx);
  void changedSearchFor(const QString &searchstring);

public Q_SLOTS:
  void copyTxHash();
  void copyAmount();
  void copyPaymentID();
  void showTxDetails();
  void computeSelected();
  void showTransactionDetails(const QModelIndex& _index);
  void walletClosed();

private:
  QScopedPointer<Ui::TransactionsFrame> m_ui;
  QScopedPointer<TransactionsListModel> m_transactionsModel;
  QMenu* contextMenu;
  QFrame *dateRangeWidget;
  QDateTimeEdit *dateFrom;
  QDateTimeEdit *dateTo;
  QWidget *createDateRangeWidget();
  QString formatAmount(int64_t _amount) const;

  void includeUnconfirmed();

  Q_SLOT void exportToCsv();

private slots:
  void dateRangeChanged();
  void resetFilterClicked();

};

}
