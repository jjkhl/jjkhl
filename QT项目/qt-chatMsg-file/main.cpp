#include "mainwindow.h"
#include "logindialog.h"
#include <QApplication>

//#include"serverwidget.h"
//#include"clientwidget.h"

int main(int argc, char *argv[])
{
    //相当于是服务器向客户端发送，类比user1向user2发送
    QApplication a(argc, argv);
    serverWidget s("user1","user2");
    s.show();
    clientwidget c1("user2");
    c1.show();

//    LoginDialog login;
//    login.show();
    return a.exec();
//    clientwidget c2;
//    c2.show();
//    //测试主窗口
//    MainWindow w;
//    w.show();

}
