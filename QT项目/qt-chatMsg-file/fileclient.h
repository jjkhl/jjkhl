#ifndef FILECLIENT_H
#define FILECLIENT_H

#include <QWidget>
#include <QTcpSocket>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QByteArray>

class FileClient : public QWidget {
    Q_OBJECT
public:
    FileClient(QWidget *parent = nullptr);

private slots:
    void connectToServer();
    void sendFile();
    void readServer();

private:
    QTcpSocket *socket;
    QLineEdit *fileLineEdit;
    QPushButton *sendButton;
    QPushButton *connectButton;
};

#endif // FILECLIENT_H
