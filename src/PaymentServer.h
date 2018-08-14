// Copyright (c) 2012-2017, The CryptoNote developers
// Copyleft (c) 2016-2018, Prosus Corp RTD
// Distributed under the MIT/X11 software license

#ifndef PAYMENTSERVER_H
#define PAYMENTSERVER_H

//
// Esta CLASE permite usar enlaces_de_pago
// del tipo "prosus:xxxxxxxxx"
//
// La estrategia es...
//
// Crear el server y registrar el evento
// cuando la aplicación es creada.
// Grabar cualquier enlace recibido en una lista.
//
// Cuando la aplicación termina de iniciar, una señal
// es enviada al slot uiReady(), el cual avisa con
// una señal receivedURL() para cualquier solicitud de
// pago que ocurra en el inicio.
// Después del inicio, receivedURL() funciona "neutral".
//
// La otra característica de esta CLASE
// es su método-estático para encontrar enlaces
// que son ejecutados desde una consola-de-comandos y,
// si el server se ejecuta desde otro proceso, enviarlo
// hacia el server original.
//

#include <QObject>
#include <QString>

class QApplication;
class QLocalServer;

class PaymentServer : public QObject
{
    Q_OBJECT

private:
    bool saveURIs;
    QLocalServer* uriServer;

public:
    // Returns true if there were URIs on the command line
    // which were successfully sent to an already-running
    // process.
    static bool ipcSendCommandLine();

    PaymentServer(QApplication* parent);

    bool eventFilter(QObject *object, QEvent *event);

public slots:
    // Signal this when the main window's UI is ready
    // to display payment requests to the user
    void uiReady();

private slots:
    void handleURIConnection();

Q_SIGNALS:
    void receivedURI(QString);

};

#endif // PAYMENTSERVER_H
