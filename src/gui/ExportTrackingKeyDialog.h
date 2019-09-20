// Copyright (c) 2012-2017, The CryptoNote developers
// Copyleft (c) 2016-2018, Prosus Corp RTD
// Distributed under the MIT/X11 software license

#include <QDialog>

namespace Ui {
class ExportTrackingKeyDialog;
}

namespace WalletGui {

class ExportTrackingKeyDialog : public QDialog {
    Q_OBJECT

public:
    ExportTrackingKeyDialog(QWidget * _parent);
    void walletOpened();
    void walletClosed();
    ~ExportTrackingKeyDialog();

private:
    QString trackingWalletKeys;
    Q_SLOT void copyKey();
    Q_SLOT void saveKeyToFile();

    QScopedPointer<Ui::ExportTrackingKeyDialog> m_ui;
};

}
