#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <settingdialog.h>
#include <QHostAddress>
#include <QUdpSocket>
#include <QLabel>
#include <QTimer>
#include <QByteArray>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

union byte8{
    uint8_t data[8];
    double fdata;
};

class SettingDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    SettingDialog *setting_ = nullptr;
    QUdpSocket *udp_ = nullptr;
    QLabel *status_ = nullptr;
    uint8_t sba_;
    double lva_, lsa_, lha_, rha_, rva_;
    QTimer *timer_;
    byte8 tmp_d_;
    QByteArray send_data_;
    int current_index_;

private slots:
    void connect_action();
    void update_and_send();
};
#endif // MAINWINDOW_H
