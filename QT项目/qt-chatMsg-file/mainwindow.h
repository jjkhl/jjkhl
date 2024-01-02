#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QMessageBox>
#include<QTcpSocket>
#include<QTcpServer>
#include<QUdpSocket>
#include<QNetworkInterface>
#include<QDateTime>
#include<QFile>
#include<QFileDialog>
#include<QDateTime>
#include<QCloseEvent>
#include<QInputDialog>
#include<QMessageBox>
#include"ChatMsgType.h"
#include"msgserver.h"
#include"serverwidget.h"
#include"clientwidget.h"


class FileSrvDlg;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

//待实现文件传输功能
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QStringList &onclients,QWidget *parent = nullptr, QString userName=QString());
    ~MainWindow();
//    void initMainWindow();
public:
    void readServer();
//    void recvFileName(QString name, QString hostip, QString rmtname, QString filename);

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_pushButton_search_clicked();

    void on_pushButton_send_clicked();

    void on_pushButton_trans_clicked();

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
    QString myname="";
    MsgServer *msgserver;
    QStringList onlineClients;
    serverWidget *sWidget;
    clientwidget *cWidget;
//    QString myFileName;
//    FileSrvDlg *myfsrv;
};
#endif // MAINWINDOW_H
