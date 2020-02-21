#include "settingdialog.h"
#include "ui_settingdialog.h"

SettingDialog::SettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDialog)
{
    ui->setupUi(this);
    ui->ip_str->setText("192.168.1.1");
    ui->port_str->setText("11223");
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

void SettingDialog::on_oks_clicked()
{
    is_setting_ = true;
    rc_address_ = std::make_shared<QHostAddress>(ui->ip_str->text());
    port_ = ui->port_str->text().toUShort();
    hide();
}
