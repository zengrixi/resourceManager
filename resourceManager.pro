QT       += core gui network xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = resourceManager

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

SOURCES +=  \
    src/gui/filebrowse.cpp \
    src/gui/lanjieview.cpp \
    src/gui/topwindow.cpp \
    src/gui/messagebox.cpp \
    src/gui/mainwindow.cpp \
    src/gui/yujinview.cpp \
    src/gui/zhikongview.cpp \
    src/main.cpp \
    src/util/ninepatchpainter.cpp \
    src/util/xmlmap.cpp

HEADERS +=  \

# 项目头文件路径
include($$PWD/include/headers.pri)

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES +=  \
    qdarkstyle/style.qrc \
    top-window-resources.qrc

FORMS +=  \
    src/gui/filebrowse.ui \
    src/gui/lanjieview.ui \
    src/gui/mainwindow.ui \
    src/gui/messagebox.ui \
    src/gui/topwindow.ui \
    src/gui/yujinview.ui \
    src/gui/zhikongview.ui

# 配置执行文件所在目录
CONFIG(debug, release|debug) {
    DESTDIR = $$PWD/../bin/debug
} else {
    DESTDIR = $$PWD/../bin/release
}
