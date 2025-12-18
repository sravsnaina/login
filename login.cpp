#include "login.h"
#include "ui_login.h"
#include "signup_dialog.h"
#include"signin_dialog.h"

Login::Login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
    ui->groupBox->setAlignment(Qt::AlignHCenter);//group box align at the center
    ui->label->setAlignment(Qt::AlignCenter);//label align at the center

}

Login::~Login()
{
    delete ui;
}



void Login::on_Singup_clicked()
{
    this->hide();
    Signup_dialog signup;//open in signup form dialog
    signup.setModal(true);
    signup.exec();
    this->show();//after closing signup form this dialog shows
}


void Login::on_signin_clicked()
{
    this->hide();
    signin_Dialog signin;//open signin form dialog
    signin.setModal(true);
    signin.exec();
    this->show();//after closing signin form this dialog shows
}

