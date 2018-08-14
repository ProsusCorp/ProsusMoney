// Copyright (c) 2012-2017, The CryptoNote developers
// Copyleft (c) 2016-2018, Prosus Corp RTD
// Distributed under the MIT/X11 software license

#pragma once

#include <QDialog>

namespace Ui {
class NewPoolDialog;
}

namespace WalletGui {

class NewPoolDialog : public QDialog {
  Q_OBJECT

public:
  NewPoolDialog(QWidget* _parent);
  ~NewPoolDialog();

  QString getHost() const;
  quint16 getPort() const;

private:
  QScopedPointer<Ui::NewPoolDialog> m_ui;
};

}
