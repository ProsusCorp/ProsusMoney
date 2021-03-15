// Copyright (c) 2012-2017, The CryptoNote developers
// Copyleft (c) 2016-2018, Prosus Corp RTD
// Distributed under the MIT/X11 software license

#pragma once

#include <QDialog>

namespace Ui {
class ImportTrackingKeyDialog;
}

namespace WalletGui {

class ImportTrackingKeyDialog : public QDialog {
  Q_OBJECT

public:
  ImportTrackingKeyDialog(QWidget* _parent);
  ~ImportTrackingKeyDialog();

  QString getKeyString() const;
  QString getFilePath() const;

private:
  QScopedPointer<Ui::ImportTrackingKeyDialog> m_ui;

  Q_SLOT void selectPathClicked();
};

}
