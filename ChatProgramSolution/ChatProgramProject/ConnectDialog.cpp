#include <QtWidgets/QDialog>
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
    std::string port; //String port number
    std::string hostname; //String hostname address
    std::string username; //String username

    port = ui.portTextEdit->toPlainText().toStdString(); //Get port number from portTextEdit and convert to string
    hostname = ui.hostnameTextEdit->toPlainText().toStdString(); //Get hostname from hostnameTextEdit and convert to string
    username = ui.usernameTextEdit->toPlainText().toStdString(); //Get username from usernameTextEdit and convert to string

    emit startClientSignal(port, hostname, username); //Emit to main window and start client connection from there
}