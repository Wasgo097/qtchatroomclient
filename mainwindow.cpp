#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QString ip,QWidget *parent) :
    QMainWindow(parent),
    my_socket(new QTcpSocket(this)),
    my_ip(ip),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->menuBar->hide();
    ui->statusBar->hide();
    ui->mainToolBar->hide();
    my_socket=new QTcpSocket(this);
    my_socket->connectToHost(my_ip,1234);
    if(my_socket->waitForConnected()){
        connect(my_socket,SIGNAL(readyRead()),this,SLOT(readyRead()));
        my_socket->flush();
        my_socket->waitForBytesWritten(3000);
    }
    else ui->display->append("Error with connection");
}
MainWindow::~MainWindow()
{
    delete ui;
    if(my_socket!=nullptr)delete my_socket;
    if(interlocutor_socket!=nullptr)delete  interlocutor_socket;
}
void MainWindow::readyRead()
{
    while(my_socket->canReadLine()){
        ui->display->append(my_socket->readLine().trimmed());
    }
}
void MainWindow::on_send_clicked()
{
    if(ui->input->toPlainText()!=""){
        ui->display->append("Ja: "+ui->input->toPlainText());
        ui->input->clear();
        QByteArray mess=("Rozmowca: "+ui->input->toPlainText()+"\r\n").toLocal8Bit();
        const char * fullmes=mess.data();
        my_socket->write(fullmes);
        my_socket->flush();
        my_socket->waitForBytesWritten(2000);
    }
}
