// Copyright (c) 2012-2017, The CryptoNote developers
// Copyleft (c) 2016-2018, Prosus Corp RTD
// Distributed under the MIT/X11 software license

#pragma once

#include <QLabel>
#include <QTimer>

namespace WalletGui {

class AnimatedLabel : public QLabel {
  Q_OBJECT
  Q_DISABLE_COPY(AnimatedLabel)

public:
  AnimatedLabel(QWidget* _parent);
  ~AnimatedLabel();

  void setSprite(const QPixmap& _sprite_pixmap, const QSize& _frame_size, quint32 _vertical_space, quint32 _frequency);
  void startAnimation();
  void stopAnimation();

private:
  QPixmap m_spritePixmap;
  QSize m_spriteFrameSize;
  quint32 m_spriteVerticalSpace;
  QTimer m_animationTimer;
  QRect m_frameRect;

  void timeout();
};

}
