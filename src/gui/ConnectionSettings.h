// Copyright (c) 2012-2017, The CryptoNote developers
// Copyleft (c) 2016-2018, Prosus Corp RTD
// Distributed under the MIT/X11 software license

#pragma  once

#include <QDialog>

namespace Ui {
class ConnectionSettingsDialog;
}

namespace WalletGui {

class NodeModel;

class ConnectionSettingsDialog : public QDialog {
  Q_OBJECT
  Q_DISABLE_COPY(ConnectionSettingsDialog)

public:
  ConnectionSettingsDialog(QWidget* _parent);
  ~ConnectionSettingsDialog();

  QString setConnectionMode() const;
  quint16 setLocalDaemonPort() const;
  QString setRemoteNode() const;
  void initConnectionSettings();

private:
  QScopedPointer<Ui::ConnectionSettingsDialog> m_ui;
  NodeModel* m_nodeModel;

  Q_SLOT void addNodeClicked();
  Q_SLOT void removeNodeClicked();

};

}

