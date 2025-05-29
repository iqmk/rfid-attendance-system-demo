#ifndef STATISTICS_HPP
#define STATISTICS_HPP

#include <QDateEdit>
#include <QComboBox>

#include "sql.hpp"
#include "report.hpp"

class Statistics : public QWidget {

	DB *db;
	Report *report = nullptr;

	int userID;

	QDateEdit *dateFrom;
	QDateEdit *dateInto;
	QComboBox *subjects;

public:
	Statistics(DB *db, QWidget *parent);
	void setUserID(int userID);
	void closeReport();

private slots:
	void generateReport();
};

#endif
