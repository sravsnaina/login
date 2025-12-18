#include "welcome_dialog.h"
#include "ui_welcome_dialog.h"
#include <QPixmap>
#include <QPainter>

/*
 * paintEvent()
 * This function is called automatically whenever the dialog
 * needs to be repainted (shown, resized, uncovered, etc.)
 * We use it here to draw a background image.
 */
void welcome_Dialog::paintEvent(QPaintEvent *event)
{
    // Create painter object to draw on this dialog
    QPainter painter(this);

    // Load background image
    QPixmap pix("C:/Users/Devender/Downloads/login_img.jpg");

    // Check if image loaded successfully
    if (!pix.isNull())
    {
        // Draw image scaled to fill the entire dialog
        painter.drawPixmap(
            this->rect(),   // Dialog's full area
            pix
        );
    }

    // Call base class paintEvent
    QDialog::paintEvent(event);
}

/*
 * Constructor
 * Receives username from login dialog
 */
welcome_Dialog::welcome_Dialog(const QString &username, QWidget *parent)
    : QDialog(parent),
      ui(new Ui::welcome_Dialog)
{
    // Setup UI designed in Qt Designer
    ui->setupUi(this);

    // (Optional) Display username in a label
    // ui->label->setText("Welcome " + username);
}

/*
 * Destructor
 * Cleans up allocated UI memory
 */
welcome_Dialog::~welcome_Dialog()
{
    delete ui;
}
