// Copyright (c) 2012-2017, The CryptoNote developers
// Copyleft (c) 2016-2018, Prosus Corp RTD
// Distributed under the MIT/X11 software license

#pragma once

#include <QDialog>

namespace Ui {
class ShowPaymentRequestDialog;
}

namespace WalletGui {

class ShowPaymentRequestDialog : public QDialog {
  Q_OBJECT

public:
  ShowPaymentRequestDialog(QWidget* _parent);
  ~ShowPaymentRequestDialog();

  void setData(const QString &paymentRequest);

  QString payment_request_uri;


private:
  QScopedPointer<Ui::ShowPaymentRequestDialog> m_ui;

  Q_SLOT void copyUri();
  Q_SLOT void saveUri();
  Q_SLOT void saveQRcodeToFile();

};

}
