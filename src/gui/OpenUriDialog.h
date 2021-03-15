// Copyright (c) 2012-2017, The CryptoNote developers
// Copyleft (c) 2016-2018, Prosus Corp RTD
// Distributed under the MIT/X11 software license

#pragma once

#include <QDialog>

namespace Ui {
class OpenUriDialog;
}

namespace WalletGui {

class OpenUriDialog : public QDialog {
  Q_OBJECT

public:
  OpenUriDialog(QWidget* _parent);
  ~OpenUriDialog();

  QString getURI() const;

private:
  QScopedPointer<Ui::OpenUriDialog> m_ui;
};

}
