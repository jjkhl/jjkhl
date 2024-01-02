#include "changepassword.h"
#include "ui_changepassword.h"

changePassWord::changePassWord(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::changePassWord)
{
    ui->setupUi(this);

    db= QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("jjkhl");
    db.setUserName("root");
    db.setPassword("199871");

}

changePassWord::~changePassWord()
{
    delete ui;
}

void changePassWord::setCredentials(const QString &name, const QString &pwd) {
    this->username = name;
    this->password = pwd;

    ui->lineEdit_username->setText(username);
    ui->lineEdit_orginPwd->setText(password);
    ui->lineEdit_username->setFocus();
}

void changePassWord::on_pushButton_change_clicked()
{
    QString newPwd=ui->lineEdit_newPwd->text();
    QString newPwdConfirm=ui->lineEdit_newPwdConfirm->text();
    if(newPwd!=newPwdConfirm)
    {
        QMessageBox::warning(this,"密码修改","两次密码输入不一致");
        return;
    }
    int ret=updateUserPassword(ui->lineEdit_username->text(),ui->lineEdit_newPwd->text(),ui->lineEdit_orginPwd->text());
    if(-1==ret)
    {
        QMessageBox::warning(this,"密码修改","未知错误");
    }
    else if(0==ret)
    {
        QMessageBox::information(this,"密码修改","密码修改成功");
        this->close();
    }
    else if(1==ret)
    {
        QMessageBox::warning(this,"密码修改","账号未创建");
    }
    else if(2==ret)
    {
        QMessageBox::warning(this,"密码修改","密码错误");
        ui->lineEdit_orginPwd->setFocus();
    }
    else if(3==ret)
    {
        QMessageBox::warning(this,"密码修改","新旧密码相同");
        ui->lineEdit_newPwd->setFocus();
    }
}
//-1未知错误；0成功；1账号错误；2原密码错误；3新密码和原密码相同
int updateUserPassword(const QString &username, const QString &newPassword,const QString &oldPassword) {
    QSqlQuery query;

    // 检查账号是否存在
    query.prepare("SELECT password FROM wechat WHERE username = :username");
    query.bindValue(":username", username);
    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
        return -1;  // 未知错误
    }

    if (!query.next()) {
        qDebug() << "Username not found:" << username;
        return 1;  // 账号错误
    }

    QString storedPassword = query.value(0).toString();
    if (storedPassword != oldPassword) {
        return 2;  // 原密码错误
    }

    if (oldPassword == newPassword) {
        return 3;  // 新旧密码相同
    }

    // 更新密码
    query.prepare("UPDATE wechat SET password = :newPassword WHERE username = :username");
    query.bindValue(":username", username);
    query.bindValue(":newPassword", newPassword);
    if (!query.exec()) {
        qDebug() << "Error updating password:" << query.lastError().text();
        return -1;  // 未知错误
    }

    return 0;  // 成功
}
