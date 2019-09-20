// Copyright (c) 2012-2017, The CryptoNote developers
// Copyleft (c) 2016-2018, Prosus Corp RTD
// Distributed under the MIT/X11 software license

#pragma once

#include <QFrame>

#include <IWallet.h>
#include <IWalletLegacy.h>
#include "SendGlassFrame.h"

namespace Ui {
  class SendFrame;
}

namespace WalletGui {

class TransferFrame;
class AddressProvider;

class SendFrame : public QFrame {
  Q_OBJECT
  Q_DISABLE_COPY(SendFrame)

public:
  SendFrame(QWidget* _parent);
  ~SendFrame();

  Q_SLOT void parsePaymentRequest(QString _request);

private:
  QScopedPointer<Ui::SendFrame> m_ui;
  QList<TransferFrame*> m_transfers;
  AddressProvider* m_addressProvider;
  SendGlassFrame* m_glassFrame;

  QString remote_node_fee_address;
  quint64 remote_node_fee;
  quint64 total_amount;

  void sendTransactionCompleted(CryptoNote::TransactionId _id, bool _error, const QString& _error_text);
  void walletActualBalanceUpdated(quint64 _balance);
  void walletSynchronized(int _error, const QString& _error_text);
  void walletSynchronizationInProgress(quint64 _current, quint64 _total);
  void insertPaymentID(QString _paymentid);
  static bool isValidPaymentId(const QByteArray& _paymentIdString);
  void onAddressFound(const QString& _address);
  void reset();

  Q_SLOT void addRecipientClicked();
  Q_SLOT void clearAllClicked();
  Q_SLOT void mixinValueChanged(int _value);
  Q_SLOT void amountValueChange();
  Q_SLOT void sendClicked();
  Q_SLOT void openUriClicked();
  Q_SLOT void generatePaymentIdClicked();

Q_SIGNALS:
  void uriOpenSignal();

};

}
