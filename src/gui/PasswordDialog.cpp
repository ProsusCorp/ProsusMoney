// Copyright (c) 2012-2017, The CryptoNote developers
// Copyleft (c) 2016-2018, Prosus Corp RTD
// Distributed under the MIT/X11 software license

#include "PasswordDialog.h"

#include "ui_passworddialog.h"

namespace WalletGui {

PasswordDialog::PasswordDialog(bool _error, QWidget* _parent) : QDialog(_parent), m_ui(new Ui::PasswordDialog) {
  m_ui->setupUi(this);
  if (!_error) {
    m_ui->m_errorLabel->hide();
  }

  adjustSize();
}

PasswordDialog::~PasswordDialog() {
}

QString PasswordDialog::getPassword() const {
  return m_ui->m_passwordEdit->text();
}
  
}
