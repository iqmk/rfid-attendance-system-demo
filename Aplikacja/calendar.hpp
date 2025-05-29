#ifndef CALENDAR_HPP
#define CALENDAR_HPP

#include <QGridLayout>
#include <QPushButton>
#include <QCalendarWidget>

class Calendar : public QWidget {
	Q_OBJECT

	QDate *date;
	QPushButton *dateBtn;
	QGridLayout *layout;
	QCalendarWidget *calendar;

	int totalHeight;

public:

	Calendar(QWidget *parent);

	int getMinHeight();
	void resize(int w, int h);

	QDate getDate();

signals:
	void onDateChange();

private slots:
	void setCalendarVisible();
	void changeDate(int a);

};


#endif
