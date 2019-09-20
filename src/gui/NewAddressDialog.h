// Copyright (c) 2012-2017, The CryptoNote developers
// Copyleft (c) 2016-2018, Prosus Corp RTD
// Distributed under the MIT/X11 software license

#pragma once

#include <QDialog>

namespace Ui {
class NewAddressDialog;
}

namespace WalletGui {

class NewAddressDialog : public QDialog {
  Q_OBJECT
  Q_DISABLE_COPY(NewAddressDialog)

public:
  NewAddressDialog(QWidget* _parent);
  ~NewAddressDialog();

  QString getAddress() const;
  QString getLabel() const;
  QString getPaymentID() const;

  void setEditLabel(QString label);
  void setEditAddress(QString address);
  void setEditPaymentId(QString paymentid);

private:
  QScopedPointer<Ui::NewAddressDialog> m_ui;
};

}
