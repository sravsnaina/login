#include "signin_dialog.h"
#include "ui_signin_dialog.h"
#include "login.h"
#include "qdebug.h"
#include "welcome_dialog.h"
#include "QMessageBox"

/* Constructor */
signin_Dialog::signin_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::signin_Dialog)
{
    // Setup UI elements designed in Qt Designer
    ui->setupUi(this);

    // Enable dialog window title bar buttons (minimize, maximize, close)
    this->setWindowFlags(Qt::Dialog |
                         Qt::WindowTitleHint |
                         Qt::WindowSystemMenuHint |
                         Qt::WindowMinMaxButtonsHint |
                         Qt::WindowCloseButtonHint);
}

/* Destructor */
signin_Dialog::~signin_Dialog()
{
    // Free UI memory
    delete ui;
}

/* Slot triggered when Sign In button is clicked */
void signin_Dialog::on_signin_clicked()
{
    // Read username and password from input fields
    QString username = ui->username_lineEdit->text();
    QString Password = ui->password_lineEdit->text();

    // Open database connection
    if (!con.conopen())
    {
        // If database connection fails, exit function
        return;
    }

    // Create SQL query object
    QSqlQuery qry;

    // Prepare SQL query with placeholders (to prevent SQL injection)
    qry.prepare("SELECT * FROM Login "
                "WHERE Username = :user AND Password = :pass");

    // Bind user input values to placeholders
    qry.bindValue(":user", username);
    qry.bindValue(":pass", Password);

    // Execute query
    if (!qry.exec()) {
        // If query execution fails, show error
        qDebug() << "Query failed:" << qry.lastError().text();
        QMessageBox::warning(this, "Error", "Login query failed!");
        con.conclose();   // Close database connection
        return;
    }

    // Check if any matching record is found
    if (qry.next()) {
        // Login successful
        con.conclose();
        QMessageBox::information(this, "Login", "Login successful!");

        // Close current sign-in dialog
        this->close();

        // Open welcome dialog and pass username
        welcome_Dialog WelcomeDialog(username, this);
        WelcomeDialog.setModal(true);
        WelcomeDialog.exec();

    } else {
        // Login failed
        con.conclose();
        QMessageBox::information(this, "Failure", "Username or password incorrect!");
    }
}
