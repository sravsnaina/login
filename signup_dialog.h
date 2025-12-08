#ifndef SIGNUP_DIALOG_H
#define SIGNUP_DIALOG_H

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

private:
    Ui::Signup_dialog *ui;
};

#endif // SIGNUP_DIALOG_H
