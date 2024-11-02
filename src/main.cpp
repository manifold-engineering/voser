#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/resources/icons/icon_32.png"));
    MainWindow w;
    w.show();
    return a.exec();
}
