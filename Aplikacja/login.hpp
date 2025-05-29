#ifndef LOGIN_HPP
#define LOGIN_HPP

#include <QGroupBox>
#include <QLineEdit>

#include "sql.hpp"

class Login : public QGroupBox {
	Q_OBJECT

	DB *db;
	UserData data;

	QLineEdit *userName;
	QLineEdit *password;

	void logIn();

public:
	Login(DB *db, QWidget *parent);

signals:
    void loginCallback(UserData ud);

};


#endif
