QT       += core gui network xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

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
    src/controllers/textdelegate.cpp \
    src/main.cpp \
    src/models/tablemodel.cpp \
    src/net/udpsocket.cpp \
    src/utils/3rdParty/NXDockWidget.cpp \
    src/utils/3rdParty/NXDockWidgetTabBar.cpp \
    src/utils/3rdParty/NXDockWidgetTabButton.cpp \
    src/utils/3rdParty/NXDockWidgetTitle.cpp \
    src/utils/3rdParty/NXMainWindow.cpp \
    src/utils/frameless_helper.cpp \
    src/utils/ninepatchpainter.cpp \
    src/utils/xmlsetting.cpp \
    src/views/loadsrcdialog.cpp \
    src/views/mainwindow.cpp \
    src/views/resourcesetting.cpp \
    src/views/tableview.cpp \
    src/views/titlebar.cpp \
    src/views/treewidget.cpp

HEADERS += \
    src/controllers/textdelegate.h \
    src/models/datamodel.h \
    src/models/tablemodel.h \
    src/net/udpsocket.h \
    src/utils/3rdParty/NXDockWidget.h \
    src/utils/3rdParty/NXDockWidgetTabBar.h \
    src/utils/3rdParty/NXDockWidgetTabButton.h \
    src/utils/3rdParty/NXDockWidgetTitle.h \
    src/utils/3rdParty/NXMainWindow.h \
    src/utils/frameless_helper.h \
    src/utils/ninepatchpainter.h \
    src/utils/xmlsetting.h \
    src/views/loadsrcdialog.h \
    src/views/mainwindow.h \
    src/views/resourcesetting.h \
    src/views/tableview.h \
    src/views/titlebar.h \
    src/views/treewidget.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/nxmainwindow.qrc

FORMS += \
    src/utils/3rdParty/NXMainWindow.ui
