#include "msgserver.h"

MsgServer::MsgServer(QObject *parent):QTcpServer(parent){}

void MsgServer::start(int port) {
    if (!this->listen(QHostAddress::Any, port)) {
        // Handle error
        qDebug()<<"Listen error";
    }
}

void MsgServer::incomingConnection(qintptr socketDescriptor) {
    QTcpSocket* client = new QTcpSocket(this);
    client->setSocketDescriptor(socketDescriptor);
    clients.append(client);

    connect(client, &QTcpSocket::readyRead, this, &MsgServer::readClient);
    connect(client, &QTcpSocket::disconnected, this, &MsgServer::clientDisconnected);

}

void MsgServer::readClient() {
    QTcpSocket* client = (QTcpSocket*)sender();
        if (!client) return;

        QByteArray data = client->readAll();
        // 获取消息类型
        ChatMsgType type = static_cast<ChatMsgType>(data.at(0) - '0');
        QString content = data.mid(2);  // 获取消息内容

        switch(type)
        {
        case OnLine:{
            //广播用户上线消息
            QString onlineMsg="<font color=\"blue\">"+content+" has joined the chat.</font>";
            for(QTcpSocket* otherClient: clients)
            {
                otherClient->write(onlineMsg.toUtf8());
            }
            break;
        }
        case OffLine:{
            QString offlineMsg="<font color=\"grey\">"+content+" has left the chat.</font>";
            for(QTcpSocket* otherClient: clients)
            {
                otherClient->write(offlineMsg.toUtf8());
            }
            break;
        }
        case ChatMsg:
            for(QTcpSocket *otherClient: clients)
            {
                if(otherClient!=client)
                    otherClient->write(content.toUtf8());  // 广播整个消息，包括消息类型
            }
            break;
        case SfileName:
            // ... 处理文件名消息

            break;
        case RefFile:
            // ... 处理文件引用消息
            break;
        }
}

void MsgServer::clientDisconnected() {
    QTcpSocket* client = (QTcpSocket*)sender();
    if (!client) return;

    clients.removeOne(client);
    client->deleteLater();
}

QTcpSocket* MsgServer::findSocketByUsername(const QString& username)
{
    for(QTcpSocket *client: clients)
    {
        if(client->objectName()==username)
        {
            return client;
        }
    }
    return nullptr;
}
