#include "logindialog.h"
#include "ui_logindialog.h"
LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    login=new QPushButton;
    password=new QLineEdit;
    user=new QLineEdit;
    login=ui->loginPushButton;
    password=ui->pwdLineEdit;
    user=ui->usrLineEdit;
    //设置登录按钮背景色
    login->setStyleSheet("background:rgb(0,170,0)");
    user->setFocus();

    //设置mysql
    db= QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("jjkhl");
    db.setUserName("root");
    db.setPassword("199871");
    bool ok=db.open();
    if (ok){
        qDebug()<<"mysql start successfully";
    }
    else {
        qDebug()<<"error open database because"<<db.lastError().text();
    }
}

LoginDialog::~LoginDialog()
{
    delete ui;
}
//切换账号
void LoginDialog::on_switch_pushButton_clicked()
{
    user->clear();
    password->clear();
    user->setFocus();
}

//登录账号
void LoginDialog::on_loginPushButton_clicked()
{
    name=user->text();
    psd=password->text();
    if(names.indexOf(name)!=-1)
    {
        QMessageBox::warning(this,"登录界面","用户已登录");
        user->setFocus();
        return;
    }
    if(!userExisted(name))
    {
        QMessageBox::warning(this,"登录界面","用户名不存在，请重新输入！");
        user->setFocus();
        return;
    }
    int ret=checkPassword(name,psd);
    if(-1==ret)
    {
        QMessageBox::warning(this,"登录界面","请再次检查用户名和密码");
        user->setFocus();
    }
    else if(1==ret){
        QMessageBox::warning(this,"登录界面","账号错误");
    }
    else if(2==ret){
        QMessageBox::warning(this,"登录界面","密码错误");
    }
    else if(0==ret)
    {
        names.append(name);
        showWeChatWindow();
    }
}
void LoginDialog::showWeChatWindow()
{
//    qDebug()<<"showWeChatWindow()";
    //创建一个专属用户的文件夹
    QDir dir;
    if(!dir.exists(name))
    {
        dir.mkdir(name);
    }
    weChatWindow=new MainWindow(names,nullptr,ui->usrLineEdit->text());
    weChatWindow->setWindowTitle(ui->usrLineEdit->text());
    weChatWindow->show();
}

//注册账号
void LoginDialog::on_registerPushButton_clicked()
{
    registerWindow.show();
    registerWindow.focusWidget();
    user->setFocus();
}

//删除账号按钮
void LoginDialog::on_delUserPushButton_clicked()
{
    name=user->text();
    psd=password->text();
    if(name.isEmpty()){
        QMessageBox::warning(this,"删除账号","请输入账号");
        return;
    }
    else if(!name.isEmpty()&&psd.isEmpty())
    {
        QMessageBox::warning(this,"删除账号","请输入密码");
        return;
    }

    QSqlQuery q;
    //-1表示未知错误，0表示成功，1表示账号错误，2表示密码错误
    int ret=checkPassword(name,psd);
    if(0==ret)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("删除账号");
        msgBox.setText("是否删除账号?");

        QAbstractButton* pButtonDelete = msgBox.addButton("删除", QMessageBox::YesRole);
        QAbstractButton* pButtonKeep =msgBox.addButton("保留", QMessageBox::NoRole);
        msgBox.setDefaultButton(qobject_cast<QPushButton*>(pButtonKeep));

        msgBox.exec();
        // 用户点击了“删除”
        if (msgBox.clickedButton() == pButtonDelete) {
            q.prepare("DELETE FROM wechat WHERE username = :username;");
            q.bindValue(":username",name);
            q.exec();
            user->clear();
            password->clear();
            QMessageBox::information(this,"删除账号","删除账号成功");
            user->setFocus();
        }
    }
    else if(1==ret)
    {
        QMessageBox::warning(this,"删除账号","账号错误",QMessageBox::Ok,QMessageBox::Ok);
    }
    else if(2==ret)
    {
        QMessageBox::warning(this,"删除账号","原账号密码错误",QMessageBox::Ok,QMessageBox::Ok);
    }
    else if(-1==ret)
    {
        QMessageBox::warning(this,"删除账号","未知错误",QMessageBox::Ok,QMessageBox::Ok);
    }
}

//修改密码
void LoginDialog::on_pushButton_changePwd_clicked()
{
    name=user->text();
    psd=password->text();
    password->setFocus();
    changepwd.setCredentials(name,psd);

    changepwd.show();

}

bool userExisted(const QString& username)
{
    QSqlQuery q;
    q.prepare("SELECT count(*) FROM wechat WHERE username = :username");
    q.bindValue(":username",username);
    if (!q.exec()) {
        qDebug() << "Query execution failed:" << q.lastError().text();
        return false; // 或者你可能想抛出一个异常或处理错误的其他方式
    }

    if (q.next() && q.value(0).toInt() == 0) {
        return false; // 不存在
    }
    return true; // 存在
}

int checkPassword(const QString &username, const QString &password) {
    QSqlQuery q;

    // 检查用户是否存在
    if(!userExisted(username))
    {
        return 1; // 账号错误
    }

    // 准备查询密码的SQL语句
    q.prepare("SELECT password FROM wechat WHERE username = :username");
    q.bindValue(":username", username);

    // 执行查询
    if (q.exec())
    {
        if (q.next())
        {
            QString storedPassword = q.value(0).toString();

            // 检查密码是否匹配
            if (storedPassword == password)
            {
                return 0; // 账号密码正确
            }
            else
            {
                return 2; // 密码错误
            }
        }
        // 注意: 如果你的数据库设计确保用户名是唯一的，那么这里不应该存在没有返回结果的情况。
        // 但为了健壮性，你可以添加一个额外的错误处理。
        else
        {
            qDebug() << "Unexpected error: No result for a known user.";
            return -1; // 或其他表示未知错误的值
        }
    }
    else
    {
        // 查询执行失败
        qDebug() << "Error executing query:" << q.lastError().text();
        return -1; // 或其他表示未知错误的值
    }
}



