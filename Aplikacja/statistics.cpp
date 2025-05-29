
#include <QFormLayout>
#include <QPushButton>

#include "statistics.hpp"

Statistics:: Statistics(DB *db, QWidget *parent = 0) : QWidget(parent) {

	setObjectName("statistics");

	this->db = db;

	QFormLayout *widgetLayout = new QFormLayout(this);

	subjects = new QComboBox();
	subjects->addItem("Wszystkie przedmioty");
	subjects->addItems(db->getSubjectNames());

	dateFrom = new QDateEdit(QDate::currentDate());
	dateFrom->setDisplayFormat(db->DATE_FORMAT);
	dateInto = new QDateEdit(QDate::currentDate());
	dateInto->setDisplayFormat(db->DATE_FORMAT);

	QPushButton *generateReportBtn = new QPushButton("Wyświetl raport");

	widgetLayout->addRow("Wybierz przedmiot: ", subjects);
	widgetLayout->addRow("Wybierz datę od:", dateFrom);
	widgetLayout->addRow("do:", dateInto);
	widgetLayout->addRow(generateReportBtn);

	connect(
		generateReportBtn, &QPushButton::clicked,
		this, &Statistics::generateReport
	);

}

void Statistics::setUserID(int userID) {
	this->userID = userID;
}

void Statistics::closeReport() {
	if(report) {
		delete report;
		report = nullptr;
	}
}

void Statistics::generateReport() {

	if(report) {
		delete report;
	}

	std::vector <std::vector<QString>> contentList = db->getStatistics(
		QVariant(userID).toString(), subjects->currentText(),
		dateFrom->text(), dateInto->text()
	);

	QStringList listOfLabels;
	if(userID != -1) {
		listOfLabels = QStringList {
			"Nazwa przedmiotu", "Liczba obecności", "Liczba zajęć"
		};
	}
	else {
		listOfLabels = QStringList {
			"Nazwa przedmiotu", "Numer ewidencyjny", "Imię", "Nazwisko",
			"Liczba obecności", "Liczba zajęć"
		};
	}

	report = new Report(contentList, listOfLabels, "RAPORT");
	report->show();

}


