#ifndef MSGSERVER_H
#define MSGSERVER_H

#include"ChatMsgType.h"
#include<QFile>
#include<QFileDialog>
#include<QDateTime>
#include<QDataStream>
#include<QTcpSocket>
#include<QTcpServer>
#include<QAbstractSocket>
#include<QMessageBox>
#include<QString>
#include<QByteArray>

class MsgServer : public QTcpServer
{
public:
    MsgServer(QObject* parent=nullptr);
    void start(int port);
protected:
    void incomingConnection(qintptr handle) override;
private slots:
    void readClient();
    void clientDisconnected();
public:
    QTcpSocket *findSocketByUsername(const QString& username);
private:
    QList<QTcpSocket*> clients;
};

#endif // MSGSERVER_H
