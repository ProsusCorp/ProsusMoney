// Copyright (c) 2012-2017, The CryptoNote developers
// Copyleft (c) 2016-2018, Prosus Corp RTD
// Distributed under the MIT/X11 software license

#pragma once

#include <QDialog>

namespace Ui {
class NewNodeDialog;
}

namespace WalletGui {

class NewNodeDialog : public QDialog {
  Q_OBJECT

public:
  NewNodeDialog(QWidget* _parent);
  ~NewNodeDialog();

  QString getHost() const;
  quint16 getPort() const;

private:
  QScopedPointer<Ui::NewNodeDialog> m_ui;
};

}
