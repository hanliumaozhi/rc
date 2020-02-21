#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include <QHostAddress>
#include <memory>

namespace Ui {
class SettingDialog;
}

class SettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingDialog(QWidget *parent = nullptr);
    ~SettingDialog();

public:
    bool is_setting_;
    std::shared_ptr<QHostAddress> rc_address_;
    uint16_t port_;

private slots:
    void on_oks_clicked();

private:
    Ui::SettingDialog *ui;
};

#endif // SETTINGDIALOG_H
