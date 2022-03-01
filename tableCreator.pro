QT       += core gui sql widgets

VERSION = 0.0.1
DEFINES += APP_VERSION=\\\"$$VERSION\\\"

CONFIG += c++11

 include(myLib/xlsx/qtxlsx.pri)
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dialogs/connection/connectiondialogsecond.cpp \
    dialogs/createTable/firststepwidget.cpp \
    dialogs/createTable/secondstepwidget.cpp \
    dialogs/createTable/thirdstepview/addrelationtablewidget.cpp \
    dialogs/createTable/thirdstepview/createanemptytablewidget.cpp \
    dialogs/createTable/thirdstepview/importtablefromxslwidget.cpp \
    dialogs/createTable/presenter/createtablepresenter.cpp \
    dialogs/createTable/thirdstepview/thirdstepwidget.cpp \
    oneTable/delegate/crosswidget.cpp \
    oneTable/delegate/tabledelegate.cpp \
    main.cpp \
    model-interface/itablemediator.cpp \
    model/mediatorrepository.cpp \
    oneTable/model/mytablemodel.cpp \
    model/postgrerequestmaker.cpp \
    oneTable/myheaderview.cpp \
    presenter/toolbarpresenter.cpp \
    validators/tablenamevalidator.cpp \
    dialogs/connection/connectiondialog.cpp \
    oneTable/dialogs/createnewcolumndialog.cpp \
    dialogs/createTable/createtabledialog.cpp \
    view/mainwindow.cpp \
    oneTable/view/mytableview.cpp \
    oneTable/view/tablewidget.cpp \
    view/toolbar.cpp

HEADERS += \
    dialogs/connection/connectiondialogsecond.h \
    dialogs/createTable/firststepwidget.h \
    dialogs/createTable/secondstepwidget.h \
    dialogs/createTable/thirdstepview/addrelationtablewidget.h \
    dialogs/createTable/thirdstepview/createanemptytablewidget.h \
    dialogs/createTable/thirdstepview/importtablefromxslwidget.h \
    dialogs/createTable/presenter/createtablepresenter.h \
    dialogs/createTable/thirdstepview/thirdstepwidget.h \
    oneTable/delegate/crosswidget.h \
    oneTable/delegate/tabledelegate.h \
    oneTable/model-interface/imytablemodel.h \
    model-interface/itablemediator.h \
    model-interface/itoolbarrequestmaker.h \
    model/databasedrivers.h \
    model/mediatorrepository.h \
    oneTable/model/mytablemodel.h \
    model/postgrerequestmaker.h \
    oneTable/myheaderview.h \
    presenter/toolbarpresenter.h \
    validators/tablenamevalidator.h \
    dialogs/connection/connectiondialog.h \
    oneTable/dialogs/createnewcolumndialog.h \
    dialogs/createTable/createtabledialog.h \
    view/mainwindow.h \
    oneTable/view/mytableview.h \
    oneTable/view/tablewidget.h \
    view/toolbar.h

# Default rules for deployment.
INSTALLS += target

RESOURCES += \
    res.qrc
