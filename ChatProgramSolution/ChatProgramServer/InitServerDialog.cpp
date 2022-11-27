#include <QtWidgets/QDialog>
#include "InitServerDialog.h"

InitServerDialog::InitServerDialog(QWidget* parent) : QDialog(parent)
{
    ui.setupUi(this); //Sets up this window for the server starting dialog

    ui.portTextEdit->setObjectName("portTextEdit");
}

InitServerDialog::~InitServerDialog()
{}

void InitServerDialog::on_cancelButton_clicked()
{
    close();
}

void InitServerDialog::on_okButton_clicked()
{
    std::string port; //String port number

    port = ui.portTextEdit->toPlainText().toStdString(); //Get port number from portTextEdit and converted to string

    emit startServerSignal(port); //Emit to main window and start server from there
}