QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../src/SmartCalc/Qcustomplot/qcustomplot.cpp \
    ../src/SmartCalc/main.cpp \
    ../src/SmartCalc/mainwindow.cpp \
    ../src/SmartCalc/s21_calculations/s21_calculate.c \
    ../src/SmartCalc/s21_collection/s21_linked_list.c \
    ../src/SmartCalc/s21_polish_notation/polish_notation.c \
    ../src/SmartCalc/s21_smart_calc.c


HEADERS += \
    ../src/SmartCalc/Qcustomplot/qcustomplot.h \
    ../src/SmartCalc/mainwindow.h \
    ../src/SmartCalc/s21_calculations/s21_calculate.h \
    ../src/SmartCalc/s21_collection/s21_linked_list.h \
    ../src/SmartCalc/s21_collection/struct.h \
    ../src/SmartCalc/s21_polish_notation/polish_notation.h \
    ../src/SmartCalc/s21_smart_calc.h \


FORMS += \
    ../src/SmartCalc/mainwindow.ui

TRANSLATIONS += \
    ../src/SmartCalc/SmartCalc_en_US.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Makefile \
    SmartCalc.pro.user
