#include "ConnectDialog.h"

ConnectDialog::ConnectDialog(QWidget* parent) : QDialog(parent)
{
    ui.setupUi(this); //Sets up this window for the client to connect to the server
}

ConnectDialog::~ConnectDialog()
{}

void ConnectDialog::on_cancelButton_clicked()
{
    close();
}

void ConnectDialog::on_okButton_clicked()
{
    //Will add code later
}