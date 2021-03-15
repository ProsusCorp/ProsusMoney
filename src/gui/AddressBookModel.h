// Copyright (c) 2012-2017, The CryptoNote developers
// Copyleft (c) 2016-2018, Prosus Corp RTD
// Distributed under the MIT/X11 software license

#pragma once

#include <QAbstractItemModel>
#include <QJsonArray>

namespace WalletGui {
  
class AddressBookModel : public QAbstractItemModel
{
  Q_OBJECT
  Q_DISABLE_COPY(AddressBookModel)

public:
  enum Columns {COLUMN_LABEL = 0, COLUMN_ADDRESS, COLUMN_PAYMENTID};
  enum Roles { ROLE_LABEL = Qt::UserRole, ROLE_ADDRESS, ROLE_PAYMENTID };

  static AddressBookModel& instance();
  int columnCount(const QModelIndex& _parent = QModelIndex()) const Q_DECL_OVERRIDE;
  QVariant data(const QModelIndex& _index, int _role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
  Qt::ItemFlags flags(const QModelIndex& _index) const Q_DECL_OVERRIDE;
  QVariant headerData(int _section, Qt::Orientation _orientation, int _role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
  QModelIndex index(int _row, int _column, const QModelIndex& _parent = QModelIndex()) const Q_DECL_OVERRIDE;
  QModelIndex	parent(const QModelIndex& _index) const Q_DECL_OVERRIDE;
  int rowCount(const QModelIndex& _parent = QModelIndex()) const Q_DECL_OVERRIDE;

  void addAddress(const QString& _label, const QString& _address, const QString& _paymentid);
  void removeAddress(quint32 _row);

  const QModelIndex indexFromContact(const QString& searchstring, const int& column);

private:
  QJsonArray m_addressBook;

  AddressBookModel();
  ~AddressBookModel();

  void reset();
  void saveAddressBook();
  void walletInitCompleted(int _error, const QString& _error_text);
};

}
