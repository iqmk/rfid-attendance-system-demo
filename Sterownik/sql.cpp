#include <QSqlQuery>
#include <QVariant>

#include "sql.hpp"

DB::DB() {
	db = QSqlDatabase::addDatabase("QMYSQL");
	db.setHostName("localhost");
	db.setDatabaseName("ewidencja_obecnosci");
	db.setUserName("root");
	db.setPassword("root");
}

bool DB::connectDB() {
	return db.open();
}

int DB::select(int id) {
	QString execute = QString::fromStdString("SELECT uzytkownik_id"
		" FROM uzytkownicy WHERE tag_id = " + std::to_string(id) + ";");

	QSqlQuery query;
	query.exec(execute);
	query.next();
	return query.value(0).toInt();
}


bool DB::insert(int userID) {
	QSqlQuery query;

	QString execute = QString::fromStdString("INSERT INTO obecnosci"
		" (uzytkownik_id, data) VALUES (" + std::to_string(userID) + ", now());");


	return query.exec(execute);
}

bool DB::checkLastAttendance(int userID) {
	int i = -1;
	QString execute = QString::fromStdString(
		"SELECT uzytkownik_id FROM obecnosci WHERE"
		" TIMESTAMPDIFF(MINUTE, obecnosci.data, now()) <= 70 AND"
		" uzytkownik_id = " + std::to_string(userID) + ";");


	QSqlQuery query;
	query.exec(execute);
	if(query.next()) {
		i = query.value(0).toInt();
	}

	return i == -1;

}

void DB::closeDB() {
	db.close();
}

bool DB::isOpen() {
	return db.isOpen();
}
