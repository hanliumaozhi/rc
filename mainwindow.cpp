#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
    setting_(new SettingDialog),
    status_(new QLabel)
{
    ui->setupUi(this);

    udp_ = new QUdpSocket(this);
    ui->statusbar->addWidget(status_);

    connect(ui->actionSetting, &QAction::triggered, setting_, &SettingDialog::show);
    connect(ui->actionConnect, &QAction::triggered, this, &MainWindow::connect_action);

    timer_ = new QTimer(this);
    connect(timer_, SIGNAL(timeout()), this, SLOT(update_and_send()));
}

MainWindow::~MainWindow()
{
    delete status_;
    delete udp_;
    delete setting_;
    delete ui;
}

void MainWindow::connect_action()
{
    udp_->connectToHost(*setting_->rc_address_.get(), setting_->port_);
    status_->setText("connection !");
    ui->actionSetting->setEnabled(false);
    timer_->start(100);
}

void MainWindow::update_and_send()
{
    lva_ = (ui->LVA->value() / 1000.0);
    ui->lva_val->setText(QString::number(lva_));

    lsa_ = (ui->LSA->value() / 1000.0);
    ui->lsa_val->setText(QString::number(lsa_));

    lha_ = (ui->LHA->value() / 1000.0);
    ui->lha_val->setText(QString::number(lha_));

    rha_ = (ui->RHA->value() / 1000.0);
    ui->rha_val->setText(QString::number(rha_));

    rva_ = (ui->RVA->value() / 1000.0);
    ui->rva_val->setText(QString::number(rva_));

    if(ui->SBA->isChecked()){
        sba_ = 1;
    }else{
        sba_ = 0;
    }

    send_data_.clear();
    send_data_.resize(41);
    send_data_[0] = sba_;
    current_index_ = 1;

    tmp_d_.fdata = lva_;
    for (int i = 0; i !=8; ++i) {
        send_data_[(current_index_+i)] = tmp_d_.data[i];
    }
    current_index_ += 8;

    tmp_d_.fdata = lsa_;
    for (int i = 0; i !=8; ++i) {
        send_data_[(current_index_+i)] = tmp_d_.data[i];
    }
    current_index_ += 8;

    tmp_d_.fdata = lha_;
    for (int i = 0; i !=8; ++i) {
        send_data_[(current_index_+i)] = tmp_d_.data[i];
    }
    current_index_ += 8;

    tmp_d_.fdata = rha_;
    for (int i = 0; i !=8; ++i) {
        send_data_[(current_index_+i)] = tmp_d_.data[i];
    }
    current_index_ += 8;

    tmp_d_.fdata = rva_;
    for (int i = 0; i !=8; ++i) {
        send_data_[(current_index_+i)] = tmp_d_.data[i];
    }
    current_index_ += 8;

    udp_->write(send_data_);

}

