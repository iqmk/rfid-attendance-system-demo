
#include "user.hpp"

User::User(DB *db, QWidget *parent = 0) : QWidget(parent) {
	this->db = db;

	timetableWidget = new QWidget(this);
	timetableLayout = new QVBoxLayout(timetableWidget);

	calendar = new Calendar(this);

	connect(calendar, &Calendar::onDateChange, this, &User::onDateChange);

}

void User::resizeEvent(QResizeEvent* e) {
	calendar->resize(width(), height());
	timetableWidget->resize(width(), height());
	QWidget::resizeEvent(e);
}

void User::clearLayout() {

	while(QLayoutItem* item = timetableLayout->takeAt(0)) {
		if(item->widget())
			delete item->widget();
		else if(item->spacerItem())
			delete item->spacerItem();
	}

	timetableLayout->addSpacing(calendar->getMinHeight());
}

void User::addStretch(int size) {
	timetableLayout->addStretch(size);
}

void User::addWidget(QWidget* widget) {
	timetableLayout->addWidget(widget);
	widget->stackUnder(calendar);
}

void User::onDateChange() {
	changeTimetableLayout(
		db->getTimetable(calendar->getDate().toString(db->DATE_FORMAT))
	);
}

QDate User::getDate() {
	return calendar->getDate();
}
