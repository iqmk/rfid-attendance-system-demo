#include <QFile>
#include <QLabel>
#include <QApplication>

#include "sql.hpp"
#include "login.hpp"
#include "student.hpp"
#include "statistics.hpp"
#include "teacherView.hpp"

class MainWindow : public QWidget {

	DB db;
	Login *login;
	Student *student;
	TeacherView *teacher;
	Statistics *statistics;

	int userID;

	QWidget *menu;
	QHBoxLayout* layout;

public:

	MainWindow(QWidget *parent = 0) :QWidget(parent) {

		setObjectName("mainWindow");
		setWindowState(Qt::WindowMaximized);

		layout = new QHBoxLayout(this);

		menu = new QWidget(this);
		menu->setObjectName("menu");
		menu->hide();

		QVBoxLayout *btnLayout = new QVBoxLayout(menu);

		QLabel *label = new QLabel("MENU");

		QPushButton *btnLogOut = new QPushButton("Wyloguj się");
		QPushButton *btnStatistics = new QPushButton("Statystyki");
		QPushButton *btnAttendances = new QPushButton("Obecności");

		btnLayout->insertWidget(0, label);
		btnLayout->insertWidget(1, btnLogOut);
		btnLayout->insertWidget(2, btnStatistics);
		btnLayout->insertWidget(3, btnAttendances);
		btnLayout->addStretch(0);

		db.connectDB();
		login = new Login(&db, this);

		connect(login, &Login::loginCallback, this, &MainWindow::loginCallback);
		connect(btnLogOut, &QPushButton::clicked, this, &MainWindow::logOut);
		connect(
			btnStatistics, &QPushButton::clicked,
			this, &MainWindow::setStatisticsVisible
		);

		connect(
			btnAttendances, &QPushButton::clicked,
			this, &MainWindow::setTimetableVisible
		);

		student = new Student(&db, this);
		student->hide();

		teacher = new TeacherView(&db, this);
		teacher->hide();

		statistics = new Statistics(&db, this);
		statistics->hide();

		layout->addWidget(menu);
		layout->addWidget(student, 0, Qt::AlignCenter);
		layout->addWidget(login, 0, Qt::AlignCenter);
		layout->addWidget(teacher, 0, Qt::AlignCenter);
		layout->addWidget(statistics, 0, Qt::AlignCenter);
	}

	~MainWindow() {
		db.closeDB();
	}

protected:
	void closeEvent(QCloseEvent*) {
		statistics->closeReport();
		teacher->closeReport();
	}

private:
    void loginCallback(UserData ud) {

		if(ud.userID > 0) {
			if(ud.status == 1) {
				this->userID = ud.userID;
				login->hide();
				menu->show();
				student->setUserID(this->userID);
				statistics->setUserID(this->userID);
				student->show();
			}
			else if(ud.status == 0) {
				this->userID = -1;
				login->hide();
				menu->show();
				layout->addWidget(teacher, 0, Qt::AlignCenter);
				statistics->setUserID(this->userID);
				teacher->show();
			}
		}
	}

	void logOut(){
		if(!student->isHidden()) {
			student->hide();
		}
		else if(!teacher->isHidden()) {
			teacher->hide();
		}

		if(!statistics->isHidden()) {
			statistics->hide();
		}

		if(!menu->isHidden()) {
			menu->hide();
		}
		statistics->closeReport();
		teacher->closeReport();
		login->show();

	}

	void setStatisticsVisible() {
		if(!student->isHidden()) {
			student->hide();
		}
		else if(!teacher->isHidden()) {
			teacher->hide();
		}

		if(statistics->isHidden()) {
			statistics->show();
		}
	}

	void setTimetableVisible() {
		if(!statistics->isHidden()) {
			statistics->hide();
		}

		if(this->userID == -1) {
			if(teacher->isHidden()) {
				teacher->show();
			}
		}
		else {
			if(student->isHidden()) {
				student->show();
			}
		}
	}
};

int main(int argc, char **argv) {
	QApplication app (argc, argv);
	QFile file("stylesheet.qss");
	file.open(QFile::ReadOnly);
	QString styleSheet = QLatin1String(file.readAll());
	app.setStyleSheet(styleSheet);

	MainWindow mainWindow;
	mainWindow.show();

	return app.exec();
}
