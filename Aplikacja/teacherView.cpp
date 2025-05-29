
#include "teacherView.hpp"

TeacherView::TeacherView(DB *db, QWidget *parent = 0) : User(db, parent) {

	setObjectName("teacher");

	changeTimetableLayout(
		db->getTimetable(getDate().toString(db->DATE_FORMAT))
	);
}

void TeacherView::changeTimetableLayout(std::vector <TimetableText> timetable) {

	clearLayout();

	for(size_t i = 0; i < timetable.size(); i++) {
		QPushButton *btn = new QPushButton(
			timetable[i].itemName + "   "+ timetable[i].time
		);

		btn->setObjectName("btn");
		addWidget(btn);
		connect(
			btn, &QPushButton::clicked, this, &TeacherView::drawAttendanceList
		);
	}

	addStretch(0);
}

void TeacherView::drawAttendanceList() {
	QPushButton *btn = (QPushButton*)sender();
	QString classDateTime = getDate().toString(db->DATE_FORMAT)
		+ " " + btn->text().right(8);

	if(report) {
		delete report;
	}

	std::vector <std::vector<QString>> contentList =
		db->getAttendanceList(classDateTime);

	QStringList listOfLabels = QStringList{
		"Numer ewidencyjny", "Imię", "Nazwisko"
	};

	report = new Report(
		contentList, listOfLabels, "LISTA OBECNOŚCI " + classDateTime
	);

	report->show();

}

void TeacherView::closeReport() {
	if(report) {
		delete report;
		report = nullptr;
	}
}
