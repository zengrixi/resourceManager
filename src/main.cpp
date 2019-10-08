#include <QApplication>

#include "src/utils/xmlsetting.h"
#include "src/views/mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    XmlSetting xml;
    xml.write_xml("./xml1.xml");
    xml.read_xml("./xml1.xml");
    return a.exec();
}
