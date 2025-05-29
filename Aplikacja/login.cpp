
#include <QFormLayout>
#include <QPushButton>

#include "login.hpp"

Login::Login(DB *db, QWidget *parent = 0) : QGroupBox("Logowanie", parent) {
	setObjectName("login");
	this->db = db;

	QFormLayout *widgetLayout = new QFormLayout(this);
	QPushButton *logBtn = new QPushButton("Zaloguj się");

	userName = new QLineEdit();
	password = new QLineEdit();
	password->setEchoMode(QLineEdit::Password);

	widgetLayout->addRow("Login", userName);
	widgetLayout->addRow("Hasło", password);
	widgetLayout->addRow(logBtn);
	widgetLayout->setFormAlignment(Qt::AlignVCenter);

	connect(logBtn, &QPushButton::clicked, this, &Login::logIn);
}

void Login::logIn() {
	data = db->logInSQL(userName->text(), password->text());
	userName->setText("");
	password->setText("");
	emit loginCallback(data);

}
