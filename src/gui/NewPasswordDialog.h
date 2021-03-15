// Copyright (c) 2012-2017, The CryptoNote developers
// Copyleft (c) 2016-2018, Prosus Corp RTD
// Distributed under the MIT/X11 software license

#pragma once

#include <QDialog>

namespace Ui {
class NewPasswordDialog;
}

namespace WalletGui {
  
class NewPasswordDialog : public QDialog {
  Q_OBJECT
  Q_DISABLE_COPY(NewPasswordDialog)

public:
  NewPasswordDialog(QWidget* _parent);
  ~NewPasswordDialog();

  QString getPassword() const;

private:
  QScopedPointer<Ui::NewPasswordDialog> m_ui;

  Q_SLOT void checkPassword(const QString& _password);
};

}
