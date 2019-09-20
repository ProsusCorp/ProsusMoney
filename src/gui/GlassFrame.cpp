// Copyright (c) 2012-2017, The CryptoNote developers
// Copyleft (c) 2016-2018, Prosus Corp RTD
// Distributed under the MIT/X11 software license

#include <QEvent>

#include "GlassFrame.h"

namespace WalletGui {

GlassFrame::GlassFrame(QWidget* _parent) : QFrame(_parent) {
  d_ptr->q_ptr = this;
}

GlassFrame::~GlassFrame() {
}

void GlassFrame::install(QWidget* _parent) {
  if (parent() == _parent) {
    return;
  }

  remove();
  setParent(_parent);
  _parent->installEventFilter(this);
  show();
  QEvent event(QEvent::Resize);
  eventFilter(0, &event);
}

void GlassFrame::remove() {
  if (parentWidget() != nullptr) {
    parentWidget()->removeEventFilter(this);
    hide();
    setParent(nullptr);
  }
}

bool GlassFrame::eventFilter(QObject* _object, QEvent* _event) {
  if (_event->type() == QEvent::Show || _event->type() == QEvent::Paint || _event->type() == QEvent::Resize) {
    resize(parentWidget()->size());
    move(0, 0);
    return true;
  }

  if (qobject_cast<QWidget*>(parent())->isVisible()) {
    setFocus();
  }

  return false;
}

}
