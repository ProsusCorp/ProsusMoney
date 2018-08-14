// Copyright (c) 2012-2017, The CryptoNote developers
// Copyleft (c) 2016-2018, Prosus Corp RTD
// Distributed under the MIT/X11 software license

#pragma once

#include <QDialog>

namespace Ui {
class PasswordDialog;
}

namespace WalletGui {

class PasswordDialog : public QDialog {
  Q_OBJECT
  Q_DISABLE_COPY(PasswordDialog)

public:
  PasswordDialog(bool _error, QWidget* _parent);
  ~PasswordDialog();

  QString getPassword() const;

private:
  QScopedPointer<Ui::PasswordDialog> m_ui;
};

}
