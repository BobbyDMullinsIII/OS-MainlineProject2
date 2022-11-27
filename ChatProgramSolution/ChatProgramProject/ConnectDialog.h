#pragma once

#include <QtWidgets/QDialog>
#include <QObject>
#include <QVariant>
#include "ui_ConnectDialog.h"

class ConnectDialog : public QDialog
{
	Q_OBJECT

public:
	ConnectDialog(QWidget* parent = nullptr);
	~ConnectDialog();

	Q_SIGNAL void startClientSignal(std::string port, std::string hostname, std::string username);

private slots:
	void on_cancelButton_clicked();
	void on_okButton_clicked();

private:
	Ui::Dialog ui;
};

