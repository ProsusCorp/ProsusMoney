// Copyright (c) 2012-2017, The CryptoNote developers
// Copyleft (c) 2016-2018, Prosus Corp RTD
// Distributed under the MIT/X11 software license

#include <QApplication>
#include <QFileDialog>
#include <QStandardPaths>

#include "ImportKeyDialog.h"

#include "ui_importkeydialog.h"

namespace WalletGui {

ImportKeyDialog::ImportKeyDialog(QWidget* _parent) : QDialog(_parent), m_ui(new Ui::ImportKeyDialog) {
  m_ui->setupUi(this);
}

ImportKeyDialog::~ImportKeyDialog() {
}

QString ImportKeyDialog::getKeyString() const {
  return m_ui->m_keyEdit->toPlainText().trimmed();
}

QString ImportKeyDialog::getFilePath() const {
  return m_ui->m_pathEdit->text().trimmed();
}

void ImportKeyDialog::selectPathClicked() {
  QString filePath = QFileDialog::getSaveFileName(this, tr("Wallet file"),
#ifdef Q_OS_WIN
    //QApplication::applicationDirPath(),
      QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation),
#else
    QDir::homePath(),
#endif
    tr("Wallets (*.wallet)")
    );

  if (!filePath.isEmpty() && !filePath.endsWith(".wallet")) {
    filePath.append(".wallet");
  }

  m_ui->m_pathEdit->setText(filePath);
}

}
