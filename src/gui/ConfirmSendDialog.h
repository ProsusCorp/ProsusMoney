// Copyright (c) 2012-2017, The CryptoNote developers
// Copyleft (c) 2016-2018, Prosus Corp RTD
// Distributed under the MIT/X11 software license

#pragma once

#include <QDialog>

namespace Ui {
class ConfirmSendDialog;
}

namespace WalletGui {

class ConfirmSendDialog : public QDialog {
  Q_OBJECT

public:
  ConfirmSendDialog(QWidget* _parent);
  ~ConfirmSendDialog();

  void showPaymentDetails(quint64 _total);
  void showPaymentId(QString _paymentid);
  void confirmNoPaymentId();

private:
  QScopedPointer<Ui::ConfirmSendDialog> m_ui;
};

}
