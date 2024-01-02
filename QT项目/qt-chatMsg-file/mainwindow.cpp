#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QStringList &onclients,QWidget *parent,QString userName)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),myname(userName),onlineClients(onclients)
{
    ui->setupUi(this);
    //启动服务器
    msgserver=new MsgServer(this);
    msgserver->start(12345);

//    myname=this->windowTitle();
    socket=new QTcpSocket(this);

    ui->label_user->setText(myname);
    connect(socket,&QTcpSocket::readyRead,this,&MainWindow::readServer);
    socket->connectToHost("localhost",12345);
    //显示用户上线
    QString onlineMsg = QString::number(OnLine) + ":" + myname;
    socket->write(onlineMsg.toUtf8());
//    connect(myfsrv,SIGNAL(sendFileName(QString)),this,SLOT(get))
}

MainWindow::~MainWindow()
{
    delete ui;
    delete socket;
    delete cWidget;
    delete sWidget;
//    delete myfsrv;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    //显示用户下线
    QString offlineMsg=QString::number(OffLine)+":"+myname;
    socket->write(offlineMsg.toUtf8());
    socket->flush();//确保数据被发送
    socket->waitForBytesWritten();//等待数据被写入
    //删除用户文件夹
    QDir dir(myname);
    if(dir.exists())
    {
        dir.removeRecursively();
    }
    event->accept();
}
void MainWindow::on_pushButton_send_clicked()
{
    QString name = myname;
    QString now = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString contentText = ui->textEdit->toPlainText();

    //将换行替换为<br>
    QString formattedContent = contentText.replace("\n", "<br>");
    QString content = "【" + name + "】(" + now + "): <br>" + formattedContent;
    QString msg = QString::number(ChatMsg) + ":" + content;
    socket->write(msg.toUtf8());

   //自己的消息显示为浅绿色背景，黑色字体
   QString formattedMsg = "You: <br><span style=\"background-color: lightgreen; color: black;\">" +formattedContent + "</span>";
   ui->chatTextBrowser->append(formattedMsg);
   ui->textEdit->clear();
}

void MainWindow::readServer()
{
    QByteArray data=socket->readAll();
    ui->chatTextBrowser->append(data);

    QString message = QString::fromUtf8(data);
    // 更新listWidget列表
    QStringList parts = message.split(" ");
    QString username = parts.at(1).split(">").last();

    if (message.contains("joined") && !onlineClients.contains(username)) {
        onlineClients.append(username);
    } else if (message.contains("left")) {
        onlineClients.removeAll(username);
    }

    // 使用onlineClients刷新listWidget
    ui->listWidget->clear();
    ui->listWidget->addItems(onlineClients);
}

void MainWindow::on_pushButton_search_clicked()
{
    bool ok;
    QString text=QInputDialog::getText(this,tr("查找用户"),
                                       tr("输入用户名："),QLineEdit::Normal,"",&ok);
    //用户点击了确定查找并输入不为空的用户名
    if(ok&&!text.isEmpty())
    {
        if(onlineClients.contains(text))
        {
            QList<QListWidgetItem*> items=ui->listWidget->findItems(text,Qt::MatchExactly);
            if(!items.isEmpty())
            {
                QListWidgetItem *item=items.first();
                item->QListWidgetItem::setBackgroundColor(Qt::yellow);
            }
        }
        else
        {
            QMessageBox::warning(this,"查找用户",tr("未找到用户%1").arg(text));
        }
    }
    if(text.isEmpty())
    {
        QMessageBox::warning(this,"警告","请输入用户名！");
    }
}

void MainWindow::on_pushButton_trans_clicked()
{
    //选中用户列表中的用户
    QListWidgetItem *selectedItem=ui->listWidget->currentItem();
    if(!selectedItem)
    {
        QMessageBox::warning(this,"传输文件","请于在线列表选中发送方！");
        return;
    }
    QString targetUsername=selectedItem->text();
    //启动文件传输服务器
    sWidget=new serverWidget(myname,targetUsername);
    sWidget->show();

    //启动客户端
    cWidget=new clientwidget(targetUsername);
    cWidget->show();
}
