// Copyright (c) 2012-2017, The CryptoNote developers
// Copyleft (c) 2016-2018, Prosus Corp RTD
// Distributed under the MIT/X11 software license

#pragma once

#include "GlassFrame.h"

namespace WalletGui {

class SendGlassFrame : public GlassFrame {
  Q_OBJECT
  Q_DISABLE_COPY(SendGlassFrame)

public:
  explicit SendGlassFrame(QWidget* _parent);
  ~SendGlassFrame();

  void updateSynchronizationState(quint32 _current, quint32 _total);

protected:
  void paintEvent(QPaintEvent* _event) override;

private:
  quint64 m_currentHeight;
  quint64 m_totalHeight;
  QPixmap m_pixmapBuffer;
  QString m_lastThemeName;

  void paintInBuffer();
  void drawProgressGraph(QPainter &_painter);
  void drawProgressLabel(QPainter &_painter);
  void drawProgressValue(QPainter &_painter);
};

}
