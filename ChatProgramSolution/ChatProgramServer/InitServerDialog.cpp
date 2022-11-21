#include "InitServerDialog.h"

InitServerDialog::InitServerDialog(QWidget* parent) : QDialog(parent)
{
    ui.setupUi(this); //Sets up this window for the server starting dialog

    InitServerDialog::setStyleSheet("background-color: lightblue; color: black;"); //Sets background color of window to light blue and text to black
}

InitServerDialog::~InitServerDialog()
{}

void InitServerDialog::on_cancelButton_clicked()
{
    close();
}

void InitServerDialog::on_okButton_clicked()
{
    //Will add code later
}