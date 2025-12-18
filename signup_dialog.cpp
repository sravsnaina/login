#include "signup_dialog.h"
#include "ui_signup_dialog.h"

#include "QDebug"
#include "QMessageBox"
#include <QRegularExpression>
#include <QIntValidator>
#include"QDate"

// -------------------------------------------------------------------
// Helper function: checks if a password is strong
// Rules:
//   - Length between 6 and 14 characters
//   - At least 1 uppercase letter
//   - At least 1 digit
//   - At least 1 special character (non letter/number)
// 'message' will contain the reason if the password is not strong
// -------------------------------------------------------------------
bool Signup_dialog::isStrongPassword(const QString &pwd, QString &message)
{
    // length between 6 and 14 ( >5 and <15 )
    if (pwd.length() <= 5 || pwd.length() >= 15) {
        message = "Password must be 6–14 characters long";
        return false;
    }

    // at least one uppercase letter
    QRegularExpression upper("[A-Z]");
    if (!upper.match(pwd).hasMatch()) {
        message = "Password must contain at least 1 uppercase letter";
        return false;
    }

    // at least one digit
    QRegularExpression digit("\\d");
    if (!digit.match(pwd).hasMatch()) {
        message = "Password must contain at least 1 number";
        return false;
    }

    // at least one special character (non letter/number)
    QRegularExpression special("[^A-Za-z0-9]");
    if (!special.match(pwd).hasMatch()) {
        message = "Password must contain at least 1 special character";
        return false;
    }

    // all rules passed
    message.clear();
    return true;
}

// -------------------------------------------------------------------
// Constructor: sets up the signup dialog UI
// -------------------------------------------------------------------
Signup_dialog::Signup_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Signup_dialog)
{
    ui->setupUi(this);
    // Enable title bar buttons
       this->setWindowFlags(Qt::Dialog |
                            Qt::WindowTitleHint |
                            Qt::WindowSystemMenuHint |
                            Qt::WindowMinMaxButtonsHint |
                            Qt::WindowCloseButtonHint);

    QRegularExpression rx("^[0-9]{10}$");
    ui->mobile_lineEdit_3->setValidator(new QRegularExpressionValidator(rx, this));

}

// -------------------------------------------------------------------
// Destructor: cleans up UI resources
// -------------------------------------------------------------------
Signup_dialog::~Signup_dialog()
{
    delete ui;
}

// -------------------------------------------------------------------
// Live password validation: called whenever the password text changes
// Updates the password error label based on strength rules
// -------------------------------------------------------------------
void Signup_dialog::on_password_lineEdit_4_textChanged(const QString &text)
{
    QString msg;

    // If password is not strong, show the message under the field
    if (!isStrongPassword(text, msg)) {
        ui->password_error_label->setText(msg);
    }
    else {
        // Clear error when password becomes valid
        ui->password_error_label->clear();
    }
}

