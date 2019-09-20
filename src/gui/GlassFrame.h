// Copyright (c) 2012-2017, The CryptoNote developers
// Copyleft (c) 2016-2018, Prosus Corp RTD
// Distributed under the MIT/X11 software license

#pragma once

#include <QFrame>

namespace WalletGui {

class GlassFrame : public QFrame {
  Q_OBJECT
  Q_DISABLE_COPY(GlassFrame)

public:
  explicit GlassFrame(QWidget* _parent);
  virtual ~GlassFrame();

  virtual void install(QWidget* _parent);
  virtual void remove();

protected:
  bool eventFilter(QObject* _object, QEvent* _event) override;
};

}
