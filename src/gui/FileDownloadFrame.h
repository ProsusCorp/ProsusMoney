// Copyright (c) 2012-2017, The CryptoNote developers
// Copyleft (c) 2016-2018, Prosus Corp RTD
// Distributed under the MIT/X11 software license

#pragma once

#include <QFrame>

#include <IWallet.h>
#include <IWalletLegacy.h>
#include "SendGlassFrame.h"
#include "Wallet/WalletGreen.h"

namespace Ui {
    class FileDownloadFrame;
}

namespace WalletGui {

    class TransferFrame;
    class AddressProvider;

    class FileDownloadFrame : public QFrame {
    Q_OBJECT
        Q_DISABLE_COPY(FileDownloadFrame)

    public:
        FileDownloadFrame(QWidget* _parent);
        ~FileDownloadFrame();

    private:
        QScopedPointer<Ui::FileDownloadFrame> m_ui;
        QList<TransferFrame*> m_transfers;
        SendGlassFrame* m_glassFrame;

        void readKeys(QString trackingKey, CryptoNote::AccountKeys &keys);

        Q_SLOT void downloadClicked();

    Q_SIGNALS:
        void uriOpenSignal();

    };

}
