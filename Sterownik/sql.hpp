#ifndef SQL_HPP
#define SQL_HPP

#include <QSqlDatabase>

class DB {
	QSqlDatabase db;
public:
	DB();
	bool connectDB();
	bool isOpen();
	void closeDB();
	int select(int id);
	bool insert(int userID);
	bool checkLastAttendance(int userID);
};

#endif
