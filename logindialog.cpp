#include "logindialog.h"
#include "ui_logindialog.h"
#include<QMessageBox>
#include<QtSql/QSqlQuery>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    setWindowTitle(tr("登录"));
    connect(ui->LoginpushButton,SIGNAL(clicked()),this,SLOT(on_loginbtnClicked()));
    connect(ui->QuitpushButton,SIGNAL(clicked()),this,SLOT(on_quitbtnClicked()));
    ui->pwdlineEdit->setFocus();
    ui->LoginpushButton->setDefault(true);
}
void LoginDialog::on_loginbtnClicked()
{
    if(ui->pwdlineEdit->text().isEmpty())
    {
        QMessageBox::information(this,tr("请输入密码"),tr("请先输入密码再登录"),QMessageBox::Ok);
        ui->pwdlineEdit->setFocus();
    }
    else
    {
        QSqlQuery query;
        query.exec("select pwd from password");
        query.next();
        if(query.value(0).toString()==ui->pwdlineEdit->text())
        {
            QDialog::accept();
        }else
        {
            QMessageBox::information(this,tr("密码错误"),tr("请先输入正确密码再登录"),QMessageBox::Ok);
            ui->pwdlineEdit->clear();
            ui->pwdlineEdit->setFocus();
        }
    }
}
void LoginDialog::on_quitbtnClicked()
{
    QDialog::reject();
}
LoginDialog::~LoginDialog()
{
    delete ui;
}
