// Copyright (c) 2012-2017, The CryptoNote developers
// Copyleft (c) 2016-2018, Prosus Corp RTD
// Distributed under the MIT/X11 software license

#include "AnimatedLabel.h"

namespace WalletGui {

AnimatedLabel::AnimatedLabel(QWidget* _parent) : QLabel(_parent), m_spriteVerticalSpace(0) {
  connect(&m_animationTimer, &QTimer::timeout, this, &AnimatedLabel::timeout);
}

AnimatedLabel::~AnimatedLabel() {
}

void AnimatedLabel::setSprite(const QPixmap& _spritePixmap, const QSize& _frameSize, quint32 _verticalSpace, quint32 _frequency) {
  m_spritePixmap = _spritePixmap;
  m_spriteFrameSize = _frameSize;
  m_spriteVerticalSpace = _verticalSpace;
  m_animationTimer.setInterval(1000 / _frequency);
  m_frameRect.setTopLeft(QPoint(0, 0));
  m_frameRect.setBottomRight(m_frameRect.topLeft() += QPoint(_frameSize.width(), _frameSize.height()));
}

void AnimatedLabel::startAnimation() {
  if (m_animationTimer.isActive()) {
    return;
  }

  m_animationTimer.start();
}

void AnimatedLabel::stopAnimation() {
  m_animationTimer.stop();
}

void AnimatedLabel::timeout() {
  setPixmap(m_spritePixmap.copy(m_frameRect));
  m_frameRect.translate(QPoint(0, m_spriteVerticalSpace + m_spriteFrameSize.height()));
  if (m_frameRect.bottom() >= m_spritePixmap.height()) {
    m_frameRect.moveTop(0);
  }
}

}
