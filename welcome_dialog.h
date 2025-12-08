#ifndef WELCOME_DIALOG_H
#define WELCOME_DIALOG_H

#include <QDialog>

namespace Ui {
class welcome_Dialog;
}

class welcome_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit welcome_Dialog(QWidget *parent = nullptr);
    ~welcome_Dialog();

private:
    Ui::welcome_Dialog *ui;
};

#endif // WELCOME_DIALOG_H
