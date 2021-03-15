// Copyright (c) 2012-2017, The CryptoNote developers
// Copyleft (c) 2016-2018, Prosus Corp RTD
// Distributed under the MIT/X11 software license

#pragma once

#include <QObject>
#include <QReadWriteLock>

#include <atomic>

#include "Worker.h"

namespace WalletGui {

class StratumClient;

class Miner : public QObject {
  Q_OBJECT

public:
  Miner(QObject* _parent, const QString& _host, quint16 _port, const QString& _login, const QString& _password = "x");
  ~Miner();

  void start(quint32 _coreCount);
  void stop();
  bool isRunning() const;

  QString getPoolHost() const;
  quint16 getPoolPort() const;
  quint32 getHashRate() const;

protected:
  void timerEvent(QTimerEvent* _event) Q_DECL_OVERRIDE;

private:
  Job m_currentJob;
  QReadWriteLock m_jobLock;
  StratumClient* m_stratumClient;
  std::atomic<quint32> m_nonce;
  std::atomic<quint32> m_hashCounter;
  quint32 m_hashCountPerSecond;
  QList<QPair<QThread*, Worker*> > m_workerThreadList;
  int m_hashRateTimerId;

Q_SIGNALS:
  void socketErrorSignal(const QString& _errorText);
};

}
