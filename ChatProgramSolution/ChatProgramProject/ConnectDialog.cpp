#include "ConnectDialog.h"

ConnectDialog::ConnectDialog(QWidget* parent) : QDialog(parent)
{
    ui.setupUi(this); //Sets up this window for the client to connect to the server

    ConnectDialog::setStyleSheet("background-color: lightblue; color: black;"); //Sets background color of window to light blue and text to black
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