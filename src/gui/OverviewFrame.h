// Copyright (c) 2012-2017, The CryptoNote developers
// Copyleft (c) 2016-2018, Prosus Corp RTD
// Distributed under the MIT/X11 software license

#pragma once

#include <QFrame>
#include <QStyledItemDelegate>

namespace Ui {
class OverviewFrame;
}

namespace WalletGui {

class RecentTransactionsModel;

class OverviewFrame : public QFrame {
  Q_OBJECT
  Q_DISABLE_COPY(OverviewFrame)

public:
  OverviewFrame(QWidget* _parent);
  ~OverviewFrame();

private:
  QScopedPointer<Ui::OverviewFrame> m_ui;
  QSharedPointer<RecentTransactionsModel> m_transactionModel;

  void transactionsInserted(const QModelIndex& _parent, int _first, int _last);
  void transactionsRemoved(const QModelIndex& _parent, int _first, int _last);
  void layoutChanged();
  void updateActualBalance(quint64 _balance);
  void updatePendingBalance(quint64 _balance);
  void reset();
};

}
