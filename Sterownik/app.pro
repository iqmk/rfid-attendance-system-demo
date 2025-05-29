
TEMPLATE = app
TARGET = sterownik

QT = sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += sterownik.cpp sql.cpp
