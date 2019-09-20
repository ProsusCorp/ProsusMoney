// Copyright (c) 2012-2017, The CryptoNote developers
// Copyleft (c) 2016-2018, Prosus Corp RTD
// Distributed under the MIT/X11 software license

#include "AddressBookDialog.h"
#include "AddressBookModel.h"

#include "ui_addressbookdialog.h"

namespace WalletGui {

AddressBookDialog::AddressBookDialog(QWidget* _parent) : QDialog(_parent), m_ui(new Ui::AddressBookDialog) {
  m_ui->setupUi(this);
  m_ui->m_addressBookView->setModel(&AddressBookModel::instance());
  if (AddressBookModel::instance().rowCount() > 0) {
    m_ui->m_addressBookView->setCurrentIndex(AddressBookModel::instance().index(0, 0));
  } 
}

AddressBookDialog::~AddressBookDialog() {
}

QString AddressBookDialog::getAddress() const {
  return m_ui->m_addressBookView->currentIndex().data(AddressBookModel::ROLE_ADDRESS).toString();
}

QString AddressBookDialog::getPaymentID() const {
  return m_ui->m_addressBookView->currentIndex().data(AddressBookModel::ROLE_PAYMENTID).toString();
}

}
