
#include <QScrollBar>
#include <QHeaderView>

#include "report.hpp"

Report::Report(
	std::vector <std::vector<QString>> contentList, QStringList listOfLabels,
	QString title) : QWidget(nullptr) {

	this->listOfLabels = listOfLabels;
	this->contentList = contentList;

	reportWidget = new QTableWidget(
		contentList.size(), listOfLabels.size(), this
	);

	setWindowTitle(title);
	reportWidget->setHorizontalHeaderLabels(listOfLabels);

	for(size_t n = 0; n < contentList.size(); n++) {
		for(int m = 0; m < listOfLabels.size(); m++) {
			reportWidget->setItem(
				n, m, new QTableWidgetItem(contentList[n][m])
			);
		}
	}

	reportWidget->resizeColumnsToContents();
	reportWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	reportWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

	int scrollSize = 0;
	if(reportWidget->verticalScrollBar()) {
		scrollSize = reportWidget->verticalScrollBar()->width();
	}

	reportWidget->setFixedSize(
		reportWidget->horizontalHeader()->length()
		+ reportWidget->verticalHeader()->width()+scrollSize,
		std::min(reportWidget->verticalHeader()->length()
		+ reportWidget->horizontalHeader()->height(), 600)
	);

}
