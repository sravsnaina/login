#include "login.h"
#include "ui_login.h"
#include "signup_dialog.h"
#include"signin_dialog.h"

Login::Login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
    ui->groupBox->setAlignment(Qt::AlignHCenter);
    ui->label->setAlignment(Qt::AlignCenter);

}

Login::~Login()
{
    delete ui;
}



void Login::on_Singup_clicked()
{
    Signup_dialog signup;
    signup.setModal(true);
    signup.exec();
}


void Login::on_signin_clicked()
{
    signin_Dialog signin;
    signin.setModal(true);
    signin.exec();
}

