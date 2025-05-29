#ifndef USER_HPP
#define USER_HPP

#include "sql.hpp"
#include "calendar.hpp"

class User : public QWidget {

	Calendar *calendar;

	QWidget *timetableWidget;
	QVBoxLayout *timetableLayout;

protected:
	DB *db;

	User(DB *db, QWidget *parent);
	void resizeEvent(QResizeEvent* e);
	void clearLayout();
	void addStretch(int size);
	virtual void changeTimetableLayout(std::vector <TimetableText>){};
	void addWidget(QWidget* widget);
	QDate getDate();

protected slots:
	void onDateChange();

};


#endif
