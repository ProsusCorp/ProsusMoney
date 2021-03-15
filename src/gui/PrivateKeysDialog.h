// Copyright (c) 2012-2017, The CryptoNote developers
// Copyleft (c) 2016-2018, Prosus Corp RTD
// Distributed under the MIT/X11 software license

#include <QDialog>

namespace Ui {
class PrivateKeysDialog;
}

namespace WalletGui {

class PrivateKeysDialog : public QDialog {
    Q_OBJECT

public:
    PrivateKeysDialog(QWidget * _parent);
    void walletOpened();
    void walletClosed();
    ~PrivateKeysDialog();

private:
    Q_SLOT void copyKey();

    QScopedPointer<Ui::PrivateKeysDialog> m_ui;
};

}
