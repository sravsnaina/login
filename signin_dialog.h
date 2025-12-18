#ifndef SIGNIN_DIALOG_H
#define SIGNIN_DIALOG_H

#include <QDialog>
#include"login.h"

namespace Ui {
class signin_Dialog;
}

class signin_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit signin_Dialog(QWidget *parent = nullptr);
    ~signin_Dialog();
    Login con;//to use the function from login class

private slots:
    void on_signin_clicked();

private:
    Ui::signin_Dialog *ui;
};

#endif // SIGNIN_DIALOG_H
