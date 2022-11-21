#pragma once

#include <QtWidgets/QDialog>
#include "ui_ConnectDialog.h"

class ConnectDialog : public QDialog
{
	Q_OBJECT

public:
	ConnectDialog(QWidget* parent = nullptr);
	~ConnectDialog();

private slots:
	void on_cancelButton_clicked();
	void on_okButton_clicked();

private:
	Ui::Dialog ui;
};

