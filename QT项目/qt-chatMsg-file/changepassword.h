#ifndef CHANGEPASSWORD_H
#define CHANGEPASSWORD_H

#include <QDialog>
#include<QMessageBox>
#include<QLineEdit>
#include<QPushButton>
#include<QSqlDatabase>
#include<QSqlError>
#include<QSqlQuery>
#include<QDebug>
#include"ChatMsgType.h"

//-1未知错误；0成功；1账号错误；2原密码错误；3新密码和原密码相同
int updateUserPassword(const QString &username, const QString &newPassword,const QString &oldPassword);

namespace Ui {
class changePassWord;
}

class changePassWord : public QDialog
{
    Q_OBJECT

public:
    explicit changePassWord(QWidget *parent = nullptr);
    ~changePassWord();

private slots:
    void on_pushButton_change_clicked();

private:
    Ui::changePassWord *ui;
    QSqlDatabase db;
    QString username,password;
public:
    void setCredentials(const QString &name, const QString &pwd);
};

#endif // CHANGEPASSWORD_H
