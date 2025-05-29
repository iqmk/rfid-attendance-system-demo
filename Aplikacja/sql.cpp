
#include <QVariant>
#include <QSqlQuery>
#include <QSqlRecord>

#include "sql.hpp"

bool DB::connectDB() {

	*(QSqlDatabase*)this = QSqlDatabase::addDatabase("QMYSQL");
	setHostName("192.168.1.142");
	setDatabaseName("ewidencja_obecnosci");
	setUserName("test");
	setPassword("test");
	return open();
}

std::vector <TimetableText> DB::getTimetable(QString date) {
	std::vector <TimetableText> temp;
	TimetableText tt;
	QString execute = "SELECT przedmioty.nazwa, TIME(zajecia.data)"
		" FROM przedmioty LEFT JOIN zajecia"
		" ON przedmioty.przedmiot_id = zajecia.przedmiot_id"
		" WHERE DATE(data) = '" + date + "';";

	QSqlQuery query;
	query.exec(execute);

	while(query.next()) {
		tt.itemName = query.value(0).toString();
		tt.time = query.value(1).toString();
		temp.push_back(tt);
	}
	return temp;
}

UserData DB::logInSQL(QString login, QString haslo) {
	UserData data;
	QString execute = "SELECT uzytkownik_id, status FROM uzytkownicy"
		" WHERE numer_ewidencyjny = '" + login + "' and haslo = '"
		+ haslo + "';";

	QSqlQuery query;
	query.exec(execute);
	int rows = query.size();

	if(rows == 1) {
		query.next();
		data.userID = query.value(0).toInt();
		data.status = query.value(1).toBool();
		return data;
	}

	return {-1, 0};
}


std::vector <std::vector<QString>> DB::getAttendanceList(QString classDateTime) {

	std::vector <std::vector<QString>> temp;

	QString execute =
		"SELECT uzytkownicy.numer_ewidencyjny, uzytkownicy.imie,"
		" uzytkownicy.nazwisko FROM uzytkownicy JOIN obecnosci"
		" ON TIMESTAMPDIFF(MINUTE, obecnosci.data, '"
		+ classDateTime + "') BETWEEN -20 AND 10"
		" AND uzytkownicy.uzytkownik_id = obecnosci.uzytkownik_id;";

	QSqlQuery query;
	query.exec(execute);
	int cols = query.record().count();
	while(query.next()) {
		std::vector<QString> record;
		for(int n = 0; n < cols; n++) {
			record.push_back(query.value(n).toString());
		}
		temp.push_back(record);
	}
	return temp;
}

bool DB::getAttendanceStatus(int userID, QString dateTime) {

	QString execute = "SELECT 1 FROM obecnosci"
		" WHERE TIMESTAMPDIFF(MINUTE, obecnosci.data, '"
		+ dateTime + "') BETWEEN -20 AND 10 AND uzytkownik_id = "
		+ QVariant(userID).toString() + ";";


	QSqlQuery query;
	query.exec(execute);

	return query.size();
}

void DB::closeDB() {
	close();
}

QStringList DB::getSubjectNames() {
	QStringList temp;

	QString execute = "SELECT nazwa FROM przedmioty;";

	QSqlQuery query;
	query.exec(execute);

	while(query.next()) {
		temp.push_back(query.value(0).toString());
	}


	return temp;

}

std::vector <std::vector<QString>> DB::getStatistics(
	QString userID, QString subjectName, QString dateFrom, QString dateInto) {

	std::vector <std::vector<QString>> temp;

	QString execute = "";

	if(subjectName == "Wszystkie przedmioty") {
		subjectName = "";
	}

	if(userID == "-1") {
		userID = "";
		execute = "SELECT przedmioty.nazwa, uzytkownicy.numer_ewidencyjny,"
		" uzytkownicy.imie, uzytkownicy.nazwisko, SUM(COALESCE((SELECT '1'"
		" FROM obecnosci WHERE obecnosci.data BETWEEN"
		" DATE_SUB(zajecia.data, INTERVAL 10 MINUTE) AND"
		" DATE_ADD(zajecia.data, INTERVAL 20 MINUTE) AND"
		" obecnosci.uzytkownik_id = uzytkownicy.uzytkownik_id), 0)),"
		" COUNT(przedmioty.nazwa) FROM przedmioty JOIN zajecia ON"
		" zajecia.przedmiot_id = przedmioty.przedmiot_id CROSS JOIN uzytkownicy"
		" WHERE zajecia.data BETWEEN '" + dateFrom + "' AND '" + dateInto
		+ "' AND (uzytkownicy.uzytkownik_id = '" + userID + "' OR '" + userID
		+ "'  = '') AND (przedmioty.nazwa = '" + subjectName + "' OR '"
		+ subjectName + "' = '') AND uzytkownicy.status = 1 GROUP BY"
		" przedmioty.nazwa, uzytkownicy.numer_ewidencyjny;";
	}
	else {
		execute = "SELECT przedmioty.nazwa AS _nazwa, SUM(COALESCE((SELECT '1'"
		" FROM obecnosci WHERE obecnosci.data BETWEEN"
		" DATE_SUB(zajecia.data, INTERVAL 10 MINUTE) AND"
		" DATE_ADD(zajecia.data, INTERVAL 20 MINUTE) AND"
		" obecnosci.uzytkownik_id = '" + userID + "'), 0)), (SELECT COUNT(*)"
		" FROM zajecia JOIN przedmioty ON"
		" przedmioty.przedmiot_id = zajecia.przedmiot_id WHERE zajecia.data"
		" BETWEEN '" + dateFrom + "' AND '" + dateInto
		+ "' AND przedmioty.nazwa = _nazwa) FROM zajecia JOIN przedmioty ON"
		" przedmioty.przedmiot_id = zajecia.przedmiot_id WHERE"
		" (przedmioty.nazwa = '" + subjectName + "' OR '" + subjectName
		+ "' = '') AND zajecia.data BETWEEN '" + dateFrom + "' AND '"
		+ dateInto + "' GROUP BY _nazwa;";
	}

	QSqlQuery query;
	query.exec(execute);
	int cols = query.record().count();
	while(query.next()) {

		std::vector<QString> record;
		for(int n = 0; n < cols; n++) {
			record.push_back(query.value(n).toString());
		}

		temp.push_back(record);

	}

	return temp;

}


