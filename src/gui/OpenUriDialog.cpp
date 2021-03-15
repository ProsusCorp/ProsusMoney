// Copyright (c) 2012-2017, The CryptoNote developers
// Copyleft (c) 2016-2018, Prosus Corp RTD
// Distributed under the MIT/X11 software license

#include "OpenUriDialog.h"

#include "ui_openuridialog.h"

namespace WalletGui {

OpenUriDialog::OpenUriDialog(QWidget* _parent) : QDialog(_parent), m_ui(new Ui::OpenUriDialog) {
  m_ui->setupUi(this);
  m_ui->m_uriEdit->setPlaceholderText("prosus:");
}

OpenUriDialog::~OpenUriDialog() {
}

QString OpenUriDialog::getURI() const {
  return m_ui->m_uriEdit->text().trimmed();
}

}
