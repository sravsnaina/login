#include "signin_dialog.h"
#include "ui_signin_dialog.h"
#include"login.h"
#include"qdebug.h"
#include"welcome_dialog.h"
#include"QMessageBox"

signin_Dialog::signin_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::signin_Dialog)
{
    ui->setupUi(this);

}

signin_Dialog::~signin_Dialog()
{
    delete ui;
}

void signin_Dialog::on_signin_clicked()
{
   QString username=ui->username_lineEdit->text();
   QString Password=ui->password_lineEdit->text();

  if(!con.conopen())
  {
      return;
  }

  QSqlQuery qry;
  qry.prepare("SELECT * FROM Login "
                  "WHERE Username = :user AND Password = :pass");
      qry.bindValue(":user", username);
      qry.bindValue(":pass", Password);

      if (!qry.exec()) {
              // SQL error
              qDebug() << "Query failed:" << qry.lastError().text();
              QMessageBox::warning(this, "Error", "Login query failed!");
              con.conclose();
              return;
          }
      if (qry.next()) {
              con.conclose();
              QMessageBox::information(this, "Login", "Login successful!");
              welcome_Dialog welcome;
              welcome.setModal(true);
              welcome.exec();
          } else {
              con.conclose();
              QMessageBox::information(this, "Failure", "Username or password incorrect!");
          }

}

