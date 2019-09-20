// Copyright (c) 2012-2017, The CryptoNote developers
// Copyleft (c) 2016-2018, Prosus Corp RTD
// Distributed under the MIT/X11 software license

#include <QApplication>
#include <QPainter>
#include <QScreen>

#include "SendGlassFrame.h"
#include "Settings.h"

namespace WalletGui {

namespace {

const char SEND_GLASS_FRAME_STYLE_SHEET_TEMPLATE[] =
  "WalletGui--SendGlassFrame {"
    "border: none;"
    "background-color: #eaCADEF7"
  "}";

const char SEND_FRAME_STYLE_SHEET[] =
  "WalletGui--SendFrame {"
    "background-color: #ffffff;"
    "border: none;"
  "}"

  "WalletGui--SendFrame #m_sendScrollarea {"
    "background-color: %backgroundColorGray%;"
    "border: none;"
    "border-bottom: 1px solid %borderColor%;"
  "}"

  "WalletGui--SendFrame #m_sendScrollarea QScrollBar:vertical {"
    "margin-top: 0px;"
    "border-top: none;"
  "}"

  "WalletGui--SendFrame #scrollAreaWidgetContents {"
    "background-color: #ffffff;"
    "border: none;"
  "}"

  "WalletGui--SendFrame #m_sendFeeFrame {"
    "border: none;"
    "border-top: 1px solid %borderColor%;"
    "border-bottom: 1px solid %borderColor%;"
  "}";

const quint32 MAX_QUINT32 = std::numeric_limits<quint32>::max();

}

SendGlassFrame::SendGlassFrame(QWidget* _parent) : GlassFrame(_parent), m_currentHeight(MAX_QUINT32), m_totalHeight(MAX_QUINT32),
  m_pixmapBuffer(QSize(340, 340) * QApplication::primaryScreen()->devicePixelRatio()),
  m_lastThemeName(Settings::instance().getCurrentTheme()) {
  setStyleSheet(SEND_GLASS_FRAME_STYLE_SHEET_TEMPLATE);
}

SendGlassFrame::~SendGlassFrame() {
}

void SendGlassFrame::paintEvent(QPaintEvent* _event) {
  if (m_lastThemeName.compare(Settings::instance().getCurrentTheme())) {
    paintInBuffer();
    m_lastThemeName = Settings::instance().getCurrentTheme();
  }

  GlassFrame::paintEvent(_event);
  QRect image_rect(m_pixmapBuffer.rect());
  int left = rect().left() + (rect().width() - m_pixmapBuffer.width()) / 2;
  int top = rect().top() + (rect().height() - m_pixmapBuffer.height()) / 2;
  image_rect.moveTopLeft(QPoint(left, top));
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);
  painter.drawPixmap(image_rect, m_pixmapBuffer);
}

void SendGlassFrame::updateSynchronizationState(quint32 _current, quint32 _total) {
  if (m_currentHeight != _current || m_totalHeight != _total) {
    m_currentHeight = _current;
    m_totalHeight = _total;
    paintInBuffer();
    update();
  }
}

void SendGlassFrame::paintInBuffer() {
  m_pixmapBuffer.fill(QColor("#00ffffff"));

  QPainter painter(&m_pixmapBuffer);
  painter.setRenderHint(QPainter::Antialiasing);

  drawProgressGraph(painter);
  drawProgressLabel(painter);
  drawProgressValue(painter);
}

void SendGlassFrame::drawProgressGraph(QPainter &_painter) {
  const int degree = 16;
  const int startAngle = 90 * degree;
  const int endAngle = -(360 * degree) * (static_cast<qreal>(m_currentHeight) / m_totalHeight);
  QRect rect = m_pixmapBuffer.rect().marginsRemoved(QMargins(5, 5, 5, 5));

  QPen pen;
  pen.setWidth(10);

  pen.setColor(QColor("#e6e6e6"));
  _painter.setPen(pen);
  _painter.drawArc(rect, 0, 360 * degree);

  pen.setColor(QColor("#30466c"));
  _painter.setPen(pen);
  _painter.drawArc(rect, startAngle, endAngle);
}

void SendGlassFrame::drawProgressLabel(QPainter &_painter) {
  QFont font;
  font.setBold(true);
  font.setPixelSize(14);
  QString msg = tr("You will be able to send xPR \n when the wallet is synchronized");
  QFontMetrics fm(font);
  QRect messageRect = fm.boundingRect(QRect(), Qt::AlignCenter, msg);
  messageRect.moveCenter(QPoint(m_pixmapBuffer.width() / 2, 163));

  QPen pen;
  pen.setColor(QColor("#364a6d"));
  _painter.setPen(pen);
  _painter.setFont(font);
  _painter.setRenderHint(QPainter::TextAntialiasing);
  _painter.drawText(messageRect, Qt::AlignCenter, msg);
}

void SendGlassFrame::drawProgressValue(QPainter &_painter) {
  QFont font;
  font.setBold(false);
  font.setPixelSize(10);
  QString msg = QString("%1 %2/%3").arg(tr("Synchronizing")).arg(m_currentHeight).arg(m_totalHeight);
  QFontMetrics fm(font);
  QRect messageRect = fm.boundingRect(QRect(), Qt::AlignCenter, msg);
  messageRect.moveCenter(QPoint(m_pixmapBuffer.width() / 2, 198));

  QPen pen;
  pen.setColor(QColor("#364a6d"));
  _painter.setPen(pen);
  _painter.setFont(font);
  _painter.drawText(messageRect, Qt::AlignCenter, msg);
}

}
