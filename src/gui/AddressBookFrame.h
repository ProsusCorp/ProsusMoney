// Copyright (c) 2012-2017, The CryptoNote developers
// Copyleft (c) 2016-2018, Prosus Corp RTD
// Distributed under the MIT/X11 software license

#pragma once

#include <QWidget>
#include <QFrame>
#include <QMenu>
#include <QStyledItemDelegate>

namespace Ui {
class AddressBookFrame;
}

namespace WalletGui {

class AddressBookFrame : public QFrame {
  Q_OBJECT
  Q_DISABLE_COPY(AddressBookFrame)

public:
  AddressBookFrame(QWidget* _parent);
  ~AddressBookFrame();
  QModelIndex index;

public slots:
  void onCustomContextMenu(const QPoint &point);

public Q_SLOTS:
  void addClicked();
  void editClicked();
  void copyClicked();
  void copyPaymentIdClicked();
  void copyLabelClicked();
  void deleteClicked();

private:
  QScopedPointer<Ui::AddressBookFrame> m_ui;

  static bool isValidPaymentId(const QByteArray& _paymentIdString);
  QMenu* contextMenu;

  Q_SLOT void currentAddressChanged(const QModelIndex& _index);
};

}
