#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize(390, 115);
    w.setWindowTitle("PIZDEC");
    w.show();

    return a.exec();
}
