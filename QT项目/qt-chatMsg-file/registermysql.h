#ifndef REGISTERMYSQL_H
#define REGISTERMYSQL_H

#include <QDialog>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QSqlError>
#include<qDebug>
#include<QPushButton>
#include<QLineEdit>
#include<QMessageBox>


namespace Ui {
class registerMysql;
}

class registerMysql : public QDialog
{
    Q_OBJECT

public:
    explicit registerMysql(QWidget *parent = nullptr);
    ~registerMysql();

private slots:
    void on_pushButton_register_clicked();

private:
    Ui::registerMysql *ui;
    QSqlDatabase db;
};

#endif // REGISTERMYSQL_H
