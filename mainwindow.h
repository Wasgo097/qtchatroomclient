#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QDebug>
#include <QTcpSocket>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QTcpSocket * my_socket{nullptr};
    QTcpSocket * interlocutor_socket{nullptr};
    QString my_ip{};
public:
    explicit MainWindow(QString ip="127.0.0.1",QWidget *parent = nullptr);
    ~MainWindow();
    QTcpSocket* get_my_socket();
    QTcpSocket* get_my_interlocutor();
    QString get_my_up();
private:
    Ui::MainWindow *ui;
private slots:
    void readyRead();
    void on_send_clicked();
};

#endif // MAINWINDOW_H
