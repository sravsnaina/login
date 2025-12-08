#include "signup_dialog.h"
#include "ui_signup_dialog.h"

Signup_dialog::Signup_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Signup_dialog)
{
    ui->setupUi(this);
}

Signup_dialog::~Signup_dialog()
{
    delete ui;
}
