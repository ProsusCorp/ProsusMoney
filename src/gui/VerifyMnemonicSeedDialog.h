// Copyright (c) 2012-2017, The CryptoNote developers
// Copyleft (c) 2016-2018, Prosus Corp RTD
// Distributed under the MIT/X11 software license

#include <QDialog>

namespace Ui {
class VerifyMnemonicSeedDialog;
}

namespace WalletGui {

class VerifyMnemonicSeedDialog : public QDialog {
    Q_OBJECT

public:
    VerifyMnemonicSeedDialog(QWidget * _parent);
    void walletClosed();
    ~VerifyMnemonicSeedDialog();

private:
    QScopedPointer<Ui::VerifyMnemonicSeedDialog> m_ui;
    int wordCount = 0;
    bool m_seedsMatch = false;

    QString getLanguageName();
    void initLanguages();

    Q_SLOT void onTextChanged();
    Q_SLOT void languageChanged();
    Q_SLOT void reject();


};

}
