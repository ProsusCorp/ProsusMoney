// Copyright (c) 2012-2017, The CryptoNote developers
// Copyleft (c) 2016-2018, Prosus Corp RTD
// Distributed under the MIT/X11 software license

#pragma once

#include <QEvent>

namespace WalletGui
{
    enum class WalletEventType : quint32 {
        ShowMessage = QEvent::User
    };

    class ShowMessageEvent : public QEvent {
      Q_DISABLE_COPY(ShowMessageEvent)

    public:
        ShowMessageEvent(const QString &_messageText, QtMsgType _messageType) : QEvent(static_cast<QEvent::Type>(WalletEventType::ShowMessage)),
            m_messageText(_messageText), m_messgaeType(_messageType) {
        }

        QString messageText() const {
          return m_messageText;
        }

        QtMsgType messageType() const {
          return m_messgaeType;
        }

    private:
        QString m_messageText;
        QtMsgType m_messgaeType;
    };

}
