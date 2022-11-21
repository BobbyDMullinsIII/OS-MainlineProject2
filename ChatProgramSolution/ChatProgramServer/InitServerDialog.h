#pragma once

#include <QtWidgets/QDialog>
#include "ui_InitServerDialog.h"

class InitServerDialog : public QDialog
{
	Q_OBJECT

public:
	InitServerDialog(QWidget* parent = nullptr);
	~InitServerDialog();

private slots:
	void on_cancelButton_clicked();
	void on_okButton_clicked();

private:
	Ui::Dialog ui;
};

