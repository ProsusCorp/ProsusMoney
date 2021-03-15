// Copyright (c) 2012-2017, The CryptoNote developers
// Copyleft (c) 2016-2018, Prosus Corp RTD
// Distributed under the MIT/X11 software license

#pragma once

#include <QDialog>

namespace Ui {
class RestoreFromMnemonicSeedDialog;
}

namespace WalletGui {

class RestoreFromMnemonicSeedDialog : public QDialog {
  Q_OBJECT

public:
  RestoreFromMnemonicSeedDialog(QWidget* _parent);
  ~RestoreFromMnemonicSeedDialog();

  QString getSeedString() const;
  QString getFilePath() const;

private:
  QScopedPointer<Ui::RestoreFromMnemonicSeedDialog> m_ui;

  int wordCount = 0;

  Q_SLOT void selectPathClicked();
  Q_SLOT void onTextChanged();
};

}
