#include <QApplication>

#include "src/net/udpsocket.h"
#include "src/views/mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    XmlSetting xml;
    xml.write_xml("./xxx.xml");
    xml.read_xml("./xxx.xml");
    return a.exec();
}
