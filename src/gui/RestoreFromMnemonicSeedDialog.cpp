// Copyright (c) 2012-2017, The CryptoNote developers
// Copyleft (c) 2016-2018, Prosus Corp RTD
// Distributed under the MIT/X11 software license

#include <QApplication>
#include <QFileDialog>
#include <QStandardPaths>
#include "RestoreFromMnemonicSeedDialog.h"
#include "ui_restorefrommnemonicseeddialog.h"

namespace WalletGui {

RestoreFromMnemonicSeedDialog::RestoreFromMnemonicSeedDialog(QWidget* _parent) : QDialog(_parent), m_ui(new Ui::RestoreFromMnemonicSeedDialog) {
  m_ui->setupUi(this);
}

RestoreFromMnemonicSeedDialog::~RestoreFromMnemonicSeedDialog() {
}

QString RestoreFromMnemonicSeedDialog::getSeedString() const {
  return m_ui->m_seedEdit->toPlainText().trimmed();
}

QString RestoreFromMnemonicSeedDialog::getFilePath() const {
  return m_ui->m_pathEdit->text().trimmed();
}

void RestoreFromMnemonicSeedDialog::selectPathClicked() {
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

void RestoreFromMnemonicSeedDialog::onTextChanged() {
  wordCount = m_ui->m_seedEdit->toPlainText().split(QRegExp("(\\s|\\n|\\r)+")
                                                  , QString::SkipEmptyParts).count();
  if(wordCount != 25) {
    m_ui->m_okButton->setEnabled(false);
    m_ui->m_errorLabel->setText(QString::number(wordCount));
    m_ui->m_errorLabel->setStyleSheet("QLabel { color : red; }");
  }
  if(wordCount == 25) {
    m_ui->m_okButton->setEnabled(true);
    m_ui->m_errorLabel->setText("OK");
    m_ui->m_errorLabel->setStyleSheet("QLabel { color : green; }");
  }
}

}