// -------------------------------------------------------------------
// Signup button click handler
// Validates all fields (username, password, confirm, mobile, email,
// gender, address), checks username uniqueness, and inserts into DB
// only if all validations pass.
// -------------------------------------------------------------------
void Signup_dialog::on_signup_clicked()
{
    // 1. Clear previous error messages
    ui->username_error_label->clear();
    ui->password_error_label->clear();
    ui->confirm_error_label->clear();
    ui->Gender_error_label->clear();
    ui->mobile_error_label->clear();
    ui->email_error_label->clear();
    ui->address_error_label->clear();

    bool ok = true;  // tracks if all validations pass

    // 2. Read values from form fields
    QString username = ui->Username_lineEdit->text().trimmed();
    QString password = ui->password_lineEdit_4->text();
    QString confirm  = ui->comfirm_password_lineEdit_2->text();
    QString mobile   = ui->mobile_lineEdit_3->text().trimmed();
    QString email    = ui->Email_lineEdit_5->text().trimmed();
    QString gender   = ui->gender_comboBox->currentText();
    int genderIndex  = ui->gender_comboBox->currentIndex();
    QDate dob = ui->DOB_dateEdit->date();
    QString address  = ui->Address_textEdit->toPlainText().trimmed();

    // ---------- USERNAME: required + unique ----------


    if (username.isEmpty()) {
        // Show error if username is empty
        ui->username_error_label->setText("Username is required");
        ok = false;
    } else {
        // check unique in DB
        if (!con.conopen()) {
            // If DB not connected, show message and stop
            QMessageBox::warning(this, "Error", "Database not connected");
            return;
        }

        QSqlQuery q;
        q.prepare("SELECT 1 FROM Login WHERE Username = :u");
        q.bindValue(":u", username);

        if (!q.exec()) {
            // Log DB error if the query fails
            qDebug() << "Username check failed:" << q.lastError().text();
        } else if (q.next()) {
            // If a row is found, username already exists
            ui->username_error_label->setText("Username already exists");
            ok = false;
        }

        // Close DB connection after use
        con.conclose();
    }

    // ---------- PASSWORD RULES ----------
    if (password.isEmpty()) {
        // Password cannot be empty
        ui->password_error_label->setText("Password is required");
        ok = false;
    } else {
        // Recheck password strength on submit
        QString pwdMsg;
        if (!isStrongPassword(password, pwdMsg)) {
            ui->password_error_label->setText(pwdMsg);
            ok = false;
        }
    }

    // ---------- MOBILE CHECK ----------
    if (mobile.isEmpty()) {
        // Mobile number required
        ui->mobile_error_label->setText("mobile number is required");
        ok = false;
    }
    else if (mobile.length() != 10) {
        // Simple length check for 10-digit mobile numbers
        ui->mobile_error_label->setText("Invalid mobilenumber is required");
        ok = false;
    }

    // ---------- CONFIRM PASSWORD ----------
    if (confirm.isEmpty()) {
        // Confirm password must not be empty
        ui->confirm_error_label->setText("Please confirm your password");
        ok = false;
    } else if (password != confirm) {
        // Confirm password must match main password
        ui->confirm_error_label->setText("Passwords do not match");
        ok = false;
    }

    // ---------- EMAIL CHECK (must be @gmail.com) ----------
    QRegularExpression re("^[\\w\\.\\-]+@gmail\\.com$");

    if (email.isEmpty()) {
        ui->email_error_label->setText("Email is required");
        ok = false;
    }
    else if (!re.match(email).hasMatch()) {
        ui->email_error_label->setText("Invalid email");
        ok = false;
    }

    // ---------- ADDRESS CHECK ----------
    if (address.isEmpty()) {
        ui->address_error_label->setText("address is required");
        ok = false;
    }

    // ---------- GENDER COMBO ----------
    // index 0 = "Please select" → not allowed as a real choice
    if (genderIndex == 0) {
        ui->Gender_error_label->setText("Please select a gender");
        ok = false;
    }

    if(dob.isValid())
    {
        int age = dob.daysTo(QDate::currentDate()) / 365;
        qDebug()<<"checking";
        if (age <= 18) {
            ui->dob_error_label->setText("Not eligible need to be 18+");
            ok=false;
        }
    }

    // ---------- FINAL: if any validation failed, stop here ----------
    if (!ok) {
        // Do not attempt to insert into DB if any errors exist
        return;
    }

    // ---------- INSERT INTO DATABASE ----------
    if (!con.conopen()) {
        // Make sure DB is connected before inserting
        QMessageBox::warning(this, "Error", "Database not connected");
        return;
    }

    QSqlQuery qry;
    // Insert all collected values into Login table
    qry.prepare("INSERT INTO Login "
                "(Username, Password, Mobile, Email, Gender, \"Date of birth\", Address) "
                "VALUES (:user, :pass, :mob, :email, :gender, :dob, :addr)");

    // Bind form values to query parameters
    qry.bindValue(":user", username);
    qry.bindValue(":pass", password);
    qry.bindValue(":mob",  mobile);
    qry.bindValue(":email", email);
    qry.bindValue(":gender", gender);
    qry.bindValue(":dob",    dob);
    qry.bindValue(":addr",   address);

    if (qry.exec()) {
        // On successful insert, close DB and show success message
        con.conclose();
        QMessageBox::information(this, "Success", "Signup successful!");
        this->close();  // Close signup dialog after success

    } else {
        // If insert fails, log error and show message
        qDebug() << "Insert failed:" << qry.lastError().text();
        con.conclose();
        QMessageBox::warning(this, "Error", "Could not save data");
    }
}


