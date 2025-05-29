#ifndef TEACHER_VIEW_HPP
#define TEACHER_VIEW_HPP

#include "report.hpp"
#include "user.hpp"

class TeacherView : public User {

	Report *report = nullptr;

	void changeTimetableLayout(std::vector <TimetableText> timetable) override;
	void drawAttendanceList();

public:
	TeacherView(DB *db, QWidget *parent);
	void closeReport();

};

#endif
