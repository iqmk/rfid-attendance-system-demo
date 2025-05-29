#ifndef STUDENT_HPP
#define STUDENT_HPP

#include "user.hpp"

class Student : public User {

	int userID;

	QPalette *color;

	QString getLabelColor(QString classStartTime);
	void changeTimetableLayout(std::vector <TimetableText> timetable) override;

public:

	Student(DB *db, QWidget *parent);
	void setUserID(int id);

};

#endif
