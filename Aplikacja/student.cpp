#include <QLabel>

#include "student.hpp"

Student::Student(DB *db, QWidget *parent = 0) : User(db, parent) {

	setObjectName("student");

	color = new QPalette();
}

void Student::changeTimetableLayout(std::vector <TimetableText> timetable) {
	clearLayout();

	for(size_t i = 0; i < timetable.size(); i++) {
		color->setColor(
			QPalette::Window,
			getLabelColor(timetable[i].time)
		);

		QLabel *label = new QLabel(
			timetable[i].itemName
			+ "   " + timetable[i].time
		);

		label->setAutoFillBackground(true);
		label->setPalette(*color);
		addWidget(label);
	}

	addStretch(0);
}

QString Student::getLabelColor(QString classStartTime) {

	QString classStartDateTime = getDate().toString(db->DATE_FORMAT) +
		" " + classStartTime;

	QString labelColor = "gray";

	if(db->getAttendanceStatus(userID, classStartDateTime)) {
		labelColor = "green";
	}
	else if(getDate() < QDate::currentDate()) {
		labelColor =  "darkRed";
	}

	return labelColor;
}

void Student::setUserID(int id) {
	userID = id;
}








