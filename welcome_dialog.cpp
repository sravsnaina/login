#include "welcome_dialog.h"
#include "ui_welcome_dialog.h"

welcome_Dialog::welcome_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::welcome_Dialog)
{
    ui->setupUi(this);
}

welcome_Dialog::~welcome_Dialog()
{
    delete ui;
}
