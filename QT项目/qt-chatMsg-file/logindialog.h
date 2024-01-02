#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H
//#include"qdom.h"
#include"mainwindow.h"
#include "registermysql.h"
#include"changepassword.h"
#include<QFile>
#include <QDialog>
#include<QDebug>
#include<QPushButton>
#include<QLineEdit>
#include<QMessageBox>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QSqlError>
#include<QDir>
#include"ChatMsgType.h"
//#include"onlineClients.h"
//检查mysql中有没有账号
bool userExisted(const QString& username);
/*
 验证用户密码
 -1表示未知错误，0表示成功，1表示账户不存在，2表示密码错误
*/
int checkPassword(const QString &username, const QString &password);

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();
private slots:
    void on_switch_pushButton_clicked();

    void on_loginPushButton_clicked();

    void showWeChatWindow();
    void on_registerPushButton_clicked();

    void on_delUserPushButton_clicked();

    void on_pushButton_changePwd_clicked();

private:
    Ui::LoginDialog *ui;
    QPushButton *login;
    QLineEdit *password,*user;
    MainWindow *weChatWindow;//聊天界面
    registerMysql registerWindow;
    changePassWord changepwd;
//    QDomDocument mydoc;//使用mysql代替xml文件
    QSqlDatabase db;
    QString name,psd;
    //存储用户名
    QStringList names;
};

#endif // LOGINDIALOG_H
