#ifndef SIGNUP_DIALOG_H
#define SIGNUP_DIALOG_H
#include"login.h"
#include <QDialog>

namespace Ui {
class Signup_dialog;
}

class Signup_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Signup_dialog(QWidget *parent = nullptr);
    ~Signup_dialog();
     Login con;
private slots:

    void on_signup_clicked();
    void on_password_lineEdit_4_textChanged(const QString &text);
    bool isStrongPassword(const QString &pwd, QString &message);



private:
    Ui::Signup_dialog *ui;
};

#endif // SIGNUP_DIALOG_H
