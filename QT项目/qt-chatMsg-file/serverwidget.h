#ifndef SERVERWIDGET_H
#define SERVERWIDGET_H

#include <QWidget>
#include<QTcpServer>
#include<QTcpSocket>
#include<QFile>
#include<QTimer>
#include<QCloseEvent>
QT_BEGIN_NAMESPACE
namespace Ui { class serverWidget; }
QT_END_NAMESPACE

class serverWidget : public QWidget
{
    Q_OBJECT

public:
   serverWidget(QString _sender,QString _receiver,QWidget *parent = nullptr);
    ~serverWidget();
    void sendData();
    void closeEvent(QCloseEvent *event);
private slots:
    void on_buttonFile_clicked();

    void on_buttonSend_clicked();

private:
    Ui::serverWidget *ui;
    QTcpServer *tcpServer;
    QTcpSocket *tcpSocket;
    QFile file;
    QString fileName;
    qint64 fileSize;
    qint64 sendSize;
    QTimer timer;
    QString sender;
    QString receiver;
};
#endif // SERVERWIDGET_H
