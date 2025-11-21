QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

TARGET          = CommunConfigPc
TEMPLATE        = app
MOC_DIR         = temp/moc
RCC_DIR         = temp/rcc
UI_DIR          = temp/ui
OBJECTS_DIR     = temp/obj
DESTDIR         = $$PWD/bin

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    app.cpp \
    main.cpp \
    mainwindow.cpp \
    projectsection.cpp

HEADERS += \
    app.h \
    mainwindow.h \
    projectsection.h

FORMS += \
    mainwindow.ui \
    projectsection.ui

RESOURCES += \
    res/res.qrc

include(./custom_table_widget/customtablewidget.pri)
include(./commun_ch/communch.pri)
include(./commun_dev/commundev.pri)
include(./point_table/pointtable.pri)

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
