#ifndef REPORT_HPP
#define REPORT_HPP

#include <QTableWidget>

class Report : public QWidget {

	QStringList listOfLabels;
	QTableWidget *reportWidget;

	std::vector <std::vector<QString>> contentList;

public:
	Report(
		std::vector <std::vector<QString>> contentList,
		QStringList listOfLabels, QString title
	);

};

#endif
