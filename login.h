#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QtSql>
#include <QDebug>
#include<QFileInfo>

QT_BEGIN_NAMESPACE
namespace Ui { class Login; }
QT_END_NAMESPACE

class Login : public QMainWindow
{
    Q_OBJECT

public:
    QSqlDatabase mydb;
    void conclose()
    {
        mydb.close();
        mydb.removeDatabase(QSqlDatabase::defaultConnection);
    }

    bool conopen()
    {
        // Create/connect to a database using SQLite driver
        mydb = QSqlDatabase::addDatabase("QSQLITE");

        // Set the database file path (absolute path)
        mydb.setDatabaseName("C:/QT programs/Login/Login_data.db");

        // Try to open the database
        if(mydb.open())
        {
             // Show status on label if connection is successful
            qDebug() << "Database opened successfully!";

            return true;

        }

        else
        {
            // Show status on label if database failed to open
            qDebug() << "Database failed to open!";
            return false;

        }
    }

public:
    Login(QWidget *parent = nullptr);
    ~Login();

private slots:


    void on_Singup_clicked();

    void on_signin_clicked();

private:
    Ui::Login *ui;

};
#endif // LOGIN_H
