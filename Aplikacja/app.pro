
TEMPLATE = app
TARGET = name_of_the_app

QT = core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += qt debug

SOURCES += main.cpp sql.cpp login.cpp student.cpp teacherView.cpp calendar.cpp statistics.cpp report.cpp user.cpp
HEADERS += login.hpp student.hpp sql.hpp teacherView.hpp calendar.hpp statistics.hpp report.hpp user.hpp
