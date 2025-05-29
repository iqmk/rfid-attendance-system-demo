#ifndef SQL_HPP
#define SQL_HPP

#include <QSqlDatabase>

#include <vector>

struct UserData {
	int userID = 0;
	bool status = 0;
};

struct TimetableText {
	QString itemName = "";
	QString time = "";
};

class DB : private QSqlDatabase {

public:
	const QString DATE_FORMAT = "yyyy-MM-dd";

	bool connectDB();
	void closeDB();
	bool getAttendanceStatus(int userID, QString dateTime);
	std::vector <TimetableText> getTimetable(QString date);
	UserData logInSQL(QString login, QString haslo);
	std::vector <std::vector<QString>> getAttendanceList(QString classDateTime);
	QStringList getSubjectNames();
	std::vector <std::vector<QString>> getStatistics(
		QString userID, QString subjectName, QString dateFrom, QString dateInto
	);
};

#endif
