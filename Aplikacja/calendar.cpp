
#include "calendar.hpp"

Calendar::Calendar(QWidget *parent = 0) : QWidget(parent) {

	calendar = new QCalendarWidget();
	date = new QDate(QDate::currentDate());
	dateBtn = new QPushButton(date->toString());

	QPushButton *left = new QPushButton("<");
	QPushButton *right = new QPushButton(">");
	layout = new QGridLayout(this);

	layout->addWidget(left, 0 , 0, Qt::AlignTop);
	layout->addWidget(dateBtn, 0 , 1, Qt::AlignTop);
	layout->addWidget(right, 0 , 2, Qt::AlignTop);
	layout->addWidget(calendar, 1, 0, -1, -1);

	connect(dateBtn, &QPushButton::clicked, this, &Calendar::setCalendarVisible);
	connect(left, &QPushButton::clicked, this, [this] {changeDate(-1);});
	connect(right, &QPushButton::clicked, this, [this] {changeDate(1);});
	connect(
		calendar, &QCalendarWidget::selectionChanged,
		this, [this] {changeDate(0);}
	);

}

void Calendar::resize(int w, int h) {
	QWidget::resize(w, h);
	totalHeight = h;
}

int Calendar::getMinHeight() {
	return dateBtn->height()+layout->verticalSpacing()*2;
}

QDate Calendar::getDate() {
	return *date;
}

void Calendar::setCalendarVisible() {
	calendar->setVisible(calendar->isHidden());
	if(calendar->isHidden()) {
		QWidget::resize(width(), getMinHeight());
	}
	else {
		QWidget::resize(width(), totalHeight);
	}
}

void Calendar::changeDate(int a) {
	if(a == 0){
		*date = calendar->selectedDate();
		dateBtn->setText(calendar->selectedDate().toString());
		emit onDateChange();
	} else {
		*date = date->addDays(a);
		dateBtn->setText(date->toString());
		calendar->setSelectedDate(*date);
	}
}

