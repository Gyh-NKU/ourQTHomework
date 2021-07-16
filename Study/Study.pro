QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    SudokuForm.cpp \
    SudokuWidget.cpp \
    add_plan.cpp \
    cal_widget.cpp \
    dialog.cpp \
    gamecenter.cpp \
    main.cpp \
    mainwindow.cpp \
    usefultools.cpp \
    widget.cpp

HEADERS += \
    SudokuForm.h \
    SudokuWidget.h \
    add_plan.h \
    cal_widget.h \
    dialog.h \
    gamecenter.h \
    mainwindow.h \
    usefultools.h \
    widget.h

FORMS += \
    SudokuForm.ui \
    SudokuWidget.ui \
    add_plan.ui \
    cal_widget.ui \
    dialog.ui \
    gamecenter.ui \
    mainwindow.ui \
    usefultools.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    res.qrc
