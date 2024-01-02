#include "registermysql.h"
#include "ui_registermysql.h"

registerMysql::registerMysql(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registerMysql)
{
    ui->setupUi(this);

    db= QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("jjkhl");
    db.setUserName("root");
    db.setPassword("199871");

}

registerMysql::~registerMysql()
{
    delete ui;
}

void registerMysql::on_pushButton_register_clicked()
{
    QString name=ui->lineEdit_newAccount->text();
    QString pwd=ui->lineEdit_newPwd->text();

    //查看两次密码是否不一致
    if(pwd!=ui->lineEdit_newPwdConfirm->text())
    {
        QMessageBox::warning(this,"账号注册","两次密码输入不一致！");
        return;
    }

    //检测账号是否已存在
    QSqlQuery q;
    q.prepare("SELECT count(*) FROM wechat WHERE username = :username");
    q.bindValue(":username", name);
    if (!q.exec()) {
        qDebug() << "Query execution error:" << q.lastError().text();
        return;
    }
    //q.next()表示将内部指针移动到第一条记录上
    if (q.next() && q.value(0).toInt() > 0) {
        QMessageBox::warning(this, "账号注册", "用户已存在");
        return;
    }

    //注册账号
    q.prepare("INSERT INTO wechat (username, password) VALUES (:username, :password)");
    q.bindValue(":username", name);
    q.bindValue(":password", pwd);
    if(!q.exec())
    {
        qDebug()<<"注册用户未知错误"<<q.lastError().text();
        return;
    }
    QMessageBox::information(this,"账号注册","用户注册成功！",QMessageBox::Ok,QMessageBox::Ok);
    this->close();
}
