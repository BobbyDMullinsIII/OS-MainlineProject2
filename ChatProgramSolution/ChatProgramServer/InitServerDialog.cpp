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

    //port = QString::toStdString(ui.portTextEdit->toPlainText()); //Get port number from portTextEdit and converted to string

    emit startServerSignal("2000"); //Emit to main window and start server from there
}