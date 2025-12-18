#ifndef WELCOME_DIALOG_H
#define WELCOME_DIALOG_H

#include <QDialog>

namespace Ui { class welcome_Dialog; }

class welcome_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit welcome_Dialog(const QString &username, QWidget *parent = nullptr);//to receive an argument
    ~welcome_Dialog();
protected:
    void paintEvent(QPaintEvent *event) override;



private:
    Ui::welcome_Dialog *ui;
    //void updateBackground();

};

#endif // WELCOME_DIALOG_H
