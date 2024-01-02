#include "fileclient.h"

FileClient::FileClient(QWidget *parent)
    : QWidget(parent) {
    socket = new QTcpSocket(this);

    fileLineEdit = new QLineEdit(this);
    sendButton = new QPushButton("Send File", this);
    connectButton = new QPushButton("Connect to Server", this);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(fileLineEdit);
    layout->addWidget(sendButton);
    layout->addWidget(connectButton);
    setLayout(layout);

    connect(sendButton, &QPushButton::clicked, this, &FileClient::sendFile);
    connect(connectButton, &QPushButton::clicked, this, &FileClient::connectToServer);
    connect(socket, &QTcpSocket::readyRead, this, &FileClient::readServer);
}

void FileClient::connectToServer() {
    socket->connectToHost("127.0.0.1", 12345);
    if (socket->waitForConnected()) {
        QMessageBox::information(this, "Connected", "Successfully connected to the server!");
    } else {
        QMessageBox::warning(this, "Error", "Could not connect to the server!");
    }
}

void FileClient::sendFile() {
    QString filePath = QFileDialog::getOpenFileName(this, "Select a file", "", "All Files (*)");
    if (filePath.isEmpty()) return;

    QFile file(filePath);
    bool ok=file.open(QIODevice::ReadOnly);
    qDebug()<<ok;
    if (!ok) {
        QMessageBox::warning(this, "Error", "Cannot open file for reading!");
        return;
    }

    QByteArray fileData = file.readAll();
    socket->write(fileData);
    file.close();
}

void FileClient::readServer() {
    // Handle server messages, like file receive requests, file data, etc.
    QByteArray data = socket->readAll();
    // Process the data as needed
}

