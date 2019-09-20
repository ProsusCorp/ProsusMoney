// Copyright (c) 2012-2017, The CryptoNote developers
// Copyleft (c) 2016-2018, Prosus Corp RTD
// Distributed under the MIT/X11 software license

#include "NewNodeDialog.h"

#include "ui_newnodedialog.h"

namespace WalletGui {

NewNodeDialog::NewNodeDialog(QWidget* _parent) : QDialog(_parent), m_ui(new Ui::NewNodeDialog) {
  m_ui->setupUi(this);
}

NewNodeDialog::~NewNodeDialog() {
}

QString NewNodeDialog::getHost() const {
  return m_ui->m_hostEdit->text().trimmed();
}

quint16 NewNodeDialog::getPort() const {
  return m_ui->m_portSpin->value();
}

}
